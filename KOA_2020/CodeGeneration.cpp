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
		data.head.FillStandartLines();
		data.head.FillDataAndProtos(idTable, lexTable);
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

	std::string ParamTypeToString(IT::Entry& entryId)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
		case IT::STRING:
			return "DWORD";
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

	// Write to ASM Comment the current parsed line
	void FunctionData::WriteLineToGenerate(LT::LexTable& lexTable, int lexTablePosition)
	{
		int tempPosition = lexTablePosition;
		std::string tempString = std::to_string(lexTable.table[tempPosition].line) + "\t ";
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
		funcCode = funcCode + COMMENT(tempString);
	}

#pragma region InitialActions
	void AsmHead::FillStandartLines()
	{
		begin = begin + STANDART_HEAD_BEGIN;
		begin = begin + STACK(4096);
		libs = libs + STANDART_HEAD_LIBS;
		protos = protos + STANDART_HEAD_PROTOS;
		consts = consts + STANDART_CONST_BEGIN;
		data = data + STANDART_DATA_BEGIN;
		for (int i = 0; i < DWORD_TEMP_VAR_INITAL_INDEX + 1; i++)
		{
			data = data + INSERT_VARS(TEMP_VAR_NAME(i), "DWORD", "?");
			data = data + NEWLINE;
		}
		for (int i = DWORD_TEMP_VAR_INITAL_INDEX + 1; i < BYTE_TEMP_VAR_INITAL_INDEX + 1; i++)
		{
			data = data + INSERT_VARS(TEMP_VAR_NAME(i), "BYTE", "?");
			data = data + NEWLINE;
		}
		data = data + STANDART_VARS;
	}

	void AsmHead::FillDataAndProtos(IT::IdTable& idTable, LT::LexTable& lexTable)
	{
		IT::Entry entryId;
		string temp;
		protos = protos + COMMENT("User Functions:");
		for (int i = 0; i < idTable.current_size; i++)
		{
			entryId = idTable.table[i];
			switch (idTable.table[i].idType)
			{
			case IT::FUNCTION:
				protos = protos + INSERT_FUNCTION_PROTO(entryId.idName);
				entryId.paramsIdx.reverse();
				if (entryId.functionParamsCount > 0)
				{
					auto idParam = entryId.paramsIdx.begin();
					protos = protos + INSERT_FIRST_PARAM(ParamTypeToString(idTable.table[*idParam]));
					idParam++;
					for (; idParam != entryId.paramsIdx.end(); idParam++)
						protos = protos + INSERT_PARAM(ParamTypeToString(idTable.table[*idParam]));
				}
				protos = protos + NEWLINE;
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
	void FunctionData::PushTempVar(IT::Entry& entryId)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
		case IT::STRING:
			funcCode = funcCode + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++dwordTempVar));
			break;
		case IT::BOOL:
			funcCode = funcCode + ADD_INVOKE_PARAM(TEMP_VAR_NAME(++byteTempVar));
			break;
		}
	}

	void FunctionData::PopTempVar(IT::Entry& entryId)
	{
		switch (entryId.idDataType)
		{
		case IT::UINT:
		case IT::STRING:
			funcCode = funcCode + POP(TEMP_VAR_NAME(dwordTempVar--));
			break;
		case IT::BOOL:
			funcCode = funcCode + POPZX(TEMP_VAR_NAME(byteTempVar--));
			break;
		}
	}
#pragma endregion

#pragma region ActionOnFunctions
	void FunctionData::StartFunction(IT::IdTable& idTable, int idTableFunctionId)
	{
		IT::Entry entryFunctionId = idTable.table[idTableFunctionId];
		idxFunction = idTableFunctionId;
		// Writing the Beginning of Function.
		funcBegin = funcBegin + STANDART_FUNC_BEGIN(entryFunctionId.idName);
		// Writing Params of Function.
		entryFunctionId.paramsIdx.reverse();
		for (auto idParam = entryFunctionId.paramsIdx.begin(); idParam != entryFunctionId.paramsIdx.end(); idParam++)
			funcBegin = funcBegin + INSERT_FUNCTION_PARAM(IdNameToString(*idParam), IdDataTypeToString(idTable.table[*idParam]));
		funcBegin = funcBegin + NEWLINE;
	}

	void FunctionData::StartMain()
	{
		funcBegin = funcBegin + MAIN_BEGIN;
		idxFunction = IDX_MAIN;
	}

	void FunctionData::InvokeFunction(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition)
	{
		IT::Entry entryFunctionId = idTable.table[lexTable.table[lexTablePosition].idxTI];
		if (!CheckOnStandartFunction(entryFunctionId.idName))
		{
			// Pop data to Temp Vars.
			entryFunctionId.paramsIdx.reverse();
			for (auto idParam = entryFunctionId.paramsIdx.begin(); idParam != entryFunctionId.paramsIdx.end(); idParam++)
				PopTempVar(idTable.table[*idParam]);
			// Start writing the invoke of function.
			funcCode = funcCode + INVOKE_FUNCTION(entryFunctionId.idName);
			// Writing params of invoke.
			for (auto idParam = entryFunctionId.paramsIdx.begin(); idParam != entryFunctionId.paramsIdx.end(); idParam++)
				PushTempVar(idTable.table[*idParam]);
			funcCode = funcCode + NEWLINE;
		}
	}

	bool FunctionData::CheckOnStandartFunction(std::string idName)
	{
		for (int i = 0; i < 4; i++)
		{
			if (standartFunctionsArray[i] == idName)
			{
				string callString;
				switch (i)
				{
				case 0:
					callString = callString + CALL_DATE;
					break;
				case 1:
					callString = callString + CALL_TIME;
					break;
				case 2:
					callString = callString + CALL_UINT_CONVERT;
					break;
				case 3:
					callString = callString + CALL_BOOL_CONVERT;
					break;
				}
				funcCode = funcCode + callString;
				return true;
			}
		}
		return false;
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

#pragma region ActionOnExpressions
	void FunctionData::ParseExpression(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition, bool isFunctionCall)
	{
		for (int i = lexTablePosition; lexTable.table[i].lexema != LEX_SEMICOLON; i++)
		{
			switch (lexTable.table[i].lexema)
			{
			case LEX_CALL_FUNCTION:
				InvokeFunction(lexTable, idTable, i);
				if (!((lexTable.table[i + 1].lexema == LEX_SEMICOLON || lexTable.table[i + 1].lexema == LEX_FILLER) && isFunctionCall))
					funcCode = funcCode + PUSH_RESULT_FUNCTION;
				break;
			case LEX_IDENTIFICATOR:
			case LEX_LITERAL:
				PushVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
				break;
			case LEX_BINARIES:
			case LEX_UNARY:
				ExecuteOperation(lexTable.table[i].operationType, lexTable.table[i].operationDataType);
				break;
			}
		}
	}

	std::string FunctionData::ParseIfElse(LT::LexTable& lexTable, IT::IdTable& idTable, int& lexTablePosition)
	{
		std::string ifCodition;
		std::string ifBody;
		std::string elseBody;
		std::string endIf = END_LABEL + std::to_string(currentIf++);
		lexTablePosition = ParseCondition(lexTable, idTable, lexTablePosition);
		ifBody = ParseIfBody(lexTable, idTable, lexTablePosition);

		return "Amigo";
	}

	int FunctionData::ParseCondition(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition)
	{
		for (int i = lexTablePosition; lexTable.table[i].lexema != LEX_COMPARISONS && lexTable.table[i].lexema != LEX_PARENTHESES_RIGHT; i++, lexTablePosition++)
		{
			switch (lexTable.table[i].lexema)
			{
			case LEX_CALL_FUNCTION:
				InvokeFunction(lexTable, idTable, i);
				funcCode = funcCode + PUSH_RESULT_FUNCTION;
				break;
			case LEX_IDENTIFICATOR:
			case LEX_LITERAL:
				PushVar(idTable.table[lexTable.table[i].idxTI], lexTable.table[i].idxTI);
				break;
			case LEX_BINARIES:
			case LEX_UNARY:
				ExecuteOperation(lexTable.table[i].operationType, lexTable.table[i].operationDataType);
				break;
			}
		}
		if (lexTable.table[lexTablePosition].lexema == LEX_COMPARISONS)
			funcCode = funcCode + IF_CONDITION;
		else
			funcCode = funcCode + IF_CONDITION_BOOL;
		ExecuteCompare(lexTable.table[lexTablePosition++].operationType);
		return lexTablePosition;
	}

	int FunctionData::ParseIfBody(LT::LexTable& lexTable, IT::IdTable& idTable, int& lexTablePosition)
	{

	}

	void FunctionData::ExecuteOperation(LT::OperationType operationType, IT::IDDATATYPE operationDataType)
	{
		switch (operationType)
		{
		case LT::PLUS:
			if (operationDataType == IT::STRING)
				funcCode = funcCode + ADD_STR;
			else
				funcCode = funcCode + ADD;
			break;
		case LT::MINUS:
			funcCode = funcCode + SUB;
			break;
		case LT::MULTIPLY:
			funcCode = funcCode + MUL;
			break;
		case LT::DIVISION:
			funcCode = funcCode + DIV;
			break;
		case LT::OR:
			funcCode = funcCode + BIT_OR;
			break;
		case LT::AND:
			funcCode = funcCode + BIT_AND;
			break;
		case LT::INVERSION:
			funcCode = funcCode + BIT_NOT;
			break;
		}
	}

	void FunctionData::ExecuteCompare(LT::OperationType operationType)
	{
		// We reverse every CompareOperation. This is necessary to simplify our life in ParseIfElse.
		switch (operationType)
		{
		case LT::EQUALLY:
			funcCode = funcCode + NOT_EQU(ELSE_LABEL + std::to_string(currentIf));
			break;
		case LT::NON_EQUALLY:
			funcCode = funcCode + EQU(ELSE_LABEL + std::to_string(currentIf));
			break;
		case LT::MORE:
			funcCode = funcCode + LESS(ELSE_LABEL + std::to_string(currentIf));
			break;
		case LT::LESS:
			funcCode = funcCode + MORE(ELSE_LABEL + std::to_string(currentIf));
			break;
		case LT::MORE_OR_EQUAL:
			funcCode = funcCode + LESS_EQU(ELSE_LABEL + std::to_string(currentIf));
			break;
		case LT::LESS_OR_EQUAL:
			funcCode = funcCode + MORE_EQU(ELSE_LABEL + std::to_string(currentIf));
			break;
		default:
			funcCode = funcCode + BOOL(ELSE_LABEL + std::to_string(currentIf));
			break;
		}
	}
#pragma endregion

	void AsmHead::AddLib(IT::Entry& entryId, int lexTablePosition)
	{
		libs = libs + INCLUDE_LIB(ValueToString(entryId));
	}

#pragma region CodeGenerationActions
	void CodeGenerationData::StartCode(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		for (; iteratorStoreState != storeState.end(); i++)
		{
			if (i->lenta_position >= lexTablePosition)
			{
				lexTablePosition = i->lenta_position;
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
					code.entryTempFunctionData.EndFunction(idTable, lexTable.table[lexTablePosition + 1].idxTI);
					code.AddFunction(code.entryTempFunctionData);
					code.ResetInfoAboutFunction();
					break;
				}
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
		code.entryTempFunctionData.WriteLineToGenerate(lexTable, lexTablePosition);
		switch (nrulechain)
		{
		case Irule_DECL_AND_INIT:
		case Irule_INIT:
			// Run on Lexemas for found posistion of the Assignment of Expression.
			while (lexTable.table[lexTablePosition].lexema != LEX_ASSIGNMENT)
				lexTablePosition++;
			code.entryTempFunctionData.ParseExpression(lexTable, idTable, lexTablePosition + 1, false);
			// Execute the Assignment.
			code.entryTempFunctionData.PopVar(idTable.table[lexTable.table[lexTablePosition - 1].idxTI], lexTable.table[lexTablePosition - 1].idxTI);
			break;
		case Irule_CALL_FUNCTION:
			code.entryTempFunctionData.ParseExpression(lexTable, idTable, lexTablePosition, true);
			break;
		case Irule_IF:
		case Irule_IF_ELSE:
			code.entryTempFunctionData.funcCode = code.entryTempFunctionData.funcCode + code.entryTempFunctionData.ParseIfElse(lexTable, idTable, lexTablePosition);
			break;
		}
	}

	void  CodeGenerationData::WriteCodeGeneration()
	{
		time_t rawtime;
		struct tm timeinfo;
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		*streamOut << "; Генерация выполнена успешно. ";
		strftime(buffer, 300, "Дата: %d.%m.%Y %H:%M:%S", &timeinfo);
		*streamOut << buffer << endl;
		*streamOut << head.begin;
		*streamOut << head.libs;
		*streamOut << head.protos;
		*streamOut << head.consts;
		*streamOut << head.data;
		*streamOut << code.codeBegin;
		for (unsigned int i = 0; i < code.codeArray.size(); i++)
		{
			*streamOut << code.codeArray[i].funcBegin;
			*streamOut << code.codeArray[i].funcCode;
			*streamOut << code.codeArray[i].funcEnd;
		}
		*streamOut << code.codeEnd;

		streamOut->close();
	}
#pragma endregion
}