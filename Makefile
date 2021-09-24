FILES=$(shell find ./test ./src -iname '*.cpp')
HEADER_FILES=$(shell find ./include -iname '*.h')
.PHONY: all
all: format build

.PHONY: format
format:
       @echo "Formatting files with clang"
       @clang-format -i $(FILES)
       @clang-format -i $(HEADER_FILES)

.PHONY: build
build:
       mkdir -p build
       cd build && \
       cmake -DCMAKE_BUILD_TYPE=Release cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -DCMAKE_C_COMPILER=/bin/x86_64-linux-gnu-gcc-11 -DCMAKE_CXX_COMPILER=/bin/x86_64-linux-gnu-g++-11  .. && \
       make

.PHONY: debug   
debug:
       mkdir -p build
       cd build && \
       cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/bin/x86_64-linux-gnu-gcc-11 -DCMAKE_CXX_COMPILER=/bin/x86_64-linux-gnu-g++-11  .. && \
       make

.PHONY: clean

