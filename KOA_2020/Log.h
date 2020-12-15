#pragma once
#include <fstream>
#include "Parm.h"
#include "In.h"
#include "Error.h"
using namespace std;
#pragma warning(disable: 4996)


namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE]{ L"" };
		wchar_t logLexTableFile[PARM_MAX_SIZE]{ L"" };
		wchar_t logIdTableFile[PARM_MAX_SIZE]{ L"" };
		ofstream* stream{ nullptr };
		ofstream* streamLexTable{ nullptr };
		ofstream* streamIdTable{ nullptr };
	};

	LOG getlog(wchar_t logfile[], wchar_t logLexTableFile[], wchar_t logIdTableFile[]);
	void WriteLine(LOG log, const char* c, ...);
	void WriteLineLexLog(LOG log, const char* c, ...);
	void WriteLine(LOG log, const wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteLogLexTable(LOG log, LT::LexTable lexTable);
	void WriteLogIdTable(LOG log, IT::IdTable idTable);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void WriteError(LOG log, Error::ERROR error);
	void Close(LOG log);
}