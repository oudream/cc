#include "defcapplication.h"


int gfn_interinfo_outView(const char* sInfo)
{
    printf( sInfo );
    return 0;
}

int gfn_interinfo_inView(DataType_Enum dte, ...)
{
    int iResult = 0;
    va_list argv;
    va_start(argv, dte);
    iResult = scanf(gc_char_format_names[dte], argv);
    va_end(argv);
    return iResult;
}

int DefcApplication::init(int, char * [])
{
    gfn_interinfo_outView_callback = gfn_interinfo_outView;
    gfn_interinfo_inView_callback = gfn_interinfo_inView;
    return 0;
}

int DefcApplication::uninit()
{
    gfn_interinfo_outView_callback = 0;
    gfn_interinfo_inView_callback = 0;
    return 0;
}

