#include "defcinterinfo.h"


GFN_INTERINFO_OUT gfn_interinfo_outView_callback = 0;
GFN_INTERINFO_OUT gfn_interinfo_outLog_callback = 0;
GFN_INTERINFO_IN gfn_interinfo_inView_callback = 0;


char* gc_char_format_names[9] = {"%d", "%d", "%d", "%ld", "%d", "%f", "%f", "%ld", "%s"};

int gfn_interinfo_out( const char* sFormat, ... )
{
    static char gs_InterinfoOut[GM_INTERINFO_MAX_OUT];
    memset(gs_InterinfoOut,0,GM_INTERINFO_MAX_OUT);
    va_list argv;
    int n;
    va_start(argv, sFormat);
    n = vsprintf(gs_InterinfoOut, sFormat, argv);
    va_end(argv);
    if (gfn_interinfo_outView_callback)
    {
        gfn_interinfo_outView_callback(gs_InterinfoOut);
    }
    if (gfn_interinfo_outLog_callback)
    {
        gfn_interinfo_outLog_callback(gs_InterinfoOut);
    }
    return 0;
}


int gfn_interinfo_in(DataType_Enum dte, ...)
{
    va_list argv;
    int n;
    va_start(argv, dte);
    if (gfn_interinfo_inView_callback)
    {
        gfn_interinfo_inView_callback(dte, argv);
    }
    va_end(argv);
}
