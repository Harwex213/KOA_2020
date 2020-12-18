#pragma once
#include "LT.h"
#include "MFST.h"

namespace Semantic
{

	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable);
}