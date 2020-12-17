#pragma once
#include <forward_list>
#include <vector>
#include <string>

#define ID_MAXSIZE		30				// максимальное количество сиволов в идентификаторе
#define TI_MAXSIZE		4096			// максимальное количество эл-ов в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию для типа integer 
#define TI_STR_DEFAULT	0x00			// значение по умолчанию для типа string
#define TI_STR_MAXSIZE	255

#define GET_DATE_FUNCTION		"GetDate"
#define GET_TIME_FUNCTION		"GetTime"
#define CWRITE_FUNCTION			 "cWrite"
#define CWRITE_LINE_FUNCTION	 "cWriteLine" 
#define GET_RANDOM_FUNCTION		 "GetRandom" 
#define BOOLTOCHAR_FUNCTION		 "BoolToChar" 
#define UINTTOCHAR_FUNCTION		 "UintToChar" 
#define CHARTOUINT_FUNCTION		 "CharToUint" 
#define CHARTOBOOL_FUNCTION		 "CharToBool" 

namespace IT
{
	enum IDDATATYPE { UNDEF = 0, UINT = 1, STRING = 2, BOOL = 3};
	enum IDTYPE { U = 0, PARAM = 1, VARIABLE = 2, FUNCTION = 3, LITERAL = 4, PROTOTYPE = 5  };

	struct Entry
	{
		int idxfirstLE;
		int functionParamsCount;
		char* idName = NULL;
		std::forward_list<std::string> visibility;
		std::forward_list<int> paramsIdx;
		IDDATATYPE	idDataType = UNDEF;
		IDTYPE	idType = U;
		union
		{
			int vUint;
			bool vBool;
			struct
			{
				unsigned char length;
				char string[TI_STR_MAXSIZE - 1];
			} vString;
		} value;

	};

	struct IdTable
	{
		int current_size = 0;
		std::vector<Entry> table;
		std::vector<std::string> functionLibNames;

		IdTable()
		{
			functionLibNames.push_back(GET_DATE_FUNCTION);
			functionLibNames.push_back(GET_TIME_FUNCTION);
			functionLibNames.push_back(CWRITE_FUNCTION);
			functionLibNames.push_back(CWRITE_LINE_FUNCTION);
			functionLibNames.push_back(GET_RANDOM_FUNCTION);
			functionLibNames.push_back(BOOLTOCHAR_FUNCTION);
			functionLibNames.push_back(UINTTOCHAR_FUNCTION);
			functionLibNames.push_back(CHARTOUINT_FUNCTION);
			functionLibNames.push_back(CHARTOBOOL_FUNCTION);
		}
	};

	void AddEntry(IdTable& idtable, Entry entry);
	Entry GetEntry(const IdTable& idtable, int n);
	int GetId(const IdTable& idTable, char* id, std::forward_list<std::string> visibility);
	int GetId(const IdTable& idTable, Entry entry);
	void Delete(IdTable& idtable);
}