#include "stdafx.h"

namespace CodeGeneration
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable, wchar_t outfile[])
	{
		CodeGenerationData data;
		data.streamOut->open(outfile);
		if (data.streamOut->fail())
			throw ERROR_THROW(114);
		data.FillStandartLines();
		data.FillDataAndProtos(idTable, lexTable);
		data.GetStoreState(mfst);
		// Dosn't make all.
		data.StartCode(lexTable, idTable);
		data.WriteCodeGeneration();
	}
}