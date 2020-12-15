#include "stdafx.h"

namespace Out 
{
	OUT getout(wchar_t outfile[])
	{
		OUT temp;
		temp.stream = new ofstream;
		temp.stream->open(outfile);
		if (!temp.stream->is_open())
		{
			temp.stream->close();
			throw ERROR_THROW(114);
		}
		wcscpy_s(temp.logfile, outfile);

		return temp;
	}
	void WriteAnalyze(OUT out, In::IN in, Log::LOG log)
	{
		time_t rawtime;
		struct tm timeinfo;								//структура хранящая текущее время
		char buffer[PARM_MAX_SIZE];
		time(&rawtime);									//текущая дата в секундах
		localtime_s(&timeinfo, &rawtime);				//текущее локальное время, представленное в структуре
		*out.stream << endl << "----- Анализ ----- ";
		strftime(buffer, 300, " Дата: %d.%m.%Y %H:%M:%S", &timeinfo);
		*out.stream << buffer << " ----- " << endl;
	}
	void Close(OUT out)
	{
		out.stream->close();
		delete out.stream;
		out.stream = NULL;
	}
}