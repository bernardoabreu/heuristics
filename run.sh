#!/bin/bash

BASE="${HOME}/heuristics"

INPUT_DIR="${BASE}/input_files"


echo "Heuristic" > out;
echo "" >> out;

ls -1v $INPUT_DIR | while read -r FILE ; do
    echo "Processing ${FILE}";
    echo "${FILE}:" >> out;
    $BASE/source/tsp -f "${INPUT_DIR}/${FILE}" >> out;
    echo "" >> out;
done
