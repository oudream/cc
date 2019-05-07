#ifndef DEFCINTERINFO_H
#define DEFCINTERINFO_H


#include "defcglobal.h"
#include "defcansi.h"


#define GM_INTERINFO_MAX_OUT 1024



typedef int (* GFN_INTERINFO_OUT)(const char*);
typedef int (* GFN_INTERINFO_IN)(DataType_Enum , ...);



extern GFN_INTERINFO_OUT gfn_interinfo_outView_callback;
extern GFN_INTERINFO_OUT gfn_interinfo_outLog_callback;
extern GFN_INTERINFO_IN gfn_interinfo_inView_callback;

extern char* gc_char_format_names[9];



int gfn_interinfo_out( const char*, ... );

int gfn_interinfo_in( DataType_Enum , ... );



///---
///define GM_INTERINFO_XXX
///---

#ifdef PROJECT_BUILD_TYPE_DEBUG

#define GM_INTERINFO_DEBUG_CHECK( p ) \
    printf( #p ); printf(p ? " = true" : " = false");

#define GM_INTERINFO_DEBUG_VALUE( p , dte ) \
    printf( #p ); printf( "=" ); printf( gc_char_format_names[dte], p );

#define GM_INTERINFO_DEBUG_PORMPT( s ) \
    printf( s );

#define GM_INTERINFO_DEBUG_PORMPT1( s , v1 ) \
    printf( s , v1 );

#define GM_INTERINFO_DEBUG_PORMPT2( s , v1, v2 ) \
    printf( s , v1, v2 );

#define GM_INTERINFO_DEBUG_PORMPT3( s , v1, v2, v3 ) \
    printf( s , v1, v2, v3 );


#else

#define GM_INTERINFO_DEBUG_CHECK( p )
#define GM_INTERINFO_DEBUG_VALUE( p , dte )
#define GM_INTERINFO_DEBUG_PORMPT( s )
#define GM_INTERINFO_DEBUG_PORMPT1( s , v1 )
#define GM_INTERINFO_DEBUG_PORMPT2( s , v1, v2 )
#define GM_INTERINFO_DEBUG_PORMPT3( s , v1, v2, v3 )

#endif


#endif //defcinterinfo_h
