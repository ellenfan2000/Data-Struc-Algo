PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
all: $(PROGS)
cyoa-step1:Story.hpp Page.hpp functions.hpp exception.hpp cyoa-step1.cpp
	g++ -pedantic -g --std=gnu++98 -Werror -Wall -o cyoa-step1 cyoa-step1.cpp
cyoa-step2:Story.hpp Page.hpp cyoa-step2.cpp functions.hpp exception.hpp
	g++ -pedantic -g --std=gnu++98 -Werror -Wall -o cyoa-step2 cyoa-step2.cpp
cyoa-step3:Story.hpp Page.hpp cyoa-step3.cpp functions.hpp exception.hpp
	g++ -pedantic -g --std=gnu++98 -Werror -Wall -o cyoa-step3 cyoa-step3.cpp
cyoa-step4:Story.hpp Page.hpp cyoa-step4.cpp functions.hpp exception.hpp
	g++ -pedantic -g --std=gnu++98 -Werror -Wall -o cyoa-step4 cyoa-step4.cpp

.PHONY: clean
clean:
	rm -f *~ $(PROGS)
