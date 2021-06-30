# Compile Command Example (Using g++)
g++ test.cpp -O2 -o example2 -std=c++20 -Wall -L../build/ -lcptp
mkdir -p tex
LD_LIBRARY_PATH=../build/ ./example2
