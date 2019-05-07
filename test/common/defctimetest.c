#include "defcansi.h"
#include "defcglobal.h"

#include <windows.h>


int testExecParams(int argc, char* argv[])
{
    printf( "agrc : %d\n", argc);
    int i;
    for (i = 0; i < argc; ++i)
    {
        printf( "%s\n", argv[i]);
    }
    printf( "\n" );

    return 0;
}


int testWin32GetTime()
{
    clock_t k;

    SYSTEMTIME st;
    memset(&st, 0, sizeof(SYSTEMTIME));


    k = clock();
    printf( "GetSystemTime begin %ld \n", k );

    int i = 0;
    for (i = 0; i < 100000; ++i)
    {
        GetSystemTime(&st);
    }

    k = clock();
    printf( "GetSystemTime end %ld \n", k );



    k = clock();
    printf( "GetSystemTimeAsFileTime begin %ld \n", k );

    FILETIME ft;
    for (i = 0; i < 100000; ++i)
    {
        GetSystemTimeAsFileTime(&ft);
    }

    k = clock();
    printf( "GetSystemTimeAsFileTime end %ld \n", k );

    return 0;
}


int main(int argc, char *argv[])
{
    printf( "hell0 begin:\n" );
    printf( "\n" );


    testExecParams(argc, argv);

    testWin32GetTime();

    char str [80];

    printf ("Please enter your name: ");
    scanf ("%s",str);
    printf ("hello %s!", str);

    printf ( "hell0 end." );

    return 0;
}
