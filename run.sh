#!/bin/bash

BASE="${HOME}/heuristics"

INPUT_DIR="${BASE}/input_files"
OUTPUT_DIR=$1

echo "Heuristic" > $OUTPUT_DIR;
echo "" >> $OUTPUT_DIR;

ls -1v $INPUT_DIR | while read -r FILE ; do
    echo "Processing ${FILE}";
    echo "${FILE}:" >> $OUTPUT_DIR;
    $BASE/source/tsp -f "${INPUT_DIR}/${FILE}" >> $OUTPUT_DIR;
    echo "" >> $OUTPUT_DIR;
done
