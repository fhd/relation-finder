CXX=g++
CXXFLAGS=-I /usr/include/boost
LDFLAGS=-l boost_thread

NAME=wbd
TARGETS=main graph_searcher client thread
OBJECTS=$(addsuffix .o,$(TARGETS))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	$(RM) $(OBJECTS) $(NAME)
