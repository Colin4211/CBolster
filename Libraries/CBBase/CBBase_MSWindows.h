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
//      CBolster\Libraries\CBBase\CBBase_MSWindows.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CBBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CBBase_MSWindows_h
#define _CBBase_MSWindows_h

/////////////////////////////////////////////////////////////////////////////
//! Windows Specific Includes
//
//  :Description
//      This header file is used to include those other header files
//      which are unique to the MS Windows platform.
//
//  :Definition
//"

#if defined(CBOLSTER_PLATFORM_FAMILY_MSWIN)

    //  ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.en/dv_vccrt/html/435242b8-caea-4063-b765-4a608200312b.htm
    //  ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.en/dv_vsdebugnative/html/91748bdc-f4cd-4d8b-ab98-0493dab7ed0d.htm
    // Turns on extra heap\alloc debugging
    //  still need to make call to function to enable.  This is done
    //  in CExOutMgr::DebugMgr
    #define _CRTDBG_MAP_ALLOC

    // Fuckin Microsoft.  Starts marking a shitload of functions
    //  as obsolete.  Problem is the recomended replacements are
    //  a PITA to call.  So we just turn of the f'n warning
    //#pragma warning ( disable : 4996 )
    #define _CRT_SECURE_NO_WARNINGS

    // To maximize portability of applications built with these
    //  libraries we stick with version 5.0 of the windows API
    // Allow use of features specific to Windows XP and later
    #ifndef WINVER
        #define WINVER 0x0501   // Set to XP
    #endif

    // Allow use of features specific to Windows XP and later
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0501
    #endif

    // Allow use of features specific to Windows 98 or later.
    #ifndef _WIN32_WINDOWS
        #define _WIN32_WINDOWS 0x0410
    #endif

    // Allow use of features specific to IE 7.0 or later.
    #ifndef _WIN32_IE
        #define _WIN32_IE 0x0700
    #endif

    // Verify the WINVER is correct
    #if (WINVER != 0x0501)
        #error "ERROR: These libraries are designed for Windows version 5.1 (XP) features"
    #endif // WINVER

    // Include the windows stuff
    #ifndef _WINDOWS_
        #define STRICT
        #define _WINSOCKAPI_
        #include <windows.h>
        #undef _WINSOCKAPI_
    #endif

#endif

//.

#endif // _CBBase_MSWindows_h


