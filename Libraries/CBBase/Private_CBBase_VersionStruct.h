/////////////////////////////////////////////////////////////////////////////
//
//  Filename: Private_CBBase_VersionStruct.h
//
//  Auto Generated:
//               Tool Name - CT_VersionTool
//            Tool Version - CToolsDev-v4.1.1.84
//      Generate Timestamp - 2025\10\01-23:33:38 utc
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __Private_CBBase_VersionStruct_h__
#define __Private_CBBase_VersionStruct_h__

namespace CBBase
{

/////////////////////////////////////////////////////////////////////////////

extern CBBase_VersionNumber                Private_CBBaseVersion_FileVersionNumber;
extern CBBase_VersionNumber                Private_CBBaseVersion_ProductVersionNumber;
extern CBBase_VersionInfo                  Private_CBBaseVersion_VersionInfo;

template < typename T_VERSIONINFO > 
    void   Private_CBBaseVersion_Initialize( T_VERSIONINFO & versionInfo )
{
    if ( versionInfo.initialize() == false )
    {
            versionInfo.initialize( Private_CBBaseVersion_VersionInfo );
    }
    return;
}


/////////////////////////////////////////////////////////////////////////////

}; // namespace CBBase

#endif /* __Private_CBBase_VersionStruct_h__ */


