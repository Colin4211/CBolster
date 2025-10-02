#!/bin/bash

CT_VERSION_PREFIX=CThings


if [ "$1" == "REPORT" ] ; then
	CT_VersionTool -Report . -verbose
elif [ "$1" == "" ] ; then
	echo   "CExtendDev -- Incrementing Version"
	CT_VersionTool -CThings ./  -Increment build -verbose
	echo   "CExtendDev -- Marking Version"
	CT_VersionTool -CThings ./ -verbose
else
	echo "CExtendDev -- Marking Version "
	CT_VersionTool -CThings ./  -SetVersionFile "$1" -SetVersionProduct "$CT_VERSION_PREFIX-$1"  -verbose
	echo   "CExtendDev -- Marking Version"
	CT_VersionTool -CThings ./ -verbose
fi




