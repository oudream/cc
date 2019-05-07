#include "defcansi.h"
#include "defcglobal.h"

#include <windows.h>

int main(int argc, char *argv[])
{
    printf( "hell begin:\n" );
    printf( "\n" );
    printf( "agrc : %d\n", argc);
    int i;
    for (i = 0; i < argc; ++i)
    {
        printf( "%s\n", argv[i]);
    }
    printf( "\n" );

//#ifdef _WIN32
//#  if defined(_MSC_VER)
//        struct _timeb tb;
//        _ftime(&tb);
//#  elif defined(__MINGW32__)
//        struct timeb tb;
//        ftime(&tb);
//#  endif
//    msepoch dtNow = static_cast<Int64>(tb.time) * ICE_INT64(1000000) + tb.millitm * 1000);

//    time_t time = static_cast<long>(_usec / 1000000);

//    struct tm* t;
//    t = localtime(&time);

//    char buf[32];
//    buf[31] = 0;
//    strftime(buf, sizeof(buf), "%x %H:%M:%S", t);
//    printf( buf );
//    std::ostringstream os;
//    os << buf << ".";
//    os.fill('0');
//    os.width(3);
//    os << static_cast<long>(_usec % 1000000 / 1000);


    clock_t k;

    SYSTEMTIME st;
    memset(&st, 0, sizeof(SYSTEMTIME));


    k = clock();
    printf( "GetSystemTime begin %d \n", k );

    for (i = 0; i < 100000; ++i)
    {
        GetSystemTime(&st);
    }

    k = clock();
    printf( "GetSystemTime end %d \n", k );



    k = clock();
    printf( "GetSystemTimeAsFileTime begin %d \n", k );

    FILETIME ft;
    for (i = 0; i < 100000; ++i)
    {
        GetSystemTimeAsFileTime(&ft);
    }

    k = clock();
    printf( "GetSystemTimeAsFileTime end %d \n", k );

    char str [80];

    printf ("Enter your family name: ");
    scanf ("%s",str);
    printf ("Enter your age: ");
    scanf ("%d",&i);
    printf ("Mr. %s , %d years old.\n",str,i);
    printf ("Enter a hexadecimal number: ");
    scanf ("%x",&i);
    printf ("You have entered %#x (%d).\n",i,i);

    printf( "hell end." );

    return 0;

}
