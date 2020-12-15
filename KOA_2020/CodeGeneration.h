#pragma once

namespace CodeGeneration
{
	struct CodeGenerationData
	{
		std::string head;
		std::string consts;
		std::string data;
		std::string code;

		void FillHead()
		{

		}
	};

	void Start();
}