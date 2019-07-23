#!/bin/bash
cd $(dirname "${0}")
# ./cleancmake.sh
cmake .
make
chmod u+x ./src/2019_cg_physics
./src/2019_cg_physics
