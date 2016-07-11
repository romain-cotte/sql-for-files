CC  ?= clang
CXX ?= clang++

EXE = sql-file

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++14

CFLAGS = -Wno-deprecated-register -O0 $(CDEBUG) $(CSTD)
CXXFLAGS = -Wno-deprecated-register -O0 $(CXXDEBUG) $(CXXSTD)

BUILD = build
DIR = src
CPPOBJ = main driver
SOBJ = parser lexer

FILES = $(addprefix $(DIR)/, $(addsuffix .cpp, $(CPPOBJ)))

OBJS  = $(addprefix $(DIR)/, $(addsuffix .o, $(CPPOBJ)))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
	parser.tab.cc parser.tab.hh \
	location.hh position.hh \
	stack.hh parser.output parser.o \
	lexer.o lexer.yy.cc $(EXE)\
	$(addprefix $(DIR)/, parser.tab.cc parser.tab.hh \
	location.hh position.hh \
	stack.hh parser.output parser.o \
	lexer.o lexer.yy.cc $(EXE))

all: wc test

wc: $(FILES)
	echo $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BUILD)/$(EXE) $(OBJS) $(DIR)/parser.o $(DIR)/lexer.o $(LIBS)

parser: $(DIR)/parser.yy
	bison -d -v $(DIR)/parser.yy -o $(DIR)/parser.tab.cc
	$(CXX) $(CXXFLAGS) -c -o $(DIR)/parser.o $(DIR)/parser.tab.cc

lexer: $(DIR)/lexer.l
	flex --outfile=$(DIR)/lexer.yy.cc $<
	$(CXX) $(CXXFLAGS) -c $(DIR)/lexer.yy.cc -o $(DIR)/lexer.o

test:
	cd test/global && ./test0.pl

start:
	./$(BUILD)/$(EXE) -o

install:
	cp ./$(BUILD)/$(EXE) ~/bin

clean:
	rm -rf $(CLEANLIST)

.PHONY: clean test all
