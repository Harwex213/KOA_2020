#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"
#include <forward_list>

#define FIRST_SYMBOL_TRUE 't'
#define FIRST_SYMBOL_FALSE 'f'
#define SYMBOL_OCT	'e'

#define UINT_MIN 0
#define DEC_NUMBER_SYMBOL 10
#define OCT_NUMBER_SYMBOL 8
#define FIRST_SYMBOL 0
#define RESET_TO_ONE 1

#define LEX_ERROR_SERIES 120
#define SEMANTICS_ERROR_SERIES 400
#define LINE in.alfaLxmTable[i].line
#define POSITION in.alfaLxmTable[i].position

namespace LexAnalysis
{
	enum CheckIdentificatorReturnCode { OK = 1, GLOBAL_DECLARATION = 2, RE_DECLARATION = 3, ALREADY_EXIST = 4, NOT_DECLARED = 5, VARIABLE_ALREADY_DEAD = 6, ID_FUNC_MATCHES_FUNC_LIB = 7, PROTOTYPE_NOT_FOUND = 8};
	enum SetValueReturnCode { SUCCESS = 1, GOING_BEYOND_UINT = 2, GOING_BEYOND_FLOAT = 3, GOING_BEYOND_STRING = 4};
	enum LexemaReturnCode { CLEAR = 1, EXCESS_BRACESRIGHT = 2, EXCESS_SEMICOLON = 3};
	struct AnalysisData
	{
		// See that we are in Function.
		bool functionIn = false;
		// See that we are in ProtoType.
		bool prototypeIn = false;
		// See that need update IdFunction.
		bool functionNeedUpdate = false;
		// See that need update info about function params.
		bool infoFunctionParamsNeedUpdate = false;
		// Id of cureent Function.
		int currentFunctionId = 0;
		// Function Params Counter.
		int functionParamsCounter = 0;
		// Counter main. If > 1 ==> Error.
		int mainWas = 0;
		// Counter braces.
		int bracesCounter = 0;
		// Vars for name-generator for literals.
		char literalIdChar[ID_MAXSIZE] = "L";
		int literalId = 0;
		// Vars for name-generator for Whule.
		std::string whileIdString = "W";
		int whileId = 0;
		// Vars for name-generator for If.
		std::string ifIdString = "I";
		int ifId = 0;
		// Vars for name-generator for Else.
		std::string elseIdString = "E";
		int elseId = 0;
		// Visibility of Identificators.
		std::forward_list<std::string> visibilityList{ STANDART_VISIBILITY };
		// Id of function params.
		std::forward_list<int> paramsIdx;
		// IdType and IdDataType
		IT::IDDATATYPE idDataType = IT::UNDEF;
		IT::IDTYPE idType = IT::U;
	};

	void Lexer(const In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable);
	bool FindGraph(const std::vector<FST::FST*> graph, FST::FST*& temp);
	LexemaReturnCode CheckLexema(const FST::FST& temp, AnalysisData& analysisData, LT::Entry& entryLex);
	void SetIdType_IdDataType_IdxFirstLE(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry, int idxLex, int idxId);
	void SetFunctionParams(AnalysisData& analysisData, int id);
	void SetName(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	void SetVisibility(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	bool ViewVisibility(std::forward_list<std::string> visibilityCurrentId, std::forward_list<std::string> visibilityExistingId);
	SetValueReturnCode SetValue(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	bool CheckOnLibsFunction(char* name);
	CheckIdentificatorReturnCode CheckForIdentificator(const IT::IdTable& idTable, IT::Entry& entryId, AnalysisData& analysisData);
	void SetIdxTI(const IT::IdTable& idTable, const IT::Entry& entryId, LT::Entry& entryLex);
	void SetLexEntry(LT::Entry& entry, char lexema, int line, int position);
	void ResetAnalysisData(AnalysisData& analysisData, IT::Entry& entry);
	void ResetEntryLex(LT::Entry& entry);
	void UpdateFunctionParamsInfo(AnalysisData& analysisData, IT::IdTable& idTable);
}	