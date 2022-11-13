test: search.o test-bsearch.cpp
	g++ -Werror -Wall -pedantic -g --std=gnu++98 -o test search.o test-bsearch.cpp
search.o : search.cpp
	g++ -Werror -Wall -pedantic -g --std=gnu++98 -c search.cpp
.PHONY: clean
clean:
	rm -f search.o test
