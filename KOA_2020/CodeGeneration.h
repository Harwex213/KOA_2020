#pragma once

#define GENERATION_DEBUG

#define S_RULE	0
#define I_RULE	1
#define E_RULE	2
#define O_RULE  3

#define HEAD_BEGIN_INDEX		1
#define HEAD_LIBS_INDEX			2
#define HEAD_PROTOS_INDEX		3
#define CONSTS_INDEX			4
#define DATA_INDEX				5
#define CODE_INDEX				6

#define VAR_NAME		"V_"

#define COMMENT(value)		"; " + value + "\n"
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

#define STANDART_LIB 

#define STACK(value) ".stack " + std::to_string(value) + "\n"

#define	INSERT_FUNCTION_PROTO(name) name + " PROTO : "
#define INSERT_FIRST_DWORD			"DWORD"
#define INSERT_DWORD				", : DWORD"

#define INSERT_VARS(name, type, value) name + " " + type + "\t" + value + "\n"

#define STANDART_FUNC_BEGIN(name)			name + "PROC"
#define INSERT_FUNCTION_PARAM(name, type)	", " + name + ": " + type
#define STANDART_FUNC_END(name)				name + "ENDP"

namespace CodeGeneration
{
	struct CodeHead
	{
		std::string begin;
		std::string libs;
		std::string protos;
	};

	struct CodeGenerationData
	{
		CodeHead head;
		std::string consts;
		std::string data;
		std::string code;

		ofstream* streamOut = new ofstream();

		MFST::MfstState entryState;
		GRB::Rule entryRule;

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
				return "dd";
			case IT::STRING:
				return "db";
			case IT::BOOL:
				return "db";
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
			case CODE_INDEX:
				code = code + COMMENT(comment);
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
			WriteComment(CODE_INDEX, "----- Code -----");
			code = code + STANDART_CODE_BEGIN;
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

		void MetFunction()
		{

		}

		void StartCode(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable)
		{
			// Проходимся по дереву разбора
			for (unsigned short k = 0; k < mfst.storestate.size(); k++)
			{
				// Получаем текущее правило.
#pragma region GetMfstState
				std::stack<MFST::MfstState> temp_storestate = mfst.storestate;
				auto j = temp_storestate.size() - 1;

				while (!temp_storestate.empty() && j-- != k)
					temp_storestate.pop();

				if (!temp_storestate.empty())
				{
					entryState = temp_storestate.top();
					temp_storestate.pop();
				}
#pragma endregion

				switch (entryState.nrule)
				{

				}
			}
		}

		void EndCode()
		{
			code = code + STANDART_CODE_END;
			WriteComment(CODE_INDEX, "----- End Code -----");
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
			*streamOut << code;

			streamOut->close();
		}
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable);
}