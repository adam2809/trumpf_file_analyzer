#!/bin/bash

echo "========= STARTING END TO END TESTS ========="

OUTPUT_FILE="data/output.csv"

rm -f "$OUTPUT_FILE"
../bin/trumpf_zadanie_rekrutacyjne "$(pwd)/data/simple/input.csv" "$OUTPUT_FILE" 3
if diff -q "$OUTPUT_FILE" "$(pwd)/data/simple/expected_output.csv" > /dev/null
then
    echo "Simple test passed"
else
    echo "Simple test failed"
fi

rm -f "$OUTPUT_FILE"
../bin/trumpf_zadanie_rekrutacyjne "$(pwd)/data/extended/input.csv" "$OUTPUT_FILE" 15
if diff -q "$OUTPUT_FILE" "$(pwd)/data/extended/expected_output.csv" > /dev/null
then
    echo "Extended test passed"
else
    echo "Extended test failed"
fi

rm -f "$OUTPUT_FILE"

exit 0
