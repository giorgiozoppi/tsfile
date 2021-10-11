PHONY: all
all: format build

.PHONY: release
release : build-clang

.PHONY: build-clang

build-clang:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++-13  .. && \
	make

.PHONY: debug-clang
debug-clang:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++-13  .. && \
	make
.PHONY: cover
cover:	test
	cd $(shell pwd)/build && make coverage-report

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -DCMAKE_CXX_COMPILER=/bin/x86_64-linux-gnu-g++-11  .. && \
	make

.PHONY: debug   
debug:
	mkdir -p build
	cd build && \
	cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/bin/x86_64-linux-gnu-gcc-11 -DCMAKE_CXX_COMPILER=/bin/x86_64-linux-gnu-g++-11  .. && \
	make

.PHONY: clean
clean:	
	@echo "Cleaning up building directory"
	@rm -fr build


.PHONY: stylecheck

stylecheck:
	@echo "Checking Google Style Guide"
	@cd build && make stylelint

.PHONY: format

format:
	@echo "Formatting files with clang"
	clang-format -i $(shell find ./src -iname '*.cc')
	clang-format -i $(shell find ./include -iname '*.h')

.PHONY: test

test:
	./build/unit_test

.PHONY: viewcoverage
viewcoverage:
	lcov --capture --directory ./build --output-file coverage.info
	firefox $(shell pwd)/build/coverage/index.html

.PHONY: viewdocs
viewdocs:
	firefox $(shell pwd)/build/docs/html/index.html

