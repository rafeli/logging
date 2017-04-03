CC = g++ 
HOSTNAME = $(shell hostname)
$(info $$HOSTNAME is '${HOSTNAME}')
ifeq "$(HOSTNAME)" "castor"
CC = g++ -D_GLIBCXX_USE_CXX11_ABI=0
endif

CFLAGS = -Wall -g -std=c++0x
LFLAGS = -L/usr/lib/x86_64-linux-gnu -L /home/rafel/local/lib/json++ 
INCLUDES =  -I /home/rafel/local/include


install: src/logging.o src/testTools.o
	cp src/logging.hpp ~/local/include/momo
	cp src/testTools.hpp ~/local/include/momo
	ar rvs ~/local/lib/libmomoLogging.a src/logging.o src/testTools.o

src/logging.o: src/logging.cpp src/logging.hpp
	cd src; $(CC) -c $(CFLAGS) logging.cpp;

src/testTools.o: src/testTools.cpp src/testTools.hpp
	cd src; $(CC) -c $(CFLAGS) testTools.cpp;

clean:
	cd src; rm -f *.o

