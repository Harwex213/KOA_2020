#pragma once

//#define GENERATION_DEBUG

#define S_RULE					0

#define Srule_INCLUDE			0
#define Srule_PROTOTYPE			1
#define Srule_FUNCTION			2
#define Srule_MAIN				3

#define I_RULE					1

#define Irule_DECL_AND_INIT		0
#define Irule_DECL				1
#define Irule_INIT				2
#define Irule_CALL_FUNCTION		3
#define Irule_IF_ELSE			4
#define Irule_IF				5

#define E_RULE					2

#define R_RULE					3

#define HEAD_BEGIN_INDEX		1
#define HEAD_LIBS_INDEX			2
#define HEAD_PROTOS_INDEX		3
#define CONSTS_INDEX			4
#define DATA_INDEX				5
#define FUNC_BEGIN_INDEX		6
#define FUNC_CODE_INDEX			7
#define FUNC_END_INDEX			8

#define IDX_MAIN	-2
#define IDX_NONE	-1
#define IDX_FUNC	1

#define STANDART_CONST_BEGIN	".const\n"
#define STANDART_DATA_BEGIN		".data\n"
#define STANDART_CODE_BEGIN		".code\n"
#define STANDART_CODE_END		"end main\n"

#define STANDART_HEAD_BEGIN		".586\n" + \
								".model flat, stdcall\n"
#define STANDART_HEAD_LIBS		"includelib kernel32.lib\n" + \
								"includelib libucrt.lib\n" + \
								"includelib StandartLib.lib\n"
#define STANDART_HEAD_PROTOS	"ExitProcess\t PROTO : DWORD\n" + \
								"Concat\t PROTO : DWORD, : DWORD, : DWORD\n" + \
								"AssignmentString\t PROTO : DWORD, : DWORD\n" + \
								"cWrite PROTO : DWORD\n" + \
								"cWriteLine PROTO : DWORD\n" + \
								"GetRandom PROTO : DWORD, : DWORD\n" + \
								"GetDate PROTO : DWORD\n" + \
								"GetTime PROTO : DWORD\n" + \
								"BoolToChar PROTO : DWORD, : DWORD\n" + \
								"UintToChar PROTO : DWORD, : DWORD\n" + \
								"CharToBool PROTO : DWORD\n" + \
								"CharToUint PROTO : DWORD\n"

#define STACK(value) ".stack " + std::to_string(value) + "\n"

#define STANDART_VARS			"strTemp\t BYTE\t 512 DUP(0)\n" + \
								"strConvert\t BYTE\t 512 DUP(0)\n" + \
								"_getDate\t BYTE\t 512 DUP (0)\n" + \
								"_getTime\t BYTE\t 512 DUP(0)\n"

#define COMMENT(value) "; " + value + "\n"
#define NEWLINE	"\n"

#define INCLUDE_LIB(lib_name) "includelib\t " + lib_name + "\n"

#define	INSERT_FUNCTION_PROTO(name) name + " PROTO"
#define INSERT_FIRST_DWORD			": DWORD"
#define INSERT_DWORD				", : DWORD"

#define VAR_NAME(var_name) "V_" + var_name

#define CALLING_VAR_COUNT			16
#define TEMP_VAR_NAME(id) "PV_" + std::to_string(id)

#define INSERT_VARS(name, type, value) name + "\t " + type + "\t" + value
#define STR_END	", 0"

#define FUNC_LIB_DATE	"GetDate"
#define FUNC_LIB_TIME	"GetTime"
#define CALL_DATE		"\t push OFFSET _getDate\n" + "\t call GetDate\n" + "\t push eax\n"
#define CALL_TIME		"\t push OFFSET _getTime\n" + "\t call GetTime\n" + "\t push eax\n"

#define FUNC_LIB_UINT_CONVERT	"UintToChar"
#define FUNC_LIB_BOOL_CONVERT	"BoolToChar"
#define CALL_UINT_CONVERT		"\t push OFFSET strConvert\n" + "\t call UintToChar\n" + "\t push eax\n"
#define CALL_BOOL_CONVERT		"\t push OFFSET strConvert\n" + "\t call BoolToChar\n" + "\t push eax\n"

#define CWRITE_FUNC			"cWrite"
#define CWRITE_LINE_FUNC	"cWriteLine"

#define STANDART_FUNC_BEGIN(name)			name + " PROC"
#define INSERT_FUNCTION_PARAM(name, type)	", " + name + ": " + type
#define STANDART_FUNC_END(name)				"\t ret\n" + name + " ENDP\n"
#define MAIN_BEGIN	"main PROC\n"
#define MAIN_END	"\t call ExitProcess\n" "main ENDP\n"

#define PUSH(name)		"\t push " + name + "\n"
#define PUSHZX(name)	"\t movzx eax, " + name + "\n" + "\t push eax\n"
#define PUSHSTR(name)	"\t push OFFSET " + name + "\n"
#define	POP(name)		"\t pop " + name + "\n"
#define	POPZX(name)		"\t pop eax\n" + "\t mov " + name + ", al\n"
#define POPSTR(name)	"\t push OFFSET " + name + "\n\t call AssignmentString\n"
#define RET(name)		"\t mov eax, " + name + "\n"
#define RETZX(name)		"\t movzx eax, " + name + "\n"
#define RETSTR(name)	"\t mov eax, " + "OFFSET " + name + "\n"
#define ADD				"\t pop eax\n" + "\t pop ebx\n" + "\t add eax, ebx\n" + "\t push eax\n"
#define ADD_STR			"\t push OFFSET strTemp\n" + "\t call Concat\n" + "\t push eax\n"
#define SUB				"\t pop eax\n" + "\t pop ebx\n" + "\t sub ebx, eax\n" + "\t push eax\n"
#define MUL				"\t pop eax\n" + "\t pop ebx\n" + "\t mul ebx\n" + "\t push eax\n"
#define DIV				"\t pop eax\n" + "\t pop ebx\n" + "\t div ebx\n" + "\t push eax\n"
#define BIT_OR			"\t pop eax\n" + "\t pop ebx\n" + "\t or  eax, ebx\n" + "\t push eax\n"
#define BIT_AND			"\t pop eax\n" + "\t pop ebx\n" + "\t and eax, ebx\n" + "\t push eax\n"
#define BIT_NOT			"\t pop eax\n" + "\t not eax\n" + "\t push eax\n"
#define EQU(label)		"\t je " + label + "\n"
#define NOT_EQU(label)	"\t jne " + label + "\n"
#define MORE(label)		"\t ja " + label + "\n"
#define LESS(label)		"\t jb " + label + "\n"
#define MORE_EQU(label)	"\t jae " + label + "\n"
#define LESS_EQU(label)	"\t jbe " + label + "\n"
#define BOOL(label)		"\t je " + label + "\n"

#define INVOKE_FUNCTION(name) "\t invoke " + name
#define ADD_INVOKE_PARAM(name) ", " + name
#define PUSH_RESULT_FUNCTION "\t push eax\n"

#define IF_CONDITION		"\t pop eax\n" + "\t pop ebx\n" + "\t cmp eax, ebx\n"
#define IF_CONDITION_BOOL	"\t pop eax\n" + "\t cmp eax, 0h\n"
#define ELSE_BODY(label)			"\t jmp " + label + "\n"
#define IF_BODY(label)				label + ":\n"
#define IF_END(label)				label + ":\n"

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
		std::string ifBodyStandart{ "BODY_BLOCK" };
		std::string ifEndStandart{ "END_BLOCK" };
		int ignoreIf = 0;
		std::string funcEnd;
		int currentIf = 0;
	};

	struct CodeGenerationData
	{
		CodeHead head;
		std::string consts;
		std::string data;
		std::string codeBegin{ STANDART_CODE_BEGIN };
		std::vector<FunctionData> codeArray;
		int currentFunction = 0;
		FunctionData entryFunctionData;
		bool FunctionWas = false;
		std::string codeEnd{ STANDART_CODE_END };

		ofstream* streamOut = new ofstream();

		int lexTablePosition = 0;
		std::list<MFST::MfstState> storeState;

		int dwordTemp = CALLING_VAR_COUNT / 2 - 1;
		int byteTemp = CALLING_VAR_COUNT;

		void WriteComment(int indexOfBlock, const char* comment);
		// Initial actions.
		void FillStandartLines();
		void FillDataAndProtos(IT::IdTable& idTable, LT::LexTable& lexTable);
		// Action on Vars.
		void PushVar(IT::Entry& entryId, int id);
		void PopVar(IT::Entry& entryId, int id);
		void RetVar(IT::Entry& entryId, int id);
		// Action on Temp Vars (required for correct function call)
		void ResetTempVars();
		void SetTempVarsToInvoke();
		void PushTempVar(IT::Entry& entryId);
		void PopTempVar(IT::Entry& entryId);
		// Code Generation Actions.
		void StartCode(LT::LexTable& lexTable, IT::IdTable& idTable);
		void ChooseConstructionChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable);
		void WriteCodeGeneration();

		void ExecuteOperation(LT::OperationType operationType, IT::Entry& entry)
		{
			switch (operationType)
			{
			case LT::PLUS:
				if (entry.idDataType == IT::STRING)
					entryFunctionData.funcCode = entryFunctionData.funcCode + ADD_STR;
				else
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

		bool CheckOnFunction(char* idName)
		{
			bool check = false;
			if (strcmp(idName, FUNC_LIB_DATE)==0)
			{
				entryFunctionData.funcCode = entryFunctionData.funcCode + CALL_DATE;	
				check = true;
			}
			if (strcmp(idName, FUNC_LIB_TIME) == 0)
			{
				entryFunctionData.funcCode = entryFunctionData.funcCode + CALL_TIME;
				check = true;
			}
			if (strcmp(idName, FUNC_LIB_UINT_CONVERT) == 0)
			{
				entryFunctionData.funcCode = entryFunctionData.funcCode + CALL_UINT_CONVERT;
				check = true;
			}
			if (strcmp(idName, FUNC_LIB_BOOL_CONVERT) == 0)
			{
				entryFunctionData.funcCode = entryFunctionData.funcCode + CALL_BOOL_CONVERT;
				check = true;
			}
			return check;
		}

		void ChooseInstructionChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			// Выводим в комментарий разбираемую строку.
			std::string tempString;
			int tempPosition = lexTablePosition;
			tempString = tempString + std::to_string(lexTable.table[tempPosition].line) + "\t ";
			while (tempPosition + 1 != lexTable.table.size() && lexTable.table[tempPosition].line == lexTable.table[lexTablePosition].line)
			{
				if (lexTable.table[tempPosition].lexema == LEX_FILLER)
				{
					tempPosition++;
					continue;
				}
				tempString += lexTable.table[tempPosition++].lexema;
			}
			char* s = (char *)tempString.c_str();
			WriteComment(FUNC_CODE_INDEX, s);
			// Выбираем цепочку
			switch (nrulechain)
			{
			case Irule_DECL_AND_INIT:
			case Irule_INIT:
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
						if (!CheckOnFunction(idTable.table[lexTable.table[i].idxTI].idName))
						{
							// Снимаем во временные переменные данные.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
								PopTempVar(idTable.table[lexTable.table[i].idxTI]);
							// Вызываем функцию через Invoke.
							entryFunctionData.funcCode = entryFunctionData.funcCode + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
							// Пишем её параметры в обратной порядке.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
								PushTempVar(idTable.table[lexTable.table[i].idxTI]);
							ResetTempVars();
							entryFunctionData.funcCode = entryFunctionData.funcCode + NEWLINE;
							bool checkCWrite = true;
							if ((strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_FUNC) == 0) ||
								(strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_LINE_FUNC) == 0))
							{
								checkCWrite = false;
							}
							if (checkCWrite)
								entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH_RESULT_FUNCTION;
						}
						break;
					}
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:
						PushVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
						break;
					case LEX_BINARIES:
					case LEX_COMPARISONS:
					case LEX_UNARY:
						// Посылаем тип идентификатора, с которым происходит складывание.
						ExecuteOperation(lexTable.table[i].operationType, idTable.table[lexTable.table[i-1].idxTI]);
						break;
					}
				}
				// Выполняем присваивание идентификатору, что был до присваивания.
				int i = lexTablePosition - 1;
				PopVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
				break;

			}
			case Irule_CALL_FUNCTION:
				// Проходимся по цепочке лексем до точки с запятой.
				for (int i = lexTablePosition; lexTable.table[i].lexema != LEX_SEMICOLON; i++)
				{
					switch (lexTable.table[i].lexema)
					{
					case LEX_CALL_FUNCTION:
					{
						if (!CheckOnFunction(idTable.table[lexTable.table[i].idxTI].idName))
						{
							// Снимаем во временные переменные данные.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
								PopTempVar(idTable.table[lexTable.table[i].idxTI]);
							// Вызываем функцию через Invoke.
							entryFunctionData.funcCode = entryFunctionData.funcCode + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
							// Пишем её параметры в обратной порядке.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
								PushTempVar(idTable.table[lexTable.table[i].idxTI]);
							ResetTempVars();
							entryFunctionData.funcCode = entryFunctionData.funcCode + NEWLINE;
							bool checkCWrite = true;
							if ((strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_FUNC) == 0) ||
								(strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_LINE_FUNC) == 0))
							{
								checkCWrite = false;
							}
							if (checkCWrite)
								entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH_RESULT_FUNCTION;
						}
						break;
					}
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:
						PushVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
						break;
					case LEX_BINARIES:
					case LEX_UNARY:
						// Посылаем тип идентификатора, с которым происходит складывание.
						ExecuteOperation(lexTable.table[i].operationType, idTable.table[lexTable.table[i-1].idxTI]);
						break;
					}
				}
				break;
			case Irule_IF:
			case Irule_IF_ELSE:
			{
				entryFunctionData.currentIf++;
#pragma region Condition
				for (int i = lexTablePosition; lexTable.table[i].lexema != LEX_COMPARISONS && lexTable.table[i].lexema != LEX_BRACES_LEFT; i++, lexTablePosition++)
				{
					switch (lexTable.table[i].lexema)
					{
					case LEX_CALL_FUNCTION:
					{
						if (!CheckOnFunction(idTable.table[lexTable.table[i].idxTI].idName))
						{
							// Снимаем во временные переменные данные.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
								PopTempVar(idTable.table[lexTable.table[i].idxTI]);
							// Вызываем функцию через Invoke.
							entryFunctionData.funcCode = entryFunctionData.funcCode + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
							// Пишем её параметры в обратной порядке.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
								PushTempVar(idTable.table[lexTable.table[i].idxTI]);
							ResetTempVars();
							entryFunctionData.funcCode = entryFunctionData.funcCode + NEWLINE;
							bool checkCWrite = true;
							if ((strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_FUNC) == 0) ||
								(strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_LINE_FUNC) == 0))
							{
								checkCWrite = false;
							}
							if (checkCWrite)
								entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH_RESULT_FUNCTION;
						}
						break;
					}
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:
						PushVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
						break;
					case LEX_BINARIES:
					case LEX_UNARY:
						// Посылаем тип идентификатора, с которым происходит складывание.
						ExecuteOperation(lexTable.table[i].operationType, idTable.table[lexTable.table[i - 1].idxTI]);
						break;
					}
				}
#pragma endregion
				if (lexTable.table[lexTablePosition].lexema == LEX_BRACES_LEFT)
					entryFunctionData.funcCode = entryFunctionData.funcCode + IF_CONDITION_BOOL;
				else
					entryFunctionData.funcCode = entryFunctionData.funcCode + IF_CONDITION;
#pragma region Compare
				switch (lexTable.table[lexTablePosition].operationType)
				{
				case LT::EQUALLY:
					entryFunctionData.funcCode = entryFunctionData.funcCode + EQU(entryFunctionData.ifBodyStandart + std::to_string(entryFunctionData.currentIf));
					break;
				case LT::NON_EQUALLY:
					entryFunctionData.funcCode = entryFunctionData.funcCode + NOT_EQU(entryFunctionData.ifBodyStandart + std::to_string(entryFunctionData.currentIf));
					break;
				case LT::MORE:
					entryFunctionData.funcCode = entryFunctionData.funcCode + MORE(entryFunctionData.ifBodyStandart + std::to_string(entryFunctionData.currentIf));
					break;
				case LT::LESS:
					entryFunctionData.funcCode = entryFunctionData.funcCode + LESS(entryFunctionData.ifBodyStandart + std::to_string(entryFunctionData.currentIf));
					break;
				case LT::MORE_OR_EQUAL:
					entryFunctionData.funcCode = entryFunctionData.funcCode + MORE_EQU(entryFunctionData.ifBodyStandart + std::to_string(entryFunctionData.currentIf));
					break;
				case LT::LESS_OR_EQUAL:
					entryFunctionData.funcCode = entryFunctionData.funcCode + LESS_EQU(entryFunctionData.ifBodyStandart + std::to_string(entryFunctionData.currentIf));
					break;
				default:
					entryFunctionData.funcCode = entryFunctionData.funcCode + BOOL(entryFunctionData.ifBodyStandart + std::to_string(entryFunctionData.currentIf));
					break;
				}
#pragma endregion
				std::string ifBody;
				ifBody = ifBody + IF_BODY(entryFunctionData.ifBodyStandart + std::to_string(entryFunctionData.currentIf));
#pragma region BODY_IF
				for (int i = lexTablePosition; lexTable.table[i].lexema != LEX_BRACES_RIGHT; i++, lexTablePosition++)
				{
					switch (lexTable.table[i].lexema)
					{
					case LEX_CALL_FUNCTION:
					{
						if (!CheckOnFunction(idTable.table[lexTable.table[i].idxTI].idName))
						{
							// Снимаем во временные переменные данные.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
							{
								switch (idTable.table[lexTable.table[i].idxTI].idDataType)
								{
								case IT::UINT:
								case IT::STRING:
									ifBody = ifBody + POP(TEMP_VAR_NAME(dwordTemp--));
									break;
								case IT::BOOL:
									ifBody = ifBody + POPZX(TEMP_VAR_NAME(byteTemp--));
									break;
								}
							}
							// Вызываем функцию через Invoke.
							ifBody = ifBody + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
							// Пишем её параметры в обратной порядке.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
							{
								switch (idTable.table[lexTable.table[i].idxTI].idDataType)
								{
								case IT::UINT:
								case IT::STRING:
									ifBody = ifBody + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++dwordTemp));
									break;
								case IT::BOOL:
									ifBody = ifBody + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++byteTemp));
									break;
								}
							}
							ResetTempVars();
							ifBody = ifBody + NEWLINE;
							bool checkCWrite = true;
							if ((strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_FUNC) == 0) ||
								(strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_LINE_FUNC) == 0))
							{
								checkCWrite = false;
							}
							if (checkCWrite)
								ifBody = ifBody + PUSH_RESULT_FUNCTION;
						}
						break;
					}
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:
						switch (idTable.table[lexTable.table[i].idxTI].idDataType)
						{
						case IT::UINT:
							ifBody = ifBody + PUSH(IdNameToString(lexTable.table[i].idxTI));
							break;
						case IT::BOOL:
							ifBody = ifBody + PUSHZX(IdNameToString(lexTable.table[i].idxTI));
							break;
						case IT::STRING:
							ifBody = ifBody + PUSHSTR(IdNameToString(lexTable.table[i].idxTI));
							break;
						}
						break;
					case LEX_BINARIES:
					case LEX_UNARY:
						// Посылаем тип идентификатора, с которым происходит складывание.
						switch (lexTable.table[i].operationType)
						{
						case LT::PLUS:
							if (idTable.table[lexTable.table[i].idxTI].idDataType == IT::STRING)
								ifBody = ifBody + ADD_STR;
							else
								ifBody = ifBody + ADD;
							break;
						case LT::MINUS:
							ifBody = ifBody + SUB;
							break;
						case LT::MULTIPLY:
							ifBody = ifBody + MUL;
							break;
						case LT::DIVISION:
							ifBody = ifBody + DIV;
							break;
						case LT::OR:
							ifBody = ifBody + BIT_OR;
							break;
						case LT::AND:
							ifBody = ifBody + BIT_AND;
							break;
						case LT::INVERSION:
							ifBody = ifBody + BIT_NOT;
							break;
						}
						break;
					}
				}
#pragma endregion
				std::string elseBody;
#pragma region BODY_ELSE
				for (int i = lexTablePosition; lexTable.table[i].lexema != LEX_BRACES_RIGHT; i++, lexTablePosition++)
				{
					switch (lexTable.table[i].lexema)
					{
					case LEX_CALL_FUNCTION:
					{
						if (!CheckOnFunction(idTable.table[lexTable.table[i].idxTI].idName))
						{
							// Снимаем во временные переменные данные.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
							{
								switch (idTable.table[lexTable.table[i].idxTI].idDataType)
								{
								case IT::UINT:
								case IT::STRING:
									elseBody = elseBody + POP(TEMP_VAR_NAME(dwordTemp--));
									break;
								case IT::BOOL:
									elseBody = elseBody + POPZX(TEMP_VAR_NAME(byteTemp--));
									break;
								}
							}
							// Вызываем функцию через Invoke.
							elseBody = elseBody + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
							// Пишем её параметры в обратной порядке.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
							{
								switch (idTable.table[lexTable.table[i].idxTI].idDataType)
								{
								case IT::UINT:
								case IT::STRING:
									elseBody = elseBody + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++dwordTemp));
									break;
								case IT::BOOL:
									elseBody = elseBody + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++byteTemp));
									break;
								}
							}
							ResetTempVars();
							elseBody = elseBody + NEWLINE;
							bool checkCWrite = true;
							if ((strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_FUNC) == 0) ||
								(strcmp(idTable.table[lexTable.table[i].idxTI].idName, CWRITE_LINE_FUNC) == 0))
							{
								checkCWrite = false;
							}
							if (checkCWrite)
								elseBody = elseBody + PUSH_RESULT_FUNCTION;
						}
						break;
					}
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:
						switch (idTable.table[lexTable.table[i].idxTI].idDataType)
						{
						case IT::UINT:
							elseBody = elseBody + PUSH(IdNameToString(lexTable.table[i].idxTI));
							break;
						case IT::BOOL:
							elseBody = elseBody + PUSHZX(IdNameToString(lexTable.table[i].idxTI));
							break;
						case IT::STRING:
							elseBody = elseBody + PUSHSTR(IdNameToString(lexTable.table[i].idxTI));
							break;
						}
						break;
					case LEX_BINARIES:
					case LEX_UNARY:
						// Посылаем тип идентификатора, с которым происходит складывание.
						switch (lexTable.table[i].operationType)
						{
						case LT::PLUS:
							if (idTable.table[lexTable.table[i].idxTI].idDataType == IT::STRING)
								elseBody = elseBody + ADD_STR;
							else
								elseBody = elseBody + ADD;
							break;
						case LT::MINUS:
							elseBody = elseBody + SUB;
							break;
						case LT::MULTIPLY:
							elseBody = elseBody + MUL;
							break;
						case LT::DIVISION:
							elseBody = elseBody + DIV;
							break;
						case LT::OR:
							elseBody = elseBody + BIT_OR;
							break;
						case LT::AND:
							elseBody = elseBody + BIT_AND;
							break;
						case LT::INVERSION:
							elseBody = elseBody + BIT_NOT;
							break;
						}
						break;
					}
				}
#pragma endregion
				elseBody = elseBody + ELSE_BODY(entryFunctionData.ifEndStandart + std::to_string(entryFunctionData.currentIf));
				entryFunctionData.funcCode = entryFunctionData.funcCode + elseBody;
				entryFunctionData.funcCode = entryFunctionData.funcCode + ifBody;
				entryFunctionData.funcCode = entryFunctionData.funcCode + IF_END(entryFunctionData.ifEndStandart + std::to_string(entryFunctionData.currentIf));
				break;
			}
			}
		}
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable, wchar_t outfile[]);
	std::string IdNameToString(int id);
	std::string IdDataTypeToString(IT::Entry& entryId);
	std::string ValueToString(IT::Entry& entryId);
}