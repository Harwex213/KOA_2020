#include "stdafx.h"

namespace LT							// таблица лексем
{
	void AddEntry(LexTable& lextable, Entry& entry)
	{
		lextable.table.push_back(entry);
		lextable.current_size++;
	};

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	};

	void Delete(LexTable& lextable)
	{
		lextable.table.clear();
		lextable.table.shrink_to_fit();
	};

	char GetOperationSymbol(const Entry& entry)
	{
		switch (entry.operationType)
		{
		case PLUS:
			return SYMBOL_PLUS;
			break;
		case MINUS:
			return SYMBOL_MINUS;
			break;
		case MULTIPLY:
			return SYMBOL_MULTIPLY;
			break;
		case DIVISION:
			return SYMBOL_DIVISION;
			break;
		case EQUALLY:
			return SYMBOL_EQUALLY;
			break;
		case NON_EQUALLY:
			return SYMBOL_NON_EQUALLY;
			break;
		case MORE:
		case MORE_OR_EQUAL:
			return SYMBOL_MORE;
			break;
		case LESS:
		case LESS_OR_EQUAL:
			return SYMBOL_LESS;
			break;
		case OR:
			return SYMBOL_OR;
			break;
		case AND:
			return SYMBOL_AND;
			break;
		case INVERSION:
			return SYMBOL_INVERSION;
			break;
		default:
			return NULL;
			break;
		}
	}
}