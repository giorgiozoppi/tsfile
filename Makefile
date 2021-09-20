.PHONY: all
all: format test build

.PHONY: format
format:
	clang-format src/*.cpp include/*.h -i

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/bin/x86_64-linux-gnu-gcc-11 -DCMAKE_CXX_COMPILER=/bin/x86_64-linux-gnu-g++-11  .. && \
	make


.PHONY: debug   
debug:
	@echo "OS: ${LINUX_DISTRO}"
	mkdir -p build
	cd build && \
	cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/bin/x86_64-linux-gnu-gcc-11 -DCMAKE_CXX_COMPILER=/bin/x86_64-linux-gnu-g++-11  .. && \
	make

.PHONY: clean
clean:
	rm -rf build
