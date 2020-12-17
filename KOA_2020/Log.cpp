#include "stdafx.h"

namespace Log
{
	LOG getlog(wchar_t logfile[], wchar_t logLexTableFile[], wchar_t logIdTableFile[], wchar_t logParsingFile[])
	{
		LOG temp;
		temp.stream = new ofstream;
		temp.streamLexTable = new ofstream;
		temp.streamIdTable = new ofstream;
		temp.streamParsing = new ofstream;
		temp.stream->open(logfile);
		temp.streamLexTable->open(logLexTableFile);
		temp.streamIdTable->open(logIdTableFile);
		temp.streamParsing->open(logParsingFile);
		if (!temp.stream->is_open() && !temp.streamLexTable->is_open() && !temp.streamIdTable->is_open())
		{
			temp.stream->close();
			temp.streamLexTable->close();
			temp.streamIdTable->close();
			throw ERROR_THROW(112);
		}
		wcscpy_s(temp.logfile, logfile);
		wcscpy_s(temp.logLexTableFile, logLexTableFile);
		wcscpy_s(temp.logIdTableFile, logIdTableFile);

		return temp;
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;

		while (*ptr != "")
		{
			*log.stream << *ptr;
			ptr++;
		}
	}
	void WriteLineLexLog(LOG log, const char* c, ...)
	{
		const char** ptr = &c;

		while (*ptr != "")
		{
			*log.streamLexTable << *ptr;
			ptr++;
		}
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char c_char[PARM_MAX_SIZE];

		while (*ptr != L"")
		{
			wcstombs(c_char, *ptr, sizeof(c_char));
			*log.stream << c_char;
			ptr++;
		}
	}
	void WriteLog(LOG log)
	{
		time_t rawtime;
		struct tm timeinfo;			//структура хранящая текущее время
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//текущая дата в секундах
		localtime_s(&timeinfo, &rawtime);	//текущее локальное время, представленное в структуре

		*log.stream << "----- Протокол ----- ";
		strftime(buffer, 300, " Дата: %d.%m.%Y %H:%M:%S", &timeinfo);
		*log.stream << buffer << " ----- " << endl;
	}
	void WriteLogLexTable(LOG log, LT::LexTable lexTable)
	{
		time_t rawtime;
		struct tm timeinfo;			//структура хранящая текущее время
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//текущая дата в секундах
		localtime_s(&timeinfo, &rawtime);	//текущее локальное время, представленное в структуре

		*log.streamLexTable << "----- Протокол ----- ";
		strftime(buffer, 300, " Дата: %d.%m.%Y %H:%M:%S", &timeinfo);
		*log.streamLexTable << buffer << " ----- " << endl;

		*log.streamLexTable << "Размер: " << lexTable.current_size << endl;
		int counter = 0;
		for (int i = 0; i < lexTable.table[lexTable.current_size - 1].line; i++)
		{
			*log.streamLexTable << lexTable.table[counter].line << ' ';
			while (counter < lexTable.table.size() && lexTable.table[counter].line == i + 1)
			{
				*log.streamLexTable << lexTable.table[counter].lexema;
				if (lexTable.table[counter].lexema == LEX_IDENTIFICATOR || lexTable.table[counter].lexema== LEX_LITERAL)
				{
					*log.streamLexTable << "(" << lexTable.table[counter].idxTI << ")";
				}
				counter++;
			}
			*log.streamLexTable << endl;
		}
	}
	void WriteLogIdTable(LOG log, IT::IdTable idTable)
	{
		time_t rawtime;
		struct tm timeinfo;			//структура хранящая текущее время
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//текущая дата в секундах
		localtime_s(&timeinfo, &rawtime);	//текущее локальное время, представленное в структуре

		*log.streamIdTable << "----- Протокол ----- ";
		strftime(buffer, 300, " Дата: %d.%m.%Y %H:%M:%S", &timeinfo);
		*log.streamIdTable << buffer << " ----- " << endl;

		int StringLength = 35;
		log.streamIdTable->setf(ios::left);
		*log.streamIdTable << endl;
		*log.streamIdTable << "|Params|\n";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "ID Name";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "idx First LE";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Visibility Init";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "DataType";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value UINT";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value FLOAT";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value BOOL";
		*log.streamIdTable << "Value STRING";
		*log.streamIdTable << endl;
		for (int i = 0; i < 7; i++)
			*log.streamIdTable << "-----------------------------------";
		*log.streamIdTable << endl;
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (idTable.table[i].idType == IT::PARAM)
			{
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idName;
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idxfirstLE;
				log.streamIdTable->width(StringLength); *log.streamIdTable << *idTable.table[i].visibility.cbegin();
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idDataType;
				switch (idTable.table[i].idDataType)
				{
				case IT::UINT:
					log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].value.vUint;
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					break;
				case IT::BOOL:
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].value.vBool;
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					break;
				case IT::STRING:
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					*log.streamIdTable << idTable.table[i].value.vString.string;
					break;
				}
				*log.streamIdTable << endl;
			}
		}
		*log.streamIdTable << endl;
		*log.streamIdTable << "|Functions|\n";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "ID Name";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "idx First LE";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Visibility";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Return DataType";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Params ID";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Params Counter";
		log.streamIdTable->width(StringLength); 
		*log.streamIdTable << endl;
		for (int i = 0; i < 7; i++)
			*log.streamIdTable << "-----------------------------------";
		*log.streamIdTable << endl;
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (idTable.table[i].idType == IT::FUNCTION)
			{
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idName;
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idxfirstLE;
				log.streamIdTable->width(StringLength); *log.streamIdTable << *idTable.table[i].visibility.cbegin();
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idDataType;
				int tempCounter = 0;
				auto iterator = idTable.table[i].paramsIdx.begin();
				while (iterator != idTable.table[i].paramsIdx.end())
				{
					*log.streamIdTable << *iterator << ' ';
					iterator++;
					tempCounter += 2;
				}
				log.streamIdTable->width(abs(StringLength - tempCounter)); *log.streamIdTable << ' ';
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].functionParamsCount;
				log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
				*log.streamIdTable << endl;
			}
		}
		*log.streamIdTable << endl;
		*log.streamIdTable << "|Variables|\n";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Name";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "idx First LE";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Visiblity";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "DataType";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value UINT";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value FLOAT";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value BOOL";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value STRING";
		*log.streamIdTable << endl;
		for (int i = 0; i < 7; i++)
			*log.streamIdTable << "-----------------------------------";
		*log.streamIdTable << endl;
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (idTable.table[i].idType == IT::VARIABLE)
			{
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idName;
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idxfirstLE;
				log.streamIdTable->width(StringLength); *log.streamIdTable << *idTable.table[i].visibility.cbegin();
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idDataType;
				switch (idTable.table[i].idDataType)
				{
				case IT::UINT:
					log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].value.vUint;
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					break;
				case IT::BOOL:
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].value.vBool;
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					break;
				case IT::STRING:
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].value.vString.string;
					break;
				}
				*log.streamIdTable << endl;
			}
		}
		*log.streamIdTable << endl;
		*log.streamIdTable << "|Literals|\n";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Name";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "idx First LE";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Visibility";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "DataType";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value UINT";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value FLOAT";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value BOOL";
		log.streamIdTable->width(StringLength); *log.streamIdTable << "Value STRING";
		*log.streamIdTable << endl;
		for (int i = 0; i < 7; i++)
			*log.streamIdTable << "-----------------------------------";
		*log.streamIdTable << endl;
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (idTable.table[i].idType == IT::LITERAL)
			{
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idName;
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idxfirstLE;
				log.streamIdTable->width(StringLength); *log.streamIdTable << *idTable.table[i].visibility.cbegin();
				log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].idDataType;
				switch (idTable.table[i].idDataType)
				{
				case IT::UINT:
					log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].value.vUint;
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					break;
				case IT::BOOL:
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].value.vBool;
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					break;
				case IT::STRING:
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << "-";
					log.streamIdTable->width(StringLength); *log.streamIdTable << idTable.table[i].value.vString.string;
					break;
				}
				*log.streamIdTable << endl;
			}
		}
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char c_char[PARM_MAX_SIZE];
		*log.stream << "----- Параметры ----- " << endl;
		wcstombs(c_char, parm.log, sizeof(c_char));
		*log.stream << "-log: " << c_char << endl;
		wcstombs(c_char, parm.out, sizeof(c_char));
		*log.stream << "-out: " << c_char << endl;
		wcstombs(c_char, parm.in, sizeof(c_char));
		*log.stream << "-in: " << c_char << endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "----- Исходные данные ----- " << endl;
		*log.stream << "Количество символов: " << in.size << endl;
		*log.stream << "Проигнорировано: " << in.ignor << endl;
		*log.stream << "Количество строк: " << in.lines << endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		bool chek_smb = false;
		if (error.inext.line != -1)
			chek_smb = true;
		if (log.stream != NULL && log.stream->is_open())
		{
			*log.stream << "Ошибка " << error.id << ": " << error.message << endl;
			if (chek_smb)
				*log.stream << "строка: " << error.inext.line << " позиция: " << error.inext.col;
		}
		else
		{
			cout << "Ошибка " << error.id << ": " << error.message << endl;
			if (chek_smb)
				cout << "строка: " << error.inext.line << " позиция: " << error.inext.col;
		}
	}
	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
		log.stream = NULL;
	}
}