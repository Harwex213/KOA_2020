#pragma once

//#define GENERATION_DEBUG

#define S_RULE				0

#define SR_INCLUDE_CHAIN	0
#define SR_MAIN_CHAIN		1
#define SR_FUNCTION_CHAIN	2

#define I_RULE					1

#define IR_DECL_INIT_CHAIN		0
#define IR_DECL_CHAIN			1
#define IR_DECL_ARR_CHAIN		2
#define IR_DECL_CONST_CHAIN		3
#define IR_INIT_CHAIN			4
#define IR_INIT_ARR_CHAIN		5
#define IR_WHILE				6
#define IR_IF_ELSE				7
#define IR_IF					8

#define E_RULE	2

#define HEAD_BEGIN_INDEX		1
#define HEAD_LIBS_INDEX			2
#define HEAD_PROTOS_INDEX		3
#define CONSTS_INDEX			4
#define DATA_INDEX				5
#define FUNC_BEGIN_INDEX		6
#define FUNC_CODE_INDEX			7
#define FUNC_END_INDEX			8

#define PUSH_VAR_COUNT			16

#define IDX_MAIN	-2
#define IDX_FUNC	1

#define VAR_NAME(name) "V_" + name
#define PVAR_NAME(id) "PV_" + std::to_string(id)

#define COMMENT(value) "; " + value + "\n"
#define NEWLINE	"\n"

#define STANDART_HEAD_BEGIN		".586\n" + \
								".model flat, stdcall\n"
#define STANDART_HEAD_LIBS		"includelib kernel32.lib\n" + \
								"includelib libucrt.lib\n" + \
								"includelib Standart.lib\n"
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
#define RET(name)							"\t mov eax, " + name + "\n"
#define RETZX(name)							"\t movzx eax, " + name + "\n"
#define STANDART_FUNC_END(name)				"\t ret\n" + name + " ENDP\n"
#define MAIN_BEGIN	"main PROC\n"
#define MAIN_END	"\t call ExitProcess\n" "main ENDP\n"

#define PUSH(name)		"\t push " + name + "\n"
#define PUSHZX(name)	"\t movzx eax, " + name + "\n" + "\t push eax\n"
#define	POP(name)		"\t pop " + name + "\n"
#define	POPZX(name)		"\t pop eax\n" + "\t mov " name + ", al\n"
#define ADD				"\t pop eax\n" + "\t pop ebx\n" + "\t add eax, ebx\n" + "\t push eax\n"
#define SUB				"\t pop eax\n" + "\t pop ebx\n" + "\t sub eax, ebx\n" + "\t push eax\n"
#define MUL				"\t pop eax\n" + "\t pop ebx\n" + "\t mul ebx\n" + "\t push eax\n"
#define DIV				"\t pop eax\n" + "\t pop ebx\n" + "\t div ebx\n" + "\t push eax\n"
#define BIT_OR			"\t pop eax\n" + "\t pop ebx\n" + "\t or  eax, ebx\n" + "\t push eax\n"
#define BIT_AND			"\t pop eax\n" + "\t pop ebx\n" + "\t and eax, ebx\n" + "\t push eax\n"
#define BIT_NOT			"\t pop eax\n" + "\t not eax\n" + "\t push eax\n"

#define INVOKE_FUNCTION(name) "\t invoke " + name
#define ADD_FUNCTION_PARAM(name) ", " + name
#define PUSH_RESULT_FUNCTION "\t push eax\n"

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

		bool DebugCheck = true;

		std::string IdNameToString(IT::Entry& entryId, int id)
		{
#ifdef GENERATION_DEBUG
			if (entryId.idType == IT::LITERAL)
				return entryId.idName;
			return entryId.idName + (std::string)"_" + *entryId.visibility.cbegin();
#endif // GENERATION_DEBUG
			return VAR_NAME(std::to_string(id));
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
				entryFunctionData.funcBegin = entryFunctionData.funcBegin + COMMENT(comment);
				break;
			case FUNC_CODE_INDEX:
				entryFunctionData.funcCode = entryFunctionData.funcCode + COMMENT(comment);
				break;
			case FUNC_END_INDEX:
				entryFunctionData.funcEnd = entryFunctionData.funcEnd + COMMENT(comment);
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
			for (int i = 0; i < PUSH_VAR_COUNT / 2; i++)
				data = data + INSERT_VARS(PVAR_NAME(i), "DWORD", "?");
			for (int i = PUSH_VAR_COUNT / 2; i < PUSH_VAR_COUNT; i++)
				data = data + INSERT_VARS(PVAR_NAME(i), "BYTE", "?");
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
				entryId.paramsIdx.reverse();
				auto idParam = entryId.paramsIdx.begin();
				char* name = nullptr;
				while (entryId.functionParamsCount > 0 && idParam != entryId.paramsIdx.end())
				{
					entryFunctionData.funcBegin = entryFunctionData.funcBegin + INSERT_FUNCTION_PARAM(IdNameToString(entryId, *idParam), IdDataTypeToString(idTable.table[*idParam].idDataType));
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

		void ExecuteOperation(LT::OperationType operationType)
		{
			switch (operationType)
			{
			case LT::PLUS:
				entryFunctionData.funcCode = entryFunctionData.funcCode + ADD;
				break;
			case LT::MINUS:
				entryFunctionData.funcCode = entryFunctionData.funcCode + SUB;
				break;
			case LT::MULTIPLY:
				entryFunctionData.funcCode = entryFunctionData.funcCode + MUL;
				break;
			case LT::DIVISION:
				entryFunctionData.funcCode = entryFunctionData.funcCode + DIV;
				break;
			case LT::EQUALLY:
				break;
			case LT::NON_EQUALLY:
				break;
			case LT::MORE:
				break;
			case LT::LESS:
				break;
			case LT::MORE_OR_EQUAL:
				break;
			case LT::LESS_OR_EQUAL:
				break;
			case LT::OR:
				entryFunctionData.funcCode = entryFunctionData.funcCode + BIT_OR;
				break;
			case LT::AND:
				entryFunctionData.funcCode = entryFunctionData.funcCode + BIT_AND;
				break;
			case LT::INVERSION:
				entryFunctionData.funcCode = entryFunctionData.funcCode + BIT_NOT;
				break;
			}
		}

		void ChooseInRuleChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			// Выводим разбираемую строку.
			std::string tempString;
			int tempPosition = lexTablePosition;
			while (lexTable.table[tempPosition].line == lexTable.table[lexTablePosition].line)
				tempString += lexTable.table[tempPosition++].lexema;
			char* s = (char *)tempString.c_str();
			WriteComment(FUNC_CODE_INDEX, s);
			switch (nrulechain)
			{
			case IR_DECL_INIT_CHAIN:
			case IR_DECL_INIT_CHAIN + 9:
			case IR_INIT_CHAIN:
			case IR_INIT_CHAIN + 9:
			{
				// Доходим до присваивания.
				while (lexTable.table[lexTablePosition].lexema != LEX_ASSIGNMENT)
					lexTablePosition++;
				// Проходимся по цепочке лексем до точки с запятой.
				for (int i = lexTablePosition + 1; lexTable.table[i].lexema != LEX_SEMICOLON; i++)
				{
					switch (lexTable.table[i].lexema)
					{
					case LEX_CALL_FUNCTION:
					{
						int dwordTemp = PUSH_VAR_COUNT / 2 - 1;
						int byteTemp = PUSH_VAR_COUNT;
						for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
						{
							if (idTable.table[lexTable.table[i].idxTI].idDataType == IT::UINT)
								entryFunctionData.funcCode = entryFunctionData.funcCode + POP(PVAR_NAME(dwordTemp--));
							else
								entryFunctionData.funcCode = entryFunctionData.funcCode + POPZX(PVAR_NAME(byteTemp--));
						}
						entryFunctionData.funcCode = entryFunctionData.funcCode + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
						dwordTemp = PUSH_VAR_COUNT / 2 - 1;
						byteTemp = PUSH_VAR_COUNT;
						for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
						{
							if (idTable.table[lexTable.table[i].idxTI].idDataType == IT::UINT)
								entryFunctionData.funcCode = entryFunctionData.funcCode + ADD_FUNCTION_PARAM(PVAR_NAME(dwordTemp--));
							else
								entryFunctionData.funcCode = entryFunctionData.funcCode + ADD_FUNCTION_PARAM(PVAR_NAME(byteTemp--));
						}
						entryFunctionData.funcCode = entryFunctionData.funcCode + NEWLINE;
						entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH_RESULT_FUNCTION;
						break;
					}
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:
						if (idTable.table[lexTable.table[i].idxTI].idDataType == IT::UINT)
							entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH(VAR_NAME(std::to_string(lexTable.table[i].idxTI)));
						else
							entryFunctionData.funcCode = entryFunctionData.funcCode + PUSHZX(VAR_NAME(std::to_string(lexTable.table[i].idxTI)));
						break;
					case LEX_BINARIES:
					case LEX_COMPARISONS:
					case LEX_UNARY:
						ExecuteOperation(lexTable.table[i].operationType);
						break;
					}
				}
				// Выполняем присваивание идентификатору, что был до присваивания.
				int i = lexTablePosition - 1;
				if (idTable.table[lexTable.table[i].idxTI].idDataType == IT::UINT)
					entryFunctionData.funcCode = entryFunctionData.funcCode + POP(VAR_NAME(std::to_string(lexTable.table[i].idxTI)));
				else
					entryFunctionData.funcCode = entryFunctionData.funcCode + POPZX(VAR_NAME(std::to_string(lexTable.table[i].idxTI)));
				break;

			}
			case IR_DECL_CHAIN:
			case IR_DECL_CHAIN + 9:
				break;
			case IR_WHILE:
			case IR_WHILE + 9:
				break;
			case IR_IF_ELSE:
			case IR_IF_ELSE + 9:
				break;
			case IR_IF:
			case IR_IF + 9:
				break;
			}
		}

		void StartCode(LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			for (unsigned int i = 0; i < StateArray.size(); i++)
			{
				switch (StateArray[i].nrule)
				{
				case S_RULE:
					lexTablePosition = StateArray[i].lenta_position;
#pragma region PopFunction
					if (FunctionWas)
					{
						// Проверяем. Если -2 => был мейн. Если нет, была просто функция.
						if (entryFunctionData.idxFunction == IDX_MAIN)
							entryFunctionData.funcEnd = entryFunctionData.funcEnd + MAIN_END;
						else
							entryFunctionData.funcEnd = entryFunctionData.funcEnd + STANDART_FUNC_END(idTable.table[entryFunctionData.idxFunction].idName);
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
					lexTablePosition = StateArray[i].lenta_position;
					ChooseInRuleChain(StateArray[i].nrulechain, lexTable, idTable);
					break;
				case E_RULE:
					// Смотрим, не конец ли функции.
					lexTablePosition = StateArray[i].lenta_position;
					if (i + 1 == StateArray.size() || StateArray[i + 1].nrule == S_RULE)
					{
						switch (entryFunctionData.idxFunction)
						{
						case IDX_MAIN:
							if (idTable.table[lexTable.table[lexTablePosition].idxTI].idDataType == IT::UINT)
								entryFunctionData.funcEnd = entryFunctionData.funcEnd + PUSH(IdNameToString(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTable.table[lexTablePosition].idxTI));
							else
								entryFunctionData.funcEnd = entryFunctionData.funcEnd + PUSHZX(IdNameToString(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTable.table[lexTablePosition].idxTI));
							break;
						case IDX_FUNC:
							if (idTable.table[lexTable.table[lexTablePosition].idxTI].idDataType == IT::UINT)
								entryFunctionData.funcEnd = entryFunctionData.funcEnd + RET(IdNameToString(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTable.table[lexTablePosition].idxTI));
							else
								entryFunctionData.funcEnd = entryFunctionData.funcEnd + RETZX(IdNameToString(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTable.table[lexTablePosition].idxTI));
							break;
						}
					}
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