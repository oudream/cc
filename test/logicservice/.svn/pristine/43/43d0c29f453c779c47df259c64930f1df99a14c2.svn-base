#ifndef CHECKWFLOGIC_H
#define CHECKWFLOGIC_H


/*********************************************************************
 @brief             : 逻辑表达式检测
 @author            : oudream
 @create date       : 2013-6-3
 @copyright         :
 @attention         : 注意 - 注意 - 注意 : 所有参数的指针（输入、输出），函数调用方自己管理；
                      所有函数返回值是指针的，不用需调用方管理；以上除非有特殊说明才能忽略！！！
 @modify log        :
*********************************************************************/


/******
 @brief             : 普通设备、两态设备数据结构
 @function          : 保存设备的配置信息与实时状态
 @author            : oudream
 @create date       : 2013-6-3
 @modify log        :
******/
typedef struct tagDeviceNormal {
    int state;
    int quality;
    long long time;
    int state_simu;
    int state_temp;
    char * name;
    char * hldata;
    char * lldata;
} DeviceNormal;


/******
 @brief             : 三态设备数据结构
 @function          : 保存设备的配置信息与实时状态
 @author            : oudream
 @create date       : 2013-6-3
 @modify log        :
******/
typedef struct tagDeviceThree {
    int state;
    int quality;
    long long time;
    int state_simu;
    int state_temp;
    char * name;
    char * gsldata;
    char * gjldata;
    char * sgldata;
    char * sjldata;
    char * jsldata;
} DeviceThree;


/******
 @brief             : 操作队列
 @function          : 保存操作项的
 @author            : oudream
 @create date       : 2013-6-3
 @modify log        :
******/
typedef struct tagOperateItem {
    char type;
    int index;
    char operate;
} OperateItem ;

/***
 @brief             : 返回错误码
 @return            : 返回错误码
 @author            : oudream
 @modify            :
***/
int wfl_getLastErrorCode();

/***
 @brief             : 返回逻辑错误信息
 @param.iErrorCode  : 错误码
 @return            :
 @author            : oudream
 @modify            :
***/
char * wfl_getErrorString(int iErrorCode);

/***
 @brief             : 检测"ldata.fil"五防逻辑格式
 @param.sLogicFirst : 逻辑首地址
 @param.sLogicEnd   : 逻辑末地址
 @return            : 返回各种格式错误码
 @author            : oudream
 @modify            :
***/
int wfl_checkStringLogic(char * sLogicFirst, char * sLogicEnd);

/***
 @brief             : 加载"ldata.fil"文件来初始化本程序用到的设备
 @param.sFileName   : 全文件名
 @return            : 返回加载了多少个设备信息。其它返回值：1 File error ; 2 Memory error ;
                      3 Reading error ;
 @author            : oudream
 @modify            :
***/
int wfl_loadLDataByFile(const char* sFileName);

/***
 @brief             : 加载文件的二进制内容
 @param.pFileBuffer : 文件的二进制内容 pFileBuffer = readfile(sFileName)
 @param.iSize       : 文件内容大小
 @return            : 返回加载了多少个设备信息。其它返回值：Memory error
 @author            : oudream
 @modify            :
***/
wfl_loadLDataByBuffer(const char* pFileBuffer, int iSize);


/***
 @brief                 : 检测操作队列最后的操作项能否操作
 @param.sOperateQueue   : 操作队列, e.g. "2261=0 \n 2030=0 \n 22613=1"
 @param.sDeviceStateList: 设备状态, e.g. "2261=0,2030=0,22613=1,2225=1,...,2219=0"
 @param.sError          : 错误字符串
 @return                : 0表示成功；大于0表示相应错误码
 @author                : oudream
 @modify                :
***/
int wfl_checkLData(const char* sOperateQueue, const char* sDeviceStateList, char* sError);


/***
 @brief             : 返回普通设备、两态设备个数
 @return            : 返回普通设备、两态设备个数
 @author            : oudream
 @modify            :
***/
int wfl_getDeviceNormalCount();

/***
 @brief             : 返回普通设备、两态设备数据信息
 @return            : 返回普通设备、两态设备数据信息
 @author            : oudream
 @modify            :
***/
const DeviceNormal * wfl_getDeviceNormals();

/***
 @brief             : 返回三态设备个数
 @return            : 返回三态设备个数
 @author            : oudream
 @modify            :
***/
int wfl_getDeviceThreeCount();

/***
 @brief             : 返回三态设备数据信息
 @return            : 返回三态设备数据信息
 @author            : oudream
 @modify            :
***/
const DeviceThree * wfl_getDeviceThrees();

/***
 @brief             : 获取"ldata.fil"错误所在行
 @return            : 返回"ldata.fil"错误所在行数
 @author            : oudream
 @modify            :
***/
int wfl_getLastErrorRow();

#endif //CHECKWFLOGIC_H
