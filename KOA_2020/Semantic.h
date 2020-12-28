#pragma once
#include "IT.h"
#include "MFST.h"
#include <vector>

namespace Semantic
{
	struct SemanticData
	{
		IT::IDDATATYPE idDataTypeGeneral = IT::UNDEF;
		IT::IDDATATYPE idDataTypeCurrParam = IT::UNDEF;
		bool isParam = false;
		bool isVoidRule = false;
		std::vector<IT::Entry> functionParamArray;
		int paramCounter = 0;
		int initialPosition = 0;
		int finalPosition = 0;

		void SetGeneralIdDataType(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition, int nrulechain);
		void AnalyzeExpression(LT::LexTable& lexTable, IT::IdTable& idTable, int initialPosition, int finalPosition);
		bool CheckOperationType(LT::Entry lexEntry, IT::IDDATATYPE idDataType);
		void FillFunctionParams(IT::IdTable& idTable, IT::Entry idEntry);
		int SetFunctionFinalPosition(LT::LexTable& lexTable, IT::IdTable& idTable, int functionPosition);
		void AnalyzeFunctionCall(LT::LexTable& lexTable, IT::IdTable& idTable, int initialPosition);
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable);
	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable);
}