#pragma once
#include "LT.h"
#include "MFST.h"

namespace Semantic
{
	void Start(const MFST::Mfst& mfst, const LT::LexTable& lextable, const IT::IdTable& idTable);
	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable);
}