#!/bin/bash

CT_VERSION_PREFIX=CThings


if [ "$1" == "REPORT" ] ; then
	CT_VersionTool -Report .
elif [ "$1" == "" ] ; then
	echo   "CExtendDev -- Incrementing Version"
	CT_VersionTool -CThings ./  -Increment build
	echo   "CExtendDev -- Marking Version"
	CT_VersionTool -CThings ./
else
	echo "CExtendDev -- Marking Version "
	CT_VersionTool -CThings ./  -SetVersionFile "$1" -SetVersionProduct "$CT_VERSION_PREFIX-$1"
	echo   "CExtendDev -- Marking Version"
	CT_VersionTool  ./
fi




