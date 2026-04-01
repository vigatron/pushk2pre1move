#!/bin/bash
set -euo pipefail

for infile in *.scr; do
    [ -e "$infile" ] || continue

    base="${infile%.scr}"
    outfile_a="${base}a.scr"
    outfile_b="${base}b.scr"

    echo "Обработка $infile -> $outfile_a"
    pushk2pre1move "$infile" 0 ../cfg/zx_filter_a.yaml "$outfile_a"

    echo "Обработка $infile -> $outfile_b"
    pushk2pre1move "$infile" 0 ../cfg/zx_filter_b.yaml "$outfile_b"
done
