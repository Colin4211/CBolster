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
//      PlatformInfo
//
//  File:
//      CBolster\Applications\PlatformInfo\main.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Applications
//      <DT_SUB_TOPIC> PlatformInfo
//      <DT_SUB_TOPIC> main
//
/////////////////////////////////////////////////////////////////////////////

#include "precomp.h"
#include "PlatformInfoVersion.h"
#include "IntEx.h"
#include "FloatEx.h"

#if defined(CBOLSTER_PLATFORM_FAMILY_MSWIN)
    #pragma warning(disable : 4996)
    #include "conio.h"
#endif // defined(CBOLSTER_PLATFORM_FAMILY_MSWIN)

/////////////////////////////////////////////////////////////////////////////

#define DUMP_INT_INFO(theType)          { theType theValue = (theType)1; IntEx_PrintInfo( #theType, theValue ); }

/////////////////////////////////////////////////////////////////////////////

#define DUMP_FLOAT_TYPE(THE_TYPE) {     \
        THE_TYPE    theType = 0;        \
        FloatEx_PrintInfo(theType);     }

#define DO_LOOKUP
#ifndef DO_LOOKUP

    #define DUMP_STD_FLOAT_TYPE(THE_TYPE) {                     \
                printf( "%12s -- bytes=%-2s -- \n", #THE_TYPE,  \
                IntEx_IntToString(sizeof(THE_TYPE)).c_str() );  }

#else

    #define DUMP_STD_FLOAT_TYPE(THE_TYPE) {                             \
            CBBase::Float_Types<THE_TYPE>::float_info_type floatInfo;  \
            printf( "%12s -- bytes=%-2s -- %s\n", #THE_TYPE,            \
                    IntEx_IntToString(sizeof(THE_TYPE)).c_str(),        \
                    floatInfo.float_type_name() );                      }

#endif

/////////////////////////////////////////////////////////////////////////////

std::string MakeHexDumpStr( const void * ptrData, size_t dataLen )
{
    std::string     resultStr;
    const Uint8 *   ptrData8 = static_cast< const Uint8 * >( ptrData );
    for ( size_t nOffset = 0; nOffset < dataLen; nOffset++ )
    {
        if ( resultStr.empty() == false )
        {
            resultStr += " ";
        }
        Uint8 curVal = ptrData8[nOffset];
        char tempStr[ 32 ];
        sprintf( tempStr, "%02X", curVal );
        resultStr += tempStr;
    }
    return (resultStr);
}

/////////////////////////////////////////////////////////////////////////////

bool  process_float_arg( const std::string & tagStr, const std::string & valStr )
{
    double theDouble = 0;
    theDouble = atof( valStr.c_str() );

    bool fHandled = false;

    #if defined(Float32_SIZEOF)
        if ( (tagStr == "Float32") || (tagStr == "Float") )
        {
            Float32 theFloat32 = static_cast<Float32>( theDouble );
            CBBase::Float32_Info   floatInfo( theFloat32 );
            FloatEx_PrintFloatValue( tagStr, floatInfo );
            fHandled = true;
        }
    #endif // defined(Float32_SIZEOF)

    #if defined(Float64_SIZEOF)
        if ( (tagStr == "Float64") || (tagStr == "Float") )
        {
            Float64 theFloat64 = static_cast<Float64>( theDouble );
            CBBase::Float64_Info  floatInfo( theFloat64 );
            FloatEx_PrintFloatValue( tagStr, floatInfo );
            fHandled = true;
        }
    #endif // defined(Float64_SIZEOF)

    #if defined(Float80_SIZEOF)
        if ( (tagStr == "Float80") || (tagStr == "Float") )
        {
            Float80 theFloat80 = static_cast<Float80>( theDouble );
            CBBase::Float80_Info  floatInfo( theFloat80 );
            FloatEx_PrintFloatValue( tagStr, floatInfo );
            fHandled = true;
        }
    #endif // defined(Float80_SIZEOF)

    #if defined(Float128_SIZEOF)
        if ( (tagStr == "Float128") || (tagStr == "Float") )
        {
            Float128 theFloat128 = static_cast<Float128>( theDouble );
            CBBase::Float128_Info  floatInfo( theFloat128 );
            FloatEx_PrintFloatValue( tagStr, floatInfo );
            fHandled = true;
        }
    #endif // defined(Float128_SIZEOF)

    return (fHandled);
}

/////////////////////////////////////////////////////////////////////////////

void  process_arg( const char * pszArg )
{
    //printf( "ProcessArg -->%s<--\n", pszArg );
    std::string             fullStr     = pszArg;
    std::string::size_type  splitPos    = fullStr.find('=');
    std::string             tagStr      = "";
    std::string             valStr      = "";
    if ( splitPos != std::string::npos )
    {
        tagStr = fullStr.substr( 0, splitPos );
        valStr = fullStr.substr( splitPos + 1 );
    }
    //printf( "tagStr -->%s<--\n", tagStr.c_str() );
    //printf( "valStr -->%s<--\n", valStr.c_str() );

    if ( process_float_arg( tagStr, valStr ) == false )
    {
        printf( "ERROR: Unhandled Arg -->%s<--\n", pszArg );
    }

    return;
}


/////////////////////////////////////////////////////////////////////////////

size_t  get_malloc_block_size( size_t initSize )
{
    size_t  nResult     = 0;
    size_t  nFirstSize  = 0;
    for ( size_t nMemSize = initSize; ((nResult==0)&&(nMemSize < 1024*1024)); nMemSize++ )
    {
        //printf( "get_malloc_block_size() ==> Trying %lu\n", (unsigned long)nMemSize );
        void * ptrMem1 = malloc( nMemSize );
        void * ptrMem2 = malloc( nMemSize );

        if ( (ptrMem1 == NULL) || (ptrMem2 == NULL) )
        {
            //printf( "ERROR: get_malloc_block_size() ==> Call to malloc(%lu) failed\n", (unsigned long)nMemSize );
            return (0);
        }

        unsigned long   addrMem1 = reinterpret_cast<unsigned long>( ptrMem1 );
        unsigned long   addrMem2 = reinterpret_cast<unsigned long>( ptrMem2 );

        //printf( "get_malloc_block_size() ==> addrMem1 = %lu\n", addrMem1 );
        //printf( "get_malloc_block_size() ==> addrMem2 = %lu\n", addrMem2 );
        if ( addrMem1 > addrMem2 )
        {
            std::swap( addrMem1, addrMem2 );
        }
        unsigned long   curBlockSize   = addrMem2 - addrMem1;
        //printf( "get_malloc_block_size() ==> curBlockSize = %lu\n", curBlockSize );

        if ( nFirstSize == 0 )
        {
            nFirstSize = curBlockSize;
            //printf( "get_malloc_block_size() ==> Storing First Value - curBlockSize = %lu\n", curBlockSize );
        }
        else if ( nFirstSize != curBlockSize )
        {
            //printf( "get_malloc_block_size() ==> Has Changed - nMemSize=%lu bloclSize=%lu\n", (nMemSize-1), nFirstSize );
            nResult = nFirstSize;
        }

        free( ptrMem1 );
        free( ptrMem2 );
    }
    return (nResult);
}

/////////////////////////////////////////////////////////////////////////////
//! int  main( int argC, const char * argV[] )
//
//  :Implementation
//"
int  main( int argC, const char * argV[] )
{
    printf( "Platform Info \n" );

    printf( "   %s\n", PlatformInfoVersion_VersionInfo.m_ProductVersion );
    printf( "   %s\n", PlatformInfoVersion_VersionInfo.m_Copyright );

    printf( " ----------------------------------------------------------------------------\n" );

    printf( "                 CBOLSTER_PLATFORM_NAME ==> %s \n", CBOLSTER_PLATFORM_NAME );
    printf( "                 CBOLSTER_PLATFORM_TYPE ==> %d \n", CBOLSTER_PLATFORM_TYPE );
    #if defined(CBOLSTER_DEBUG)
        printf( "                 CBOLSTER_DEBUG \n" );
    #endif
    #if defined(CBOLSTER_RELEASE)
        printf( "                 CBOLSTER_RELEASE \n" );
    #endif

    printf( " ----------------------------------------------------------------------------\n" );
    size_t mallocBlockSize = 1;
    for ( int nCount = 0; nCount < 8; nCount++ )
    {
        size_t oldSize = mallocBlockSize + 1;
        mallocBlockSize = get_malloc_block_size( oldSize );
        printf( " Malloc Block Size = alloc(%lu) -- uses=%lu\n", (unsigned long)(oldSize), (unsigned long)(mallocBlockSize) ); fflush( stdout );
    }

    printf( " ----------------------------------------------------------------------------\n" );
    printf( " Endian\n" ); fflush( stdout );

    Uint16          endian16    = 0x1234;
    Uint32          endian32    = 0x12345678;
    Uint64          endian64    = 0x123456789ABCDEF0;
    const void *    ptrData16   = static_cast< const void * >( &endian16 );
    const void *    ptrData32   = static_cast< const void * >( &endian32 );
    const void *    ptrData64   = static_cast< const void * >( &endian64 );

    for ( int tIndex = 1; tIndex <= 3; tIndex++ )
    {
        const std::string   labelStr    = ( (tIndex==1) ? "Uint16" : ( (tIndex == 2) ? "Uint32" : "Uint64" ) );
        const std::string   valStr      = ( (tIndex==1) ? "0x1234            " : ( (tIndex == 2) ? "0x12345678        " : "0x123456789ABCDEF0" ) );
        const void *        ptrData     = ( (tIndex==1) ? ptrData16 : ( (tIndex == 2) ? ptrData32 : ptrData64 ) );
        const size_t        dataLen     = ( (tIndex==1) ? sizeof(endian16) : ( (tIndex == 2) ? sizeof(endian32) : sizeof(endian64) ) );
        std::string         dumpStr     = MakeHexDumpStr( ptrData, dataLen );

        const Uint8 *       ptrData8    = static_cast< const Uint8 * >( ptrData );
        Uint8               leadByte    = ptrData8[ 0 ];
        std::string         endianStr   = ( (leadByte == 0x12) ? "BIG   " : "LITTLE" );

        printf( "   %s -- %s -- %s -- %s\n", endianStr.c_str(), labelStr.c_str(), valStr.c_str(), dumpStr.c_str() );
    }

    printf( " ----------------------------------------------------------------------------\n" );

    CBBase_VersionInfo baseVersionInfo;
    CBBase_GetLibraryVersionInfo( &baseVersionInfo );

    printf( "          CBBase_VersionInfo - CompanyName    ==> %s \n", baseVersionInfo.m_CompanyName );
    printf( "          CBBase_VersionInfo - Copyright      ==> %s \n", baseVersionInfo.m_Copyright );
    printf( "          CBBase_VersionInfo - ProductVersion ==> %s \n", baseVersionInfo.m_ProductVersion );
    printf( "          CBBase_VersionInfo - FileVersion    ==> %s \n", baseVersionInfo.m_FileVersion );
    printf( "          CBBase_VersionInfo - ProductName    ==> %s \n", baseVersionInfo.m_ProductName );
    printf( "          CBBase_VersionInfo - Comments       ==> %s \n", baseVersionInfo.m_Comments );
    printf( "          CBBase_VersionInfo - Trademarks     ==> %s \n", baseVersionInfo.m_Trademarks );
    printf( "          CBBase_VersionInfo - FileName       ==> %s \n", baseVersionInfo.m_FileName );
    printf( "          CBBase_VersionInfo - InternalName   ==> %s \n", baseVersionInfo.m_InternalName );
    printf( " ----------------------------------------------------------------------------\n" );

    CBBase::VersionInfo versionInfo;
    CBBase::GetLibraryVersionInfo( versionInfo );

    printf( "          CBBase::VersionInfo - VersionNumber ==> %u.%u.%u.%u\n",
                static_cast<unsigned int>(versionInfo.m_VersionNumber.m_Major),
                static_cast<unsigned int>(versionInfo.m_VersionNumber.m_Minor),
                static_cast<unsigned int>(versionInfo.m_VersionNumber.m_Revision),
                static_cast<unsigned int>(versionInfo.m_VersionNumber.m_Build) );
    printf( "          CBBase::VersionInfo - ProductName   ==> %s \n", versionInfo.m_ProductName );
    printf( "          CBBase::VersionInfo - Version       ==> %s \n", versionInfo.m_Version );
    printf( "          CBBase::VersionInfo - OwnerName     ==> %s \n", versionInfo.m_OwnerName );
    printf( "          CBBase::VersionInfo - Copyright     ==> %s \n", versionInfo.m_Copyright );
    printf( "          CBBase::VersionInfo - Copyright_1   ==> %s \n", versionInfo.m_Copyright_1 );
    printf( "          CBBase::VersionInfo - Copyright_2   ==> %s \n", versionInfo.m_Copyright_2 );
    printf( "          CBBase::VersionInfo - Copyright_3   ==> %s \n", versionInfo.m_Copyright_3 );
    printf( "          CBBase::VersionInfo - Copyright_4   ==> %s \n", versionInfo.m_Copyright_4 );
    printf( "          CBBase::VersionInfo - Comments_1    ==> %s \n", versionInfo.m_Comments_1 );
    printf( "          CBBase::VersionInfo - Comments_2    ==> %s \n", versionInfo.m_Comments_2 );
    printf( "          CBBase::VersionInfo - Comments_3    ==> %s \n", versionInfo.m_Comments_3 );
    printf( "          CBBase::VersionInfo - Comments_4    ==> %s \n", versionInfo.m_Comments_4 );

    printf( " ----------------------------------------------------------------------------\n" );

    DUMP_INT_INFO( time_t );
    DUMP_INT_INFO( size_t );
    DUMP_INT_INFO( off_t );
    DUMP_INT_INFO( ptrdiff_t );
    DUMP_INT_INFO( wchar_t );
    DUMP_INT_INFO( wctype_t );
    DUMP_INT_INFO( wint_t );

    printf( " ----------------------------------------------------------------------------\n" );

    DUMP_INT_INFO( char );
    DUMP_INT_INFO( signed char );
    DUMP_INT_INFO( unsigned char );

    printf( " ----------------------------------------------------------------------------\n" );

    DUMP_INT_INFO( short );
    DUMP_INT_INFO( signed short );
    DUMP_INT_INFO( unsigned short );

    printf( " ----------------------------------------------------------------------------\n" );

    DUMP_INT_INFO( int );
    DUMP_INT_INFO( signed int );
    DUMP_INT_INFO( unsigned int );

    printf( " ----------------------------------------------------------------------------\n" );

    DUMP_INT_INFO( long );
    DUMP_INT_INFO( signed long );
    DUMP_INT_INFO( unsigned long );

    printf( " ----------------------------------------------------------------------------\n" );

    DUMP_INT_INFO( long long );
    DUMP_INT_INFO( signed long long );
    DUMP_INT_INFO( unsigned long long );

    printf( " ----------------------------------------------------------------------------\n" );

    #if defined(Int8_SIZEOF)
        DUMP_INT_INFO( Int8 );
    #endif // defined(Int8_SIZEOF)

    #if defined(Int16_SIZEOF)
        DUMP_INT_INFO( Int16 );
    #endif // defined(Int16_SIZEOF)

    #if defined(Int32_SIZEOF)
        DUMP_INT_INFO( Int32 );
    #endif // defined(Int32_SIZEOF)

    #if defined(Int64_SIZEOF)
        DUMP_INT_INFO( Int64 );
    #endif // defined(Int64_SIZEOF)

    #if defined(Int128_SIZEOF)
        DUMP_INT_INFO( Int128 );
    #endif // defined(Int128_SIZEOF)

    printf( " ----------------------------------------------------------------------------\n" );

    #if defined(Uint8_SIZEOF)
        DUMP_INT_INFO( Uint8 );
    #endif // defined(Uint8_SIZEOF)

    #if defined(Uint16_SIZEOF)
        DUMP_INT_INFO( Uint16 );
    #endif // defined(Uint16_SIZEOF)

    #if defined(Uint32_SIZEOF)
        DUMP_INT_INFO( Uint32 );
    #endif // defined(Uint32_SIZEOF)

    #if defined(Uint64_SIZEOF)
        DUMP_INT_INFO( Uint64 );
    #endif // defined(Uint64_SIZEOF)

    #if defined(Uint128_SIZEOF)
        DUMP_INT_INFO( Uint128 );
    #endif // defined(Uint128_SIZEOF)

    printf( " ----------------------------------------------------------------------------\n" );

    DUMP_STD_FLOAT_TYPE( float );
    DUMP_STD_FLOAT_TYPE( double );
    DUMP_STD_FLOAT_TYPE( long  double );

    printf( " ----------------------------------------------------------------------------\n" );

    #if defined(Float32_SIZEOF)
        DUMP_FLOAT_TYPE( Float32 );
        printf( " ----------------------------------------------------------------------------\n" );
    #endif // defined(Float32_SIZEOF)

    #if defined(Float64_SIZEOF)
        DUMP_FLOAT_TYPE( Float64 );
        printf( " ----------------------------------------------------------------------------\n" );
    #endif // defined(Float64_SIZEOF)

    #if defined(Float80_SIZEOF)
        DUMP_FLOAT_TYPE( Float80 );
        printf( " ----------------------------------------------------------------------------\n" );
    #endif // defined(Float80_SIZEOF)

    #if defined(Float128_SIZEOF)
        DUMP_FLOAT_TYPE( Float128 );
        printf( " ----------------------------------------------------------------------------\n" );
    #endif // defined(Float128_SIZEOF)

    DUMP_INT_INFO( std::string::size_type );
    DUMP_INT_INFO( std::string::value_type );
    DUMP_INT_INFO( std::wstring::size_type );
    DUMP_INT_INFO( std::wstring::value_type );

    printf( " ----------------------------------------------------------------------------\n" );

    for ( int nArg = 1; nArg < argC; nArg++ )
    {
        //printf( "argV[%d] -->%s<--\n", nArg, argV[nArg] );
        process_arg( argV[nArg] );
        printf( " ----------------------------------------------------------------------------\n" );
    }


    #if defined(CBOLSTER_PLATFORM_FAMILY_MSWIN)
        getch();
    #endif // defined(CBOLSTER_PLATFORM_FAMILY_MSWIN)

    return (0);
}
//.



