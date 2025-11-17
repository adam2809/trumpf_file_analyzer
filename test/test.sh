#!/bin/bash

echo "========= STARTING END TO END TESTS ========="

OUTPUT_FILE="data/output.csv"

../bin/trumpf_zadanie_rekrutacyjne "$(pwd)/data/simple_lf/input.csv" "$OUTPUT_FILE" 3
if diff -q "$OUTPUT_FILE" "$(pwd)/data/simple_lf/expected_output.csv" > /dev/null
then
    echo "Simple test with LF files passed"
else
    echo "Simple test with LF files failed"
fi

../bin/trumpf_zadanie_rekrutacyjne "$(pwd)/data/simple_crlf/input.csv" "$OUTPUT_FILE" 3
if diff -q "$OUTPUT_FILE" "$(pwd)/data/simple_crlf/expected_output.csv" > /dev/null
then
    echo "Simple test with CRLF files passed"
else
    echo "Simple test with CRLF files failed"
fi

../bin/trumpf_zadanie_rekrutacyjne "$(pwd)/data/extended/input.csv" "$OUTPUT_FILE" 15
if diff -q "$OUTPUT_FILE" "$(pwd)/data/extended/expected_output.csv" > /dev/null
then
    echo "Extended test passed"
else
    echo "Extended test failed"
fi

exit 0
