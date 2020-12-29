#include "stdafx.h"
#define DEBUG_SEMANTIC

namespace Semantic
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		SemanticData semanticData;
		for (auto i = mfst.storestate.begin(); i != mfst.storestate.end(); i++)
		{
			if (i->nrule == S_RULE)
				semanticData.SetFunctionIdDataType(lexTable, idTable, i->lenta_position, i->nrulechain);
			if (i->nrule == R_RULE && idTable.table[lexTable.table[i->lenta_position + 1].idxTI].idDataType != semanticData.idDataTypeFunction)
				throw ERROR_THROW_IN(408, lexTable.table[i->lenta_position + 1].line, lexTable.table[i->lenta_position + 1].position);
			if (i->nrule == I_RULE)
			{
				semanticData.SetGeneralIdDataType(lexTable, idTable, i->lenta_position, i->nrulechain);
				if (!semanticData.isVoidRule)
					semanticData.AnalyzeExpression(lexTable, idTable);
				semanticData.isVoidRule = false;
			}
		}
	}

	void SemanticData::SetGeneralIdDataType(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition, int nrulechain)
	{
		IT::Entry tempIdEntry;
		finalPosition = lexTablePosition;
		switch (nrulechain)
		{
		case Irule_DECL_AND_INIT:
		case Irule_INIT:
			// Run on Lexemas in search	of an identificator.
			while (lexTable.table[lexTablePosition].lexema != LEX_IDENTIFICATOR)
				lexTablePosition++;
			// Set the idDataTypeGeneral and initalPosition of Analyzing.
			tempIdEntry = idTable.table[lexTable.table[lexTablePosition].idxTI];
			idDataTypeGeneral = tempIdEntry.idDataType;
			initialPosition = lexTablePosition + 2;
			// Run on Lexemas in search of the end of Expression, and set the finalPosition.
			while (lexTable.table[finalPosition].lexema != LEX_SEMICOLON)
				finalPosition++;
			break;
		case Irule_CALL_FUNCTION:
			idDataTypeGeneral = IT::UNDEF;
			initialPosition = lexTablePosition;
			while (lexTable.table[finalPosition].lexema != LEX_SEMICOLON)
				finalPosition++;
			break;
		case Irule_IF:
		case Irule_IF_ELSE:
			idDataTypeGeneral = IT::BOOL;
			initialPosition = lexTablePosition + 2;
			while (lexTable.table[finalPosition].lexema != LEX_BRACES_LEFT)
			{
				if (lexTable.table[finalPosition].lexema == LEX_COMPARISONS)
					idDataTypeGeneral = IT::UNDEF;
				finalPosition++;
			}
			finalPosition--;
			break;
		case Irule_DECL:
		case Irule_UNDEF:
			isVoidRule = true;
			break;
		}
	}

	void SemanticData::SetFunctionIdDataType(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition, int nrulechain)
	{
		switch (nrulechain)
		{
		case Srule_INCLUDE:
			// Check for Right Lib Name.
			break;
		case Srule_FUNCTION:
			idDataTypeFunction = idTable.table[lexTable.table[lexTablePosition + 2].idxTI].idDataType;
			break;
		case Srule_MAIN:
			idDataTypeFunction = IT::UINT;
			break;
		}
	}

	void SemanticData::AnalyzeExpression(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		IT::Entry tempIdEntry;
		for (int i = initialPosition; i < finalPosition; i++)
		{
			switch (lexTable.table[i].lexema)
			{
			case LEX_IDENTIFICATOR:
			case LEX_LITERAL:
				tempIdEntry = idTable.table[lexTable.table[i].idxTI];
				if (tempIdEntry.idDataType != idDataTypeGeneral && idDataTypeGeneral != IT::UNDEF)
					throw ERROR_THROW_IN(412, lexTable.table[i].line, lexTable.table[i].position);
				if (tempIdEntry.idType == IT::FUNCTION || tempIdEntry.idType == IT::PROTOTYPE)
					i = AnalyzeFunctionCall(lexTable, idTable, i);
				break;
			case LEX_BINARIES:
			case LEX_UNARY:
				lexTable.table[i].operationDataType = idDataTypeGeneral;
				if (!CheckOperationType(lexTable.table[i], idDataTypeGeneral))
					throw ERROR_THROW_IN(413, lexTable.table[i].line, lexTable.table[i].position);
				break;
			}
		}
	}

	bool SemanticData::CheckOperationType(LT::Entry lexEntry, IT::IDDATATYPE idDataType)
	{
		switch (idDataType)
		{
#ifdef DEBUG_SEMANTIC
		case IT::UNDEF:
			cout << "Something Wrong!" << endl;
			return false;
#endif // DEBUG_SEMANTIC
		case IT::UINT:
			return true;
		case IT::STRING:
			return lexEntry.operationType == LT::PLUS;
		case IT::BOOL:
			return lexEntry.lexema == LEX_COMPARISONS;
		}
	}

	int SemanticData::AnalyzeFunctionCall(LT::LexTable& lexTable, IT::IdTable& idTable, int functionPosition)
	{
		// Accept the params DataType info.
		IT::Entry tempIdEntry = idTable.table[lexTable.table[functionPosition].idxTI];
		std::vector<IT::Entry> functionParamArray = FillFunctionParams(idTable, tempIdEntry);
		// Set the position of Lexema - "(".
		int lexTablePosition = functionPosition + 1;
		int paramIterator = 0;
		if (functionParamArray.size() > 0)
		{
			IT::IDDATATYPE currentParamDataType = functionParamArray[paramIterator++].idDataType;
			while (lexTable.table[lexTablePosition].lexema != LEX_PARENTHESES_RIGHT)
			{
				switch (lexTable.table[lexTablePosition].lexema)
				{
				case LEX_IDENTIFICATOR:
				case LEX_LITERAL:
					tempIdEntry = idTable.table[lexTable.table[lexTablePosition].idxTI];
					if (tempIdEntry.idDataType != currentParamDataType)
						throw ERROR_THROW_IN(410, lexTable.table[lexTablePosition].line, lexTable.table[lexTablePosition].position);
					if (tempIdEntry.idType == IT::FUNCTION || tempIdEntry.idType == IT::PROTOTYPE)
						lexTablePosition = AnalyzeFunctionCall(lexTable, idTable, lexTablePosition);
					break;
				case LEX_BINARIES:
				case LEX_UNARY:
					lexTable.table[lexTablePosition].operationDataType = currentParamDataType;
					if (!CheckOperationType(lexTable.table[lexTablePosition], currentParamDataType))
						throw ERROR_THROW_IN(413, lexTable.table[lexTablePosition].line, lexTable.table[lexTablePosition].position);
					break;
				case LEX_COMMA:
					if (paramIterator >= functionParamArray.size())
						throw ERROR_THROW_IN(411, lexTable.table[initialPosition].line, lexTable.table[initialPosition].position);
					currentParamDataType = functionParamArray[paramIterator++].idDataType;
					break;
				}
				++lexTablePosition;
			}
		}
		else if (lexTable.table[++lexTablePosition].lexema != LEX_PARENTHESES_RIGHT)
			throw ERROR_THROW_IN(411, lexTable.table[initialPosition].line, lexTable.table[initialPosition].position);
		return lexTablePosition;
	}

	std::vector<IT::Entry> SemanticData::FillFunctionParams(IT::IdTable& idTable, IT::Entry idEntry)
	{
		std::vector<IT::Entry> functionParamArray;
		idEntry.paramsIdx.reverse();
		for (auto idParam = idEntry.paramsIdx.begin(); idParam != idEntry.paramsIdx.end(); idParam++)
			functionParamArray.push_back(idTable.table[*idParam]);
		return functionParamArray;
	}

	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable)
	{
		IT::Entry tempIdEntry = IT::GetEntry(idTable, entry.idxTI);
		return tempIdEntry.functionParamsCount == deFactoParamsCount;
	}
}