#include "stdafx.h"

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM sample;
		wchar_t* temp_in = NULL;
		wchar_t* temp_out = NULL;
		wchar_t* temp_log = NULL;

		bool check_in = false;
		bool check_out = false;
		bool check_log = false;

		if (argc > 1)
		{
			for (int i = 1; i < argc; i++)
			{
				if (wcslen(argv[i]) <= PARM_MAX_SIZE)
				{
					if (!check_in && (temp_in = wcsstr(argv[i], PARM_IN)))
						check_in = true;

					if (!check_out && (temp_out = wcsstr(argv[i], PARM_OUT)))
						check_out = true;

					if (!check_log && (temp_log = wcsstr(argv[i], PARM_LOG)))
						check_log = true;
				}
				else
					throw ERROR_THROW(104);
			}

			if (check_in)
				wcscpy_s(sample.in, (temp_in + wcslen(PARM_IN)));
			else
				throw ERROR_THROW(100);

			if (check_out)
				wcscpy_s(sample.out, (temp_out + wcslen(PARM_OUT)));
			else
			{
				wcscpy_s(sample.out, sample.in);
				wcscat_s(sample.out, PARM_OUT_DEFAULT_EXT);
			}

			if (check_log)
			{
				wcscpy_s(sample.log, (temp_log + wcslen(PARM_LOG)));
				wcsncpy_s(sample.logLexTable, sample.log, wcslen(sample.log) - 4);
				wcscat_s(sample.logLexTable, PARM_LOG_LEXTABLE_EXT);
				wcsncpy_s(sample.logIdTable, sample.log, wcslen(sample.log) - 4);
				wcscat_s(sample.logIdTable, PARM_LOG_IDTABLE_EXT);
			}
			else
			{
				wcscpy_s(sample.log, sample.in);
				wcscat_s(sample.log, PARM_LOG_DEFAULT_EXT);
			}

		}
		else
			throw ERROR_THROW(100);

		return sample;
	}
}