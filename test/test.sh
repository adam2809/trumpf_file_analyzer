#!/bin/bash

echo "========= STARTING TESTS ========="

../bin/trumpf_zadanie_rekrutacyjne data/simple/input.txt data/output.txt
if cmp -s "data/simple/expected_output.txt" "data/output.txt" ; then
    echo "Simple test passed"
else
    echo "Simple test failed"
    exit 1
fi

../bin/trumpf_zadanie_rekrutacyjne data/extended/input.txt data/output.txt
if cmp -s "data/extended/expected_output.txt" "data/output.txt" ; then
    echo "Extended test passed"
else
    echo "Extended test failed"
    exit 1
fi

exit 0
