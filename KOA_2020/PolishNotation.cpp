#include "stdafx.h"
#define DEBUG_PN

namespace PolishNotation
{
	void TransformToPolishNotation(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		// Если в параметрах поставить просто арифмитическое действие, то сломается

		for (int i = 0; i < lexTable.current_size; i++)
		{
			if (lexTable.table[i].lexema == LEX_ASSIGNMENT)
				PolishNotationExpression(i + 1, lexTable, idTable);
			if (lexTable.table[i].lexema == LEX_WHILE || lexTable.table[i].lexema == LEX_IF)
				PolishNotationCondition(i + 1, lexTable, idTable);
		}
	}

	void PolishNotationExpression(int positionAfterAssignment, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		int lexTablePosition = positionAfterAssignment;
		PolishNotationData data;

		while (lexTable.table[lexTablePosition].lexema != LEX_SEMICOLON)
		{
			data.tempLexEntry = lexTable.table[lexTablePosition];
			switch (data.tempLexEntry.lexema)
			{
				case LEX_LITERAL:
				case LEX_IDENTIFICATOR:
				{
					// Если в параметрах + стек Параметров не пустой -> увеличиваем количество фактических параметров.
					if (data.stackCFunc.isParams && data.stackCFunc.stackParams[data.stackCFunc.countFunction] == 0)
						data.stackCFunc.stackParams[data.stackCFunc.countFunction]++;

					// Смотрим -> фунция или переменная.
					IT::Entry tempIdEntry = IT::GetEntry(idTable, data.tempLexEntry.idxTI);
					if (tempIdEntry.idType == IT::FUNCTION || tempIdEntry.idType == IT::PROTOTYPE)
					{
						// Мы в параметрах.
						data.stackCFunc.isParams = true;
						// Сохраняем лексему вызванной функции.
						data.stackCFunc.calledFunction.push_back(data.tempLexEntry);
						// Заносим счётчик новой функции.
						data.stackCFunc.stackParams.push_back(0);
						data.stackCFunc.countFunction++;
					}
					else
						data.resultChain.push_back(data.tempLexEntry);

					break;
				}
				case LEX_COMPARISONS:
				case LEX_UNARY:
				case LEX_BINARIES:
				{
					data.transformDone = true;
					data.SetOperationPriority();
					data.AnalyzePriority();
					break;
				}
				case LEX_PARENTHESES_LEFT:
				{
					if (data.stackCFunc.isParams)
						goto LeftBrackets;
					data.MetParethesisLeft();
					break;
				}
				case LEX_PARENTHESES_RIGHT:
				{
					if (data.stackCFunc.isParams)
						goto RightBrackets;
					data.MetParethesisRight();
					break;
				}
				case LEX_BRACKETS_LEFT:
				{
				LeftBrackets:
					data.MetBracketsLeft();
					break;
				}
				case LEX_BRACKETS_RIGHT:
				{
				RightBrackets:
					data.MetBracketsRight();
					if (data.stackCFunc.isParams)
						data.PushFunctionInfo(idTable);
					break;
				}
				case LEX_COMMA:
				{
					data.MetComma();
					break;
				}
			}
			lexTablePosition++;
		}
		data.PopLastOperations();
		data.UpdateTables(positionAfterAssignment, lexTablePosition, lexTable, idTable);

#ifdef DEBUG_PN
		cout << endl;
		for (int i = 0; i < data.resultChain.size(); i++)
		{
			if (data.resultChain[i].operationType == LT::NONE)
			{
				if (data.resultChain[i].lexema == LEX_FILLER)
					continue;
				cout << data.resultChain[i].lexema;
			}
			else
				cout << LT::GetOperationSymbol(data.resultChain[i]);
		}
		cout << endl;
#endif // DEBUG
	}

	void PolishNotationCondition(int positionAfterParenthesis, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		int lexTablePosition = positionAfterParenthesis;
		PolishNotationData data;

		while (lexTable.table[lexTablePosition].lexema != LEX_BRACES_LEFT)
		{
			data.tempLexEntry = lexTable.table[lexTablePosition];
			switch (data.tempLexEntry.lexema)
			{
			case LEX_LITERAL:
			case LEX_IDENTIFICATOR:
			{
				// Если в параметрах + стек Параметров не пустой -> увеличиваем количество фактических параметров.
				if (data.stackCFunc.isParams && data.stackCFunc.stackParams[data.stackCFunc.countFunction] == 0)
					data.stackCFunc.stackParams[data.stackCFunc.countFunction]++;

				// Смотрим -> фунция или переменная.
				IT::Entry tempIdEntry = IT::GetEntry(idTable, data.tempLexEntry.idxTI);
				if (tempIdEntry.idType == IT::FUNCTION)
				{
					// Мы в параметрах.
					data.stackCFunc.isParams = true;
					// Сохраняем лексему вызванной функции.
					data.stackCFunc.calledFunction.push_back(data.tempLexEntry);
					// Заносим счётчик новой функции.
					data.stackCFunc.stackParams.push_back(0);
					data.stackCFunc.countFunction++;
				}
				else
					data.resultChain.push_back(data.tempLexEntry);

				break;
			}
			case LEX_COMPARISONS:
			case LEX_UNARY:
			case LEX_BINARIES:
			{
				data.transformDone = true;
				data.SetOperationPriority();
				data.AnalyzePriority();
				break;
			}
			case LEX_PARENTHESES_LEFT:
			{
				if (data.stackCFunc.isParams)
					goto LeftBrackets;
				data.MetParethesisLeft();
				break;
			}
			case LEX_PARENTHESES_RIGHT:
			{
				if (data.stackCFunc.isParams)
					goto RightBrackets;
				data.MetParethesisRight();
				break;
			}
			case LEX_BRACKETS_LEFT:
			{
			LeftBrackets:
				data.MetBracketsLeft();
				break;
			}
			case LEX_BRACKETS_RIGHT:
			{
			RightBrackets:
				data.MetBracketsRight();
				if (data.stackCFunc.isParams)
					data.PushFunctionInfo(idTable);
				break;
			}
			case LEX_COMMA:
			{
				data.MetComma();
				break;
			}
			}
			lexTablePosition++;
		}
		data.PopLastOperations();
		data.UpdateTables(positionAfterParenthesis, lexTablePosition, lexTable, idTable);

#ifdef DEBUG_PN
		cout << endl;
		for (int i = 0; i < data.resultChain.size(); i++)
		{
			if (data.resultChain[i].operationType == LT::NONE)
			{
				if (data.resultChain[i].lexema == LEX_FILLER)
					continue;
				cout << data.resultChain[i].lexema;
			}
			else
				cout << LT::GetOperationSymbol(data.resultChain[i]);
		}
		cout << endl;
#endif // DEBUG
	}
}