#pragma once
#include "Error.h"
#include "GRB.h"
#include "LT.h"
#include <stack>
#include <string>

#define MFST_DIAGN_MAXSIZE 2 * ERRORMASSAGE_MAX_SIZE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short> MFSTSTSTACK;

static int FST_TRACE_n = -1;
static char rbuf[205]{}, sbuf[205]{}, lbuf[1024]{};

#define MFST_TRACE_START	log.streamParsing->setf(std::ios::left);									\
							log.streamParsing->width (4); *log.streamParsing <<" Шаг"<< ':';					\
							log.streamParsing->width(20); *log.streamParsing <<" Правило";					\
							log.streamParsing->width(30); *log.streamParsing <<" Входная лента";				\
							log.streamParsing->width(20); *log.streamParsing <<" Стек";						\
							*log.streamParsing <<std::endl;

#define MFST_TRACE1			log.streamParsing->setf(std::ios::left);									\
							log.streamParsing->width (4); *log.streamParsing<<++FST_TRACE_n << ": ";			\
							log.streamParsing->width(20); *log.streamParsing<<rule.getCRule(rbuf, nrulechain);\
							log.streamParsing->width(30); *log.streamParsing<<getCLenta(lbuf, lenta_position);\
							log.streamParsing->width(20); *log.streamParsing<<getCSt(sbuf);					\
							*log.streamParsing <<std::endl;

#define MFST_TRACE2			log.streamParsing->setf(std::ios::left);									\
							log.streamParsing->width (4); *log.streamParsing<<FST_TRACE_n<< ": ";				\
							log.streamParsing->width(20); *log.streamParsing<< " ";							\
							log.streamParsing->width(30); *log.streamParsing<<getCLenta(lbuf, lenta_position);\
							log.streamParsing->width(20); *log.streamParsing<<getCSt(sbuf);					\
							*log.streamParsing <<std::endl;

#define MFST_TRACE3			log.streamParsing->setf(std::ios::left);									\
							log.streamParsing->width (4); *log.streamParsing<<++FST_TRACE_n << ": ";			\
							log.streamParsing->width(20); *log.streamParsing<< " ";							\
							log.streamParsing->width(30); *log.streamParsing<<getCLenta(lbuf, lenta_position);\
							log.streamParsing->width(20); *log.streamParsing<<getCSt(sbuf);					\
							*log.streamParsing <<std::endl;

#define MFST_TRACE4(c)		log.streamParsing->width(4);  *log.streamParsing << ++FST_TRACE_n << ": "; log.streamParsing->width(20); *log.streamParsing << c << std::endl;
#define MFST_TRACE5(c)		log.streamParsing->width(4);  *log.streamParsing << FST_TRACE_n   << ": "; log.streamParsing->width(20); *log.streamParsing << c << std::endl;
#define MFST_TRACE6(c,k)	log.streamParsing->width(4);  *log.streamParsing << FST_TRACE_n   << ": "; log.streamParsing->width(20); *log.streamParsing << c << k << std::endl;
#define	MFST_TRACE7			log.streamParsing->width(4);  *log.streamParsing << state.lenta_position<<": ";						\
							log.streamParsing->width(20); *log.streamParsing << rule.getCRule(rbuf, state.nrulechain) << std::endl;

namespace MFST
{
	struct MfstState			// состояние автомата (для сохранения)
	{
		short lenta_position;	// позиция на ленте
		short nrule;			// номер текущего правила
		short nrulechain;		// номер текущей цепочки в тукщем правиле
		MFSTSTSTACK st;			// стек автомата
		
		MfstState();
		MfstState(
			short pposition,	// позиция на ленте
			MFSTSTSTACK pst,	// стек автомата
			short pnrulechain	// номер текущей цепочка в 
		);
		MfstState(
			short pposition,	// позиция на ленте
			MFSTSTSTACK pst,	// стек автомата
			short pnrule,		// номер текущего правила
			short pnrulechain	// номер текущей цепочки в текущем правиле
		);
	};

	struct Mfst					// магазинный автомат
	{
		enum RC_STEP			// код возврата функции step
		{
			NS_OK,				// найдена цепочка и правило, цепочка записана в стек
			NS_NORULE,			// не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN,		// не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,			// неизвестный нетерминальный символ грамматики
			TS_OK,				// текущий символ ленты == вершине стека, подвинулась лента, pop стека
			TS_NOK,				// текущий символ ленты != вершине стека, восстановлено состояние
			LENTA_END,			// текущая позиция ленты >= lenta_size
			SURPRISE			// неожиданный код возврата (ошибка в step)
		};
		
		struct MfstDiagnosis		// диагностика
		{
			short lenta_position;	// позиция на ленте
			RC_STEP rc_step;		// код завершения шага
			short nrule;			// номер правила
			short nrule_chain;		// номер цепочки правила
			
			MfstDiagnosis();		// 
			MfstDiagnosis(			//	
				short	plenta_position,	// позиция на ленте
				RC_STEP prc_step,			// код завершения шага
				short	pnrule,				// номер правила
				short	pnrule_chain		// номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];		// последние самые глубокие сообщения

		GRBALPHABET* lenta;					// перекодированая (TS/NS) лента (из lex)
		short lenta_position;				// текущая позиция на ленте
		short nrule;						// номер текущего правила
		short nrulechain;					// номер текущей цепочки в текущем правиле
		short lenta_size;					// размерз ленты
		GRB::Greibach grebach;				// грамматика Грейбах
		LT::LexTable lex;					// результат работы лексического анализатора
		MFSTSTSTACK st;						// стек автомата
		std::stack<MfstState> storestate;	// стек для сохранения состояний
		
		Mfst();
		Mfst(								
			LT::LexTable plex,				// результат работы лексического анализатора
			GRB::Greibach pgrebach			// грамматика Грейбах
		);

		char* getCSt(char* buf);			// получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25);	// лента: n символов с pos
		char* getDiagnosis(char* buf, short n);		// получить n-ую строку диагностики или 0х00
		bool saveState(Log::LOG log);					// сохранить состояние автомата
		bool restState(Log::LOG log);					// восстановить состояние автомата
		bool push_chain(					// поместить цепочку правила в стек
			GRB::Rule::Chain chain			// цепочка правила
		);
		RC_STEP	step(Log::LOG log);						// выполнить шаг автомата
		bool start(Log::LOG log);						// запустить автомат
		bool saveDiagnosis(
			RC_STEP pprc_step				// код завершения шага
		);
		void printRules(Log::LOG log);					// вывести последовательность правил

		struct Deducation					// вывод
		{
			short size;						// количество шагов в выводе
			short* nrules;					// номер правила грамматики
			short* nrulechains;				// номера цепочек правила грамматики (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;

		bool saveDeducation();				// сохранить дерево вывода
	};
}