#!/bin/bash

echo "========= STARTING END TO END TESTS ========="

OUTPUT_FILE="data/output.csv"

../bin/trumpf_zadanie_rekrutacyjne "$(pwd)/data/simple/input.csv" "$OUTPUT_FILE" 3
if diff -q "$OUTPUT_FILE" "$(pwd)/data/simple/expected_output.csv" > /dev/null
then
    echo "Simple test passed"
else
    echo "Simple test failed"
fi

exit 0
