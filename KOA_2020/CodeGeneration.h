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

#define CALLING_VAR_COUNT			16

#define IDX_MAIN	-2
#define IDX_FUNC	1

#define STANDART_CONST_BEGIN	".const\n"
#define STANDART_DATA_BEGIN		".data\n"
#define STANDART_CODE_BEGIN		".code\n"
#define STANDART_CODE_END		"end main\n"

#define STANDART_HEAD_BEGIN		".586\n" + \
								".model flat, stdcall\n"
#define STANDART_HEAD_LIBS		"includelib kernel32.lib\n" + \
								"includelib libucrt.lib\n" + \
								"includelib Standart.lib\n"
#define STANDART_HEAD_PROTOS	"ExitProcess\t PROTO : DWORD\n" + \
								"Concat\t PROTO : DWORD, : DWORD, : DWORD\n" + \
								"AssignmentString\t PROTO : DWORD, : DWORD\n"
								//"cWrite PROTO : DWORD\n" + \
								//"cWriteLine PROTO : DWORD\n" + \
								//"GetRandom PROTO : DWORD, : DWORD\n" + \
								//"BoolToChar PROTO : DWORD, : DWORD\n" + \
								//"UintToChar PROTO : DWORD, : DWORD\n" + \
								//"CharToBool PROTO : DWORD\n" + \
								//"CharToUint PROTO : DWORD\n"

#define STACK(value) ".stack " + std::to_string(value) + "\n"

#define STANDART_VARS			"strTemp\t BYTE\t 512 DUP(0)\n" + \
								"strConvert\t BYTE\t 512 DUP(0)\n" + \
								"_getDate\t BYTE\t 512 DUP (0)\n" + \
								"_getTime\t BYTE\t 512 DUP(0)"

#define COMMENT(value) "; " + value + "\n"
#define NEWLINE	"\n"

#define INCLUDE_LIB(lib_name) "includelib\t " + lib_name + "\n"

#define	INSERT_FUNCTION_PROTO(name) name + " PROTO : "
#define INSERT_FIRST_DWORD			"DWORD"
#define INSERT_DWORD				", : DWORD"

#define VAR_NAME(var_name) "V_" + var_name
#define PVAR_NAME(id) "PV_" + std::to_string(id)

#define INSERT_VARS(name, type, value) name + "\t " + type + "\t" + value + "\n"

#define STANDART_FUNC_BEGIN(name)			name + " PROC"
#define INSERT_FUNCTION_PARAM(name, type)	", " + name + ": " + type
#define STANDART_FUNC_END(name)				"\t ret\n" + name + " ENDP\n"
#define MAIN_BEGIN	"main PROC\n"
#define MAIN_END	"\t call ExitProcess\n" "main ENDP\n"

#define PUSH(name)		"\t push " + name + "\n"
#define PUSHZX(name)	"\t movzx eax, " + name + "\n" + "\t push eax\n"
#define PUSHSTR(name)	"\t push OFFSET" + name + "\n"
#define	POP(name)		"\t pop " + name + "\n"
#define	POPZX(name)		"\t pop eax\n" + "\t mov " + name + ", al\n"
#define POPSTR(name)	"\t push OFFSET " + name + "\n call AssignmentString\n"
#define RET(name)		"\t mov eax, " + name + "\n"
#define RETZX(name)		"\t movzx eax, " + name + "\n"
#define RETSTR(name)	"\t mov eax, " + "OFFSET name\n"
#define ADD				"\t pop eax\n" + "\t pop ebx\n" + "\t add eax, ebx\n" + "\t push eax\n"
#define ADD_STR			"\t push OFFSET strTemp\n" + "\t call Concat\n" + "\t push eax\n"
#define SUB				"\t pop eax\n" + "\t pop ebx\n" + "\t sub eax, ebx\n" + "\t push eax\n"
#define MUL				"\t pop eax\n" + "\t pop ebx\n" + "\t mul ebx\n" + "\t push eax\n"
#define DIV				"\t pop eax\n" + "\t pop ebx\n" + "\t div ebx\n" + "\t push eax\n"
#define BIT_OR			"\t pop eax\n" + "\t pop ebx\n" + "\t or  eax, ebx\n" + "\t push eax\n"
#define BIT_AND			"\t pop eax\n" + "\t pop ebx\n" + "\t and eax, ebx\n" + "\t push eax\n"
#define BIT_NOT			"\t pop eax\n" + "\t not eax\n" + "\t push eax\n"
#define EQU(label)		"\t je" + label + "\n"
#define NOT_EQU(label)	"\t jne" + label + "\n"
#define MORE(label)		"\t ja" + label + "\n"
#define LESS(label)		"\t jb" + label + "\n"
#define MORE_EQU(label)	"\t jae" + label + "\n"
#define LESS_EQU(label)	"\t jbe" + label + "\n"

#define INVOKE_FUNCTION(name) "\t invoke " + name
#define ADD_INVOKE_PARAM(name) ", " + name
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

	struct IfData
	{
		std::string ifCondition;
		std::string ifElseBody;
		std::string ifBody;
		std::string ifEnd;
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
		std::vector<IfData> ifArray;
		int currentIf = 0;
		std::string codeEnd{ STANDART_CODE_END };

		ofstream* streamOut = new ofstream();

		int lexTablePosition = 0;
		std::list<MFST::MfstState> storeState;

		int dwordTemp = CALLING_VAR_COUNT / 2 - 1;
		int byteTemp = CALLING_VAR_COUNT;

		void ResetPVars()
		{
			dwordTemp = CALLING_VAR_COUNT / 2 - 1;
			byteTemp = CALLING_VAR_COUNT;
		}

		std::string IdNameToString(int id)
		{
			return VAR_NAME(std::to_string(id));
		}

		std::string IdDataTypeToString(IT::Entry& entryId)
		{
			switch (entryId.idDataType)
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

		void PushVar(IT::Entry& entryId, int id)
		{
			switch (entryId.idDataType)
			{
			case IT::UINT:
				entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH(IdNameToString(id));
				break;
			case IT::BOOL:
				entryFunctionData.funcCode = entryFunctionData.funcCode + PUSHZX(IdNameToString(id));
				break;
			case IT::STRING:
				entryFunctionData.funcCode = entryFunctionData.funcCode + PUSHSTR(IdNameToString(id));
				break;
			}
		}

		void PopVar(IT::Entry& entryId, int id)
		{
			switch (entryId.idDataType)
			{
			case IT::UINT:
				entryFunctionData.funcCode = entryFunctionData.funcCode + POP(IdNameToString(id));
				break;
			case IT::BOOL:
				entryFunctionData.funcCode = entryFunctionData.funcCode + POPZX(IdNameToString(id));
				break;
			case IT::STRING:
				entryFunctionData.funcCode = entryFunctionData.funcCode + POPSTR(IdNameToString(id));
				break;
			}
		}

		void RetVar(IT::Entry& entryId, int id)
		{
			switch (entryId.idDataType)
			{
			case IT::UINT:
				entryFunctionData.funcCode = entryFunctionData.funcCode + RET(IdNameToString(id));
				break;
			case IT::BOOL:
				entryFunctionData.funcCode = entryFunctionData.funcCode + RETZX(IdNameToString(id));
				break;
			case IT::STRING:
				entryFunctionData.funcCode = entryFunctionData.funcCode + RETSTR(IdNameToString(id));
				break;
			}
		}

		void PushPVar(IT::Entry& entryId)
		{
			switch (entryId.idDataType)
			{
			case IT::UINT:
			case IT::STRING:
				entryFunctionData.funcCode = entryFunctionData.funcCode + ADD_INVOKE_PARAM(PVAR_NAME(dwordTemp--));
				break;
			case IT::BOOL:
				entryFunctionData.funcCode = entryFunctionData.funcCode + ADD_INVOKE_PARAM(PVAR_NAME(byteTemp--));
				break;
			}
		}

		void PopPVar(IT::Entry& entryId)
		{
			switch (entryId.idDataType)
			{
			case IT::UINT:
			case IT::STRING:
				entryFunctionData.funcCode = entryFunctionData.funcCode + POP(IdNameToString(dwordTemp--));
				break;
			case IT::BOOL:
				entryFunctionData.funcCode = entryFunctionData.funcCode + POPZX(IdNameToString(byteTemp));
				break;
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
			for (int i = 0; i < CALLING_VAR_COUNT / 2; i++)
				data = data + INSERT_VARS(PVAR_NAME(i), "DWORD", "?");
			for (int i = CALLING_VAR_COUNT / 2; i < CALLING_VAR_COUNT; i++)
				data = data + INSERT_VARS(PVAR_NAME(i), "BYTE", "?");
		}

		void FillDataAndProtos(IT::IdTable& idTable, LT::LexTable& lexTable)
		{
			WriteComment(HEAD_PROTOS_INDEX, "----- User and Libs Function Protos -----");
			for (int i = 0; i < idTable.current_size; i++)
			{
				switch (idTable.table[i].idType)
				{
				case IT::FUNCTION:
				case IT::PROTOTYPE:
					head.protos = head.protos + INSERT_FUNCTION_PROTO(idTable.table[i].idName);
					if (idTable.table[i].functionParamsCount > 0)
						head.protos = head.protos + INSERT_FIRST_DWORD;
					for (int j = 1; j < idTable.table[i].functionParamsCount; j++)
						head.protos = head.protos + INSERT_DWORD;
					head.protos = head.protos + NEWLINE;
					break;
				case IT::VARIABLE:
					data = data + INSERT_VARS(IdNameToString(i), IdDataTypeToString(idTable.table[i]), ValueToString(idTable.table[i]));
					break;
				case IT::LITERAL:
					consts = consts + INSERT_VARS(IdNameToString(i), IdDataTypeToString(idTable.table[i]), ValueToString(idTable.table[i]));
					break;
				}
			}
			WriteComment(HEAD_PROTOS_INDEX, "----- End User and Libs Function Protos -----");
		}

		void ChooseSChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			IT::Entry entryId;
			switch (nrulechain)
			{
			case Srule_INCLUDE:
				// ������� �� ��������.
				while (lexTable.table[lexTablePosition].lexema != LEX_LITERAL)
					lexTablePosition++;
				// ����������� � tempEntry ���� ����������.
				entryId = idTable.table[lexTable.table[lexTablePosition].idxTI];
				// ���������� ����������.
				head.libs = head.libs + INCLUDE_LIB(ValueToString(entryId));
				break;
			case Srule_FUNCTION:
			{
				// ������, ��� ������� ����.
				FunctionWas = true;
				// ������� �� �������������� (�������).
				while (lexTable.table[lexTablePosition].lexema != LEX_IDENTIFICATOR)
					lexTablePosition++;
				// ����������� � tempEntry ������������� �������.
				entryId = idTable.table[lexTable.table[lexTablePosition].idxTI];
				// ������ id �������, � ������� ���������.
				entryFunctionData.idxFunction = lexTable.table[lexTablePosition].idxTI;
				// �������� ������ �������.
				entryFunctionData.funcBegin = entryFunctionData.funcBegin + STANDART_FUNC_BEGIN(entryId.idName);
				// ����� ��������� �������.
				entryId.paramsIdx.reverse();
				auto idParam = entryId.paramsIdx.begin();
				while (entryId.functionParamsCount > 0 && idParam != entryId.paramsIdx.end())
				{
					entryFunctionData.funcBegin = entryFunctionData.funcBegin + INSERT_FUNCTION_PARAM(IdNameToString(*idParam), IdDataTypeToString(idTable.table[*idParam]));
					idParam++;
				}
				entryFunctionData.funcBegin = entryFunctionData.funcBegin + NEWLINE;
				break;
			}
			case Srule_MAIN:
				// ������, ��� ������� ����.
				FunctionWas = true;
				// �������� ������ ����.
				entryFunctionData.funcBegin = entryFunctionData.funcBegin + MAIN_BEGIN;
				// ������ id �����.
				entryFunctionData.idxFunction = IDX_MAIN;
				break;
			}
		}

		void ExecuteOperation(LT::OperationType operationType, IT::Entry& entry)
		{
			switch (operationType)
			{
			case LT::PLUS:
				if (entry.idDataType == IT::STRING)
					entryFunctionData.funcCode = entryFunctionData.funcCode + ADD_STR;
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
				entryFunctionData.funcCode = entryFunctionData.funcCode + EQU();
				break;
			case LT::NON_EQUALLY:
				entryFunctionData.funcCode = entryFunctionData.funcCode + NOT_EQU();
				break;
			case LT::MORE:
				entryFunctionData.funcCode = entryFunctionData.funcCode + MORE();
				break;
			case LT::LESS:
				entryFunctionData.funcCode = entryFunctionData.funcCode + LESS();
				break;
			case LT::MORE_OR_EQUAL:
				entryFunctionData.funcCode = entryFunctionData.funcCode + MORE_EQU();
				break;
			case LT::LESS_OR_EQUAL:
				entryFunctionData.funcCode = entryFunctionData.funcCode + LESS_EQU();
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

		void ChooseIChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			// ������� � ����������� ����������� ������.
			std::string tempString;
			int tempPosition = lexTablePosition;
			tempString += lexTable.table[tempPosition].line + "\t ";
			while (lexTable.table[tempPosition].line == lexTable.table[lexTablePosition].line)
				tempString += lexTable.table[tempPosition++].lexema;
			char* s = (char *)tempString.c_str();
			WriteComment(FUNC_CODE_INDEX, s);
			// �������� �������
			switch (nrulechain)
			{
			case Irule_DECL_AND_INIT:
			case Irule_INIT:
			{
				// ������� �� ������������.
				while (lexTable.table[lexTablePosition].lexema != LEX_ASSIGNMENT)
					lexTablePosition++;
				// ���������� �� ������� ������ �� ����� � �������.
				for (int i = lexTablePosition + 1; lexTable.table[i].lexema != LEX_SEMICOLON; i++)
				{
					switch (lexTable.table[i].lexema)
					{
					case LEX_CALL_FUNCTION:
					{
						// ������� �� ��������� ���������� ������.
						for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
							PopPVar(idTable.table[lexTable.table[i].idxTI]);
						ResetPVars();
						// �������� ������� ����� Invoke.
						entryFunctionData.funcCode = entryFunctionData.funcCode + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
						// ����� � ��������� � �������� �������.
						for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
							PushPVar(idTable.table[lexTable.table[i].idxTI]);
						ResetPVars();
						entryFunctionData.funcCode = entryFunctionData.funcCode + NEWLINE;
						entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH_RESULT_FUNCTION;
						break;
					}
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:
						PushVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
						break;
					case LEX_BINARIES:
					case LEX_COMPARISONS:
					case LEX_UNARY:
						ExecuteOperation(lexTable.table[i].operationType, idTable.table[lexTable.table[i].idxTI]);
						break;
					}
				}
				// ��������� ������������ ��������������, ��� ��� �� ������������.
				int i = lexTablePosition - 1;
				PopVar(idTable.table[lexTable.table[i].idxTI], i);
				break;

			}
			case Irule_CALL_FUNCTION:
				// ���������� �� ������� ������ �� ����� � �������.
				for (int i = lexTablePosition + 1; lexTable.table[i].lexema != LEX_SEMICOLON; i++)
				{
					switch (lexTable.table[i].lexema)
					{
					case LEX_CALL_FUNCTION:
					{
						// ������� �� ��������� ���������� ������.
						for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
							PopPVar(idTable.table[lexTable.table[i].idxTI]);
						ResetPVars();
						// �������� ������� ����� Invoke.
						entryFunctionData.funcCode = entryFunctionData.funcCode + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
						// ����� � ��������� � �������� �������.
						for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
							PushPVar(idTable.table[lexTable.table[i].idxTI]);
						ResetPVars();
						entryFunctionData.funcCode = entryFunctionData.funcCode + NEWLINE;
						entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH_RESULT_FUNCTION;
						break;
					}
					case LEX_IDENTIFICATOR:
					case LEX_LITERAL:
						PushVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
						break;
					case LEX_BINARIES:
					case LEX_COMPARISONS:
					case LEX_UNARY:
						ExecuteOperation(lexTable.table[i].operationType, idTable.table[lexTable.table[i].idxTI]);
						break;
					}
				}
				break;
			case Irule_IF_ELSE:

				break;
			case Irule_IF:

				break;
			}
		}

		void StartCode(LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			for (auto i = storeState.begin(); i != storeState.end(); i++)
			{
				lexTablePosition = i->lenta_position;
				switch (i->nrule)
				{
				case S_RULE:
#pragma region PopFunction
					if (FunctionWas)
					{
						// ���������. ���� -2 => ��� ����. ���� ���, ���� ������ �������.
						if (entryFunctionData.idxFunction == IDX_MAIN)
							entryFunctionData.funcEnd = entryFunctionData.funcEnd + MAIN_END;
						else
							entryFunctionData.funcEnd = entryFunctionData.funcEnd + STANDART_FUNC_END(idTable.table[entryFunctionData.idxFunction].idName);
						// ������� ������� � ������.
						codeArray.push_back(entryFunctionData);
						currentFunction++;
						// ������� ������ � �������.
						entryFunctionData.funcBegin.clear();
						entryFunctionData.funcCode.clear();
						entryFunctionData.funcEnd.clear();
						entryFunctionData.idxFunction = -1;
					}
#pragma endregion
					ChooseSChain(i->nrulechain, lexTable, idTable);
					break;
				case I_RULE:
					ChooseIChain(i->nrulechain, lexTable, idTable);
					break;
				case R_RULE:
					// ����� �������. ��������� ���������.
					for (int i = lexTablePosition + 1; lexTable.table[i].lexema != LEX_SEMICOLON; i++)
					{
						switch (lexTable.table[i].lexema)
						{
						case LEX_CALL_FUNCTION:
						{
							// ������� �� ��������� ���������� ������.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
								PopPVar(idTable.table[lexTable.table[i].idxTI]);
							ResetPVars();
							// �������� ������� ����� Invoke.
							entryFunctionData.funcCode = entryFunctionData.funcCode + INVOKE_FUNCTION(idTable.table[lexTable.table[i].idxTI].idName);
							// ����� � ��������� � �������� �������.
							for (int k = 0; k < idTable.table[lexTable.table[i].idxTI].functionParamsCount; k++)
								PushPVar(idTable.table[lexTable.table[i].idxTI]);
							ResetPVars();
							entryFunctionData.funcCode = entryFunctionData.funcCode + NEWLINE;
							entryFunctionData.funcCode = entryFunctionData.funcCode + PUSH_RESULT_FUNCTION;
							break;
						}
						case LEX_IDENTIFICATOR:
						case LEX_LITERAL:
							PushVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
							break;
						case LEX_BINARIES:
						case LEX_COMPARISONS:
						case LEX_UNARY:
							ExecuteOperation(lexTable.table[i].operationType, idTable.table[lexTable.table[i].idxTI]);
							break;
						}
					}
					// ���������� ���.
					switch (entryFunctionData.idxFunction)
					{
					case IDX_MAIN:
						PushVar(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTable.table[lexTablePosition].idxTI);
						break;
					case IDX_FUNC:
						RetVar(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTable.table[lexTablePosition].idxTI);
						break;
					}
					break;
				default:
					break;
				}
			}
			// ������� ��������� ������� � ������.
#pragma region PopLastFunction
			if (entryFunctionData.idxFunction == -2)
				entryFunctionData.funcEnd = entryFunctionData.funcEnd + MAIN_END;
			else
				entryFunctionData.funcEnd = entryFunctionData.funcEnd + STANDART_FUNC_END(idTable.table[lexTable.table[lexTablePosition].idxTI].idName);
			// ������� ������� � ������.
			codeArray.push_back(entryFunctionData);
			currentFunction++;
			// ������� ������ � �������.
			entryFunctionData.funcBegin.clear();
			entryFunctionData.funcCode.clear();
			entryFunctionData.funcEnd.clear();
			entryFunctionData.idxFunction = -1;
#pragma endregion
		}

		void WriteCodeGeneration()
		{
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

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable, wchar_t outfile[]);
}