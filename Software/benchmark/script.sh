#!/bin/ bash

set -Eeuxo pipefail

src_DIR="/home/vincent/Desktop/Bachelor/Software/source"
OUT_DIR="/home/vincent/Desktop/Bachelor/Software/build" 

REGEX="aa.a.ba.b.cd.c.|+.d.d.d."
Q_GRAM=3;
NUMBER=20;

./benchmark $REGEX $NUMBER
