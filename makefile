# make
all:

# make test
test: bin/test

# make clean
clean:
	rm -rf obj

# make mrproper
mrproper:
	rm -rf obj bin


# link object files and build binary for unit testing number
bin/test: obj/catch_amalgamated.o obj/utils_string.o obj/number.o obj/test_number.o
	g++ $^ -o $@

# compiles test_number.cpp
obj/test_number.o: test_number.cpp lib/catch_amalgamated.hpp number.h utils/string.h
	g++ -c $< -o $@ -I . -I lib/

# compiles number.cpp
obj/number.o: number.cpp number.h utils/string.h utils/require.h
	g++ -c $< -o $@ -I .

# compiles utils/string.cpp
obj/utils_string.o: utils/string.cpp utils/string.h
	g++ -c $< -o $@ -I .

# compiles lib used for unit testing (catch2)
obj/catch_amalgamated.o: lib/catch_amalgamated.cpp lib/catch_amalgamated.hpp
	g++ -c $< -o $@ -I lib/


.PHONY: all test clean mrproper

# will create all necessary directories after the Makefile is parsed
$(shell mkdir -p obj bin)
