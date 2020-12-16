#include "stdafx.h"

namespace CodeGeneration
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		CodeGenerationData data;
		data.FillStandartLines();
		data.FillDataAndProtos(idTable, lexTable);
		data.GetStoreState(mfst);
		data.StartCode(lexTable, idTable);
		data.EndCode();
		data.WriteCodeGeneration();
	}
}