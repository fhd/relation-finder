CXX=g++
CXXFLAGS=-I /usr/include/boost
LDFLAGS=-l boost_thread

NAME=wbd
OBJS=main.o search.o client.o thread.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(NAME)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) *.o $(NAME)
