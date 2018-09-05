#!/bin/bash

PROGRAM=huff
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

# Setup

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

# I/O

input_0() {
    cat <<EOF
ABBCCCDDDDEEEEEFFFFFF
EOF
}

output_0_tsv() {
    cat <<EOF
D	00	4
E	01	5
F	10	6
C	110	3
B	1110	2
\n	11110	1
A	11111	1
EOF
}

output_0_csv() {
    cat <<EOF
"D","00",4
"E","01",5
"F","10",6
"C","110",3
"B","1110",2
"\n","11110",1
"A","11111",1
EOF
}

output_0_json() {
    cat <<EOF
{
  "D": {"encoding": "00", "count": 4},
  "E": {"encoding": "01", "count": 5},
  "F": {"encoding": "10", "count": 6},
  "C": {"encoding": "110", "count": 3},
  "B": {"encoding": "1110", "count": 2},
  "\n": {"encoding": "11110", "count": 1},
  "A": {"encoding": "11111", "count": 1},
}
EOF
}

output_0_yaml() {
    cat <<EOF
"D": {"encoding": "00", "count": 4}
"E": {"encoding": "01", "count": 5}
"F": {"encoding": "10", "count": 6}
"C": {"encoding": "110", "count": 3}
"B": {"encoding": "1110", "count": 2}
"\n": {"encoding": "11110", "count": 1}
"A": {"encoding": "11111", "count": 1}
EOF
}

input_1() {
    cat <<EOF
Watch and pray so that you will not fall into temptation. The spirit is
willing, but the flesh is weak.
EOF
}

output_1_tsv() {
    cat <<EOF
h	0000	5
n	0001	5
o	0010	5
u	00110	2
k	001110	1
y	001111	2
s	0100	5
e	0101	5
t	011	11
w	10000	3
p	10001	3
a	1001	7
l	1010	7
.	101100	2
c	1011010	1
m	1011011	1
d	1011100	1
b	1011101	1
g	1011110	1
T	1011111	1
\n	110000	2
,	1100010	1
W	1100011	1
f	110010	2
r	110011	2
i	1101	9
 	111	18
EOF
}

output_1_csv() {
    cat <<EOF
"h","0000",5
"n","0001",5
"o","0010",5
"u","00110",2
"k","001110",1
"y","001111",2
"s","0100",5
"e","0101",5
"t","011",11
"w","10000",3
"p","10001",3
"a","1001",7
"l","1010",7
".","101100",2
"c","1011010",1
"m","1011011",1
"d","1011100",1
"b","1011101",1
"g","1011110",1
"T","1011111",1
"\n","110000",2
",","1100010",1
"W","1100011",1
"f","110010",2
"r","110011",2
"i","1101",9
" ","111",18
EOF
}

output_1_json() {
    cat <<EOF
{
  "h": {"encoding": "0000", "count": 5},
  "n": {"encoding": "0001", "count": 5},
  "o": {"encoding": "0010", "count": 5},
  "u": {"encoding": "00110", "count": 2},
  "k": {"encoding": "001110", "count": 1},
  "y": {"encoding": "001111", "count": 2},
  "s": {"encoding": "0100", "count": 5},
  "e": {"encoding": "0101", "count": 5},
  "t": {"encoding": "011", "count": 11},
  "w": {"encoding": "10000", "count": 3},
  "p": {"encoding": "10001", "count": 3},
  "a": {"encoding": "1001", "count": 7},
  "l": {"encoding": "1010", "count": 7},
  ".": {"encoding": "101100", "count": 2},
  "c": {"encoding": "1011010", "count": 1},
  "m": {"encoding": "1011011", "count": 1},
  "d": {"encoding": "1011100", "count": 1},
  "b": {"encoding": "1011101", "count": 1},
  "g": {"encoding": "1011110", "count": 1},
  "T": {"encoding": "1011111", "count": 1},
  "\n": {"encoding": "110000", "count": 2},
  ",": {"encoding": "1100010", "count": 1},
  "W": {"encoding": "1100011", "count": 1},
  "f": {"encoding": "110010", "count": 2},
  "r": {"encoding": "110011", "count": 2},
  "i": {"encoding": "1101", "count": 9},
  " ": {"encoding": "111", "count": 18},
}
EOF
}

output_1_yaml() {
    cat <<EOF
"h": {"encoding": "0000", "count": 5}
"n": {"encoding": "0001", "count": 5}
"o": {"encoding": "0010", "count": 5}
"u": {"encoding": "00110", "count": 2}
"k": {"encoding": "001110", "count": 1}
"y": {"encoding": "001111", "count": 2}
"s": {"encoding": "0100", "count": 5}
"e": {"encoding": "0101", "count": 5}
"t": {"encoding": "011", "count": 11}
"w": {"encoding": "10000", "count": 3}
"p": {"encoding": "10001", "count": 3}
"a": {"encoding": "1001", "count": 7}
"l": {"encoding": "1010", "count": 7}
".": {"encoding": "101100", "count": 2}
"c": {"encoding": "1011010", "count": 1}
"m": {"encoding": "1011011", "count": 1}
"d": {"encoding": "1011100", "count": 1}
"b": {"encoding": "1011101", "count": 1}
"g": {"encoding": "1011110", "count": 1}
"T": {"encoding": "1011111", "count": 1}
"\n": {"encoding": "110000", "count": 2}
",": {"encoding": "1100010", "count": 1}
"W": {"encoding": "1100011", "count": 1}
"f": {"encoding": "110010", "count": 2}
"r": {"encoding": "110011", "count": 2}
"i": {"encoding": "1101", "count": 9}
" ": {"encoding": "111", "count": 18}
EOF
}

# Testing

echo "Testing Huffman utility..."

printf " %-40s ... " "Usage"
if ! ./$PROGRAM -h |& grep -q -i usage; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 0 (TSV)"
input_0 | ./$PROGRAM |& diff -y - <(output_0_tsv) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 0 (TSV)  (valgrind)"
input_0 | valgrind --leak-check=full ./$PROGRAM &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 0 (CSV)"
input_0 | ./$PROGRAM -f csv |& diff -y - <(output_0_csv) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 0 (CSV)  (valgrind)"
input_0 | valgrind --leak-check=full ./$PROGRAM -f csv &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 0 (JSON)"
input_0 | ./$PROGRAM -f json |& diff -y - <(output_0_json) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 0 (JSON) (valgrind)"
input_0 | valgrind --leak-check=full ./$PROGRAM -f json&> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 0 (YAML)"
input_0 | ./$PROGRAM -f yaml |& diff -y - <(output_0_yaml) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 0 (YAML) (valgrind)"
input_0 | valgrind --leak-check=full ./$PROGRAM -f yaml&> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 1 (TSV)"
input_1 | ./$PROGRAM -f tsv |& diff -y - <(output_1_tsv) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 1 (TSV)  (valgrind)"
input_1 | valgrind --leak-check=full ./$PROGRAM &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 1 (CSV)"
input_1 | ./$PROGRAM -f csv |& diff -y - <(output_1_csv) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 1 (CSV)  (valgrind)"
input_1 | valgrind --leak-check=full ./$PROGRAM -f csv &> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 1 (JSON)"
input_1 | ./$PROGRAM -f json |& diff -y - <(output_1_json) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 1 (JSON) (valgrind)"
input_1 | valgrind --leak-check=full ./$PROGRAM -f json&> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 1 (YAML)"
input_1 | ./$PROGRAM -f yaml |& diff -y - <(output_1_yaml) &> $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "Input 1 (YAML) (valgrind)"
input_1 | valgrind --leak-check=full ./$PROGRAM -f yaml&> $WORKSPACE/test
if [ $(awk '/ERROR SUMMARY:/ {print $4}' $WORKSPACE/test) -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

TESTS=$(($(grep -c Success $0) - 1))
echo "   Score $(echo "scale=2; ($TESTS - $FAILURES) / $TESTS.0 * 2.50" | bc | awk '{printf "%0.2f\n", $0}')"
echo
