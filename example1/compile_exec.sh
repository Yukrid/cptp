# Compile Command Example (Using g++)
g++ example1.cpp -O2 -o example1 -std=c++20 -Wall -L../build/ -lcptp
mkdir -p tex
LD_LIBRARY_PATH=../build/ ./example1
