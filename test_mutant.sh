#!/bin/bash

OUTPUT_FILE=test.out

# Compile the file
clang++ RedBlackTreeUtility.c TestRBT.cpp -o "$OUTPUT_FILE" -ldeepstate_AFL
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Compilation successful. Running test..."

# Run the tests
rm -rf fuzz_AFL
./"$OUTPUT_FILE" --fuzz --timeout 10 --abort_on_fail
EXIT_CODE=$?

# Check the program's exit code
if [ $EXIT_CODE -eq 0 ]; then
    echo "Program executed successfully."
else
    echo "Program exited with code $EXIT_CODE."
    exit "$EXIT_CODE"
fi

# Clean up
rm -f "$OUTPUT_FILE"
