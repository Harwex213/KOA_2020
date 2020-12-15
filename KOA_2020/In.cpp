#include "stdafx.h"

namespace In
{
	IN getin(wchar_t* infile)
	{
		IN sample;
		ifstream file(infile);

		char unsigned txt_temp;
		bool chek_file = false;
		PARSED_WORDS entry;
		ANALYSIS_DATA interimData;

		if (file.is_open())
		{
			while ((txt_temp = file.get()) && !file.eof())
			{
				chek_file = true;
				sample.size++;
				interimData.positionNumber++;
 				AnalyzeLetter(sample.code[txt_temp], txt_temp, interimData, sample);
			}
			int counter_temp = 0;
			sample.alfaLxmTable = new PARSED_WORDS[interimData.specialSymbolCounter];
			for (int i = 0, j = 0; i < interimData.specialSymbolCounter; i++)
			{
				entry.text = new char[sample.symbolsNew[++j] + 1];
				entry.text[sample.symbolsNew[j++]] = NULL;
				counter_temp = 0;
				entry.position = sample.symbolsNew[j++];
				entry.line = sample.symbolsNew[j++];
				while (j != sample.symbolsNew.size() && sample.symbolsNew[j] != interimData.specialSymbol)
				{
					entry.text[counter_temp++] = sample.symbolsNew[j];
					j++;
				}
				AddWord(sample, entry);
			}
			if (!chek_file)
				throw ERROR_THROW(113)
		}
		else
		{
			file.close();
			throw ERROR_THROW(110);
		}
		file.close();
		sample.lines = interimData.lineNumber;
		return sample;
	}

	void AddWord(IN& in, PARSED_WORDS entry)
	{
		in.alfaLxmTable[in.wordCounter].line = entry.line;
		in.alfaLxmTable[in.wordCounter].position = entry.position;
		if (entry.text != NULL)
		{
			in.alfaLxmTable[in.wordCounter].text = new char[strlen(entry.text)];	
			strcpy(in.alfaLxmTable[in.wordCounter].text, entry.text);
		}
		else
			cout << "\nFound NULL in function 'addword' while chek 'entry.text'\n";
		cout << entry.text << "\t\tposition: " << entry.position << "\t" << entry.line << endl;
		in.wordCounter++;
	};

	void AnalyzeLetter(int symbol_type, char symbol, ANALYSIS_DATA& interimData, IN& in)
	{
		switch (symbol_type)
		{
		case IN::T:
			if (interimData.doubleSeparator)
			{
				interimData.ResealWord(in);
				interimData.doubleSeparator = false;
			}
			interimData.tempVector.push_back(symbol);
			interimData.symbolCounter++;
			interimData.wasTrueSymbol = true;
			if (symbol == IN_DOUBLE_QUOTE)
			{
				if (interimData.literalIn)
				{
					if (interimData.wasTrueSymbol)
						interimData.ResealWord(in);
					interimData.literalIn = false;
				}
				else
					interimData.literalIn = true;
			}
			break;
		case IN::F:
			throw ERROR_THROW_IN(111, interimData.lineNumber, interimData.positionNumber);
			break;
		case IN::W:
			if (interimData.literalIn)
			{
				interimData.symbolCounter++;
				interimData.tempVector.push_back(symbol);
			}
			else if (interimData.wasTrueSymbol)
				interimData.ResealWord(in);
			break;
		case IN::S:
			if (!interimData.literalIn)
			{
				if (interimData.doubleSeparator)
				{
					if (symbol != IN_ASSIGNMENT)
						interimData.ResealWord(in);
					interimData.doubleSeparator = false;
				}
				else if (symbol == IN_ASSIGNMENT || symbol == IN_MORE || symbol == IN_LESS || symbol == IN_EXCLAMATION_MARK)
					interimData.doubleSeparator = true;

				if (interimData.wasTrueSymbol)
					interimData.ResealWord(in);

				if (symbol == IN_MINUS && !in.symbolsNew.empty() && *in.symbolsNew.rbegin() == IN_ASSIGNMENT)
					interimData.wasMinus = true;
				else
					interimData.wasMinus = false;
			}

			interimData.tempVector.push_back(symbol);
			interimData.symbolCounter++;
			if (!(interimData.doubleSeparator || interimData.wasMinus) && !interimData.literalIn)
				interimData.ResealWord(in);
			break;
		default:
			if (interimData.literalIn)
				throw ERROR_THROW_IN(111, interimData.lineNumber, interimData.positionNumber)
			else if (interimData.wasTrueSymbol)
				interimData.ResealWord(in);
			interimData.lineNumber++;
			interimData.positionNumber = 0;
			break;
		}
	}
}