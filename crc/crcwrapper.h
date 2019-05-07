#ifndef CRCWRAPPER_H
#define CRCWRAPPER_H

#include <QtCore>

class CrcWrapper
{
private:
    const static ushort ccitt_table[];

public:
    CrcWrapper();

    static ushort calc16(const char *bBuffer, ushort len);
};

#endif // CRCWRAPPER_H
