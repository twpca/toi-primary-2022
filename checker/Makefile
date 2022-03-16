CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -D CMS -D TESTSYS
CHECKER_LIST = diff spy

all: $(CHECKER_LIST)

clean:
	rm -f $(CHECKER_LIST)

diff: diff.cpp
	$(CC) diff.cpp $(CCARGS) -o diff

spy: spy.cpp
	$(CC) spy.cpp $(CCARGS) -o spy
