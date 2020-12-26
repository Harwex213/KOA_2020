#include "stdafx.h"
#define GRB_ERROR_SERIES 140

namespace GRB
{
	Greibach greibach(
		NS('S'),
		TS('$'),
		11,
		Rule(
				// Functions and Main.
				// 0
				NS('S'),
				GRB_ERROR_SERIES + 1,
				5,
				// Include.
				// 0
				Rule::Chain(3, TS('d'), TS('l'), NS('S')),
				// Prototype.
				// 1
				Rule::Chain(8, TS('t'), TS('p'), TS('i'), TS('('), NS('P'), TS(')'), TS(';'), NS('S')),
				// Function.
				// 2
				Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), NS('P'), TS(')'), TS('{'), NS('I'), NS('R'), TS('}'), NS('S')),
				// Main.
				// 3
				Rule::Chain(6, TS('m'), TS('{'), NS('I'), NS('R'), TS('}'), NS('S')),
				Rule::Chain()
			),
		Rule(
				// Instructions. 
				// 1
				NS('I'),
				GRB_ERROR_SERIES + 2,
				7,
				// Declaration and assignment.
				// 0
				Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('I')),
				// Declaration.
				// 1
				Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('I')),
				// Assignment.
				// 2
				Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('I')),
				// Calling Function.
				// 3
				Rule::Chain(6, TS('i'), TS('('), NS('C'), TS(')'), TS(';'), NS('I')),
				// if -> else
				// 4
				Rule::Chain(13, TS('q'), TS('('), NS('E'), NS('X'), TS(')'), TS('{'), NS('I'), TS('}'), TS('e'), TS('{'), NS('I'), TS('}'), NS('I')),
				// if.
				// 5
				Rule::Chain(9, TS('q'), TS('('), NS('E'), NS('X'), TS(')'), TS('{'), NS('I'), TS('}'), NS('I')),
				Rule::Chain()
			),
		Rule(
				// Expressions.
				// 2
				NS('E'),
				GRB_ERROR_SERIES + 3,
				7,
				// Identificator.
				Rule::Chain(2, TS('i'), NS('O')),
				// Literal.
				Rule::Chain(2, TS('l'), NS('O')),
				// Calling Function.
				Rule::Chain(5, TS('i'), TS('('), NS('C'), TS(')'), NS('O')),
				// Expression in Parenthesis.
				Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('O')),
				// Identificator with Unary.
				Rule::Chain(3, TS('b'), TS('i'), NS('O')),
				// Literal with Unary.
				Rule::Chain(3, TS('b'), TS('l'), NS('O')),
				// Calling Function with Unary.
				Rule::Chain(6, TS('b'), TS('i'), TS('('), NS('C'), TS(')'), NS('O'))
			),
		Rule(
				// Return.
				// 3
				NS('R'),
				GRB_ERROR_SERIES + 7,
				4,
				Rule::Chain(3, TS('r'), TS('i'), TS(';')),
				Rule::Chain(3, TS('r'), TS('l'), TS(';')),
				// Identificator with Unary.
				Rule::Chain(4, TS('r'), TS('b'), TS('i'), TS(';')),
				// Literal with Unary.
				Rule::Chain(4, TS('r'), TS('b'), TS('l'), TS(';'))
			),
		Rule(
				// Arithmetic and Logic Binary Operations.
				NS('O'),
				GRB_ERROR_SERIES + 3,
				2,
				// Binaries: {+ - * / | &}
				Rule::Chain(3, TS('v'), NS('U'), NS('E')),
				Rule::Chain()
			),
		Rule(
				// Compare Operations.
				NS('X'),
				GRB_ERROR_SERIES + 3,
				2,
				// Comparisons: { > < >= <= }
				Rule::Chain(3, TS('g'), NS('U'), NS('E')),
				Rule::Chain()
		),
		Rule(
				// Unary Operations
				NS('U'),
				GRB_ERROR_SERIES + 3,
				2,
				// { ~ }
				Rule::Chain(1, TS('b')),
				Rule::Chain()
		),
		Rule(
				// Params while creating.
				NS('P'),
				GRB_ERROR_SERIES + 4,
				2,
				Rule::Chain(3, TS('t'), TS('i'), NS('B')),
				Rule::Chain()
			),
		Rule(
				// Params while calling.
				NS('C'),
				GRB_ERROR_SERIES + 5,
				7,
				Rule::Chain(3, TS('i'), NS('O'), NS('A')),
				Rule::Chain(5, TS('i'), TS('('), NS('C'), TS(')'), NS('A')),
				Rule::Chain(3, TS('l'), NS('O'), NS('A')),
				Rule::Chain(4, TS('b'), TS('i'), NS('O'), NS('A')),
				Rule::Chain(6, TS('b'), TS('i'), TS('('), NS('C'), TS(')'), NS('A')),
				Rule::Chain(4, TS('b'), TS('l'), NS('O'), NS('A')),
				Rule::Chain()
			),
		Rule(
				// Params creating.
				NS('B'),
				GRB_ERROR_SERIES + 4,
				2,
				Rule::Chain(2, TS(','), NS('P')),
				Rule::Chain()
			),
		Rule(
				// Params calling.
				NS('A'),
				GRB_ERROR_SERIES + 5,
				2,
				Rule::Chain(2, TS(','), NS('C')),
				Rule::Chain()
			)
	);

	Greibach getGreibach() { return greibach; }

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;						//����� �������� � int
		for (short i = 0; i < size; i++)
			nt[i] = (GRBALPHABET)p[i];			//����� ����� �������� � short
	}

	Rule::Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...)
	{
		nn = pnn;
		idError = iderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (short i = 0; i < size; i++)
			chains[i] = p[i];
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottomT;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (short i = 0; i < size; i++)
			rules[i] = p[i];
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < this->size && this->rules[k].nn != pnn)
			k++;
		if (k < this->size)
			prule = this->rules[rc = k];
		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < this->size)
			rc = this->rules[n];
		return rc;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];		//������ �����������?
		b[0] = Chain::alphabet_to_char(this->nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getCChain(bchain);		//��� ���������� ������������?
		strcat_s(b, sizeof(bchain) + 5, bchain);	//������ (+5) � ���������� 
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t && chains[j].nt[0] != 0)
			j++;
		rc = (j < size ? j : -1);
		if (rc >= 0)				//����� �� �������� �� (rc != -1)???
			pchain = chains[rc];
		return rc;
	}
	
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
}