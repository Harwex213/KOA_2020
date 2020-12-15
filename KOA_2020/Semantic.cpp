#include "stdafx.h"

namespace Semantic
{
	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable)
	{
		IT::Entry tempIdEntry = IT::GetEntry(idTable, entry.idxTI);
		return tempIdEntry.functionParamsCount == deFactoParamsCount;
			
	}
}