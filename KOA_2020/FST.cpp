#include "stdafx.h"

namespace FST
{
	RELATION::RELATION(char c, short ns)
	{
		symbol = c;
		nnode = ns;
	}
	NODE::NODE()
	{
		n_relation = 0;
		RELATION* relations = NULL;
	}
	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* ptr = &rel;
		relations = new RELATION[n];
		for (int i = 0; i < n; ++i, ptr++)relations[i] = *ptr;
	}
	FST::FST()
	{
		lexema = '\0';
		string = NULL;
		nstates = 0;
		nodes = NULL;
		rstates = NULL;
		nextFST = NULL;
	}
	FST::FST(const char lxm, char* &s, short ns, NODE n, ...)
	{
		lexema = lxm;
		string = &s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE* ptr = &n;
		for (int i = 0; i < ns; ++i)nodes[i] = ptr[i];
		rstates = new short[ns];								//why new?
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
		nextFST = NULL;
	}

	bool step(FST& fst, short*& rstates)						// один шаг автомата
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);						// смена массивов 

		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[0][fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
				};
		};
		return rc;
	};

	bool execute(FST& fst)				// выполнить распознавание цепочки
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen(*(fst.string));
		bool rc = true;

		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;										// продинули позицию
			rc = step(fst, rstates);							// один шаг автомата
		}

		delete[] rstates;
		if (rc)
			if (!(fst.rstates[fst.nstates - 1] == lstring))
				rc = false;
		memset(fst.rstates, 0xff, sizeof(short) * fst.nstates);
		fst.rstates[0] = 0;
		fst.position = -1;
		return rc;
	}
};