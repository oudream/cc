//#include "defcansi.h"

#include <assert.h>

#include <ctype.h>

#include <errno.h>

#include <float.h>

#include <iso646.h>

#include <limits.h>

#include <locale.h>

#include <math.h>

#include <setjmp.h>

#include <signal.h>

#include <stdarg.h>

#include <stddef.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>


#define GM_PRINT_DATATYPE_SIZE( T ) \
    printf( "name : size / [ %s : %d ]", #T, sizeof( T ))

void testDataType()
{
    printf( "print all Data Type size : ");

    printf( "name : size / [ %s : %d ]", "#TT", sizeof(int));
    GM_PRINT_DATATYPE_SIZE( int ) ;

}

int main(int argc, char *argv[])
{
    printf( "hell begin:\n" );

    char str[] ="<bbbbbbbb><cccccccccc>=0";
    char * pch;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str,"<>");
    while (pch != NULL)
    {
      printf ("%s\n",pch);
      pch = strtok (NULL, "<>");
    }

    printf( "hello end." );

    return 0;
}
