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
//      CBolster\Libraries\CBBase\CBBase_VersionNumber.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CBBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CBBase_VersionNumber_h
#define _CBBase_VersionNumber_h

namespace CBBase
{

/////////////////////////////////////////////////////////////////////////////

#if defined(CBOLSTER_PLATFORM_FAMILY_MSWIN)
    #pragma pack(push,1)
#elif defined(CBOLSTER_PLATFORM_FAMILY_LINUX)
    #pragma pack(push,1)
#else
    #error "ERROR: This code is platform specific"
#endif


/////////////////////////////////////////////////////////////////////////////
//! CBBase_VersionNumber
//
//  :Description
//      This structure is used to store a version number.
//
//  :Definition
//"
typedef struct
{
    Uint32          m_Major;
    Uint32          m_Minor;
    Uint32          m_Revision;
    Uint32          m_Build;
} VersionNumber;
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CBBase



/////////////////////////////////////////////////////////////////////////////
//! CBBase_VersionNumber
//
//  :Description
//      This structure is tagged as obsolete.  We will continue to use
//      it untill all dependant code has been modified to use
//      the new structure above.
//
//  :Definition
//"
typedef struct
{
    Uint32          m_Major;
    Uint32          m_Minor;
    Uint32          m_Revision;
    Uint32          m_Build;
} CBBase_VersionNumber;
//.

/////////////////////////////////////////////////////////////////////////////

#if defined(CBOLSTER_PLATFORM_FAMILY_MSWIN)
    #pragma pack(pop)
#elif defined(CBOLSTER_PLATFORM_FAMILY_LINUX)
    #pragma pack(pop)
#else
    #error "ERROR: This code is platform specific"
#endif


/////////////////////////////////////////////////////////////////////////////

#endif // _CBBase_VersionNumber_h
