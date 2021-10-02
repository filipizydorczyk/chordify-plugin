#!/bin/bash

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

rm -rf ~/.lv2/chordify.lv2/
cp -r ${SCRIPT_DIR}/../build/chordify.lv2 ~/.lv2/chordify.lv2/
