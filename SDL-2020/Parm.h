#pragma once
#include <tchar.h>

#define PARM_IN L"-in:"
#define PARM_OUT L"-out:"
#define PARM_LOG L"-log:"
#define PARM_MFST L"-mfst:"
#define PARM_IDTABLE L"-idtable:"
#define PARM_LEXTABLE L"-lextable:"
#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT L".out"
#define PARM_LOG_DEFAULT_EXT L".log"
#define PARM_TXT_DEFAULT_EXT L".txt"

namespace Parm {
	struct PARM {
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
		wchar_t mfst[PARM_MAX_SIZE];
		wchar_t idtable[PARM_MAX_SIZE];
		wchar_t lextable[PARM_MAX_SIZE];
	};

	PARM getparm(int argc, _TCHAR* argv[]);
}