#pragma once
#include <vector>
#pragma warning(disable: 4996)

#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL	'\n'
#define	IN_VERT_LINE	'|'
#define	IN_NULL_STR	'\0'
#define IN_EXCLAMATION_MARK '!'
#define IN_DOUBLE_QUOTE '"'
#define IN_ASSIGNMENT '='
#define IN_MORE '>'
#define IN_LESS '<'
#define IN_MINUS '-'
#define IN_POINT '.'
#define IN_COMMA ','

/*	SYMBOLS:
	[a-z] [A-Z] [0-9] _ .	: " #			TRUE SYMBOLS/Long Symbols	(T)
	пробел табул€ци€						WHITESPACE/Wait				(W)
	+ - * / () {} [] ; , | & ~ = <>	~ ^	!	SEPARATORS/					(S)
	F										FALSE SYMBOLS/Error			(F)
*/
#define IN_CODE_TABLE {\
/* 0  | 1-a | 2-b | 3-c | 4-d | 5-e |  6  |  7  | 8-h |  9  |  A  |  B  |  C  |  D  |  E  |  F  |    */\
 IN::T,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::W,  '|',IN::F,IN::F,IN::F,IN::F,IN::F, /*0*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*1*/\
 IN::W,IN::S,IN::T,IN::T,IN::F,IN::T,IN::S,IN::T,IN::S,IN::S,IN::S,IN::S,IN::S,IN::S,IN::T,IN::S, /*2*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::S,IN::S,IN::S,IN::S,IN::S, /*3*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*4*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::S,IN::T,IN::S,IN::S,IN::T, /*5*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*6*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::S,IN::S,IN::S,IN::S,IN::F, /*7*/\
     																								   \
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*8*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*9*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::T,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*A*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::T,IN::T,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*B*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*C*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*D*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*E*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*F*/\
}

namespace In
{
	struct PARSED_WORDS
	{
		char* text;			 //word
		int position = 0;	 //Position of word
		int line = 0;		 //Line of word
	};

	struct IN
	{
		int size = 0;
		int ignor = 0;
		int	lines = 1;

		enum { L = 64, A = 128, S = 256, W = 512, T = 1024, F = 2048, I = 4096 };
		int code[256] = IN_CODE_TABLE;

		std::vector<short> symbolsNew;
		int wordCounter = 0;
		PARSED_WORDS* alfaLxmTable;
	};

	struct ANALYSIS_DATA
	{
		int symbolCounter = 0;
		int positionNumber = 0;
		int lineNumber = 1;
		bool literalIn = false;
		bool doubleSeparator = false;
		bool wasTrueSymbol = false;
		bool wasAssignment = false;
		bool wasMinus = false;
		bool shiftPosition = false;
		std::vector<short> tempVector;
		char specialSymbol = -128;
		int specialSymbolCounter = 0;

		void ResealWord(IN& in)
		{
			tempVector.insert(tempVector.begin(), lineNumber);
			int temp = positionNumber;
			if (symbolCounter > 1)
				temp = temp - symbolCounter;
			if (shiftPosition)
				temp--;
			tempVector.insert(tempVector.begin(), temp);
			tempVector.insert(tempVector.begin(), symbolCounter);
			tempVector.insert(tempVector.begin(), specialSymbol);
			specialSymbolCounter++;
			in.symbolsNew.insert(in.symbolsNew.end(), tempVector.begin(), tempVector.end());
			tempVector.clear();
			symbolCounter = 0;
			wasTrueSymbol = false;
			shiftPosition = false;
		}
	};

	IN getin(wchar_t* infile);
	void AddWord(IN& in, PARSED_WORDS entry);
	void AnalyzeLetter(int symbol_type, char symbol, ANALYSIS_DATA& interimData, IN& in);
}