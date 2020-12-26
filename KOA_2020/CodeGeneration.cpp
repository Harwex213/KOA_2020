#include "stdafx.h"

namespace CodeGeneration
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable, wchar_t outfile[])
	{
		CodeGenerationData data;
		data.storeState = mfst.storestate;
		data.streamOut->open(outfile);
		if (data.streamOut->fail())
			throw ERROR_THROW(114);
		data.FillStandartLines();
		data.FillDataAndProtos(idTable, lexTable);
		data.StartCode(lexTable, idTable);
		data.WriteCodeGeneration();
	}

#pragma region DataToString
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
			if (entryId.idType != IT::LITERAL)
				return "512 DUP(0)";
			return entryId.value.vString.string;
		case IT::BOOL:
			return std::to_string(entryId.value.vBool);
		}
	}
#pragma endregion

	void CodeGenerationData::WriteComment(int indexOfBlock, const char* comment)
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

#pragma region InitialActions
	void CodeGenerationData::FillStandartLines()
	{
		head.begin = head.begin + STANDART_HEAD_BEGIN;
		head.begin = head.begin + STACK(4096);
		head.libs = head.libs + STANDART_HEAD_LIBS;
		head.protos = head.protos + STANDART_HEAD_PROTOS;
		consts = consts + STANDART_CONST_BEGIN;
		data = data + STANDART_DATA_BEGIN;
		for (int i = 0; i < CALLING_VAR_COUNT / 2; i++)
		{
			data = data + INSERT_VARS(TEMP_VAR_NAME(i), "DWORD", "?");
			data = data + NEWLINE;
		}
		for (int i = CALLING_VAR_COUNT / 2; i < CALLING_VAR_COUNT; i++)
		{
			data = data + INSERT_VARS(TEMP_VAR_NAME(i), "BYTE", "?");
			data = data + NEWLINE;
		}
		data = data + STANDART_VARS;
	}

	void CodeGenerationData::FillDataAndProtos(IT::IdTable& idTable, LT::LexTable& lexTable)
	{
		WriteComment(HEAD_PROTOS_INDEX, "----- User and Libs Function Protos -----");
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
				data = data + INSERT_VARS(IdNameToString(i), IdDataTypeToString(idTable.table[i]), ValueToString(idTable.table[i]));
				data = data + NEWLINE;
				break;
			case IT::LITERAL:
				consts = consts + INSERT_VARS(IdNameToString(i), IdDataTypeToString(idTable.table[i]), ValueToString(idTable.table[i]));
				if (idTable.table[i].idDataType == IT::STRING)
					consts = consts + STR_END;
				consts = consts + NEWLINE;
				break;
			}
		}
		WriteComment(HEAD_PROTOS_INDEX, "----- End User and Libs Function Protos -----");
	}
#pragma endregion

#pragma region ActionOnVars
	void CodeGenerationData::PushVar(IT::Entry& entryId, int id)
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

	void CodeGenerationData::PopVar(IT::Entry& entryId, int id)
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

	void CodeGenerationData::RetVar(IT::Entry& entryId, int id)
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
#pragma endregion

#pragma region ActionOnTempVars
	void CodeGenerationData::ResetTempVars()
	{
		dwordTemp = CALLING_VAR_COUNT / 2 - 1;
		byteTemp = CALLING_VAR_COUNT;
	}

	void CodeGenerationData::SetTempVarsToInvoke()
	{
		dwordTemp = 0;
		byteTemp = CALLING_VAR_COUNT / 2;
	}

	void CodeGenerationData::PushTempVar(IT::Entry& entryId)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
		case IT::STRING:
			entryFunctionData.funcCode = entryFunctionData.funcCode + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++dwordTemp));
			break;
		case IT::BOOL:
			entryFunctionData.funcCode = entryFunctionData.funcCode + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++byteTemp));
			break;
		}
	}

	void CodeGenerationData::PopTempVar(IT::Entry& entryId)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
		case IT::STRING:
			entryFunctionData.funcCode = entryFunctionData.funcCode + POP(TEMP_VAR_NAME(dwordTemp--));
			break;
		case IT::BOOL:
			entryFunctionData.funcCode = entryFunctionData.funcCode + POPZX(TEMP_VAR_NAME(byteTemp--));
			break;
		}
	}
#pragma endregion

#pragma region CodeGenerationActions
	void CodeGenerationData::StartCode(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		for (auto i = storeState.begin(); i != storeState.end(); i++)
		{
			lexTablePosition = i->lenta_position;
			switch (i->nrule)
			{
			case S_RULE:
				ChooseConstructionChain(i->nrulechain, lexTable, idTable);
				break;
			case I_RULE:
				ChooseIChain(i->nrulechain, lexTable, idTable);
				break;
			case R_RULE:
			{
				lexTablePosition++;
				// Проверяем. Если -2 => был мейн. Если нет, была просто функция.
				switch (entryFunctionData.idxFunction)
				{
				case IDX_MAIN:
					PushVar(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTable.table[lexTablePosition].idxTI);
					entryFunctionData.funcEnd = entryFunctionData.funcEnd + MAIN_END;
					break;
				case IDX_NONE:
					break;
				default:
					RetVar(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTable.table[lexTablePosition].idxTI);
					entryFunctionData.funcEnd = entryFunctionData.funcEnd + STANDART_FUNC_END(idTable.table[entryFunctionData.idxFunction].idName);
					break;
				}
				// Заносим функцию в вектор.
				codeArray.push_back(entryFunctionData);
				currentFunction++;
				// Очищаем данные о функции.
				entryFunctionData.funcBegin.clear();
				entryFunctionData.funcCode.clear();
				entryFunctionData.funcEnd.clear();
				entryFunctionData.idxFunction = IDX_NONE;
				break;
			}
			default:
				break;
			}
		}
	}

	void CodeGenerationData::ChooseConstructionChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		IT::Entry entryId;
		switch (nrulechain)
		{
		case Srule_INCLUDE:
			// Доходим до литерала.
			while (lexTable.table[lexTablePosition].lexema != LEX_LITERAL)
				lexTablePosition++;
			// Присваиваем в tempEntry путь библиотеки.
			entryId = idTable.table[lexTable.table[lexTablePosition].idxTI];
			// Подключаем библиотеку.
			head.libs = head.libs + INCLUDE_LIB(ValueToString(entryId));
			break;
		case Srule_FUNCTION:
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
			while (entryId.functionParamsCount > 0 && idParam != entryId.paramsIdx.end())
			{
				entryFunctionData.funcBegin = entryFunctionData.funcBegin + INSERT_FUNCTION_PARAM(IdNameToString(*idParam), IdDataTypeToString(idTable.table[*idParam]));
				idParam++;
			}
			entryFunctionData.funcBegin = entryFunctionData.funcBegin + NEWLINE;
			break;
		}
		case Srule_MAIN:
			// Ставим, что функция была.
			FunctionWas = true;
			// Начинаем писать мейн.
			entryFunctionData.funcBegin = entryFunctionData.funcBegin + MAIN_BEGIN;
			// Ставим id мейна.
			entryFunctionData.idxFunction = IDX_MAIN;
			break;
		}
	}

	void  CodeGenerationData::WriteCodeGeneration()
	{
		time_t rawtime;
		struct tm timeinfo;			//структура хранящая текущее время
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//текущая дата в секундах
		localtime_s(&timeinfo, &rawtime);	//текущее локальное время, представленное в структуре

		*streamOut << "; Генерация выполнена успешно. ";
		strftime(buffer, 300, "Дата: %d.%m.%Y %H:%M:%S", &timeinfo);
		*streamOut << buffer << endl;
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
#pragma endregion

}