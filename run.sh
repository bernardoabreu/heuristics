#!/bin/bash

BASE="${HOME}/heuristics"

INPUT_DIR="${BASE}/input_files"
OUTPUT_DIR="${BASE}/output"


mkdir -p $OUTPUT_DIR


echo "Construtive heuristic" > out;
echo "" >> out;

ls $INPUT_DIR | while read -r FILE ; do
    echo "Processing ${FILE}";
    echo "${FILE}:" >> out;
    ./source/tsp -f "${INPUT_DIR}/${FILE}" >> out;
    echo "" >> out;
done
