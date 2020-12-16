#pragma once

#define GENERATION_DEBUG

#define HEAD_INDEX		1
#define CONSTS_INDEX	2
#define DATA_INDEX		3
#define CODE_INDEX		4

#define VAR_NAME		"V_"
#define SEPARATOR_NAME	"_"

#define COMMENT(value)		"; " + value + "\n"
#define NEWLINE	"\n"

#define STANDART_HEAD_BEGIN		".586\n" + \
								".model flat, stdcall\n" + \
								"includelib kernel32.lib\n" + \
								"includelib libucrt.lib\n" + \
								"ExitProcess PROTO: DWORD\n"
#define STANDART_CONST_BEGIN	".const\n"
#define STANDART_DATA_BEGIN		".data\n"
#define STANDART_CODE_BEGIN		".code\n"
#define STANDART_CODE_END		"end main"

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
	struct CodeGenerationData
	{
		std::string head;
		std::string consts;
		std::string data;
		std::string code;

		ofstream* streamOut = new ofstream();

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
			case HEAD_INDEX:
				head = head + COMMENT(comment);
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
			WriteComment(HEAD_INDEX, "----- Start -----");
			head = head + STANDART_HEAD_BEGIN;
			WriteComment(HEAD_INDEX, "----- End Start -----");
			consts = consts + STANDART_CONST_BEGIN;
			data = data + STANDART_DATA_BEGIN;
			WriteComment(CODE_INDEX, "----- Code -----");
			code = code + STANDART_CODE_BEGIN;
		}

		void FillStack(int value)
		{
			head = head + STACK(value);
		}

		void FillData(IT::IdTable& idTable, LT::LexTable& lexTable)
		{
			WriteComment(HEAD_INDEX, "----- Function Protos -----");
			for (int i = 0; i < idTable.current_size; i++)
			{
				switch (idTable.table[i].idType)
				{
				case IT::FUNCTION:
					head = head + INSERT_FUNCTION_PROTO(idTable.table[i].idName);
					if (idTable.table[i].functionParamsCount > 0)
						head = head + INSERT_FIRST_DWORD;
					for (int j = 1; j < idTable.table[i].functionParamsCount; j++)
						head = head + INSERT_DWORD;
					head = head + NEWLINE;
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
			WriteComment(HEAD_INDEX, "----- End Function Protos -----");
			FillStack(4096);
		}

		void StartCode()
		{

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

			*streamOut << head;
			*streamOut << consts;
			*streamOut << data;
			*streamOut << code;

			streamOut->close();
		}
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable);
}