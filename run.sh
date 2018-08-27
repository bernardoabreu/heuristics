#!/bin/bash

BASE="${HOME}/heuristics"

INPUT_DIR="${BASE}/input_files"
OUTPUT_DIR="${BASE}/output"


# # parse the options
# while getopts 'd:v:h' opt ; do
#   case $opt in
#     d) DATA_SETS=("$OPTARG");;
#     v) TEST_VERSION=$OPTARG; USE_ALL=false ;;
#     h) echo "Options: -d data sets (default: ${DATA_SETS[*]})"
#        echo "         -v test version (default: Use all)";
#        exit 0 ;;
#   esac
# done

# # skip over the processed options
# shift $((OPTIND-1)) 


ls $INPUT_DIR | while read -r FILE ; do
    echo "Processing ${FILE}";
    ./source/tsp -f "${INPUT_DIR}/${FILE}" > "${OUTPUT_DIR}/${FILE}.out"
done
