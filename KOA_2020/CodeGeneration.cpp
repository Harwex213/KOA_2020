#include "stdafx.h"

namespace CodeGeneration
{
	void Start(MFST::Mfst& mfst, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		CodeGenerationData data;
		data.FillStandartLines();
		data.FillData(idTable, lexTable);
		data.StartCode();
		data.EndCode();
		data.WriteCodeGeneration();
	}
}