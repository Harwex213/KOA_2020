#pragma once
#include "IT.h"
#include "MFST.h"
#include <vector>
#include <string>

#define LIB_NAME_COUNT		1
#define LIB_NAME_DATETIME	"DateTime.lib"

namespace Semantic
{
	struct SemanticData
	{
		IT::IDDATATYPE idDataTypeGeneral = IT::UNDEF;
		IT::IDDATATYPE idDataTypeFunction = IT::UNDEF;
		bool isVoidRule = false;
		int initialPosition = 0;
		int finalPosition = 0;
		std::string libsNameArray[LIB_NAME_COUNT] =  { LIB_NAME_DATETIME };

		void SetGeneralIdDataType(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition, int nrulechain);
		void SetFunctionIdDataType(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition, int nrulechain);
		void AnalyzeExpression(LT::LexTable& lexTable, IT::IdTable& idTable);
		bool CheckOperationType(LT::Entry lexEntry, IT::IDDATATYPE idDataType);
		int AnalyzeFunctionCall(LT::LexTable& lexTable, IT::IdTable& idTable, int initialPosition);
		std::vector<IT::Entry> FillFunctionParams(IT::IdTable& idTable, IT::Entry idEntry);
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable);
	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable);
}