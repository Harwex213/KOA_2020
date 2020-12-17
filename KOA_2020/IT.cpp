#include "stdafx.h"

namespace IT
{
	void AddEntry(IdTable& idtable, Entry entry)
	{
		idtable.table.push_back(entry);
		idtable.table[idtable.current_size].idName = new char[strlen(entry.idName) + 1];
		strcpy(idtable.table[idtable.current_size].idName, entry.idName);
		idtable.current_size++;
	}
	Entry GetEntry(const IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	int GetId(const IdTable& idTable, char* id, std::forward_list<std::string> visibility)
	{
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (LexAnalysis::ViewVisibility(visibility, idTable.table[i].visibility) && (strcmp(id, idTable.table[i].idName) == 0))
				return i;
		}
		return LT_TI_NULLXDX;
	}
	int GetId(const IdTable& idTable, Entry entry)
	{
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (LexAnalysis::ViewVisibility(entry.visibility, idTable.table[i].visibility))
				switch (entry.idType)
				{
					case IT::LITERAL:
					{
						switch (entry.idDataType)
						{
						case IT::UINT:
							if (entry.value.vUint == idTable.table[i].value.vUint)
								return i;
							break;
						case IT::BOOL:
							if (entry.value.vBool == idTable.table[i].value.vBool)
								return i;
							break;
						case IT::STRING:
							if (strcmp(entry.value.vString.string, idTable.table[i].value.vString.string) == 0)
								return i;
							break;
						}
						break;
					}
					default:
					{
						if (strcmp(entry.idName, idTable.table[i].idName) == 0)
							return i;
						break;
					}
				}
		}
		return LT_TI_NULLXDX;
	}
	void Delete(IdTable& idtable)
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			delete[] idtable.table[i].idName;
		}
	}
}