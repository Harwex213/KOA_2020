#pragma once
#include "IT.h"
#include "MFST.h"
#include <vector>

namespace Semantic
{
	struct SemanticData
	{
		IT::IDDATATYPE idDataTypeGeneral = IT::UNDEF;
		bool isVoidRule = false;
		int paramCounter = 0;
		int initialPosition = 0;
		int finalPosition = 0;

		void SetGeneralIdDataType(LT::LexTable& lexTable, IT::IdTable& idTable, int lexTablePosition, int nrulechain);
		void AnalyzeExpression(LT::LexTable& lexTable, IT::IdTable& idTable, int initialPosition, int finalPosition);
		bool CheckOperationType(LT::Entry lexEntry, IT::IDDATATYPE idDataType);
		int SetFunctionFinalPosition(LT::LexTable& lexTable, IT::IdTable& idTable, int functionPosition);
		int AnalyzeFunctionCall(LT::LexTable& lexTable, IT::IdTable& idTable, int initialPosition);
		std::vector<IT::Entry> FillFunctionParams(IT::IdTable& idTable, IT::Entry idEntry);
	};

	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable);
	bool CheckFunctionCountParams(int deFactoParamsCount, LT::Entry& entry, const IT::IdTable& idTable);
}