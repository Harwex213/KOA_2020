#include "stdafx.h"
//#define DEBUG

namespace MFST
{
	MfstState::MfstState()
	{
		lenta_position = 0;
		nrule = -1;
		nrulechain = -1;
	}

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrulechain = pnrulechain;
	}

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrule = pnrule;
		nrulechain = pnrulechain;
	}

	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		nrule = -1;
		nrule_chain = -1;
	}

	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
	}

	Mfst::Mfst()
	{
		lenta = 0;
		lenta_size = lenta_position = 0;
	}

	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgrebach)
	{
		grebach = pgrebach;
		lex = plex;
		lenta = new short[lenta_size = lex.current_size];

		for (int k = 0; k < lenta_size; k++)
			lenta[k] = TS(lex.table[k].lexema);

		lenta_position = 0;
		st.push(grebach.stbottomT);
		st.push(grebach.startN);
		nrulechain = -1;
	}

	Mfst::RC_STEP Mfst::step(Log::LOG log)
	{
		RC_STEP rc = SURPRISE;
		if (lenta_position < lenta_size)
		{
			if (ISNS(st.top())) //нетерминал?
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain+1)) >= 0)
					{
#ifdef DEBUG
						MFST_TRACE1;
#endif // DEBUG
						saveState(log);
						st.pop();
						push_chain(chain);
						nrulechain = -1;
						rc = NS_OK;
#ifdef DEBUG
						MFST_TRACE2;
#endif // DEBUG
					}
					else
					{
#ifdef DEBUG
						MFST_TRACE4("NS_NORULECHAIN/NS_RULE");
#endif // DEBUG
						saveDiagnosis(NS_NORULECHAIN);
						rc = restState(log) ? NS_NORULECHAIN : NS_NORULE;
					}
				}
				else
				{
					rc = NS_ERROR;
				}
			}
			else if (st.top() == lenta[lenta_position])
			{
				lenta_position++;
				st.pop();
				nrulechain = -1;
				rc = TS_OK;
#ifdef DEBUG
				MFST_TRACE3;
#endif // DEBUG
			}
			else
			{
#ifdef DEBUG
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN");
#endif // DEBUG
				rc = restState(log) ? TS_NOK : NS_NORULECHAIN;
			}
		}
		else
		{
			rc = LENTA_END;
#ifdef DEBUG
			MFST_TRACE4("LENTA_END");
#endif // DEBUG
		}

		return rc;
	}

	bool Mfst::push_chain(GRB::Rule::Chain chain)
	{
		for (int k = chain.size - 1; k >= 0; k--)
		{
			st.push(chain.nt[k]);
		}
		return true; //Почему нельзя сделать void??? И на 132 строке тоже
	}

	bool Mfst::saveState(Log::LOG log)
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain));
#ifdef DEBUG
		MFST_TRACE6("SAVESTATE:", storestate.size());
#endif // DEBUG
		return true;
	}

	bool Mfst::restState(Log::LOG log)
	{
		bool rc = false;

		MfstState state;

		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();

			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;

			storestate.pop();
#ifdef DEBUG
			MFST_TRACE5("RESTSTATE");
			MFST_TRACE2;
#endif // DEBUG
		}

		return rc;
	}

	bool Mfst::saveDiagnosis(RC_STEP prc_step)
	{
		bool rc = false;
		short k = 0;

		while (k < MFST_DIAGN_MAXSIZE && lenta_position <= diagnosis[k].lenta_position)
			k++;

		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k+1; j < MFST_DIAGN_NUMBER; j++)
				diagnosis[j].lenta_position = -1;
		}

		return rc;
	}

	bool Mfst::start(Log::LOG log)
	{
		time_t rawtime;
		struct tm timeinfo;			//структура хранящая текущее время
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//текущая дата в секундах
		localtime_s(&timeinfo, &rawtime);	//текущее локальное время, представленное в структуре

		*log.streamParsing << "----- Протокол ----- ";
		strftime(buffer, 300, " Дата: %d.%m.%Y %H:%M:%S", &timeinfo);
		*log.streamParsing << buffer << " ----- " << endl;

		MFST_TRACE_START;
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step(log);
		
		while(rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
			rc_step = step(log);

		switch (rc_step)
		{
		case MFST::Mfst::LENTA_END:
			MFST_TRACE4("------>LENTA END");
			*log.streamParsing << "------------------------------------------------------------------------------------------   ------" << endl;
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: всего строк %d, синтаксический анализ выполнен без ошибок", 0, lenta_size);
			*log.streamParsing << setw(4) << left << 0 << "всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок" << endl;
			rc = true;
			break;

		case MFST::Mfst::NS_NORULE:
			MFST_TRACE4("------>NS_NORULE");
			*log.streamParsing << "------------------------------------------------------------------------------------------   ------" << std::endl;
			*log.streamParsing << getDiagnosis(buf, 0) << endl;
			*log.streamParsing << getDiagnosis(buf, 1) << endl;
			*log.streamParsing << getDiagnosis(buf, 2) << endl;
			break;

		case MFST::Mfst::NS_NORULECHAIN:
			MFST_TRACE4("------>NS_NORULECHAIN");
			break;

		case MFST::Mfst::NS_ERROR:
			MFST_TRACE4("------>NS_ERROR");
			break;

		case MFST::Mfst::SURPRISE:
			MFST_TRACE4("------>NS_SURPRISE");
			break;
		}

		return rc;
	}
	
	char* Mfst::getCSt(char* buf)
	{
		for (int k = (signed)st.size(); k >= 0; --k)
		{
			MFSTSTSTACK temp_storestate = st;
			short p = 0;
			short j = temp_storestate.size();
				
			while (!temp_storestate.empty() && j-- != k)
				temp_storestate.pop();

			if (!temp_storestate.empty())
			{
				p = temp_storestate.top();
				temp_storestate.pop();
			}
			buf[st.size() - k] = GRB::Rule::Chain::alphabet_to_char(p);
		}

		buf[st.size()] = 0x00;
		return buf;
	}

	char* Mfst::getCLenta(char* buf, short pos, short n)
	{
		short i = 0;
		short k = (pos + n < lenta_size) ? pos + n : lenta_size;

		for (i = pos; i < k; i++)
			buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);

		buf[i - pos] = 0x00;
		return buf;
	}

	char* Mfst::getDiagnosis(char* buf, short n)
	{
		char* rc = (char*)"";
		int errId = 0;
		int lpos = -1;

		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errId = grebach.getRule(diagnosis[n].nrule).idError;
			Error::ERROR err = Error::geterror(errId);
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: строка %d,	%s", err.id, lex.table[lpos].line, err.message);
			rc = buf;
		}

		return rc;
	}

	void Mfst::printRules(Log::LOG log)
	{
		MfstState state;
		GRB::Rule rule;
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			std::stack<MfstState> temp_storestate = storestate;
			short j = temp_storestate.size() - 1;

			while (!temp_storestate.empty() && j-- != k)
				temp_storestate.pop();

			if (!temp_storestate.empty())
			{
				state = temp_storestate.top();
				temp_storestate.pop();
			}

			rule = grebach.getRule(state.nrule);
			log.streamParsing->width(4);  *log.streamParsing << state.lenta_position << ": ";						\
				log.streamParsing->width(20); *log.streamParsing << rule.getCRule(rbuf, state.nrulechain) << std::endl;
		}
	}

	bool Mfst::saveDeducation()
	{
		MfstState state;
		GRB::Rule rule;

		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			std::stack<MfstState> temp_storestate = storestate;
			short j = temp_storestate.size();

			while (!temp_storestate.empty() && j-- != k)
				temp_storestate.pop();
			
			if (!temp_storestate.empty())
			{
				state = temp_storestate.top();
				temp_storestate.pop();
			}

			deducation.nrules[k] = state.nrule;
			deducation.nrulechains[k] = state.nrulechain;
		}

		return true;
	}
}