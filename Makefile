CC  ?= clang
CXX ?= clang++

EXE = sql-file

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++14

CFLAGS = -Wno-deprecated-register -O0 $(CDEBUG) $(CSTD)
CXXFLAGS = -Wno-deprecated-register -O0 $(CXXDEBUG) $(CXXSTD)


CPPOBJ = main fq_driver
SOBJ =  parser lexer

FILES = $(addsuffix .cpp, $(CPPOBJ))

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
	fq_parser.tab.cc fq_parser.tab.hh \
	location.hh position.hh \
	stack.hh fq_parser.output parser.o \
	lexer.o fq_lexer.yy.cc $(EXE)\

.PHONY: all

all: wc test

wc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)


parser: fq_parser.yy
	bison -d -v fq_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o fq_parser.tab.cc

lexer: fq_lexer.l
	flex --outfile=fq_lexer.yy.cc $<
	$(CXX) $(CXXFLAGS) -c fq_lexer.yy.cc -o lexer.o

.PHONY: test
test:
	cd test && ./test0.pl

start:
	./$(EXE) -o

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

