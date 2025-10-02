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
//      CBolster\Libraries\CBBase\CBBase.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CBBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CBBase_h
#define _CBBase_h

/////////////////////////////////////////////////////////////////////////////

#include "CBBase_Platform.h"

/////////////////////////////////////////////////////////////////////////////
//  Some compilers dont support constexpr.  So we use this
//  #define to allow that code to still compile.  Even if its a little
//  less efficient
//

#if defined(CBOLSTER_PLATFORM_FAMILY_LINUX)
    #define CBOLSTER_CONSTEXPR_FUNCTION  constexpr

    #define CBOLSTER_CONSTEXPR_DECLARE   constexpr
    #define CBOLSTER_CONSTEXPR_DEFINE    constexpr
#else
    #define CBOLSTER_CONSTEXPR_FUNCTION

    #define CBOLSTER_CONSTEXPR_DECLARE
    #define CBOLSTER_CONSTEXPR_DEFINE    const
#endif


/////////////////////////////////////////////////////////////////////////////
//  Includes
//

#include "CBBase_MSWindows.h"
#include "CBBase_Linux.h"

#include "CBBase_StdC.h"
#include "CBBase_StdCPP.h"

#include "CBBase_Integers.h"
#include "CBBase_FloatClass.h"
#include "CBBase_Floats.h"

#include "CBBase_VectorTypes.h"
#include "CBBase_DequeTypes.h"
#include "CBBase_ListTypes.h"
#include "CBBase_SetTypes.h"

#include "CBBase_VersionNumber.h"
#include "CBBase_VersionInfo.h"
#include "CBBase_GetLibraryVersionInfo.h"


/////////////////////////////////////////////////////////////////////////////

#endif  // _CBBase_h


