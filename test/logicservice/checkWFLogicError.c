#include "defcansi.h"
#include "defcglobal.h"

char * f_WFLogiceErrorBuffer = 0;
int f_WFLogiceErrorSize = 0;

#define MAX_WFLOGICE_ERROR_COUNT 1024
char * f_WFLogiceErrors[MAX_WFLOGICE_ERROR_COUNT];
int f_WFLogiceErrorCount = 0;


int loadWFLogicErrors()
{
    int i = 0;
    for (; i < MAX_WFLOGICE_ERROR_COUNT; ++i)
    {
        f_WFLogiceErrors[i] = 0;
    }

    char * pchIndex = f_WFLogiceErrorBuffer;
    char * pchEnd = f_WFLogiceErrorBuffer + f_WFLogiceErrorSize - 1;
    int iStep = 0;
    char * numberFirst = 0;
    char * numberEnd = 0;
    char * contentFirst = 0;
    char * contentEnd = 0;
    f_WFLogiceErrorCount = 0;
    while ( pchIndex <= pchEnd )
    {
        switch (iStep)
        {
        case 0:
            if ( * pchIndex >= '0' || * pchIndex <= '9' )
            {
                numberFirst = pchIndex;
                numberEnd = 0;
                iStep = 1;
            }
            break;
        case 1:
            if ( * pchIndex == '=' || * pchIndex == ' ' )
            {
                if ( * pchIndex == '=')
                {
                    contentFirst = pchIndex + 1;
                    contentEnd = 0;
                    iStep = 2;
                }
                if ( numberEnd == 0 )
                {
                    numberEnd = pchIndex;
                    * pchIndex = 0;
                }
            }
            break;
        case 2:
            if ( * pchIndex == '\r' || * pchIndex == '\n' || pchIndex == pchEnd )
            {
                if ( contentEnd == 0 )
                {
                    contentEnd = pchIndex - 1;
                    * pchIndex = 0;
                    int iNumber = atoi(numberFirst);
                    if (iNumber != 0 && iNumber < MAX_WFLOGICE_ERROR_COUNT)
                    {
                        if (contentEnd - contentFirst + 1 > 0)
                        {
                            f_WFLogiceErrors[iNumber] = contentFirst;
                            f_WFLogiceErrorCount ++;
                        }
                    }
                }
                iStep = 0;
            }
            break;
        default:
            break;
        }
        pchIndex ++;
    }
    return f_WFLogiceErrorCount;
}

int loadWFLogicErrorBuffer()
{
    FILE * pFile;
    size_t lSize;
    char * buffer;
    long bufferSize;
    size_t result;

    pFile = fopen ( "logicError.fil" , "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    bufferSize = sizeof(char)*lSize + 1;
    buffer = (char*) malloc (bufferSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    /* the whole file is now loaded in the memory buffer. */

    // terminate
    fclose (pFile);

    if (f_WFLogiceErrorBuffer)
    {
        free ( f_WFLogiceErrorBuffer );
        f_WFLogiceErrorBuffer = 0;
    }
    f_WFLogiceErrorBuffer = buffer;
    f_WFLogiceErrorSize = bufferSize;

    return loadWFLogicErrors();
}


