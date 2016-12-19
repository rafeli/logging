CC = g++ # -D_GLIBCXX_USE_CXX11_ABI=0
CFLAGS = -Wall -g -std=c++0x
LFLAGS = -L/usr/lib/x86_64-linux-gnu -L /home/rafel/local/lib/json++ 
INCLUDES =  -I /home/rafel/local/include


install: src/logging.o
	cp src/logging.hpp ~/local/include/momo
	ar rvs ~/local/lib/libmomoLogging.a src/logging.o

src/logging.o: src/logging.cpp src/logging.hpp
	cd src; $(CC) -c $(CFLAGS) logging.cpp;

clean:
	cd src; rm -f *.o

