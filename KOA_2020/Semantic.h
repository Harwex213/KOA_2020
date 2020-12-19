#pragma once
#include "LT.h"
#include "MFST.h"

namespace Semantic
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lextable, IT::IdTable& idTable);

	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable);
}