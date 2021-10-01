# Apache IoTDB TsFile Native.

## Status
![Build Status](https://app.travis-ci.com/giorgiozoppi/tsfile.svg?branch=dev)
[![Coverage Status](https://coveralls.io/repos/github/giorgiozoppi/tsfile/badge.svg?branch=dev)](https://coveralls.io/github/giorgiozoppi/tsfile?branch=dev)

## Welcome!
Apache IoTDB TsFile Native is a C++20 library for reading/storing Apache IOTDB TsFile. TsFile is a columnar storage file format designed for time series data, which supports efficient compression and query. It is easy to integrate TsFile into your IoT big data processing frameworks.

## Motivation

The target of TsFile project is to support: high ingestion rate up to tens of million data points per second and rare updates only for the correction of low quality data; compact data packaging and deep compression for long-live historical data; traditional sequential and conditional query, complex exploratory query, signal processing, data mining and machine learning. The goal of this project is to provide tsfile for embedded applications where resource consumption is improtant.

## Current Code.


We've just started so for the moment, this is just an exercise in C++ 20 but we plan to work on it deeply in the next weeks. Still there's nothing usable.

### Code Coverage

To build with gcov code coverage and upload results to http://coveralls.io, here are some instructions.

First, build the project with coverage and run the test suite

- ``` cd $TS_FILE_HOME ```
- ``` mkdir debug ```
- ``` cd build ```
- ``` ctest -v ```
- ``` make coverage-report ```
- ``` gem install coveralls-lcov```  (you need ruby)
- ``` coveralls-lcov --repo-token "COVERALL_TOKEN" coverage.info```

## Features
The features of TsFile is as follow:

- Write
  - Fast data import
  - Efficiently compression schemas
- Read
  - Efficiently query
  - Time-sorted query data set

Below we see a eye of bird view image:

![TsFile Format Structure](/assets/format.png)

## Code Style

We use for the naming the Google C++ Code Style Guidelines. Please look at (https://google.github.io/styleguide/cppguide.html#General_Naming_Rules)

## Visual Studio Code Support.

We provide Visual Studio Code support for C/C++ Extensions in the vscode_cpp.json. If you want to use it, we require llvm-13. To
setup clang-13 in Ubuntu 20.04 you need to execute the following commands:
```
$ wget -O /tmp/repo.key https://apt.llvm.org/llvm-snapshot.gpg.key
$ sudo apt-key add /tmp/repo.key
$ sudo add-apt-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-13 main"
$ sudo apt-get -y update
$ sudo apt-get -y install clang-13 clang-tools-13 libclang-common-13-dev libclang-13-dev libclang1-13 clang-format-13 libc++-13-dev libc++abi-13-dev lld-13 libunwind-13-dev libfuzzer-13-dev
```
Then you might want to copy vscode_cpp.json in your ```.vscode/c_cpp_properties.json```.

# Documentation / Doxygen
We support doxygen in the Release target. So you might need to install:
```
$ apt-get install doxygen graphviz
$ make docs
```
The above command will generate the html documentation in build.

