#pragma once
#include "LT.h"
#include "MFST.h"

namespace Semantic
{

	enum SemanticReturnCode { NORMAL = 0, INCONGRUITY_PARAM = 1, INCONGRUITY_OPERAND = 2, INCONGRUITY_OPERTAION = 3, INCONGRUITY_RETURN_TYPE = 4 };
	enum TYPE_OF_CHECK		{ EXPRESSION = 1, CONDITION = 2, RETURN_EXPRESSION = 3 };
	void Start(const MFST::Mfst& mfst, const LT::LexTable& lextable, const IT::IdTable& idTable);
	SemanticReturnCode CheckOnIncongruity(int& PositionToCheck, const LT::LexTable& lexTable, const IT::IdTable& idTable, TYPE_OF_CHECK typeOfCheck);
	bool CheckParamsType(int positionOfCalling, const IT::IdTable& idTable, const LT::LexTable& lexTable);
	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable);
}