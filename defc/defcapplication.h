#ifndef DEFCAPPLICATION_H
#define DEFCAPPLICATION_H


#include "defcglobal.h"
#include "defcansi.h"
#include "defcinterinfo.h"


class DefcApplication
{
public:
    static int init(int, char*[]);

    static int uninit();

};


#endif //DEFCAPPLICATION_H
