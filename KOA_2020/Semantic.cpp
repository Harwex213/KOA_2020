#include "stdafx.h"

namespace Semantic
{
	void Start(const MFST::Mfst& mfst, const LT::LexTable& lexTable, const IT::IdTable& idTable)
	{
		TYPE_OF_CHECK typeOfCheck;
		SemanticReturnCode returnCode = NORMAL;
		int positionToCheck = 0;
		for (auto i = mfst.storestate.begin(); i != mfst.storestate.end(); i++)
		{
			// Если нашли правило с Инструкцией.
			if (i->nrule == I_RULE)
			{
				positionToCheck = i->lenta_position;
				// Смотрим по подходящей цепочке.
				switch (i->nrulechain)
				{
				case Irule_IF_ELSE:
				case Irule_IF:
					typeOfCheck = CONDITION;
					returnCode = CheckOnIncongruity(positionToCheck, lexTable, idTable, typeOfCheck);
					break;
				case Irule_INIT:
					typeOfCheck = EXPRESSION;
					returnCode = CheckOnIncongruity(positionToCheck, lexTable, idTable, typeOfCheck);
					break;
				}
			}
			if (i->nrule == R_RULE)
			{
				typeOfCheck = RETURN_EXPRESSION;
				returnCode = CheckOnIncongruity(positionToCheck, lexTable, idTable, typeOfCheck);

			}
			switch (returnCode)
			{
			case Semantic::NORMAL:
				break;
			case Semantic::INCONGRUITY_PARAM:
				throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 10, lexTable.table[positionToCheck].line, lexTable.table[positionToCheck].position);
				break;
			case Semantic::INCONGRUITY_OPERAND:
				throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 12, lexTable.table[positionToCheck].line, lexTable.table[positionToCheck].position);
				break;
			case Semantic::INCONGRUITY_OPERTAION:
				throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 13, lexTable.table[positionToCheck].line, lexTable.table[positionToCheck].position);
				break;
			case Semantic::INCONGRUITY_RETURN_TYPE:
				throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 8, lexTable.table[positionToCheck].line, lexTable.table[positionToCheck].position);
				break;
			default:
				break;
			}
		}
	}

	SemanticReturnCode CheckOnIncongruity(int& PositionToCheck, const LT::LexTable& lexTable, const IT::IdTable& idTable, TYPE_OF_CHECK typeOfCheck)
	{
		SemanticReturnCode returnCode = NORMAL;
		switch (typeOfCheck)
		{
		case Semantic::EXPRESSION:
		{
			// Доходим до идентификатора (которому по идеи должны присвоить данные).
			while (lexTable.table[PositionToCheck].lexema != LEX_IDENTIFICATOR)
				PositionToCheck++;
			// Сохраняем его возвращаемый тип данных.
			IT::IDDATATYPE idDataTypeAssignmentId = idTable.table[lexTable.table[PositionToCheck].idxTI].idDataType;
			// Временные переменные.
			IT::Entry entryId;
			while (lexTable.table[PositionToCheck].lexema != LEX_SEMICOLON)
			{
				entryId = idTable.table[lexTable.table[PositionToCheck].idxTI];
				if (entryId.idType == IT::FUNCTION && entryId.idDataType != idDataTypeAssignmentId && !CheckParamsType(PositionToCheck, idTable, lexTable))
				{

				}


				PositionToCheck++;
			}
			break;
		}
		case Semantic::CONDITION:

			break;
		case Semantic::RETURN_EXPRESSION:

			break;
		}
		return returnCode;
	}

	bool CheckParamsType(int positionOfCalling, const IT::IdTable& idTable, const LT::LexTable& lexTable)
	{
		int positionTemp = positionOfCalling;
		auto paramsIdx = idTable.table[positionOfCalling].paramsIdx;
		paramsIdx.reverse();
		auto idParam = paramsIdx.begin();
		bool paramsCoindence = true;
		for (int i = 0; i < idTable.table[positionOfCalling].functionParamsCount; i++)
		{
			if (idTable.table[lexTable.table[positionTemp--].idxTI].idDataType != idTable.table[*idParam].idDataType)
				paramsCoindence = false;
		}
		return paramsCoindence;
	}

	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable)
	{
		IT::Entry tempIdEntry = IT::GetEntry(idTable, entry.idxTI);
		return tempIdEntry.functionParamsCount == deFactoParamsCount;
	}
}