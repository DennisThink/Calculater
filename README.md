##Calculater

Author: DennisMi. 
Site: https://www.dennisthink.com 
Email: dennismi1024@gmail.com

---
![Buildtool](https://img.shields.io/badge/buildtool-CMake-green.svg) ![PlatForm](https://img.shields.io/badge/platform-Windows%20%20Linux-brightgreen.svg) ![compiler](https://img.shields.io/badge/compiler-gcc_clang_VS-brightgreen.svg) ![testtool](https://img.shields.io/badge/test-doctest-brightgreen.svg)
---
This is a simple Calculater writen by C++ with C++11 standard.It Only Support Add(+),Sub(-),Mul(*) and Div(/) 4 operators and LeftBracket('(') and Right bracket(')') Expresion。


Expression Example:
---
1. 2+3 * 4=14.0000
2. 2+2 * (2-4)=-2.0000


The result is because I use `double` to represent a number in the program.

Compiler Result:
----
|Platform|Compiler|Result|
|--------|--------|------|
|Window7(64Bit)|VS2015(Community Edition)|Passed|
|Ubuntu(16.04  64Bit)|gcc 6.3.0 |Passed|
|Ubuntu(16.04  64Bit)|clang6.0 |Passed|

Detail:
---
I have test It with `doctest`.It can be compiled On Windows7 64Bit with CMake and VS2015 and on Ubuntu 16.04 with g++6.3.0 and Clang 6.0.

Build:
-----
![testtool](https://img.shields.io/badge/Linux-g++_clang++-brightgreen.svg)


```
//Make temp dir
mkdir build

//chdir to temp dir
cd build

//use g++
cmake .. -DCMAKE_CXX_COMPILER=g++

//use clang++
cmake .. -DCMAKE_CXX_COMPILER=clang++

//build
make -j4 

//compute
./calu

//test
./testCalu
```
---
Other:
*doctest*: https://github.com/onqtam/doctest

