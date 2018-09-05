#!/bin/bash

PROGRAM=test_queue
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
Node{symbol: L, count: 2, left: 0x0, right: 0x0}
Node{symbol: A, count: 1, left: 0x0, right: 0x0}
Node{symbol: B, count: 4, left: 0x0, right: 0x0}
Node{symbol: E, count: 3, left: 0x0, right: 0x0}
Node{symbol: C, count: 0, left: 0x0, right: 0x0}
Node{symbol: A, count: 1, left: 0x0, right: 0x0}
Node{symbol: L, count: 2, left: 0x0, right: 0x0}
Node{symbol: E, count: 3, left: 0x0, right: 0x0}
Node{symbol: B, count: 4, left: 0x0, right: 0x0}
EOF
}

# Setup

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

# Testing

echo "Testing Priority Queue..."

printf " %-40s ... " "queue_create"
./$PROGRAM 0 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_create   (valgrind)"
valgrind --leak-check=full ./$PROGRAM 0 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -eq 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_delete"
./$PROGRAM 1 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_delete   (valgrind)"
valgrind --leak-check=full ./$PROGRAM 1 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_push 0"
./$PROGRAM 2 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_push 0   (valgrind)"
valgrind --leak-check=full ./$PROGRAM 2 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_push 1"
./$PROGRAM 3 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_push 1   (valgrind)"
valgrind --leak-check=full ./$PROGRAM 3 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_push 2"
./$PROGRAM 4 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_push 2   (valgrind)"
valgrind --leak-check=full ./$PROGRAM 4 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_pop"
./$PROGRAM 5 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_pop      (valgrind)"
valgrind --leak-check=full ./$PROGRAM 5 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_dump"
./$PROGRAM 6 &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_dump     (output)"
./$PROGRAM 6 |& diff -y - <(output) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "queue_dump     (valgrind)"
valgrind --leak-check=full ./$PROGRAM 6 &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

TESTS=$(($(grep -c Success $0) - 1))
echo "   Score $(echo "scale=2; ($TESTS - $FAILURES) / $TESTS.0 * 3.00" | bc | awk '{printf "%0.2f\n", $0}')"
echo
