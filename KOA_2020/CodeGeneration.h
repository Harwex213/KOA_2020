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

#define COMMENT(value) "; " + value + "\n"
#define NEWLINE	"\n"

#define STANDART_HEAD_BEGIN		".586\n" + \
								".model flat, stdcall\n"
#define STACK(value) ".stack " + std::to_string(value) + "\n"
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

#define STANDART_CONST_BEGIN	".const\n"

#define STANDART_DATA_BEGIN		".data\n"
#define STANDART_VARS			"strTemp\t BYTE\t 512 DUP(0)\n" + \
								"strConvert\t BYTE\t 512 DUP(0)\n" + \
								"_getDate\t BYTE\t 512 DUP (0)\n" + \
								"_getTime\t BYTE\t 512 DUP(0)\n"
#define VAR_NAME(var_name) "V_" + var_name
// Dword Temp Var:	0	1	2	3	4	5	6	7
#define DWORD_TEMP_VAR_INITAL_INDEX	7
// Byte Temp Var:	8	9	10	11	12	13	14	15
#define BYTE_TEMP_VAR_INITAL_INDEX	15
#define TEMP_VAR_NAME(id) "TEMP_V_" + std::to_string(id)

#define STANDART_CODE_BEGIN		".code\n"
#define STANDART_CODE_END		"end main\n"

#define INCLUDE_LIB(lib_name) "includelib\t " + lib_name + "\n"

#define INSERT_VARS(name, type, value) name + "\t " + type + "\t" + value
#define STR_END	", 0"

#define	INSERT_FUNCTION_PROTO(name) name + " PROTO"
#define INSERT_FIRST_PARAM(type)	": " + type
#define INSERT_PARAM(type)			", : " + type

#define FUNC_LIB_DATE	"GetDate"
#define CALL_DATE		"\t push OFFSET _getDate\n" + "\t call GetDate\n"
#define FUNC_LIB_TIME	"GetTime"
#define CALL_TIME		"\t push OFFSET _getTime\n" + "\t call GetTime\n"
#define FUNC_LIB_UINT_CONVERT	"UintToChar"
#define CALL_UINT_CONVERT		"\t push OFFSET strConvert\n" + "\t call UintToChar\n"
#define FUNC_LIB_BOOL_CONVERT	"BoolToChar"
#define CALL_BOOL_CONVERT		"\t push OFFSET strConvert\n" + "\t call BoolToChar\n"

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

#define INVOKE_FUNCTION(name) "\t invoke " + name
#define ADD_INVOKE_PARAM(name) ", " + name
#define PUSH_RESULT_FUNCTION "\t push eax\n"

#define IF_CONDITION		"\t pop eax\n" + "\t pop ebx\n" + "\t cmp eax, ebx\n"
#define IF_CONDITION_BOOL	"\t pop eax\n" + "\t cmp eax, 0h\n"
#define ELSE_LABEL			"ELSE_BLOCK_"
#define END_LABEL			"END_BLOCK_"

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

#define RET(name)		"\t mov eax, " + name + "\n"
#define RETZX(name)		"\t movzx eax, " + name + "\n"
#define RETSTR(name)	"\t mov eax, " + "OFFSET " + name + "\n"

namespace CodeGeneration
{
	struct AsmHead
	{
		std::string begin;
		std::string libs;
		std::string protos;
		std::string consts;
		std::string data;

		// Initial actions.
		void FillStandartLines();
		void FillDataAndProtos(IT::IdTable& idTable, LT::LexTable& lexTable);
		void SetFunctionParamInProto();
		// Action on Libs.
		void AddLib(IT::Entry& entryId, int lexTablePosition);
	};

	struct FunctionData
	{
		int idxFunction = IDX_NONE;
		std::string funcBegin;
		std::string funcCode;
		std::string funcEnd;

		int currentIf = 0;
		int dwordTempVar = DWORD_TEMP_VAR_INITAL_INDEX;
		int byteTempVar = BYTE_TEMP_VAR_INITAL_INDEX;
		std::string standartFunctionsArray[4] = { FUNC_LIB_DATE, FUNC_LIB_TIME, FUNC_LIB_UINT_CONVERT, FUNC_LIB_BOOL_CONVERT };

		// Additional Actions.
		void WriteLineToGenerate(LT::LexTable& lexTable, int lexTablePosition);
		// Action on Vars.
		void PushVar(IT::Entry& entryId, int id);
		void PopVar(IT::Entry& entryId, int id);
		void RetVar(IT::Entry& entryId, int id);
		// Action on Temp Vars (required for correct function call)
		void PushTempVar(IT::Entry& entryId);
		void PopTempVar(IT::Entry& entryId);
		// Action on Functions.	
		void StartFunction(IT::IdTable& idTable, int idTableId);
		void StartMain();
		void InvokeFunction(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition);
		bool CheckOnStandartFunction(std::string idName);
		void EndFunction(IT::IdTable& idTable, int idTableId);
		// Action on Expressions.
		void ParseExpression(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition, bool isFunctionCall);
		std::string ParseIfElse(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition);
		void ParseCondition(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition);
		void ExecuteOperation(LT::OperationType operationType, IT::Entry& entry);
		void ExecuteCompare(LT::OperationType operationType, IT::Entry& entry);
	};

	struct AsmCode
	{
		std::string codeBegin{ STANDART_CODE_BEGIN };
		std::vector<FunctionData> codeArray;
		std::string codeEnd{ STANDART_CODE_END };

		int currentFunction = 0;
		FunctionData entryTempFunctionData;

		// Action on Functions.
		void AddFunction(FunctionData entryFunctionData);
		void ResetInfoAboutFunction();
	};

	struct CodeGenerationData
	{
		// ASM code.
		AsmHead head;
		AsmCode code;

		ofstream* streamOut = new ofstream();
		int lexTablePosition = 0;
		std::list<MFST::MfstState> storeState;

		// Code Generation Actions.
		void StartCode(LT::LexTable& lexTable, IT::IdTable& idTable);
		void ChooseConstructionChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable);
		void ChooseInstructionChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable);
		void WriteCodeGeneration();
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable, wchar_t outfile[]);
	std::string IdNameToString(int id);
	std::string IdDataTypeToString(IT::Entry& entryId);
	std::string ParamTypeToString(IT::Entry& entryId);
	std::string ValueToString(IT::Entry& entryId);
}