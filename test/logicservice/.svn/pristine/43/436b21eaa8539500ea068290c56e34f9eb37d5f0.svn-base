#include "checkWFLogic.h"

#include "defcansi.h"
#include "defcglobal.h"

#include "checkWFLogicError.c"

//main step:
//getDevicesLData buffer : (e.g.) device information - name , ldata
//getDevicesState
//checkOperateLogice


//checkOperateLogice step:
//

//--------------------------------------------------------------------------------
//--------define----------
//--------------------------------------------------------------------------------

#define DEVICE_TYPE_NORMAL   0
#define DEVICE_TYPE_THREE    1

#define EXPRESSION_TYPE_CONDITION   0
#define EXPRESSION_TYPE_LOGIC       1

#define operation_l     0   //0
#define operation_h     1   //1
#define operation_gs    2   //0
#define operation_gj    3   //0
#define operation_sg    4   //1
#define operation_sj    5   //0
#define operation_js    6   //0
#define operation_jg    7   //1
#define operation_x     8   //0

#define check_true      ( -1    )
#define check_false     ( -127  )
#define check_error126  ( -126  )
#define check_error125  ( -125  )
#define check_error124  ( -124  )
#define check_error123  ( -123  )
#define check_error122  ( -122  )
#define check_error121  ( -121  )
#define check_error120  ( -120  )
#define check_error119  ( -119  )
#define check_error118  ( -118  )
#define check_error117  ( -117  )
#define check_error116  ( -116  )
#define check_error115  ( -115  )
#define check_error114  ( -114  )
#define check_error113  ( -113  )
#define check_error112  ( -112  )
#define check_error111  ( -111  )
#define check_error110  ( -110  )

#define Error_Bigin     (   -1  )

#define Error_Inter_Begin  (Error_Bigin - MAX_WFLOGICE_ERROR_COUNT - 1)


#define Error_Inter_getErrorString_1  ( Error_Inter_Begin - 0 )
//const char cs_error_inter_getErrorString_1[] = "";

//const char * cs_inter_errors[1] = {
//    c_getErrorString_1
//    };




const int ci_operation_values[9] = {0,1,0,0,1,0,0,1,0};



#define             MAX_DEVICENORMAL_COUNT  4096
int                 f_deviceNormalCount      = 0;
DeviceNormal        f_deviceNormals[MAX_DEVICENORMAL_COUNT];

#define             MAX_DEVICETHREE_COUNT   1024
int                 f_deviceThreeCount       = 0;
DeviceThree         f_deviceThrees[MAX_DEVICETHREE_COUNT];

char *              f_ldataBuffer        = 0;
int                 f_ldataSize          = 0;

OperateItem         f_operateItems[511];
int                 f_operateCount = 0;

int                 f_lastErrorCode = 0;
char *              f_lastErrorDeviceName = 0;
int                 f_lastErrorDeviceEid = 0;
int                 g_logicItemCount = 0;
int                 f_lastErrorRow = 0;
int                 f_lastErrorColumn = 0;


//--------------------------------------------------------------------------------
//--------common method----------
//--------------------------------------------------------------------------------

int errorCode(int iErrorCode)
{
    f_lastErrorCode = iErrorCode;
    return iErrorCode;
}


void setLDataBuffer( char* pBuffer, int iSize )
{
    if (f_ldataBuffer)
    {
        free( f_ldataBuffer );
        f_ldataBuffer = 0;
        f_ldataSize = 0;
    }
    f_ldataBuffer = pBuffer;
    f_ldataSize = iSize;
}

int findDeviceNormalByName(const char* sName, int iNameLength)
{
    int i = 0;
    DeviceNormal * pDevice;
    for (i = 0; i < f_deviceNormalCount; ++i)
    {
        pDevice = & f_deviceNormals[i];
        if (memcmp(pDevice->name, sName, iNameLength) == 0)
        {
            return i;
        }
    }
    return -1;
}

int findDeviceThreeByName(const char* sName, int iNameLength)
{
    int i = 0;
    DeviceThree * pDevice;
    for (i = 0; i < f_deviceThreeCount; ++i)
    {
        pDevice = & f_deviceThrees[i];
        if (memcmp(pDevice->name, sName, iNameLength) == 0)
        {
            return i;
        }
    }
    return -1;
}

int getOperation(const char * sOperation)
{
    char sOperation2[2];
    memcpy(sOperation2, sOperation, 2);
    sOperation2[0] = tolower(sOperation2[0]);
    sOperation2[1] = tolower(sOperation2[1]);

    if ( ! memcmp( sOperation2 , "h" , 1 ) )
    {
        return operation_h;
    }
    else if ( ! memcmp( sOperation2 , "l" , 1 ) )
    {
        return operation_l;
    }
    else if ( ! memcmp( sOperation2 , "gj" , 2 ) )
    {
        return operation_gj;
    }
    else if ( ! memcmp( sOperation2 , "gs" , 2 ) )
    {
        return operation_gs;
    }
    else if ( ! memcmp( sOperation2 , "sg" , 2 ) )
    {
        return operation_sg;
    }
    else if ( ! memcmp( sOperation2 , "sj" , 2 ) )
    {
        return operation_sj;
    }
    else if ( ! memcmp( sOperation2 , "js" , 2 ) )
    {
        return operation_js;
    }
    else
    {
        return -1;
    }
}

void replaceBlank(char* sBuffer, int iSize, const char c)
{
    if (iSize <= 0) return;
    const char* sEnd = sBuffer + iSize - 1;
    char * pch = sBuffer;
    while ( pch <= sEnd )
    {
        if ( * pch >= 0x0A && * pch <= 0x0D ) * pch = c ;
        pch ++;
    }
}

int countCharacter(const char * s, char c)
{
    int i = 0;
    const char * pch = s;
    while ( * pch != 0)
    {
        if ( * pch == c)
            i++;
        pch ++;
    }
    return i;
}

/***
 *param.actionFBSAFirst = 'F' | 'S'
 *return 0 : ok
 *return 1 : name invalid
 *return 2 : charType invalid
 *return 3 : action invalid
 *return 4 : actionFBSAFirst invalid
 ***/
int checkStringExpression(char * sNameFirst, char * sNameEnd, int iCharType, char * sActionFirst, char * sActionEnd, char * sActionFBSAFirst, char * sActionFBSAEnd)
{
    if ( ! ( sNameEnd - sNameFirst + 1 > 0 && sNameEnd - sNameFirst + 1 < 64 ) )
    {
        return 1;
    }
    if ( ( iCharType == 2 || iCharType == 5 ) && ( sActionEnd - sActionFirst + 1 != 1 || sActionFBSAEnd - sActionFBSAFirst + 1 < 1 ) )
    {
        return 2;
    }
    if ( iCharType == 3 && sActionEnd - sActionFirst + 1 != 1 )
    {
        return 3;
    }
    return 0;
}


int wfl_checkStringLogic(char * sLogicFirst, char * sLogicEnd)
{
    ///
    /// \brief checkStringLogic
    /// \param sLogicFirst :
    /// \param sLogicEnd = !
    /// \return
    ///

    char * pch1 = sLogicFirst;
    char iBigBraceDouble = 0;                   // {}
    char iSmallBraceDouble = 0;                 // ()
    int  iStep = 0;
    int  iLogicFirstEqualSign = 0;
//2261 L:{22613=1 S}|2|2030=01;{}|1|22611=00,22612=00,22614=00+(22611=01+22612=01),22614=01!


    while ( pch1 <= sLogicEnd)
    {
        switch ( iStep )
        {
        case 0:
            for(;*pch1 == ' ';)pch1++;
            if(* pch1 == '{')
            {
                iStep = 1;
                iBigBraceDouble++;
            }
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return  Error_Bigin;
            }
            break;
        case 1:
            for(;*pch1 == ' ';)pch1++;
            if(* pch1 == '}')
            {
                iBigBraceDouble--;
                if(iSmallBraceDouble != 0)
                {
                    f_lastErrorColumn = pch1 - sLogicFirst;
                    return Error_Bigin;
                }
                iStep = 5;
                break;
            }
            if(( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-')
            {
                iStep = 2;
                break;
            }
            if( * pch1 == '(')
            {
                iStep = 8;
                iSmallBraceDouble++;
            }
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            break;
         case 2:
            for(pch1 ; * pch1 != '='; pch1++ )
            {
                for(;*pch1 == ' ';)pch1++;
                if(( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-')
                {
                    iLogicFirstEqualSign++;
                    continue;
                }
                else
                {
                    f_lastErrorColumn = pch1 - sLogicFirst;
                    return Error_Bigin;
                }
            }
            if(iLogicFirstEqualSign == 0)             //iLogicFirstEqualSign == 0ʱ,*pch1 == '='.
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            iLogicFirstEqualSign = 0;
            iStep = 3;
            break;
         case 3:
            for(;*pch1 == ' ';)pch1++;
            if(* pch1 >= '0' && * pch1 <= '9')
                iStep = 11;
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            break;
         case 4:
            for(;*pch1 == ' ';)pch1++;
            if(( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ))
            {
                for(;*pch1 == ' ';)pch1++;
                iStep = 1;
            }
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            break;
         case 5:
            for(;*pch1 == ' ';)pch1++;
            if(* pch1 == '|')
                iStep = 6;
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            break;
         case 6:
            for(;*pch1 == ' ';)pch1++;
            if(* pch1 >= '1' && * pch1 <= '9')
                iStep = 7;
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            break;
         case 7:
            for(;*pch1 == ' ';)pch1++;
            if(* pch1 == '|')
            {
                iStep = 8;
                for(;*pch1 == ' ';)pch1++;
                if(* ++pch1 == '!')
                    iStep = 13;
                pch1--;
                break;
            }
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            break;
         case 8:
            for(;*pch1 == ' ';)pch1++;
            if(* pch1 == '(')
            {
                iSmallBraceDouble++;
                iStep = 9;
                break;
            }
            if(( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-')
            {
                pch1--;
                iStep = 9;
            }
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            break;
         case 9:
            for(pch1 ; * pch1 != '='; pch1++ )
            {
                for(;*pch1 == ' ';)pch1++;
                if(( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-')
                {
                    iLogicFirstEqualSign++;
                    continue;
                }
                else
                {
                    f_lastErrorColumn = pch1 - sLogicFirst;
                    return Error_Bigin;
                }
            }
            if(iLogicFirstEqualSign == 0)             //iLogicFirstEqualSign == 0ʱ,*pch1 == '='.
                return f_lastErrorColumn = pch1 - sLogicFirst;
            iLogicFirstEqualSign = 0;
            iStep = 10;
            break;
         case 10:
            for(;*pch1 == ' ';)pch1++;
            if( * pch1 >= '0' && * pch1 <= '9' )
                iStep = 11;
            else
                return Error_Bigin;
            break;
         case 11:
            if( * pch1 == ' ' && iBigBraceDouble == 1)
            {
                for(;*pch1 == ' ';)pch1++;
                if(( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ))
                {
                    iStep = 12;
                    break;
                }
                else
                {
                    f_lastErrorColumn = pch1 - sLogicFirst;
                    return Error_Bigin;
                }
            }
            for(;*pch1 == ' ';)pch1++;
            if( * pch1 >= '0' && * pch1 <= '2' )
            {
                if(* ++pch1 == '!')
                {
                    iStep = 13;
                    --pch1;
                    break;
                }
                --pch1;
                iStep = 12;
            }
            else
                return Error_Bigin;
            break;
         case 12:
            for(;*pch1 == ' ';)pch1++;
            if( * pch1 == '+' || * pch1 == ',')
            {
                iStep = 8;
                break;
            }
            else if( * pch1 == ')')
            {
                iSmallBraceDouble--;
                if(* ++pch1 == ',' || * pch1 == ';' || * pch1 == '!' || * pch1 == '+')
                {
                    iStep = 13;
                    --pch1;
                    break;
                }
                if(* pch1 == '}')
                {
                    iStep = 1;
                    --pch1;
                    break;
                }
                if(* pch1 == ')')
                {
                    iStep = 12;
                    --pch1;
                    break;
                }
                else
                {
                    f_lastErrorColumn = pch1 - sLogicFirst;
                    return Error_Bigin;
                }
            }
            else if( * pch1 == '}')
            {
                iBigBraceDouble--;
                iStep = 5;
            }
            else if( * pch1 == ';')
                iStep = 0;
            else
            {
                f_lastErrorColumn = pch1 - sLogicFirst;
                return Error_Bigin;
            }
            break;
         case 13:
            for(;*pch1 == ' ';)pch1++;
            if( * pch1 == ',' || * pch1 == '+')
            {
                iStep = 8;
                break;
            }
            if( * pch1 == ';')
            {
                iStep = 0;
                break;
            }
            if( * pch1 == '!')
            {
                g_logicItemCount++;
                break;
            }
        }
         pch1++;
    }
    if ( iBigBraceDouble != 0 )
        return Error_Bigin;
    if ( iSmallBraceDouble != 0 )
        return Error_Bigin;
    return 0;
}

int preProcessDevice(char * sNameFirst, char * sNameEnd, char * sActionFirst, char * sActionEnd, char * sLogicFirst, char * sLogicEnd)
{
    int iErrorCode = 0;
    int sNameLength = sNameEnd - sNameFirst + 1;
    if (sNameFirst == 0 || sNameLength > 255 || sNameLength < 1)
    {
        return errorCode(Error_Inter_Begin); // LData Format Error : Device Name Length Invalid;
    }
    iErrorCode = wfl_checkStringLogic(sLogicFirst, sLogicEnd);
    if (iErrorCode)
    {
        return errorCode(Error_Bigin); // LData Format Error : Logic String Invalid;
    }
    char sAction = tolower(* sActionFirst);
    if ( sAction == 'h' || sAction == 'l' )
    {
        int iDeviceIndex = findDeviceNormalByName(sNameFirst, sNameLength);
        if ( iDeviceIndex < 0 )
        {
            if ( f_deviceNormalCount >= MAX_DEVICENORMAL_COUNT )
            {
                return errorCode(Error_Inter_Begin - 2); //MAX_DEVICENORMALCOUNT error
            }
            iDeviceIndex = f_deviceNormalCount;
            f_deviceNormalCount ++;
        }
        f_deviceNormals[ iDeviceIndex ].name = sNameFirst;
        if ( sAction == 'h' )
        {
            f_deviceNormals[ iDeviceIndex ].hldata = sLogicFirst;
        }
        else
        {
            f_deviceNormals[ iDeviceIndex ].lldata = sLogicFirst;
        }
    }
    else if ( sAction == 'g' || sAction == 's' || sAction == 'j' )
    {
        int iDeviceIndex = findDeviceThreeByName(sNameFirst, sNameLength);
        if ( iDeviceIndex < 0 )
        {
            if ( f_deviceThreeCount >= MAX_DEVICETHREE_COUNT )
            {
                return errorCode(Error_Bigin - 3); //MAX_DEVICENORMALCOUNT error
            }
            iDeviceIndex = f_deviceThreeCount;
            f_deviceThreeCount ++;
        }
        if ( sActionEnd - sActionFirst + 1 > 1 )
        {
            f_deviceThrees[ iDeviceIndex ].name = sNameFirst;
            char sAction2 = tolower(* (sActionFirst + 1));
            if (sAction == 'g' && sAction2 == 's')
            {
                f_deviceThrees[ iDeviceIndex ].gsldata = sLogicFirst;
            }
            else if (sAction == 'g' && sAction2 == 'j')
            {
                f_deviceThrees[ iDeviceIndex ].gjldata = sLogicFirst;
            }
            else if (sAction == 's' && sAction2 == 'g')
            {
                f_deviceThrees[ iDeviceIndex ].sgldata = sLogicFirst;
            }
            else if (sAction == 's' && sAction2 == 'j')
            {
                f_deviceThrees[ iDeviceIndex ].sjldata = sLogicFirst;
            }
            else if (sAction == 'j' && sAction2 == 's')
            {
                f_deviceThrees[ iDeviceIndex ].jsldata = sLogicFirst;
            }
            //error
            else
            {
               return errorCode(Error_Inter_Begin - 4); // LData Format Error : Action String Invalid;
            }
        }
        //error
        else
        {
            return errorCode(Error_Inter_Begin - 4); // LData Format Error : Action String Invalid;
        }
    }
    return 0;
}

int preProcessDevices()
{
    char * sLDataBufferEnd = f_ldataBuffer + f_ldataSize - 1;
    char * pch1 = f_ldataBuffer;
    char * sNameFirst = 0;
    char * sNameEnd = 0;
    char * sActionFirst = 0;
    char * sActionEnd = 0;
    char * sLogicFirst = 0;
    char * sLogicEnd = 0;
    int iStep = 0;
    //init
    int iCount = 0;
    f_deviceNormalCount = 0;
    f_deviceThreeCount = 0;
    while ( pch1 <= sLDataBufferEnd )
    {
        switch (iStep)
        {
        case 0:
            if ( ( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-' )
            {
                sNameFirst = pch1;
                sNameEnd = 0;
                iStep = 1;
            }
            break;
        case 1:
            if ( * pch1 == ' ' )
            {
                sNameEnd = pch1 - 1;
                * pch1 = 0;
                iStep = 2;
            }
            break;
        case 2:
            if ( ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) )
            {
                sActionFirst = pch1;
                sActionEnd = 0;
                iStep = 3;
            }
            break;
        case 3:
            if ( * pch1 == ':' )
            {
                sActionEnd = pch1 - 1;
                * pch1 = 0;
                iStep = 4;
            }
            break;
        case 4:
            if ( * pch1 == '{' )
            {
                sLogicFirst = pch1;
                sLogicEnd = 0;
                iStep = 5;
            }
            break;
        case 5:
            if ( * pch1 == '!' )
            {
                sLogicEnd = pch1;

                char cError = preProcessDevice(sNameFirst, sNameEnd, sActionFirst, sActionEnd, sLogicFirst, sLogicEnd);
                if ( cError )
                {
                    return iCount;
                }
                else
                {
                    iCount ++;
                }
                iStep = 6;
            }
            break;
        case 6:
            if ( * pch1 == '\r' || * pch1 == '\n')
            {
                * pch1 = '\0'; // '\0' == 0
                iStep = 0;
            }
        default:
            break;
        }
        pch1 ++;
    }
    return 0;
}

int preProcessOperates(const char * sOperateQueue)
{
    ///
    ///
    /// \brief processOperateItems:
    /// \param sOperateQueue ( example : 2261=1\n2262=0\n2263=1 )
    /// \return : operateItemCount
    ///
    ///e.g.
    ///
    ///2261=1
    ///2262=0
    ///2263=1
    ///operate ( name translate to index )
    ///1=1
    ///2=0
    ///3=1
    const char * sNameFirst = 0;
    const char * sNameEnd = 0;
    char cAction = 0;
    const char * pch1 = sOperateQueue;
    int iIndex = 0;
    int iCount = 0;
    int iStep = 0;
    while ( * pch1 != 0 )
    {
        switch (iStep)
        {
        case 0:
            if ( ( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-' )
            {
                sNameFirst = pch1;
                iStep = 1;
            }
            break;
        case 1:
            if ( * pch1 == ' ' || * pch1 == '=')
            {
                sNameEnd = pch1 - 1;
                iStep = 2;
            }
            break;
        case 2:
            if ( * pch1 >= '0' && * pch1 <= '2')
            {
                cAction = * pch1 - '0';
                iIndex = findDeviceNormalByName(sNameFirst , sNameEnd - sNameFirst + 1);
                if (iIndex >= 0)
                {
                    f_deviceNormals[iIndex].state_simu = cAction;
                    OperateItem * pOperate = & f_operateItems[iCount];
                    pOperate->type = DEVICE_TYPE_NORMAL;
                    pOperate->index = iIndex;
                    pOperate->operate = cAction;
                    iCount++;
                }
                else
                {
                    iIndex = findDeviceThreeByName(sNameFirst , sNameEnd - sNameFirst + 1);
                    if (iIndex >= 0)
                    {
                        f_deviceNormals[iIndex].state_simu = cAction;
                        OperateItem * pOperate = & f_operateItems[iCount];
                        pOperate->type = DEVICE_TYPE_THREE;
                        pOperate->index = iIndex;
                        pOperate->operate = cAction;
                        iCount++;
                    }
                }
                iStep = 0;
            }
            break;
        default:
            break;
        }
        pch1 ++;
    }
    f_operateCount = iCount;
    return iCount;
}

int preProcessStates(const char * sStateQueue)
{
    // 2261=1,2262=0,2251=1
    const char * sNameFirst = 0;
    const char * sNameEnd = 0;
    char cState = 0;
    const char * pch1 = sStateQueue;
    int iIndex = 0;
    int iCount = 0;
    int iStep = 0;
    if (* pch1 == 0)  return;

    while ( * pch1 != 0 )
    {
        switch (iStep)
        {
        case 0:
            if ( ( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-' )
            {
                sNameFirst = pch1;
                iStep = 1;
            }
            break;
        case 1:
            if ( * pch1 == ' ' || * pch1 == '=')
            {
                sNameEnd = pch1 - 1;
                iStep = 2;
            }
            break;
        case 2:
            if ( * pch1 >= '0' && * pch1 <= '2')
            {
                cState = * pch1 - '0';
                iIndex = findDeviceNormalByName(sNameFirst , sNameEnd - sNameFirst + 1);
                if (iIndex >= 0)
                {
                    f_deviceNormals[iIndex].state = cState;
                    iCount++;
                }
                else
                {
                    iIndex = findDeviceThreeByName(sNameFirst , pch1 - sNameFirst);
                    if (iIndex >= 0)
                    {
                        f_deviceThrees[iIndex].state = cState;
                        iCount++;
                    }
                }
                iStep = 0;
            }
            break;
        default:
            break;
        }
        pch1 ++;
    }
    return iCount;
}

///1) loadDevices
///2)
int wfl_loadLDataByFile(const char *sFileName)
{
    loadWFLogicErrorBuffer();

    FILE * pFile;
    size_t iSize;
    char * buffer;
    long bufferSize;
    size_t iResult;

    pFile = fopen ( sFileName , "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); return 1;}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    iSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    bufferSize = sizeof(char)*iSize + 1;
    buffer = (char*) malloc (bufferSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); return 2;}

    // copy the file into the buffer:
    iResult = fread (buffer,1,iSize,pFile);
    if (iResult != iSize) {fputs ("Reading error",stderr); return 3;}

    /* the whole file is now loaded in the memory buffer. */

    fclose (pFile);
    setLDataBuffer(buffer, iSize);
    preProcessDevices();
    return f_deviceNormalCount + f_deviceThreeCount;
}

int wfl_loadLDataByBuffer(const char *pFileBuffer, int iSize)
{
    // allocate memory to contain the whole file:
    char * pBuffer2 = (char*) malloc (sizeof(char)*iSize);
    if (pBuffer2 == NULL) {fputs ("Memory error",stderr); return 2;}

    memcpy(pBuffer2, pFileBuffer, iSize);

    setLDataBuffer(pBuffer2, iSize);
    preProcessDevices();
    return f_deviceNormalCount + f_deviceThreeCount;
}

char * getLogicByOperate(OperateItem * pOperate)
{
    ///
    /// \brief getLogicByOperate
    /// \param pOperate
    /// \return : Logic
    ///
    int iDeviceIndex = pOperate->index;
    if ( pOperate->type == DEVICE_TYPE_NORMAL )
    {
        switch ( pOperate->operate )
        {
            case operation_l:
                return f_deviceNormals[iDeviceIndex].lldata;
                break;
            case operation_h:
                return f_deviceNormals[iDeviceIndex].hldata;
                break;
            default:
                return 0;
                break;
        }
    }
    else if ( pOperate->type == DEVICE_TYPE_THREE )
    {
        switch ( pOperate->operate )
        {
            case operation_gj:
                return f_deviceThrees[iDeviceIndex].gjldata;
                break;
            case operation_gs:
                return f_deviceThrees[iDeviceIndex].gsldata;
                break;
            case operation_sg:
                return f_deviceThrees[iDeviceIndex].sgldata;
                break;
            case operation_sj:
                return f_deviceThrees[iDeviceIndex].sjldata;
                break;
            case operation_js:
                return f_deviceThrees[iDeviceIndex].jsldata;
                break;
            default:
                return 0;
                break;
        }
    }
    return 0;
}

int checkCondition_findOperate_f(char cType, int iIndex, char cOperate)
{
    int i = 0;
    OperateItem * pOperate = 0;
    for (i = f_operateCount - 2; i >= 0; i--)
    {
        pOperate = & f_operateItems[i];
        if ( pOperate->type == cType && pOperate->index == iIndex && pOperate->operate == cOperate )
        {
            return i;
        }
    }
    return -1;
}

int checkCondition_findOperate(char cType, int iIndex)
{
    int i = 0;
    OperateItem * pOperate = 0;
    for (i = f_operateCount - 2; i >= 0; i--)
    {
        pOperate = & f_operateItems[i];
        if ( pOperate->type == cType && pOperate->index == iIndex )
        {
            return i;
        }
    }
    return -1;
}

int checkCondition_findOperate_s(char cType, int iIndex, char cOperate)
{
    int i = 0;
    OperateItem * pOperate = 0;
    for (i = f_operateCount - 2; i >= 0; i--)
    {
        pOperate = & f_operateItems[i];
        if ( pOperate->type == cType && pOperate->index == iIndex )
        {
            return ( pOperate->operate == cOperate ) ? i : -1;
        }
    }
    return -1;
}

char checkConditionItem(char * sConditionFirst, char * sConditionLast)
{
    if ( sConditionLast - sConditionFirst + 1 == 1 ) return * sConditionFirst;
    char * sName = 0;
    int iNameLength = 0;
    char cOperate = 0;
    char cDirect = 0;
    char * pch1 = sConditionFirst;
    int iStep = 0;
    char cResult;
    while ( pch1 <= sConditionLast )
    {
        switch (iStep)
        {
        case 0:
            if ( ( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-' )
            {
                sName = pch1;
                iStep = 1;
            }
            break;
        case 1:
            if ( * pch1 == '=' || * pch1 == ' ' )
            {
                iNameLength = pch1 - sName;
                iStep = 2;
            }
            break;
        case 2:
            if ( * pch1 >= '0' && * pch1 <= '5' )
            {
                cOperate = * pch1 - '0';
                iStep = 3;
            }
            break;
        case 3:
            if ( * pch1 == 'F' || * pch1 == 'f' )
            {
                cDirect = * pch1;
                int iDeviceIndex = findDeviceNormalByName( sName, iNameLength );
//Device Normal
                if ( iDeviceIndex >= 0 )
                {
                    if ( cOperate == 0 || cOperate == 3 )
                    {
                        if ( checkCondition_findOperate_f( DEVICE_TYPE_NORMAL, iDeviceIndex, 0 ) > -1 )
                        {
                            return check_true;
                        }
                        else
                        {
                            return check_false;
                        }
                    }
                    else if ( cOperate == 1 || cOperate == 4 )
                    {
                        if ( checkCondition_findOperate_f( DEVICE_TYPE_NORMAL, iDeviceIndex, 1 ) > -1 )
                        {
                            return check_true;
                        }
                        else
                        {
                            return check_false;
                        }
                    }
                    //has action
                    else if ( cOperate == 2 )
                    {
                        if ( checkCondition_findOperate( DEVICE_TYPE_NORMAL, iDeviceIndex ) > -1 )
                        {
                            return check_true;
                        }
                        else
                        {
                            return check_false;
                        }

                    }
                    //no action
                    else if ( cOperate == 5 )
                    {
                        if ( checkCondition_findOperate( DEVICE_TYPE_NORMAL, iDeviceIndex ) < 0 )
                        {
                            return check_true;
                        }
                        else
                        {
                            return check_false;
                        }

                    }
                }
                else
                {
                    iDeviceIndex = findDeviceThreeByName( sName, iNameLength );
//Device Three
                    if ( iDeviceIndex >= 0 )
                    {
                        if ( cOperate == 0 || cOperate == 1 || cOperate == 2 )
                        {
                            if ( checkCondition_findOperate_f( DEVICE_TYPE_NORMAL, iDeviceIndex, cOperate ) > -1 )
                            {
                                return check_true;
                            }
                            else
                            {
                                return check_false;
                            }
                        }
                    }
                    else
                    {
//Device none
                        return errorCode(Error_Bigin - 4); // can not find device
                    }
                }
            }
            else if ( * pch1 == 'S' || * pch1 == 's' )
            {
                cDirect = * pch1;

                if ( cOperate == 0 || cOperate == 1 || cOperate == 2 )
                {
                    int iDeviceIndex = findDeviceNormalByName( sName, iNameLength );
                    if ( iDeviceIndex >= 0 )
                    {
                        if ( checkCondition_findOperate_s( DEVICE_TYPE_NORMAL, iDeviceIndex, cOperate ) > -1 )
                        {
                            return check_true;
                        }
                        else
                        {
                            return check_false;
                        }
                    }
                    else
                    {
                        iDeviceIndex = findDeviceNormalByName( sName, iNameLength );
                        if ( iDeviceIndex >= 0 )
                        {
                            if ( checkCondition_findOperate_s( DEVICE_TYPE_THREE, iDeviceIndex, cOperate ) > -1 )
                            {
                                return check_true;
                            }
                            else
                            {
                                return check_false;
                            }
                        }
                        else
                        {
                            return errorCode(Error_Bigin - 4); // can not find device
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
        pch1 ++;
    }
    if ( ! iNameLength )
    {
        cResult = errorCode(Error_Bigin - 5); // checkCondition - name invalid!
    }
    if ( ! cOperate )
    {
        cResult = errorCode(Error_Bigin - 6); // checkCondition - operate invalid!
    }
    if ( ! cDirect )
    {
        cResult = errorCode(Error_Bigin - 7); // checkCondition - direct invalid!
    }
    return cResult;
}

char checkLogicItem(char * sConditionFirst, char * sConditionLast)
{
    if ( sConditionLast - sConditionFirst + 1 == 1 ) return * sConditionFirst;
    char * sName = 0;
    int iNameLength = 0;
    char cError = 0;
    char cOperate = 0;
    char * pch1 = sConditionFirst;
    int iStep = 0;
    while ( pch1 <= sConditionLast )
    {
        switch (iStep)
        {
        case 0:
            if ( ( * pch1 >= '0' && * pch1 <= '9' ) || ( * pch1 >= 'a' && * pch1 <= 'z' ) || ( * pch1 >= 'A' && * pch1 <= 'Z' ) || * pch1 == '-' )
            {
                sName = pch1;
                iStep = 1;
            }
            break;
        case 1:
            if ( * pch1 == '=' || * pch1 == ' ' )
            {
                iNameLength = pch1 - sName;
                iStep = 2;
            }
            break;
        case 2:
            if ( * pch1 >= '0' && * pch1 <= '9' )
            {
                cError = * pch1 - '0';
                iStep = 3;
            }
            break;
        case 3:
            if ( * pch1 >= '0' && * pch1 <= '5' )
            {
                cOperate = * pch1 - '0';
                int iIndex = findDeviceNormalByName(sName , iNameLength);
                if (iIndex >= 0)
                {
                    if ( f_deviceNormals[iIndex].state_simu == cOperate )
                    {
                        return 0;
                    }
                    else
                    {
                        f_lastErrorDeviceName = f_deviceNormals[iIndex].name;
                        f_lastErrorDeviceEid = cError;
                        return 1;
                    }
                }
                else
                {
                    iIndex = findDeviceThreeByName(sName , iNameLength);
                    if (iIndex >= 0)
                    {
                        if ( f_deviceThrees[iIndex].state_simu == cOperate )
                        {
                            return 0;
                        }
                        else
                        {
                            f_lastErrorDeviceName = f_deviceThrees[iIndex].name;
                            f_lastErrorDeviceEid = cError;
                            return 1;
                        }
                    }
                    else
                    {
                        return errorCode(Error_Bigin - 4);
                    }
                }
            }
            break;
        default:
            break;
        }
        pch1 ++;
    }
    return errorCode(Error_Bigin - 8);
}

char checkExpressionItem(char * sConditionFirst, char * sConditionLast, char cExpressionType)
{
    switch (cExpressionType)
    {
    case EXPRESSION_TYPE_CONDITION:
        return checkConditionItem(sConditionFirst, sConditionLast);
        break;
    case EXPRESSION_TYPE_LOGIC:
        return checkLogicItem(sConditionFirst, sConditionLast);
        break;
    default:
        break;
    }
    return 1;
}

char checkExpressionAnd(char * sConditionFirst, char * sConditionLast, char cExpressionType)
{
    char * pch1 = sConditionFirst;
    char * sFirst = sConditionFirst;
    char cResult = check_true;
    while ( pch1 <= sConditionLast )
    {
        if ( * pch1 == ',' )
        {
            cResult = checkExpressionItem( sFirst, pch1 - 1 , cExpressionType );
            if (cResult != check_true)
            {
                return cResult;
            }
            else
            {
                sFirst = pch1 + 1;
            }
        }
        pch1 ++;
    }
    return checkExpressionItem( sFirst, sConditionLast , cExpressionType );
}

char checkExpressionGroup(char * sConditionFirst, char * sConditionLast, char cExpressionType)
{
    char * pch1 = sConditionFirst;
    char * sFirst = sConditionFirst;
    char cResult = check_true;
    while ( pch1 <= sConditionLast )
    {
        if ( * pch1 == '+' )
        {
            cResult = checkExpressionAnd( sFirst, pch1 - 1 , cExpressionType );
            if (cResult == check_true)
            {
                return check_true;
            }
            else
            {
                sFirst = pch1 + 1;
            }
        }
        pch1 ++;
    }
    return checkExpressionAnd( sFirst, sConditionLast , cExpressionType );
}

int checkExpressionFull(char * sConditionFirst, char * sConditionLast, char cExpressionType)
{
    int iConditionLength = sConditionLast - sConditionFirst + 1;
    if (iConditionLength >= 4096 || iConditionLength < 0)
        return errorCode(Error_Bigin - 1); // condition invalid!
    if (iConditionLength == 0) return check_true;
    char sCondition2[4096];
    char * sCondition2Last = & sCondition2[iConditionLength - 1];
    memcpy(sCondition2, sConditionFirst, iConditionLength);
    char * pch1 = sCondition2;
    char * pch2 = 0;
    char * sFirst = 0;
    char * sLast = 0;
    char cResult = check_true;
    while ( pch1 <= sCondition2Last )
    {
        if ( * pch1 == ')' )
        {
            sLast = pch1;
            pch2 = pch1;
            while ( * pch2 != '(' )
            {
                pch2 --;
                if (pch2 == sCondition2)
                    return errorCode(Error_Bigin - 1); // condition format error!
            }
            sFirst = pch2;
            cResult = checkExpressionGroup( sFirst + 1 , sLast - 1 , cExpressionType );
            * sFirst = cResult;
            memmove( sFirst + 1, sLast + 1, sCondition2Last - sLast );
            sCondition2Last = sCondition2Last - (sLast - sFirst);
        }
        pch1 ++;
    }
    return checkExpressionGroup( sCondition2, sCondition2Last , cExpressionType );
}

int wfl_checkLData(const char *sOperateQueue, const char *sDeviceStateList, char * sError)
{
    //2261 L:{22613=1 S}|2|2030=01;{}|1|22611=00,22612=00,22614=00+(22611=01+22612=01),22614=01!

    if ( preProcessOperates(sOperateQueue) <= 0 )
    {
        return errorCode(Error_Bigin - 1); //has not valid operate item!
    }

    preProcessStates(sDeviceStateList);

    OperateItem * pOperate = & f_operateItems[f_operateCount - 1];
    char * sLData = getLogicByOperate(pOperate);
    if ( ! sLData )
    {
        return errorCode(Error_Bigin - 2);// can not find LData data!
    }
    char * pch1 = 0;
    char * pch2 = 0;
    char * pch3 = 0;
    char cResult;

    pch1 = sLData;
    while ( * pch1 != '!' )
    {
        pch1 ++;
        if ( * pch1 == '}' )
        {
            pch2 = pch1;
            while ( pch2 > sLData )
            {
                pch2 --;
                if (* pch2 == '{')
                {
//Condition
                    if ( checkExpressionFull(pch2 + 1, pch1 - 1, EXPRESSION_TYPE_CONDITION) )
                    {
                        pch3 = 0;
                        while ( * pch1 != '!' )
                        {
                            pch1 ++;
                            if ( * pch1 == '|' )
                            {
                                pch3 = pch1;
                            }
                            else if ( * pch1 == ';' or * pch1 == '!' )
                            {
                                if ( pch3 != 0 )
                                {
                                    cResult = checkExpressionFull(pch3 + 1, pch1 - 1 , EXPRESSION_TYPE_LOGIC);
                                    if ( * pch2 == '!' )
                                    {
                                        if ( cResult == check_true )
                                        {
                                            return 0;
                                        }
                                        else
                                        {
                                            if ( sError )
                                            {
                                                sError = wfl_getErrorString(cResult);
                                            }
                                            return cResult;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}


int wfl_getDeviceNormalCount()
{
    return f_deviceNormalCount;
}


int wfl_getDeviceThreeCount()
{
    return f_deviceThreeCount;
}


int wfl_getLastErrorCode()
{
    return f_lastErrorCode;
}

int wfl_getLastErrorRow()
{
    f_lastErrorRow = g_logicItemCount + 1;
    return f_lastErrorRow;
}

int wfl_getLastErrorColumn()
{
    return f_lastErrorColumn;
}

char * wfl_getErrorString(int iErrorCode)
{
    int iIndex = 0 - iErrorCode;
    if ( iIndex >= 0 && iIndex < MAX_WFLOGICE_ERROR_COUNT)
        return f_WFLogiceErrors[iErrorCode];
    else
    {
//        errorCode(Error_Inter_getErrorString_1);
        return 0;
    }
}

const DeviceNormal *wfl_getDeviceNormals()
{
    return f_deviceNormals;
}

const DeviceThree *wfl_getDeviceThrees()
{
    return f_deviceThrees;
}
