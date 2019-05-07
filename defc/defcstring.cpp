#include "defcstring.h"



int string_isblank(int c)
{
    switch (c) {
    case '\t':
    case '\n':
    case '\v':
    case '\f':
    case '\r':
        return TRUE;
        break;
    default:
        return FALSE;
        break;
    }
    return FALSE;
}

