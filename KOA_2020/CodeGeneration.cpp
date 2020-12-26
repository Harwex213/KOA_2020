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
		{
			if (entryId.idType != IT::LITERAL)
				return "512 DUP(0)";
			return entryId.value.vString.string;
		}
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
			head.consts = head.consts + COMMENT(comment);
			break;
		case DATA_INDEX:
			head.data = head.data + COMMENT(comment);
			break;
		case FUNC_BEGIN_INDEX:
			code.entryTempFunctionData.funcBegin = code.entryTempFunctionData.funcBegin + COMMENT(comment);
			break;
		case FUNC_CODE_INDEX:
			code.entryTempFunctionData.funcCode = code.entryTempFunctionData.funcCode + COMMENT(comment);
			break;
		case FUNC_END_INDEX:
			code.entryTempFunctionData.funcEnd = code.entryTempFunctionData.funcEnd + COMMENT(comment);
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
		head.consts = head.consts + STANDART_CONST_BEGIN;
		head.data = head.data + STANDART_DATA_BEGIN;
		for (int i = 0; i < DWORD_TEMP_VAR_INITAL_INDEX + 1; i++)
		{
			head.data = head.data + INSERT_VARS(TEMP_VAR_NAME(i), "DWORD", "?");
			head.data = head.data + NEWLINE;
		}
		for (int i = DWORD_TEMP_VAR_INITAL_INDEX + 1; i < BYTE_TEMP_VAR_INITAL_INDEX + 1; i++)
		{
			head.data = head.data + INSERT_VARS(TEMP_VAR_NAME(i), "BYTE", "?");
			head.data = head.data + NEWLINE;
		}
		head.data = head.data + STANDART_VARS;
	}

	void CodeGenerationData::FillDataAndProtos(IT::IdTable& idTable, LT::LexTable& lexTable)
	{
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
				head.data = head.data + INSERT_VARS(IdNameToString(i), IdDataTypeToString(idTable.table[i]), ValueToString(idTable.table[i]));
				if (idTable.table[i].idDataType == IT::STRING)
					head.data = head.data + STR_END;
				head.data = head.data + NEWLINE;
				break;
			case IT::LITERAL:
				head.consts = head.consts + INSERT_VARS(IdNameToString(i), IdDataTypeToString(idTable.table[i]), ValueToString(idTable.table[i]));
				if (idTable.table[i].idDataType == IT::STRING)
					head.data = head.data + STR_END;
				head.consts = head.consts + NEWLINE;
				break;
			}
		}
	}
#pragma endregion

#pragma region ActionOnVars
	void FunctionData::PushVar(IT::Entry& entryId, int id)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
			funcCode = funcCode + PUSH(IdNameToString(id));
			break;
		case IT::BOOL:
			funcCode = funcCode + PUSHZX(IdNameToString(id));
			break;
		case IT::STRING:
			funcCode = funcCode + PUSHSTR(IdNameToString(id));
			break;
		}
	}

	void FunctionData::PopVar(IT::Entry& entryId, int id)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
			funcCode = funcCode + POP(IdNameToString(id));
			break;
		case IT::BOOL:
			funcCode = funcCode + POPZX(IdNameToString(id));
			break;
		case IT::STRING:
			funcCode = funcCode + POPSTR(IdNameToString(id));
			break;
		}
	}

	void FunctionData::RetVar(IT::Entry& entryId, int id)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
			funcCode = funcCode + RET(IdNameToString(id));
			break;
		case IT::BOOL:
			funcCode = funcCode + RETZX(IdNameToString(id));
			break;
		case IT::STRING:
			funcCode = funcCode + RETSTR(IdNameToString(id));
			break;
		}
	}
#pragma endregion

#pragma region ActionOnTempVars
	void CodeGenerationData::ResetTempVars()
	{
		code.dwordTempVar = DWORD_TEMP_VAR_INITAL_INDEX;
		code.byteTempVar = BYTE_TEMP_VAR_INITAL_INDEX;
	}

	void CodeGenerationData::PushTempVar(IT::Entry& entryId)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
		case IT::STRING:
			code.entryTempFunctionData.funcCode = code.entryTempFunctionData.funcCode + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++code.dwordTempVar));
			break;
		case IT::BOOL:
			code.entryTempFunctionData.funcCode = code.entryTempFunctionData.funcCode + ADD_INVOKE_PARAM(TEMP_VAR_NAME(code.byteTempVar));
			break;
		}
	}

	void CodeGenerationData::PopTempVar(IT::Entry& entryId)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
		case IT::STRING:
			code.entryTempFunctionData.funcCode = code.entryTempFunctionData.funcCode + POP(TEMP_VAR_NAME(code.dwordTempVar--));
			break;
		case IT::BOOL:
			code.entryTempFunctionData.funcCode = code.entryTempFunctionData.funcCode + POPZX(TEMP_VAR_NAME(code.byteTempVar--));
			break;
		}
	}
#pragma endregion

#pragma region ActionOnFunctions
	void FunctionData::StartFunction(IT::IdTable& idTable, int idTableFunctionId)
	{
		IT::Entry entryId = idTable.table[idTableFunctionId];
		idxFunction = idTableFunctionId;
		// Writing the Beginning of Function.
		funcBegin = funcBegin + STANDART_FUNC_BEGIN(entryId.idName);
		// Writing Params of Function.
		entryId.paramsIdx.reverse(); auto idParam = entryId.paramsIdx.begin();
		while (entryId.functionParamsCount > 0 && idParam != entryId.paramsIdx.end())
		{
			funcBegin = funcBegin + INSERT_FUNCTION_PARAM(IdNameToString(*idParam), IdDataTypeToString(idTable.table[*idParam]));
			idParam++;
		}
		funcBegin = funcBegin + NEWLINE;
	}

	void FunctionData::StartMain()
	{
		funcBegin = funcBegin + MAIN_BEGIN;
		idxFunction = IDX_MAIN;
	}

	void FunctionData::EndFunction(IT::IdTable& idTable, int idTableId)
	{
		switch (idxFunction)
		{
		case IDX_MAIN:
			PushVar(idTable.table[idTableId], idTableId);
			funcEnd = funcEnd + MAIN_END;
			break;
		case IDX_NONE:
			throw ERROR_THROW(1);
		default:
			RetVar(idTable.table[idTableId], idTableId);
			funcEnd = funcEnd + STANDART_FUNC_END(idTable.table[idxFunction].idName);
			break;
		}
	}

	void AsmCode::AddFunction(FunctionData entryFunctionData)
	{
		codeArray.push_back(entryFunctionData);
		currentFunction++;
	}

	void AsmCode::ResetInfoAboutFunction()
	{
		entryTempFunctionData.funcBegin.clear();
		entryTempFunctionData.funcCode.clear();
		entryTempFunctionData.funcEnd.clear();
		entryTempFunctionData.idxFunction = IDX_NONE;
	}
#pragma endregion

	void AsmHead::AddLib(IT::Entry& entryId, int lexTablePosition)
	{
		libs = libs + INCLUDE_LIB(ValueToString(entryId));
	}

#pragma region CodeGenerationActions
	void CodeGenerationData::StartCode(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		for (auto i = storeState.begin(); i != storeState.end(); i++)
		{
			if (i->lenta_position >= lexTablePosition)
				switch (i->nrule)
				{
				// Constructions.
				case S_RULE:
					ChooseConstructionChain(i->nrulechain, lexTable, idTable);
					break;
				// Instructions.
				case I_RULE:
					ChooseInstructionChain(i->nrulechain, lexTable, idTable);
					break;
				// Return.
				case R_RULE:
					code.entryTempFunctionData.EndFunction(idTable, lexTable.table[i->nrulechain + 1].idxTI);
					code.AddFunction(code.entryTempFunctionData);
					code.ResetInfoAboutFunction();
					break;
				}
		}
	}

	void CodeGenerationData::ChooseConstructionChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		switch (nrulechain)
		{
		case Srule_INCLUDE:
			// Run on Lexemas for found Literal.
			while (lexTable.table[lexTablePosition].lexema != LEX_LITERAL)
				lexTablePosition++;
			head.AddLib(idTable.table[lexTable.table[lexTablePosition].idxTI], lexTablePosition);
			break;
		case Srule_FUNCTION:
			// Run on Lexemas for found Identificator of Function.
			while (lexTable.table[lexTablePosition].lexema != LEX_IDENTIFICATOR)
				lexTablePosition++;
			code.entryTempFunctionData.StartFunction(idTable, lexTable.table[lexTablePosition].idxTI);
			break;
		case Srule_MAIN:
			code.entryTempFunctionData.StartMain();
			break;
		}
	}

	void CodeGenerationData::ChooseInstructionChain(int nrulechain, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		// ¬ыводим в комментарий разбираемую строку.
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
		char* s = (char*)tempString.c_str();
		WriteComment(FUNC_CODE_INDEX, s);
		// ¬ыбираем цепочку
		switch (nrulechain)
		{
		case Irule_DECL_AND_INIT:
		case Irule_INIT:
			break;
		case Irule_CALL_FUNCTION:
			break;
		case Irule_IF:
		case Irule_IF_ELSE:
			break;
		}
	}

	void CodeGenerationData::ExecuteOperation(LT::OperationType operationType, IT::Entry& entry)
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

	void  CodeGenerationData::WriteCodeGeneration()
	{
		time_t rawtime;
		struct tm timeinfo;			//структура хран€ща€ текущее врем€
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//текуща€ дата в секундах
		localtime_s(&timeinfo, &rawtime);	//текущее локальное врем€, представленное в структуре

		*streamOut << "; √енераци€ выполнена успешно. ";
		strftime(buffer, 300, "ƒата: %d.%m.%Y %H:%M:%S", &timeinfo);
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