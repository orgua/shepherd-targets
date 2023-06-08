#!/usr/bin/env xonsh

from os.path import *

SCRIPTDIR = abspath(dirname($ARG0))
CONFIGPATH = normpath(SCRIPTDIR + "/glue_config.py")
echo using @(CONFIGPATH)

#$GLUERC = CONFIGPATH
glue -c @(CONFIGPATH)

