#ifndef DEFCCRC_H
#define DEFCCRC_H


#include "defcglobal.h"
#include "defcansi.h"


#ifdef __cplusplus
extern "C" {
#endif



GM_COMMON_API uchar    GM_COMMON_MODE crc_sum8(const uchar* pData, int iLength);

GM_COMMON_API ushort   GM_COMMON_MODE crc_sum16(const uchar* pData, int iLength);

GM_COMMON_API uchar    GM_COMMON_MODE crc_8(const uchar* pData, int iLength);

GM_COMMON_API ushort   GM_COMMON_MODE crc_16(const uchar* pData, int iLength);

GM_COMMON_API ushort   GM_COMMON_MODE crc_yaban16(const uchar* pData, int iLength);

GM_COMMON_API ushort   GM_COMMON_MODE crc_modbus(const uchar* pData, int iLength);



#ifdef __cplusplus
}
#endif


#endif //DEFCCRC_H
