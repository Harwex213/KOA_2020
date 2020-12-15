#pragma once
#include <iostream>
#include <tchar.h>
#include <vector>
#include "IT.h"
#include "LT.h"

namespace FST
{
	struct RELATION								// ребро :символ->вершина графа переходов КА
	{
		char symbol;							// символ перехода
		short nnode;							// номер смежной вершины
		RELATION(char с = 0x00,					// символ перехода
			short ns = NULL);					// новое состояние												
	};

	struct NODE									// вершина графа переходов
	{
		short n_relation;						// количество инциндентных ребер
		RELATION* relations;					// инцидентные ребра; 1 --a--> 2, ребро a инцидентна вершинам 1 и 2
		NODE();
		NODE(
			short n,							// количество инциндентных ребер
			RELATION rel, ...					// список ребер
		);
	};

	struct FST
	{
		IT::IDDATATYPE idDataType = IT::UNDEF;
		LT::OperationType operationType = LT::NONE;
		char lexema;
		char** string;
		short position = 0;
		short nstates;
		NODE* nodes;
		short* rstates;
		FST* nextFST;

		FST();
		FST(
			const char lxm,
			char* &s,							//цепочка (строка, завершатся 0x00 )
			short ns,							//количество состояний автомата 
			NODE n, ...							//список состояний (граф переходов)
		);
	};

	bool execute(								//выполнить распознавание цепочки 
		FST& fst									//недетерминировнный конечный автомат
	);

};
