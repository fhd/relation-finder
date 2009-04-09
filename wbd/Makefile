CXX=g++
CXXFLAGS=-g -I /usr/include/boost
LDFLAGS=-l boost_thread
OBJS=main.o search.o server.o client.o thread.o

all: wbd

wbd: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o wbd

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) *.o wbd
