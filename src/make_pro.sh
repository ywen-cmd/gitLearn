#!/bin/bash

pushd $(pwd) > /dev/null
cd $(dirname ${BASH_SOURCE:-$0})
cd ..

python $(pwd)/tools/make_msg_finder.py $(pwd)
qmake -makefile .qmake.cache.pro DEFINES+=NETLIST_VIEWER
qmake -makefile -recursive procise.pro $@

popd > /dev/null