#include "defctime.h"

#include "defcansi.h"

#ifdef GM_OS_WIN
#include <windows.h>
#endif


msepoch datetime_now()
{
#ifdef GM_OS_WIN
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);

    const uint64 iShift = 116444736000000000ULL; // (27111902 << 32) + 3577643008

    union {
        FILETIME as_file_time;
        uint64 as_integer; // 100-nanos since 1601-Jan-01
    } caster;
    caster.as_file_time = ft;

    caster.as_integer -= iShift; // filetime is now 100-nanos since 1970-Jan-01
    uint64 iMicros = caster.as_integer / 10; // truncate to microseconds

    // and cannot be before 1970-Jan-01
    time_t t = static_cast<time_t>(iMicros / 1000000UL); // seconds since epoch
    // microseconds -- static casts supress warnings
    uint32 sub_sec = static_cast<uint32>(iMicros % 1000000UL);
#else
    timeval tv;
    gettimeofday(&tv, 0); //gettimeofday does not support TZ adjust on Linux.
    std::time_t t = tv.tv_sec;
    boost::uint32_t sub_sec = tv.tv_usec;
//#else
//#error Now however neither gettimeofday nor FILETIME support is detected.
#endif
    msepoch dt = t;
    return dt * 1000 + sub_sec / 1000;
}


int getNarme(int i)
{
}


