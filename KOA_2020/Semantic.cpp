#include "stdafx.h"

namespace Semantic
{
	void Start(const MFST::Mfst& mfst, const LT::LexTable& lextable, const IT::IdTable& idTable)
	{
		for (auto i = mfst.storestate.begin(); i != mfst.storestate.end(); i++)
		{
			// Если нашли правило с Инструкцией.
			if (i->nrule == I_RULE)
			{
				// Смотрим по подходящей цепочке.
				switch (i->nrulechain)
				{
				case Irule_IF_ELSE:
				case Irule_IF:
					
					break;
				case Irule_INIT:
				case Irule_DECL_AND_INIT:

					break;
				}
			}
		}
	}

	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable)
	{
		IT::Entry tempIdEntry = IT::GetEntry(idTable, entry.idxTI);
		return tempIdEntry.functionParamsCount == deFactoParamsCount;
	}
}