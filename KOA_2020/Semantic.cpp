#include "stdafx.h"

namespace Semantic
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		for (auto i = mfst.storestate.begin(); i != mfst.storestate.end(); i++)
		{
			if (i->nrule == I_RULE)
			{
				int position = i->nrulechain;
				switch (i->nrulechain)
				{
				case Irule_CALL_FUNCTION:
					
					break;
				case Irule_DECL_AND_INIT:

					break;
				case Irule_INIT:

					break;
				case Irule_IF_ELSE:
				case Irule_IF:
					while (lexTable.table[position].lexema != LEX_BRACES_LEFT)
						position++;
					if (lexTable.table[position].operationType == LT::NONE)
					{

					}
					else
					{

					}
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