#pragma once

//#define GENERATION_DEBUG

#define S_RULE				0
#define SR_INCLUDE_CHAIN	0
#define SR_MAIN_CHAIN		1
#define SR_FUNCTION_CHAIN	2

#define I_RULE					1
#define IR_DECL_INIT_CHAIN		0
#define IR_DECL_INIT_CHAINwide	IR_DECL_INIT_CHAIN + 8
#define IR_DECL_CHAIN			1
#define IR_DECL_CHAINwide		IR_DECL_CHAIN + 8


#define HEAD_BEGIN_INDEX		1
#define HEAD_LIBS_INDEX			2
#define HEAD_PROTOS_INDEX		3
#define CONSTS_INDEX			4
#define DATA_INDEX				5
#define FUNC_BEGIN_INDEX		6
#define FUNC_CODE_INDEX			7
#define FUNC_END_INDEX			8

#define VAR_NAME "V_"

#define COMMENT(value) "; " + value + "\n"
#define NEWLINE	"\n"

#define STANDART_HEAD_BEGIN		".586\n" + \
								".model flat, stdcall\n"
#define STANDART_HEAD_LIBS		"includelib kernel32.lib\n" + \
								"includelib libucrt.lib\n"
#define STANDART_HEAD_PROTOS	"ExitProcess PROTO: DWORD\n"

#define STANDART_CONST_BEGIN	".const\n"
#define STANDART_DATA_BEGIN		".data\n"
#define STANDART_CODE_BEGIN		".code\n"
#define STANDART_CODE_END		"end main\n"

#define INCLUDE_LIB(name) "includelib " + name + "\n"

#define STACK(value) ".stack " + std::to_string(value) + "\n"

#define	INSERT_FUNCTION_PROTO(name) name + " PROTO : "
#define INSERT_FIRST_DWORD			"DWORD"
#define INSERT_DWORD				", : DWORD"

#define INSERT_VARS(name, type, value) name + " " + type + "\t" + value + "\n"

#define STANDART_FUNC_BEGIN(name)			name + " PROC"
#define INSERT_FUNCTION_PARAM(name, type)	", " + name + ": " + type
#define STANDART_FUNC_END(name)				"	ret\n" + name + " ENDP\n"
#define MAIN_BEGIN	"main PROC\n"
#define MAIN_END	"	push 0\n" + "	call ExitProcess\n" "main ENDP\n"

namespace CodeGeneration
{
	struct CodeHead
	{
		std::string begin;
		std::string libs;
		std::string protos;
	};

	struct FunctionData
	{
		// -2 ==> Main.
		int idxFunction = -1;
		std::string funcBegin;
		std::string funcCode;
		std::string funcEnd;
	};

	struct CodeGenerationData
	{
		CodeHead head;
		std::string consts;
		std::string data;
		std::string codeBegin{ STANDART_CODE_BEGIN };
		std::string codeEnd{ STANDART_CODE_END };
		std::vector<FunctionData> codeArray;
		int currentFunction = 0;
		FunctionData entryFunctionData;

		ofstream* streamOut = new ofstream();

		std::vector<MFST::MfstState> StateArray;
		int lexTablePosition = 0;
		bool FunctionWas = false;

		std::string IdNameToString(IT::Entry& entryId, int id)
		{
#ifdef GENERATION_DEBUG
			if (entryId.idType == IT::LITERAL)
				return entryId.idName;
			return entryId.idName + (std::string)"_" + *entryId.visibility.cbegin();
#endif // GENERATION_DEBUG
			return VAR_NAME + std::to_string(id);
		}

		std::string IdDataTypeToString(IT::IDDATATYPE idDataType)
		{
			switch (idDataType)
			{
			case IT::UINT:
				return "DWORD";
			case IT::STRING:
				return "BYTE";
			case IT::BOOL:
				return "BYTE";
			}
		}

		std::string ValueToString(IT::Entry& entryId)
		{
			switch (entryId.idDataType)
			{
			case IT::UINT:
				return std::to_string(entryId.value.vUint);
			case IT::STRING:
				return entryId.value.vString.string;
			case IT::BOOL:
				return std::to_string(entryId.value.vBool);
			}
		}

		void WriteComment(int indexOfBlock, const char* comment)
		{
			switch (indexOfBlock)
			{
			case HEAD_BEGIN_INDEX:
				head.begin = head.begin + COMMENT(comment);
				break;
			case HEAD_LIBS_INDEX:
				head.libs = head.libs + COMMENT(comment);
				break;
			case HEAD_PROTOS_INDEX:
				head.protos = head.protos + COMMENT(comment);
				break;
			case CONSTS_INDEX:
				consts = consts + COMMENT(comment);
				break;
			case DATA_INDEX:
				data = data + COMMENT(comment);
				break;
			case FUNC_BEGIN_INDEX:
				codeArray[currentFunction].funcBegin = codeArray[currentFunction].funcBegin + COMMENT(comment);
				break;
			case FUNC_CODE_INDEX:
				codeArray[currentFunction].funcCode = codeArray[currentFunction].funcCode + COMMENT(comment);
				break;
			case FUNC_END_INDEX:
				codeArray[currentFunction].funcEnd = codeArray[currentFunction].funcEnd + COMMENT(comment);
				break;
			}
		}

		void FillStandartLines()
		{
			head.begin = head.begin + STANDART_HEAD_BEGIN;
			head.begin = head.begin + STACK(4096);
			head.libs = head.libs + STANDART_HEAD_LIBS;
			head.protos = head.protos + STANDART_HEAD_PROTOS;
			consts = consts + STANDART_CONST_BEGIN;
			data = data + STANDART_DATA_BEGIN;
		}

		void FillDataAndProtos(IT::IdTable& idTable, LT::LexTable& lexTable)
		{
			WriteComment(HEAD_PROTOS_INDEX, "----- User Function Protos -----");
			for (int i = 0; i < idTable.current_size; i++)
			{
				switch (idTable.table[i].idType)
				{
				case IT::FUNCTION:
					head.protos = head.protos + INSERT_FUNCTION_PROTO(idTable.table[i].idName);
					if (idTable.table[i].functionParamsCount > 0)
						head.protos = head.protos + INSERT_FIRST_DWORD;
					for (int j = 1; j < idTable.table[i].functionParamsCount; j++)
						head.protos = head.protos + INSERT_DWORD;
					head.protos = head.protos + NEWLINE;
					break;
				case IT::PARAM:
				case IT::VARIABLE:
					data = data + INSERT_VARS(IdNameToString(idTable.table[i], i), IdDataTypeToString(idTable.table[i].idDataType), ValueToString(idTable.table[i]));
					break;
				case IT::LITERAL:
					consts = consts + INSERT_VARS(IdNameToString(idTable.table[i], i), IdDataTypeToString(idTable.table[i].idDataType), ValueToString(idTable.table[i]));
					break;
				}
			}
			WriteComment(HEAD_PROTOS_INDEX, "----- End User Function Protos -----");
		}

		void GetStoreState(MFST::Mfst& mfst)
		{
			// Проходимся по дереву разбора
			for (unsigned short k = 0; k < mfst.storestate.size(); k++)
			{
				// Получаем текущее правило.
				std::stack<MFST::MfstState> temp_storestate = mfst.storestate;
				auto j = temp_storestate.size() - 1;

				while (!temp_storestate.empty() && j-- != k)
					temp_storestate.pop();

				if (!temp_storestate.empty())
				{
					StateArray.push_back(temp_storestate.top());
					temp_storestate.pop();
				}
			}
		}

		void ChooseSnRuleChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			IT::Entry entryId;
			switch (nrulechain)
			{
			case SR_INCLUDE_CHAIN:
				// Доходим до литерала.
				while (lexTable.table[lexTablePosition].lexema != LEX_LITERAL)
					lexTablePosition++;
				// Присваиваем в tempEntry путь библиотеки.
				entryId = idTable.table[lexTable.table[lexTablePosition].idxTI];
				// Подключаем библиотеку.
				head.libs = head.libs + INCLUDE_LIB(entryId.value.vString.string);
				break;
			case SR_FUNCTION_CHAIN:
			{
				// Ставим, что функция была.
				FunctionWas = true;
				// Доходим до идентификатора (функции).
				while (lexTable.table[lexTablePosition].lexema != LEX_IDENTIFICATOR)
					lexTablePosition++;
				// Присваиваем в tempEntry идентификатор функции.
				entryId = idTable.table[lexTable.table[lexTablePosition].idxTI];
				// Ставим id функции, в которой находимся.
				entryFunctionData.idxFunction = lexTable.table[lexTablePosition].idxTI;
				// Начинаем писать функцию.
				entryFunctionData.funcBegin = entryFunctionData.funcBegin + STANDART_FUNC_BEGIN(entryId.idName);
				// Пишем параметры функции.
				auto idParam = entryId.paramsIdx.begin();
				char* name = nullptr;
				while (entryId.functionParamsCount > 0 && idParam != entryId.paramsIdx.end())
				{
					entryFunctionData.funcBegin = entryFunctionData.funcBegin + INSERT_FUNCTION_PARAM(idTable.table[*idParam].idName, IdDataTypeToString(idTable.table[*idParam].idDataType));
					idParam++;
				}
				entryFunctionData.funcBegin = entryFunctionData.funcBegin + NEWLINE;
				break;
			}
			case SR_MAIN_CHAIN:
				// Ставим, что функция была.
				FunctionWas = true;
				// Начинаем писать мейн.
				entryFunctionData.funcBegin = entryFunctionData.funcBegin + MAIN_BEGIN;
				// Ставим id мейна.
				entryFunctionData.idxFunction = -2;
				break;
			}
		}

		void ChooseInRuleChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
		{

		}

		void StartCode(LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			for (unsigned int i = 0; i < StateArray.size(); i++)
			{
				switch (StateArray[i].nrule)
				{
				case S_RULE:
#pragma region PopFunction
					if (FunctionWas)
					{
						// Проверяем. Если -2 => был мейн. Если нет, была просто функция.
						if (entryFunctionData.idxFunction == -2)
							entryFunctionData.funcEnd = entryFunctionData.funcEnd + MAIN_END;
						else
							entryFunctionData.funcEnd = entryFunctionData.funcEnd + STANDART_FUNC_END(idTable.table[lexTable.table[lexTablePosition].idxTI].idName);
						// Заносим функцию в вектор.
						codeArray.push_back(entryFunctionData);
						currentFunction++;
						// Очищаем данные о функции.
						entryFunctionData.funcBegin.clear();
						entryFunctionData.funcCode.clear();
						entryFunctionData.funcEnd.clear();
						entryFunctionData.idxFunction = -1;
					}
#pragma endregion
					ChooseSnRuleChain(StateArray[i].nrulechain, lexTable, idTable);
					break;
				case I_RULE:
					ChooseInRuleChain(StateArray[i].nrulechain, lexTable, idTable);
					break;
				default:
					break;
				}
			}
			// Заносим последнюю функцию в вектор.
#pragma region PopLastFunction
			if (entryFunctionData.idxFunction == -2)
				entryFunctionData.funcEnd = entryFunctionData.funcEnd + MAIN_END;
			else
				entryFunctionData.funcEnd = entryFunctionData.funcEnd + STANDART_FUNC_END(idTable.table[lexTable.table[lexTablePosition].idxTI].idName);
			// Заносим функцию в вектор.
			codeArray.push_back(entryFunctionData);
			currentFunction++;
			// Очищаем данные о функции.
			entryFunctionData.funcBegin.clear();
			entryFunctionData.funcCode.clear();
			entryFunctionData.funcEnd.clear();
			entryFunctionData.idxFunction = -1;
#pragma endregion
		}

		void WriteCodeGeneration()
		{
			streamOut->open("../KOA_2020_asm/KOA_2020.asm");
			if (streamOut->fail())
				throw ERROR_THROW(114);

			*streamOut << head.begin;
			*streamOut << head.libs;
			*streamOut << head.protos;
			*streamOut << consts;
			*streamOut << data;
			*streamOut << codeBegin;
			for (unsigned int i = 0; i < codeArray.size(); i++)
			{
				*streamOut << codeArray[i].funcBegin;
				*streamOut << codeArray[i].funcCode;
				*streamOut << codeArray[i].funcEnd;
			}
			*streamOut << codeEnd;

			streamOut->close();
		}
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable);
}