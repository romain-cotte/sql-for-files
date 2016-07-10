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
CPPOBJ = main fq_driver
SOBJ = parser lexer

FILES = $(addprefix $(DIR)/, $(addsuffix .cpp, $(CPPOBJ)))

OBJS  = $(addprefix $(DIR)/, $(addsuffix .o, $(CPPOBJ)))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
	fq_parser.tab.cc fq_parser.tab.hh \
	location.hh position.hh \
	stack.hh fq_parser.output parser.o \
	lexer.o fq_lexer.yy.cc $(EXE)\
	$(addprefix $(DIR)/, fq_parser.tab.cc fq_parser.tab.hh \
	location.hh position.hh \
	stack.hh fq_parser.output parser.o \
	lexer.o fq_lexer.yy.cc $(EXE))

.PHONY: all

all: wc test

wc: $(FILES)
	echo $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BUILD)/$(EXE) $(OBJS) $(DIR)/parser.o $(DIR)/lexer.o $(LIBS)

parser: $(DIR)/fq_parser.yy
	bison -d -v $(DIR)/fq_parser.yy -o $(DIR)/fq_parser.tab.cc
	$(CXX) $(CXXFLAGS) -c -o $(DIR)/parser.o $(DIR)/fq_parser.tab.cc

lexer: $(DIR)/fq_lexer.l
	flex --outfile=$(DIR)/fq_lexer.yy.cc $<
	$(CXX) $(CXXFLAGS) -c $(DIR)/fq_lexer.yy.cc -o $(DIR)/lexer.o

.PHONY: test
test:
	cd test/global && ./test0.pl

start:
	./$(BUILD)/$(EXE) -o

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

