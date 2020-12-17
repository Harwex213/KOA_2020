#include "stdafx.h"

namespace IT
{
	void SetLibFunctions(IdTable& idTable)
	{
		// Вносим прототипы функций из библиотек.
		Entry entryTemp;
		entryTemp.visibility.push_front(STANDART_VISIBILITY);
		// 0
		GET_DATE_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 1
		GET_TIME_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 2
		CWRITE_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 3 (2.1)
		CWRITE_PARAM_1;
		AddLibEntry(idTable, entryTemp);
		// 4
		CWRITE_LINE_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 5 (4.1)
		CWRITE_LINE_PARAM_1;
		AddLibEntry(idTable, entryTemp);
		// 6
		GET_RANDOM_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 7 (6.1)
		GET_RANDOM_PARAM_1;
		AddLibEntry(idTable, entryTemp);
		// 8 (6.2)
		GET_RANDOM_PARAM_2;
		AddLibEntry(idTable, entryTemp);
		// 9
		BOOLTOCHAR_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 10 (9.1)
		BOOLTOCHAR_PARAM_1;
		AddLibEntry(idTable, entryTemp);
		// 11
		UINTTOCHAR_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 12 (11.1)
		UINTTOCHAR_PARAM_1;
		AddLibEntry(idTable, entryTemp);
		// 13
		CHARTOUINT_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 14 (13.1)
		CHARTOUINT_PARAM_1;
		AddLibEntry(idTable, entryTemp);
		// 15
		CHARTOBOOL_FUNCTION;
		AddLibEntry(idTable, entryTemp);
		// 16 (15.1)
		CHARTOBOOL_PARAM_1;
		AddLibEntry(idTable, entryTemp);
	}

	void AddEntry(IdTable& idtable, Entry entry)
	{
		idtable.table.push_back(entry);
		idtable.table[idtable.current_size].idName = new char[strlen(entry.idName) + 1];
		strcpy(idtable.table[idtable.current_size].idName, entry.idName);
		idtable.current_size++;
	}
	void AddLibEntry(IdTable& idtable, Entry entry)
	{
		idtable.tableLibId.push_back(entry);
		idtable.tableLibId[idtable.current_size].idName = new char[strlen(entry.idName) + 1];
		strcpy(idtable.tableLibId[idtable.current_size].idName, entry.idName);
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
			delete[] idtable.tableLibId[i].idName;
		}
	}
}