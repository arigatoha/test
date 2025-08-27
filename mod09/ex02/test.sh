#!/bin/bash

EXECUTABLE="./PmergeMe"

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found at $EXECUTABLE. Did the makefile fail?"
    exit 1
fi

NUM_OF_ELEMENTS=40
MIN_VALUE=0
MAX_VALUE=40

INPUT_ARRAY=()
UNIQUE_COUNT=0

while [ $UNIQUE_COUNT -lt $NUM_OF_ELEMENTS ]; do
    RAND_NUM=$(( RANDOM % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE ))

    if [[ ! " ${INPUT_ARRAY[@]} " =~ " ${RAND_NUM} " ]]; then
        INPUT_ARRAY+=("$RAND_NUM")
        UNIQUE_COUNT=$((UNIQUE_COUNT + 1))
    fi
done

echo "---TEST_WITH_RANDOM_INPUT---"

$EXECUTABLE "${INPUT_ARRAY[@]}"


if [ $? -eq 0 ]; then
    echo "--- Test passed! ✅ ---"
else
    echo "--- Test failed! ❌ ---"
fi
