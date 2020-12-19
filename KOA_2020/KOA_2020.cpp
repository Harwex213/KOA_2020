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
		log = Log::getlog(parm.log, parm.logLexTable, parm.logIdTable, parm.logParsing);

		// Lex Analysis Stage.
		In::IN in = In::getin(parm.in);
		LT::LexTable lexTable;
		IT::IdTable idTable;
		IT::SetLibFunctions(idTable);
		LexAnalysis::Lexer(in, lexTable, idTable);

		// Write results Stage.
		Log::WriteLineLexLog(log, "...Лексический анализ произведён без ошибок...\n", "");
		Log::WriteLogLexTable(log, lexTable);
		Log::WriteLogIdTable(log, idTable);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);

		// Parse Stage.
		MFST::Mfst mfst(lexTable, GRB::getGreibach());
		if (!mfst.start(log))
			throw ERROR_THROW(140);
		mfst.printRules(log);

		// Polish Notation Stage.
		PolishNotation::TransformToPolishNotation(mfst, lexTable, idTable);
		Log::WriteLineLexLog(log, "...Преобразование выражений в вид польской обратной записи...\n", "");
		Log::WriteLogLexTable(log, lexTable);

		// Semantic Stage.
		Semantic::Start(mfst, lexTable, idTable);

		//// Code Generation Stage.
		//CodeGeneration::Start(mfst, lexTable, idTable);

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