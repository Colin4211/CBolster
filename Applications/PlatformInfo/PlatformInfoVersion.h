/////////////////////////////////////////////////////////////////////////////
//
//  Filename: PlatformInfoVersion.h
//
//  Auto Generated:
//               Tool Name - CT_VersionTool
//            Tool Version - CToolsDev-v4.1.1.84
//      Generate Timestamp - 2025\10\02-00:08:58 utc
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __PlatformInfoVersion_h__
#define __PlatformInfoVersion_h__

/////////////////////////////////////////////////////////////////////////////

extern CBBase_VersionNumber                PlatformInfoVersion_FileVersionNumber;
extern CBBase_VersionNumber                PlatformInfoVersion_ProductVersionNumber;
extern CBBase_VersionInfo                  PlatformInfoVersion_VersionInfo;

#define PlatformInfoVersion_InitializeVersion( utilVersionInfo ) \
    { if ( utilVersionInfo.initialize() == false ) { \
            utilVersionInfo.initialize( PlatformInfoVersion_VersionInfo ); \
    } }


/////////////////////////////////////////////////////////////////////////////

#endif /* __PlatformInfoVersion_h__ */


