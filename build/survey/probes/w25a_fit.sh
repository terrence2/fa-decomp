#!/usr/bin/env bash
# usage: w25a_fit.sh <path/to/obj> <rvaDEC> <out_fit.obj> [--map ...] [--patch ...]
cd /home/terrence/Projects/fa-decomp
python3 tools/fitobj.py "$1" "$2" "$3" "${@:4}"
