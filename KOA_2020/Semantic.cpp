#include "stdafx.h"

namespace Semantic
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		SemanticData data;
		for (auto i = mfst.storestate.begin(); i != mfst.storestate.end(); i++)
		{
			if (i->nrule == I_RULE)
			{
				int position = i->lenta_position;
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
					{
						data.EntryIdStack.push_back(idTable.table[lexTable.table[position].idxTI]);
						position++;
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