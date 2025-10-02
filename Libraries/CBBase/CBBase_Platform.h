/////////////////////////////////////////////////////////////////////////////
//
//  CBolster Libraries
//  Copyright (c) 1999, Colin Goodall
//      This software is licensed under the MIT License.
//      See the LICENSE file for details.
//
/////////////////////////////////////////////////////////////////////////////
//
//  Module:
//      CBBase
//
//  File:
//      CBolster\Libraries\CBBase\CBBase_Platform.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CBBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CBBase_Platform_h
#define _CBBase_Platform_h

/////////////////////////////////////////////////////////////////////////////
//! CBOLSTER_PLATFORM_XXXXX
//
//  :Description
//      These definitions are used to provide a series of absolutely unique
//      identifiers to allow code to identify which platform it is
//      being compiled.
//
//      Currently only CBOLSTER_PLATFORM_TYPE_MSWIN32 is supported.
//      If this code is to be targeted at other platforms in the future a
//      new identifier and detection sequence must be added to this
//      file.  Then all dependant libraries must be tested to ensure that
//      they will operate as advertised on the new platform
//
//  :Symbols
//      = CBOLSTER_PLATFORM_NAME
//          This symbol is always defined.  It represents a string
//          with a description of the current target platform.
//      = CBOLSTER_PLATFORM_TYPE_MSWIN32
//          When compiling as a Win32 library this symbol is defined
//          as (1).  Otherwise it is undefined.
//      = CBOLSTER_PLATFORM_TYPE_LINUX_I32
//          When compiling as a Win32 library this symbol is defined
//          as (2).  Otherwise it is undefined.
//
//  :Definition
//"

//  Detect Windows CBBase
#if !defined(CBOLSTER_PLATFORM_NAME)
    #if defined(_MSC_VER)
        #if defined(_WIN32) && !defined(_WIN64) && defined(_M_IX86)
            #if !defined(_MT)
                #error "ERROR: Your project must be linked with the multithreaded option."
            #endif // !defined(_MT)
            #define CBOLSTER_PLATFORM_NAME                   ("MSWinI32")
            #define CBOLSTER_PLATFORM_TYPE_MSWIN_I32         (1032)
            #define CBOLSTER_PLATFORM_TYPE                   (CBOLSTER_PLATFORM_TYPE_MSWIN_I32)
        #elif defined(_WIN32) && defined(_WIN64) && defined(_M_X64)
            #if !defined(_MT)
                #error "ERROR: Your project must be linked with the multithreaded option."
            #endif // !defined(_MT)
            #define CBOLSTER_PLATFORM_NAME                   ("MSWinI64")
            #define CBOLSTER_PLATFORM_TYPE_MSWIN_I64         (1064)
            #define CBOLSTER_PLATFORM_TYPE                   (CBOLSTER_PLATFORM_TYPE_MSWIN_I64)
        #endif // defined(_MSC_VER) && defined(_WIN32)
    #endif // defined(_MSC_VER)
#endif // !defined(PLATFORM_NAME)

//  Detect Linux
#if !defined(CBOLSTER_PLATFORM_NAME)
    #if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__gnu_linux__)
        // To see all the #defines for the default compiler
        //      gcc -dM -E - < /dev/null
        #if defined(__i386__)
            #define CBOLSTER_PLATFORM_NAME               ("LinuxI32")
            #define CBOLSTER_PLATFORM_TYPE_LINUX_I32     (2032)
            #define CBOLSTER_PLATFORM_TYPE               (CBOLSTER_PLATFORM_TYPE_LINUX_I32)
        #elif defined(__x86_64)
            #define CBOLSTER_PLATFORM_NAME               ("LinuxI64")
            #define CBOLSTER_PLATFORM_TYPE_LINUX_I64     (2064)
            #define CBOLSTER_PLATFORM_TYPE               (CBOLSTER_PLATFORM_TYPE_LINUX_I64)
        #elif defined(__arm__)
            #define CBOLSTER_PLATFORM_NAME               ("LinuxARM")
            #define CBOLSTER_PLATFORM_TYPE_LINUX_ARM32   (2132)
            #define CBOLSTER_PLATFORM_TYPE               (CBOLSTER_PLATFORM_TYPE_LINUX_ARM32)
        #elif defined(__aarch64__)
            #define CBOLSTER_PLATFORM_NAME               ("LinuxARM64")
            #define CBOLSTER_PLATFORM_TYPE_LINUX_ARM64   (2164)
            #define CBOLSTER_PLATFORM_TYPE               (CBOLSTER_PLATFORM_TYPE_LINUX_ARM64)
        #endif
    #endif
#endif // !defined(CBOLSTER_PLATFORM_NAME)

//  If the PLATFORM_NAME has not been defined then we have a problem!
#if !defined(CBOLSTER_PLATFORM_NAME)
    #error "ERROR: Unable to determine target platform"
#endif // !defined(PLATFORM_NAME)

// Determine platform family
#if ( (CBOLSTER_PLATFORM_TYPE >= 1000) && (CBOLSTER_PLATFORM_TYPE <= 1999) )
    #define CBOLSTER_PLATFORM_FAMILY_NAME        ("MSWin")
    #define CBOLSTER_PLATFORM_FAMILY_MSWIN       (1000)
    #define CBOLSTER_PLATFORM_FAMILY             (CBOLSTER_PLATFORM_FAMILY_MSWIN)
#elif ( (CBOLSTER_PLATFORM_TYPE >= 2000) && (CBOLSTER_PLATFORM_TYPE <= 2999) )
    #define CBOLSTER_PLATFORM_FAMILY_NAME        ("Linux")
    #define CBOLSTER_PLATFORM_FAMILY_LINUX       (2000)
    #define CBOLSTER_PLATFORM_FAMILY             (CBOLSTER_PLATFORM_FAMILY_LINUX)
#endif

//  If the PLATFORM_FAMILY has not been defined then we have a problem!
#if defined(CBOLSTER_PLATFORM_FAMILY_LINUX) || defined(CBOLSTER_PLATFORM_FAMILY_MSWIN)
    // This is okay
#else
    #error "ERROR: Unable to determine target platform family"
#endif // !defined(PLATFORM_NAME)

//.


/////////////////////////////////////////////////////////////////////////////
//! CBOLSTER_DEBUG
//
//  :Description
//      Every application can be targetted as either debug or release.
//      The following symbols define which is the current build.
//      Please note that either one or the other will be defined,
//      but not both.
//      - CBOLSTER_DEBUG
//      - CBOLSTER_RELEASE
//"

#if !defined(CBOLSTER_DEBUG)
    #if defined(_DEBUG) || defined(DEBUG)
        #define CBOLSTER_DEBUG
    #endif
#endif

#if !defined(CBOLSTER_RELEASE)
    #if defined(_RELEASE) || defined(RELEASE) || defined(NDEBUG)
        #define CBOLSTER_RELEASE
    #endif
#endif

    // The gcc compiler does not define any debug
    //  symbol.  We rely on the CBOLSTER_DEBUG symbol
    //  being defined directly in the makefile and
    //  supplied as an argument to gcc
#if defined(CBOLSTER_PLATFORM_FAMILY_LINUX)
    #if (!defined(CBOLSTER_DEBUG)) && (!defined(CBOLSTER_RELEASE))
        #error "ERROR: The symbol CBOLSTER_DEBUG or CBOLSTER_RELEASE must be pre-defined"
    #endif
#endif

#if defined(CBOLSTER_DEBUG) && defined(CBOLSTER_RELEASE)
    #error "ERROR: Both CBOLSTER_DEBUG and CBOLSTER_RELEASE cannot be defined"
#endif

#if defined(CBOLSTER_DEBUG)
    #define CBOLSTER_BUILD_TARGET        ("Debug")
#elif defined(CBOLSTER_RELEASE)
    #define CBOLSTER_BUILD_TARGET        ("Release")
#else
    #error "ERROR: Either CBOLSTER_DEBUG or CBOLSTER_RELEASE must be defined"
#endif

//.



#endif  // _CBBase_Platform_h


