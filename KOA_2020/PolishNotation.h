#pragma once
#include "LT.h"
#include "IT.h"
#include "Error.h"
// | Priority	| Operation |
// | 0			| {			|
// | 0			| }			|
// | 1			| , 		|
// | 2			| |			|
// | 3			| &			|
// | 4			| != == 	|
// | 5			| > < 		|
// | 5			| >= <= 	|
// | 6			| +			|
// | 6			| -			|
// | 7			| *			|
// | 7			| /			|
// | 8			| ~			|
// | 9			| [ 		|
// | 9			| ]			|
#define PARETHESIS_PRIORITY 0
#define COMMA_PRIORITY		1
#define OR_PRIORITY			2
#define AND_PRIORITY		3
#define COMPARE_EQ_PRIORITY	4
#define COMPARE_ML_PRIORITY	5
#define PM_PRIORITY			6
#define MD_PRIORITY			7
#define UNARY_PRIORITY		8
#define BRACKETS_PRIORITY	0

#define LEX_CALL_FUNCTION '@'
#define LEX_ARRAY_ADDRES  '$'

namespace PolishNotation 
{
	struct Operator
	{
		LT::Entry savedEntryOperation;
		int priority;
	};
	struct StackCalledFunction
	{
		vector<LT::Entry> calledFunction;
		vector<int> stackParams;
		int countFunction = -1;
		bool isParams = false;
	};
	struct PolishNotationData
	{
		stack<Operator> operationStack;
		Operator tempOperationEntry;

		vector<LT::Entry> resultChain;
		LT::Entry tempLexEntry;

		StackCalledFunction stackCFunc;

		bool transformDone = false;

		void SetOperationPriority()
		{
			tempOperationEntry.savedEntryOperation = tempLexEntry;
			switch (tempLexEntry.operationType)
			{
			case LT::OR:
				tempOperationEntry.priority = OR_PRIORITY;
				break;
			case LT::AND:
				tempOperationEntry.priority = AND_PRIORITY;
				break;
			case LT::EQUALLY:
			case LT::NON_EQUALLY:
				tempOperationEntry.priority = COMPARE_EQ_PRIORITY;
			case LT::MORE:
			case LT::LESS:
			case LT::MORE_OR_EQUAL:
			case LT::LESS_OR_EQUAL:
				tempOperationEntry.priority = COMPARE_ML_PRIORITY;
				break;
			case LT::PLUS:
			case LT::MINUS:
				tempOperationEntry.priority = PM_PRIORITY;
				break;
			case LT::MULTIPLY:
			case LT::DIVISION:
				tempOperationEntry.priority = MD_PRIORITY;
				break;
			case LT::INVERSION:
				tempOperationEntry.priority = UNARY_PRIORITY;
				break;
			}
		}

		void AnalyzePriority()
		{
			// Если стек операций пустой или на его дне открывающая скобка -> заносим текущую Entry.
			if (operationStack.empty() ||
				operationStack.top().savedEntryOperation.lexema == LEX_PARENTHESES_LEFT ||
				operationStack.top().savedEntryOperation.lexema == LEX_BRACES_LEFT)
			{
				operationStack.push(tempOperationEntry);
			}
			else
			{
				// Выталкиваем все операции с большим, либо равным приоритетом. После помещаем текущую операцию.
				while (!operationStack.empty() && operationStack.top().priority >= tempOperationEntry.priority)
				{
					resultChain.push_back(operationStack.top().savedEntryOperation);
					operationStack.pop();
				}
				operationStack.push(tempOperationEntry);
			}
		}

		void MetParethesisLeft()
		{
			tempOperationEntry.priority = PARETHESIS_PRIORITY;
			tempOperationEntry.savedEntryOperation = tempLexEntry;
			operationStack.push(tempOperationEntry);
		}

		void MetParethesisRight()
		{
			// Выносим из стека все операции до скобки.
			while (operationStack.top().savedEntryOperation.lexema != LEX_PARENTHESES_LEFT)
			{
				resultChain.push_back(operationStack.top().savedEntryOperation);
				operationStack.pop();
			}
			// И уничтожаем скобку.
			operationStack.pop();
		}

		void MetBracketsLeft()
		{
			tempOperationEntry.priority = BRACKETS_PRIORITY;
			tempOperationEntry.savedEntryOperation = tempLexEntry;
			tempOperationEntry.savedEntryOperation.lexema = LEX_BRACKETS_LEFT;
			operationStack.push(tempOperationEntry);
		}

		void MetBracketsRight()
		{
			// Выносим из стека все операции до скобки.
			while (operationStack.top().savedEntryOperation.lexema != LEX_BRACKETS_LEFT)
			{
				resultChain.push_back(operationStack.top().savedEntryOperation);
				operationStack.pop();
			}
			// И уничтожаем скобку.
			operationStack.pop();
		}
		
		void PushFunctionInfo(const IT::IdTable& idTable)
		{
			// Проверяем чтобы количество фактических и ожидаемых параметров было одинаково.
			if (!Semantic::CheckFunctionCountParams(stackCFunc.stackParams[stackCFunc.countFunction], stackCFunc.calledFunction[stackCFunc.countFunction], idTable))
				throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 1, tempLexEntry.line, tempLexEntry.position);
			// Заносим вызов функции в результирующую цепочку, предварительно поменяв её лексему.
			stackCFunc.calledFunction[stackCFunc.countFunction].lexema = LEX_CALL_FUNCTION;
			resultChain.push_back(stackCFunc.calledFunction[stackCFunc.countFunction]);
			stackCFunc.countFunction--;
			// Смотрим пуст ли стек с количеством параметров. Если да -> функции закончились. Если нет -> убираем последнюю функцию из вектора.
			if (stackCFunc.stackParams.empty())
				stackCFunc.isParams = false;
			if (stackCFunc.isParams)
			{
				stackCFunc.calledFunction.pop_back();
				stackCFunc.calledFunction.shrink_to_fit();
				stackCFunc.stackParams.pop_back();
				stackCFunc.stackParams.shrink_to_fit();
			}
		}

		void MetComma()
		{
			// Увеличиваем количество передаваемых параметров.
			stackCFunc.stackParams[stackCFunc.countFunction]++;
			// Выталкиваем все операции до скобки.
			bool check = true;
			while (check)
			{
				if (operationStack.top().savedEntryOperation.lexema == LEX_PARENTHESES_LEFT || operationStack.top().savedEntryOperation.lexema == LEX_BRACKETS_LEFT)
					check = false;
				else
				{
					resultChain.push_back(operationStack.top().savedEntryOperation);
					operationStack.pop();
				}
			}
		}

		void PopLastOperations()
		{
			while (!operationStack.empty())
			{
				resultChain.push_back(operationStack.top().savedEntryOperation);
				operationStack.pop();
			}
		}

		void UpdateTables(int positionAfterAssignment, int endPosition, LT::LexTable& lexTable, IT::IdTable& idtable)
		{
			LT::Entry entry; entry.lexema = -6; entry.line = resultChain[resultChain.size()-1].line;
			for (int i = positionAfterAssignment + resultChain.size(); i < endPosition; i++)
				resultChain.push_back(entry);
			lexTable.table.erase(lexTable.table.begin() + positionAfterAssignment, lexTable.table.begin() + endPosition);
			lexTable.table.insert(lexTable.table.begin() + positionAfterAssignment, resultChain.begin(), resultChain.end());
			lexTable.table.shrink_to_fit();
			lexTable.current_size = lexTable.table.size();
		}
	};
	void TransformToPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable);
	void PolishNotationExpression(int positionAfterAssignment, LT::LexTable& lextable, IT::IdTable& idtable);
	void PolishNotationCondition(int positionAfterParenthesis, LT::LexTable& lextable, IT::IdTable& idtable);
};