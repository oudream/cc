#include "defcansi.h"
#include "defcglobal.h"


int test_readFile()
{
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen ( "temp.txt" , "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    /* the whole file is now loaded in the memory buffer. */

    // terminate
    fclose (pFile);

    printf(buffer);
    printf("\n");

    free (buffer);
}

#include "checkWFLogic.h"

int testCheckWFLogic1()
{
    int iDeviceNormalCount = 0;
    int iDeviceThreeCount = 0;
    int iErrorRow = 0;
    int iErrorColumn = 0;
    int Error = 0;
    char * ErrorDiscribe = 0;


    wfl_loadLDataByFile("ldata.fil");
    Error = wfl_getLastErrorCode();

    iDeviceNormalCount = wfl_getDeviceNormalCount();
    const DeviceNormal * pDeviceNormal = wfl_getDeviceNormals();
    int i = 0;
    for (; i < iDeviceNormalCount; ++i)
    {
        const DeviceNormal * pDevice = & pDeviceNormal[i];
        printf( "DeviceNormal.name : %s\n", pDevice->name );
        printf( "DeviceNormal.hlogic : %s\n", pDevice->hldata );
        printf( "DeviceNormal.llogic : %s\n", pDevice->lldata );
        printf( "\n" );
    }

    iDeviceThreeCount = wfl_getDeviceThreeCount();
    const DeviceThree * pDeviceThree = wfl_getDeviceThrees();
    for (i = 0; i < iDeviceThreeCount; ++i)
    {
        const DeviceThree * pDevice = & pDeviceThree[i];
        printf( "DeviceThree.name : %s\n", pDevice->name );
        printf( "DeviceThree.gjlogic : %s\n", pDevice->gjldata );
        printf( "DeviceThree.gslogic : %s\n", pDevice->gsldata );
        printf( "DeviceThree.sglogic : %s\n", pDevice->sgldata );
        printf( "DeviceThree.sjlogic : %s\n", pDevice->sjldata );
        printf( "DeviceThree.jslogic : %s\n", pDevice->jsldata );
        printf( "\n" );
    }

    printf( "Device Normal Count : %d", iDeviceNormalCount);
    printf( "\n" );
    printf( "Device Three Count : %d", iDeviceThreeCount);
    printf( "\n" );

    char sOperateQueue[] = "2261=1 \n 2271=0 \n 1123=1";
    char sDeviceStateList[] = "2261=0 \n 2271=1 \n 1123=0";
    if(Error >= 0)
    {
        wfl_checkLData(sOperateQueue, sDeviceStateList, 0);
        Error = wfl_getLastErrorCode();
        if(Error < 0)
        {
            ErrorDiscribe = wfl_getErrorString(Error);
            printf("mistake:%s\n",ErrorDiscribe);
        }
    }
    else
    {
        iErrorRow    = wfl_getLastErrorRow();
//        int iErrorColumn = wfl_getLastErrorColumn();
        ErrorDiscribe = wfl_getErrorString(Error);
        printf("µÚ%dÐÐ%s\n",iErrorRow,ErrorDiscribe);
    }
}

int testCheckWFLogic2()
{
//    "101 H:{((1989=0 1,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+(1044=1 S+1045=6 S))}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"           ,
//    "101 H:{(1989=0 1,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+(1044=1 S+1045=6 S))}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"            ,
//    "101 H:{((1989= 1,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+(1044=1 S+1045=6 S))}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"            ,
//    "101 H:{((1989=0 1,1988=1 S + 2046=0 F),(1022=01022=0 S,1023=1 F)+(1044=1 S+1045=6 S))}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"     ,
//    "101 H:{1045=6 S}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"  ,
//    "101 H:{1045=6 S}|2|(100=11,1001=01),(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!" ,
//    "101 H:{1045=6 S}|2|(100=11,1001=01),(1002=01+1003=10)+(1004=01,1005=00));{}1|2001=20,(2202=31+2002=10)!",
//    "101 H:{1045=6 S}|2|(100=11,1001=01),(1002=01+1003=10)+(1004=01,1005=00)){}|1|2001=20,(2202=31+2002=10)!",
//    "101 H:{1045=6 S}|2|(100=11,1001=01),(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,+(2202=31+2002=10)!",
//    "101 H:{1045=6 S}|2|(1a 00=11,1001=01),(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!",
//    "101 H:{((1989=0 F,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+555=0 f)}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"

    char * sLogics[11] = {
        "{((1989=0 1,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+(1044=1 S+1045=6 S))}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"           ,
        "{(1989=0 F,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+(1044=1 S+1045=6 S)}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"            ,
        "{(1989= 1 f,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+(1044=1 S+1045=6 S)}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"            ,
        "{((1989=0 F,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+(1044=1 S+1045=6 S))}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"     ,
        "{1045=1 S}|2|(100=11,1001=01),(1002=01+1003=10)+(1004=01,1005=00);{}|1|2001=20,(2202=31+2002=10)!"  ,
        "{((1989=0 F,1988=1 S + 2046=0 F),(1022=0 S,1023=1 F)+555=0 f)}|2|(100=11,1001=01,(1002=01+1003=10)+(1004=01,1005=00));{}|1|2001=20,(2202=31+2002=10)!"
    };
    int i = 0;
    int Error = 0;
    char * ErrorDiscribe = 0;
    for ( ; i <= 5; i++ )
    {
        char * sFirst = sLogics[i];
        char * sEnd = sFirst + strlen(sFirst) - 1;
        int iResult = wfl_checkStringLogic(sFirst, sEnd);
        printf("%d\n", iResult);
    }
    loadWFLogicErrorBuffer();
    Error = wfl_getLastErrorCode();
    ErrorDiscribe = wfl_getErrorString(Error);
    printf("´íÎó£º%s\n",ErrorDiscribe);
}

#include "reversePolishNotation.h"

void testRPExpression()
{
    char sEx[] = "23+35*3-(2+5*2-6)+1";

    char * sR1 = RPExpression2(sEx);
    printf( "%s\n", sR1);

    char sR[80] = {};
    RPExpression1(sEx, sR);
    printf( "%s\n", sR);
}

int main(int argc, char *argv[])
{
    printf( "hell0 begin:\n" );
    printf( "\n" );

//    char str [80];

//    printf ("Please enter your name: ");
//    scanf ("%s",str);
//    printf ("hello %s begin: ", str);
//    printf ("\n");


    testCheckWFLogic1();


//    testRPExpression();

    printf ( "hello end." );

    return 0;
}

