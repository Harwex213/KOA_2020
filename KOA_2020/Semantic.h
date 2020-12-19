#pragma once
#include "LT.h"
#include "MFST.h"
#include <vector>

namespace Semantic
{
	struct SemanticData
	{
		std::vector<IT::Entry> EntryIdStack;
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable);
	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable);
}