#include "stdafx.h"
// -in:c:#in\in.txt -out:c:#in\out.txt -log:c:#in\log.txt

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log;
	try
	{
		//std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log, parm.logLexTable, parm.logIdTable);

		// Lex Analysis Stage.
		In::IN in = In::getin(parm.in);
		LT::LexTable lexTable;
		IT::IdTable idTable = IT::Create(TI_MAXSIZE);
		LexAnalysis::Lexer(in, lexTable, idTable);

		// Write results Stage.
		Log::WriteLogLexTable(log, lexTable);
		Log::WriteLogIdTable(log, idTable);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);

		// Parse Stage.
		// For Debug:
		//MFST_TRACE_START;
		MFST::Mfst mfst(lexTable, GRB::getGreibach());
		mfst.start();
		mfst.printRules();

		// Polish Notation Stage.
		PolishNotation::TransformToPolishNotation(lexTable, idTable);
		Log::WriteLineLexLog(log, "...Преобразование выражений в вид польской обратной записи...\n", "");
		Log::WriteLogLexTable(log, lexTable);

		// Clear RAM Stage.
		LT::Delete(lexTable);
		IT::Delete(idTable);

		// Close files Stage.
		Log::Close(log);

		// Time optimization check.
		//std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		//std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration < double >> (t2 - t1);
		//std::cout << time_span.count() << " seconds.";
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}

	return 0;
}