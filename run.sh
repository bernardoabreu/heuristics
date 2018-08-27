#!/bin/bash

BASE="${HOME}/heuristics"

INPUT_DIR="${BASE}/input_files"
OUTPUT_DIR="${BASE}/output"


mkdir -p $OUTPUT_DIR


ls $INPUT_DIR | while read -r FILE ; do
    echo "Processing ${FILE}";
    ./source/tsp -f "${INPUT_DIR}/${FILE}" > "${OUTPUT_DIR}/${FILE}.out"
done
