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

	SemanticReturnCode CheckOnIncongruity(int& PositionToCheck, const LT::LexTable& lextable, const IT::IdTable& idTable, TYPE_OF_CHECK typeOfCheck)
	{
		return NORMAL;
	}

	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable)
	{
		IT::Entry tempIdEntry = IT::GetEntry(idTable, entry.idxTI);
		return tempIdEntry.functionParamsCount == deFactoParamsCount;
	}
}