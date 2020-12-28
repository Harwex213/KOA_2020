#include "stdafx.h"
#define DEBUG_SEMANTIC

namespace Semantic
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		SemanticData semanticData;
		for (auto i = mfst.storestate.begin(); i != mfst.storestate.end(); i++)
		{
			if (i->nrule == I_RULE)
			{
				semanticData.SetGeneralIdDataType(lexTable, idTable, i->lenta_position, i->nrulechain);
				if (!semanticData.isVoidRule)
					semanticData.AnalyzeExpression(lexTable, idTable, semanticData.initialPosition, semanticData.finalPosition);
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
				finalPosition++;
			finalPosition--;
			break;
		case Irule_UNDEF:
			isVoidRule = true;
			break;
		}
	}

	void SemanticData::AnalyzeExpression(LT::LexTable& lexTable, IT::IdTable& idTable, int initialPosition, int finalPosition)
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
				{
					if (isParam)
						throw ERROR_THROW_IN(410, lexTable.table[i].line, lexTable.table[i].position);
					throw ERROR_THROW_IN(412, lexTable.table[i].line, lexTable.table[i].position);
				}
				if (tempIdEntry.idType == IT::FUNCTION || tempIdEntry.idType == IT::PROTOTYPE)
					AnalyzeFunctionCall(lexTable, idTable, i);
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

	int SemanticData::SetFunctionFinalPosition(LT::LexTable& lexTable, IT::IdTable& idTable, int functionPosition)
	{
		IT::Entry idEntry = idTable.table[lexTable.table[functionPosition].idxTI];
		idEntry.paramsIdx.reverse();
		int i = functionPosition + 1;
		while (lexTable.table[i].lexema != LEX_COMMA && lexTable.table[i].lexema != LEX_PARENTHESES_RIGHT)
		{

			i++;
		}
		for (auto idParam = idEntry.paramsIdx.begin(); idParam != idEntry.paramsIdx.end(); idParam++)
		{

		}

		return 0;
	}

	int SemanticData::AnalyzeFunctionCall(LT::LexTable& lexTable, IT::IdTable& idTable, int functionPosition)
	{
		IT::Entry tempIdEntry = idTable.table[lexTable.table[functionPosition].idxTI];
		std::vector<IT::Entry> functionParamArray = FillFunctionParams(idTable, tempIdEntry);
		int lexTablePosition = functionPosition + 1;
		if (functionParamArray.size() > 0)
		{
			for (int i = 0; i < functionParamArray.size(); i++)
			{
				while (lexTable.table[lexTablePosition].lexema != LEX_PARENTHESES_RIGHT)
				{
					switch (lexTable.table[lexTablePosition].lexema)
					{
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:

						break;
					case LEX_BINARIES:
					case LEX_UNARY:

						break;
					}
				}
			}
		}
		else if (lexTable.table[lexTablePosition + 1].lexema != LEX_PARENTHESES_RIGHT)
			throw ERROR_THROW_IN(411, lexTable.table[initialPosition].line, lexTable.table[initialPosition].position);
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