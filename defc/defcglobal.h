#ifndef DEFCGLOBAL_H
#define DEFCGLOBAL_H

//-----------------------------------------------------------------------------------------
//
//os system : analyse, define
//
//-----------------------------------------------------------------------------------------

/*
   The operating system, must be one of: (GM_OS_x)

     DARWIN   - Darwin OS (synonym for GM_OS_MAC)
     SYMBIAN  - Symbian
     MSDOS    - MS-DOS and Windows
     OS2      - OS/2
     OS2EMX   - XFree86 on OS/2 (not PM)
     WIN32    - Win32 (Windows 2000/XP/Vista/7 and Windows Server 2003/2008)
     WINCE    - WinCE (Windows CE 5.0)
     CYGWIN   - Cygwin
     SOLARIS  - Sun Solaris
     HPUX     - HP-UX
     ULTRIX   - DEC Ultrix
     LINUX    - Linux
     FREEBSD  - FreeBSD
     NETBSD   - NetBSD
     OPENBSD  - OpenBSD
     BSDI     - BSD/OS
     IRIX     - SGI Irix
     OSF      - HP Tru64 UNIX
     SCO      - SCO OpenServer 5
     UNIXWARE - UnixWare 7, Open UNIX 8
     AIX      - AIX
     HURD     - GNU Hurd
     DGUX     - DG/UX
     RELIANT  - Reliant UNIX
     DYNIX    - DYNIX/ptx
     QNX      - QNX
     LYNX     - LynxOS
     BSD4     - Any BSD 4.4 system
     UNIX     - Any UNIX BSD/SYSV system
*/

/*
__MINGW32__
_MSC_VER
*/
/*
GM_OS_WIN32
GM_OS_WINCE
GM_OS_UNIX
GM_OS_LINUX
*/


#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#  define GM_OS_DARWIN
#  define GM_OS_BSD4
#  ifdef __LP64__
#    define GM_OS_DARWIN64
#  else
#    define GM_OS_DARWIN32
#  endif
#elif defined(__SYMBIAN32__) || defined(SYMBIAN)
#  define GM_OS_SYMBIAN
#  define GM_NO_POSIX_SIGNALS
#  define GM_NO_GETIFADDRS
#elif defined(__CYGWIN__)
#  define GM_OS_CYGWIN
#elif defined(MSDOS) || defined(_MSDOS)
#  define GM_OS_MSDOS
#elif defined(__OS2__)
#  if defined(__EMX__)
#    define GM_OS_OS2EMX
#  else
#    define GM_OS_OS2
#  endif
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define GM_OS_WIN32
#  define GM_OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  if defined(WINCE) || defined(_WIN32_WCE)
#    define GM_OS_WINCE
#  else
#    define GM_OS_WIN32
#  endif
#elif defined(__MWERKS__) && defined(__INTEL__)
#  define GM_OS_WIN32
#elif defined(__sun) || defined(sun)
#  define GM_OS_SOLARIS
#elif defined(hpux) || defined(__hpux)
#  define GM_OS_HPUX
#elif defined(__ultrix) || defined(ultrix)
#  define GM_OS_ULTRIX
#elif defined(sinix)
#  define GM_OS_RELIANT
#elif defined(__native_client__)
#  define GM_OS_NACL
#elif defined(__linux__) || defined(__linux)
#  define GM_OS_LINUX
#elif defined(__FreeBSD__) || defined(__DragonFly__)
#  define GM_OS_FREEBSD
#  define GM_OS_BSD4
#elif defined(__NetBSD__)
#  define GM_OS_NETBSD
#  define GM_OS_BSD4
#elif defined(__OpenBSD__)
#  define GM_OS_OPENBSD
#  define GM_OS_BSD4
#elif defined(__bsdi__)
#  define GM_OS_BSDI
#  define GM_OS_BSD4
#elif defined(__sgi)
#  define GM_OS_IRIX
#elif defined(__osf__)
#  define GM_OS_OSF
#elif defined(_AIX)
#  define GM_OS_AIX
#elif defined(__Lynx__)
#  define GM_OS_LYNX
#elif defined(__GNU__)
#  define GM_OS_HURD
#elif defined(__DGUX__)
#  define GM_OS_DGUX
#elif defined(__QNXNTO__)
#  define GM_OS_QNX
#elif defined(_SEQUENT_)
#  define GM_OS_DYNIX
#elif defined(_SCO_DS) /* SCO OpenServer 5 + GCC */
#  define GM_OS_SCO
#elif defined(__USLC__) /* all SCO platforms + UDK or OUDK */
#  define GM_OS_UNIXWARE
#elif defined(__svr4__) && defined(i386) /* Open UNIX 8 + GCC */
#  define GM_OS_UNIXWARE
#elif defined(__INTEGRITY)
#  define GM_OS_INTEGRITY
#elif defined(VXWORKS) /* there is no "real" VxWorks define - this has to be set in the mkspec! */
#  define GM_OS_VXWORKS
#elif defined(__MAKEDEPEND__)
#else
#  error "GM has not been ported to this OS - talk to ........"
#endif

/*OS Define */
#if defined(GM_OS_WIN32) || defined(GM_OS_WIN64) || defined(GM_OS_WINCE)
#  define GM_OS_WIN
#endif

#if defined(GM_OS_DARWIN)
#  define GM_OS_MAC /* GM_OS_MAC is mostly for compatibility, but also more clear */
#  define GM_OS_MACX /* GM_OS_MACX is only for compatibility.*/
#  if defined(GM_OS_DARWIN64)
#     define GM_OS_MAC64
#  elif defined(GM_OS_DARWIN32)
#     define GM_OS_MAC32
#  endif
#endif

#ifdef GM_AUTODETECT_COCOA
#  ifdef GM_OS_MAC64
#    define GM_MAC_USE_COCOA 1
#    define GM_BUILD_KEY GM_BUILD_KEY_COCOA
#  else
#    define GM_BUILD_KEY GM_BUILD_KEY_CARBON
#  endif
#endif

#if defined(GM_WS_MAC64) && !defined(GM_MAC_USE_COCOA) && !defined(GM_BUILD_QMAKE) && !defined(GM_BOOTSTRAPPED)
#error "You are building a 64-bit application, but using a 32-bit version of GM. Check your build configuration."
#endif

#if defined(GM_OS_MSDOS) || defined(GM_OS_OS2) || defined(GM_OS_WIN)
#  undef GM_OS_UNIX
#elif !defined(GM_OS_UNIX)
#  define GM_OS_UNIX
#endif

#if defined(GM_OS_DARWIN) && !defined(GM_LARGEFILE_SUPPORT)
#  define GM_LARGEFILE_SUPPORT 64
#endif

#ifdef GM_OS_DARWIN
#  ifdef MAC_OS_X_VERSION_MIN_REQUIRED
#    undef MAC_OS_X_VERSION_MIN_REQUIRED
#  endif
#  define MAC_OS_X_VERSION_MIN_REQUIRED MAC_OS_X_VERSION_10_4
#  include <AvailabilityMacros.h>
#  if !defined(MAC_OS_X_VERSION_10_3)
#     define MAC_OS_X_VERSION_10_3 MAC_OS_X_VERSION_10_2 + 1
#  endif
#  if !defined(MAC_OS_X_VERSION_10_4)
#       define MAC_OS_X_VERSION_10_4 MAC_OS_X_VERSION_10_3 + 1
#  endif
#  if !defined(MAC_OS_X_VERSION_10_5)
#       define MAC_OS_X_VERSION_10_5 MAC_OS_X_VERSION_10_4 + 1
#  endif
#  if !defined(MAC_OS_X_VERSION_10_6)
#       define MAC_OS_X_VERSION_10_6 MAC_OS_X_VERSION_10_5 + 1
#  endif
#  if !defined(MAC_OS_X_VERSION_10_7)
#       define MAC_OS_X_VERSION_10_7 MAC_OS_X_VERSION_10_6 + 1
#  endif
#  if (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_7)
#    warning "This version of Mac OS X is unsupported"
#  endif
#endif

#ifdef __LSB_VERSION__
#  if __LSB_VERSION__ < 40
#    error "This version of the Linux Standard Base is unsupported"
#  endif
#ifndef GM_LINUXBASE
#  define GM_LINUXBASE
#endif
#endif





//-----------------------------------------------------------------------------------------
//
//data type : define
//
//-----------------------------------------------------------------------------------------

typedef signed char         int8        ;   /* 8 bit signed */
typedef unsigned char       uint8       ;   /* 8 bit unsigned */
typedef short               int16       ;   /* 16 bit signed */
typedef unsigned short      uint16      ;   /* 16 bit unsigned */
typedef int                 int32       ;   /* 32 bit signed */
typedef unsigned int        uint32      ;   /* 32 bit unsigned */
typedef long long           int64       ;   /* 64 bit signed */
typedef unsigned long long  uint64      ;   /* 64 bit unsigned */

#ifndef QT_BEGIN_INCLUDE_NAMESPACE
typedef unsigned char       uchar       ;   /* 8 bit unsigned */
typedef unsigned short      ushort      ;   /* 16 bit unsigned */
typedef unsigned int        uint        ;   /* 32 bit unsigned */
#endif
typedef long long           longlong    ;   /* 64 bit signed */
typedef unsigned long long  ulonglong   ;   /* 64 bit unsigned */

typedef unsigned char       byte        ;   /* 8 bit unsigned */
typedef unsigned short      word        ;   /* 16 bit unsigned */
typedef unsigned int        dword       ;   /* 32 bit unsigned */

typedef    void* 			pvoid;


#ifndef    TRUE
#define    TRUE	1
#endif
#ifndef    FALSE
#define	   FALSE 0
#endif
#ifndef    NULL
#define	   NULL 0
#endif


//1970.1.1 0:0:0:00
//millisecond
typedef long long msepoch;
//microsecond
typedef long long usepoch;
//typedef unsigned long long msepoch;



typedef enum __DataType_Enum{ DataType_Char, DataType_Short, DataType_Int, DataType_Long, DataType_Bool, DataType_Float, DataType_Double, DataType_DateTime, DataType_String } DataType_Enum;



//-----------------------------------------------------------------------------------------
//
//long long convert : define
//
//-----------------------------------------------------------------------------------------
#if defined(_MSC_VER)
#  define GM_INT64_C(c) c ## i64    /* signed 64 bit constant */
#  define GM_UINT64_C(c) c ## ui64   /* unsigned 64 bit constant */
#else
#  define GM_INT64_C(c) static_cast<long long>(c ## LL)     /* signed 64 bit constant */
#  define GM_UINT64_C(c) static_cast<unsigned long long>(c ## ULL) /* unsigned 64 bit constant */
#endif





//-----------------------------------------------------------------------------------------
//
///GM_DLL_API
///GM_CALL_MODE
//
//-----------------------------------------------------------------------------------------

#if defined(GM_OS_WIN)
#    define GM_DLL_EXPORT extern "C" __declspec(dllexport)
#    define GM_DLL_IMPORT extern "C" __declspec(dllimport)
#    define GM_DLL_HIDDEN
#else
#    define GM_DLL_EXPORT     __attribute__((visibility("default")))
#    define GM_DLL_IMPORT
#    define GM_DLL_HIDDEN     __attribute__((visibility("hidden")))
#endif


#ifndef GM_DLL_API
#   if defined(GM_PROJECT_APP_DLL)
#       define GM_DLL_API  GM_DLL_EXPORT
#   else
#       define GM_DLL_API  GM_DLL_IMPORT
#   endif
#endif


#ifndef GM_CALL_MODE
#  if defined(GM_OS_WIN)
#    define GM_CALL_MODE __cdecl
#  else
#    define GM_CALL_MODE
#  endif
#endif

#if defined(GM_COMMON_DLL)
#   define GM_COMMON_API  GM_DLL_API
#   define GM_COMMON_MODE GM_CALL_MODE
#else
#   define GM_COMMON_API
#   define GM_COMMON_MODE
#endif



//-----------------------------------------------------------------------------------------
//
//limit : define
//
//-----------------------------------------------------------------------------------------
#define GM_STRING_FROM_IDENTITY( p ) #p

#define GM_STRING_IS_BLANK( p ) ( ( p ) > 0x09 && ( p ) < 0x0D )


///-mno-cygwin


#endif
