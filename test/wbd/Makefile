CXX=g++
CXXFLAGS=-I /usr/include/boost
LDFLAGS=-l boost_unit_test_framework

TARGETS=graph_searcher_test
SOURCE_DIR=../../src/wbd
SOURCE_FILES=$(SOURCE_DIR)/graph_searcher.cpp

all: $(TARGETS)

test: $(TARGETS) $(addprefix run-,$(TARGETS))

%: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SOURCE_FILES) -o $@ $^

run-%: %
	-./$^

clean:
	$(RM) $(TARGETS)
