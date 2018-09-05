#!/bin/bash

PROGRAM=test_node
WORKSPACE=/tmp/$PROGRAM.$(id -u)
FAILURES=0

# Functions

error() {
    echo "$@"
    [ -r $WORKSPACE/test ] && (echo; cat $WORKSPACE/test; echo)
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

output() {
    cat <<EOF
Node{symbol: C, count: 0, left: 0x0, right: 0x0}
Node{symbol: A, count: 1, left: 0x0, right: 0x0}
Node{symbol: L, count: 2, left: 0x0, right: 0x0}
Node{symbol: E, count: 3, left: 0x0, right: 0x0}
Node{symbol: B, count: 4, left: 0x0, right: 0x0}
Node{symbol: \n, count: 5, left: 0x0, right: 0x0}
EOF
}

# Setup

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

# Testing

echo "Testing Huffman Node..."

printf " %-40s ... " "node_create"
./$PROGRAM 0 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "node_create    (valgrind)"
valgrind --leak-check=full ./$PROGRAM 0 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -eq 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "node_delete"
./$PROGRAM 1 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "node_delete    (valgrind)"
valgrind --leak-check=full ./$PROGRAM 1 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "node_dump"
./$PROGRAM 2 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "node_dump      (output)"
./$PROGRAM 2 |& diff -y - <(output) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "node_dump      (valgrind)"
valgrind --leak-check=full ./$PROGRAM 2 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

TESTS=$(($(grep -c Success $0) - 1))
echo "   Score $(echo "scale=2; ($TESTS - $FAILURES) / $TESTS.0 * 1.50" | bc | awk '{printf "%0.2f\n", $0}')"
echo
