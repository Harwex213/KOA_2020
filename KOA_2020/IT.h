#pragma once
#include <forward_list>
#include <vector>
#include <string>

#define ID_MAXSIZE		30				// максимальное количество сиволов в идентификаторе
#define TI_MAXSIZE		4096			// максимальное количество эл-ов в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию для типа integer 
#define TI_STR_DEFAULT	0x00			// значение по умолчанию для типа string
#define TI_STR_MAXSIZE	514

#define STANDART_VISIBILITY "GLOBAL"
#define LITERAL_VISIBILITY "LITERAL"
#define FUNCTION_VISIBILITY "FUNCTION"

#define GET_DATE_FUNCTION		entryTemp.idName = (char*)"GetDate"; entryTemp.idDataType = STRING; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 0;	// 0

#define GET_TIME_FUNCTION		entryTemp.idName = (char*)"GetTime"; entryTemp.idDataType = STRING; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 0;	// 1

#define CWRITE_FUNCTION			entryTemp.idName = (char*)"cWrite"; entryTemp.idDataType = UINT; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 1; \
								entryTemp.paramsIdx.push_front(3);																										// 2
#define CWRITE_PARAM_1			entryTemp.idName = (char*)""; entryTemp.idType = PARAM; entryTemp.idDataType = STRING;													// 3

#define CWRITE_LINE_FUNCTION	entryTemp.idName = (char*)"cWriteLine"; entryTemp.idDataType = UINT; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 1; \
								entryTemp.paramsIdx.push_front(5);																										// 4
#define CWRITE_LINE_PARAM_1		entryTemp.idName = (char*)""; entryTemp.idType = PARAM; entryTemp.idDataType = STRING;													// 5

#define GET_RANDOM_FUNCTION		entryTemp.idName = (char*)"GetRandom"; entryTemp.idDataType = UINT; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 2; \
								entryTemp.paramsIdx.push_front(7);	entryTemp.paramsIdx.push_front(8);																	// 6
#define GET_RANDOM_PARAM_1		entryTemp.idName = (char*)""; entryTemp.idType = PARAM; entryTemp.idDataType = UINT;													// 7
#define GET_RANDOM_PARAM_2		entryTemp.idName = (char*)""; entryTemp.idType = PARAM; entryTemp.idDataType = UINT;													// 8

#define BOOLTOCHAR_FUNCTION		entryTemp.idName = (char*)"BoolToChar"; entryTemp.idDataType = STRING; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 1; \
								entryTemp.paramsIdx.push_front(10);																										// 9
#define BOOLTOCHAR_PARAM_1		entryTemp.idName = (char*)""; entryTemp.idType = PARAM; entryTemp.idDataType = BOOL;													// 10

#define UINTTOCHAR_FUNCTION		entryTemp.idName = (char*)"UintToChar"; entryTemp.idDataType = STRING; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 1; \
								entryTemp.paramsIdx.push_front(12);																										// 11
#define UINTTOCHAR_PARAM_1		entryTemp.idName = (char*)""; entryTemp.idType = PARAM; entryTemp.idDataType = UINT;													// 12

#define CHARTOUINT_FUNCTION		entryTemp.idName = (char*)"CharToUint"; entryTemp.idDataType = UINT; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 1; \
								entryTemp.paramsIdx.push_front(14);																										// 13
#define CHARTOUINT_PARAM_1		entryTemp.idName = (char*)""; entryTemp.idType = PARAM; entryTemp.idDataType = STRING;													// 14

#define CHARTOBOOL_FUNCTION		entryTemp.idName = (char*)"CharToBool"; entryTemp.idDataType = BOOL; entryTemp.idType = PROTOTYPE; entryTemp.functionParamsCount = 1; \
								entryTemp.paramsIdx.push_front(16);																										// 15
#define CHARTOBOOL_PARAM_1		entryTemp.idName = (char*)""; entryTemp.idType = PARAM; entryTemp.idDataType = STRING;													// 16

#define	CLEAR_PARAMSIDX			entry.paramsIdx.clear();

#define LIB_IDENTIFICATOR_AMOUNT	17

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
		union VALUE
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
		std::vector<Entry> tableLibId;
	};

	void SetLibFunctions(IdTable& idtable);
	void AddEntry(IdTable& idtable, Entry entry);
	void AddLibEntry(IdTable& idtable, Entry& entry);
	Entry GetEntry(const IdTable& idtable, int n);
	int GetId(const IdTable& idTable, char* id, std::forward_list<std::string> visibility);
	int GetId(const IdTable& idTable, Entry entry);
	void Delete(IdTable& idtable);
}