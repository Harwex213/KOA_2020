#pragma once
#define	PARM_IN					L"-in:"	
#define	PARM_OUT				L"-out:"
#define	PARM_LOG				L"-log:"
#define	PARM_MAX_SIZE			300
#define	PARM_OUT_DEFAULT_NAME	L"../KOA_2020_asm/KOA_2020.asm"
#define	PARM_LOG_DEFAULT_EXT	L".log"
#define	PARM_LOG_LEXTABLE_EXT	L".lexTable.txt"
#define	PARM_LOG_IDTABLE_EXT	L".idTable.txt"
#define	PARM_LOG_PARSING_EXT	L".parsing.txt"

namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
		wchar_t logLexTable[PARM_MAX_SIZE];
		wchar_t logIdTable[PARM_MAX_SIZE];
		wchar_t logParsing[PARM_MAX_SIZE];
	};

	PARM getparm(int argc, wchar_t* argv[]);
}