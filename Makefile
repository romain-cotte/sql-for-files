CC  ?= clang
CXX ?= clang++

EXE = sql-file

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++14

CFLAGS = -O0 $(CDEBUG) $(CSTD)
CXXFLAGS = -O0 $(CXXDEBUG) $(CXXSTD)

BUILD = build
SOURCE_DIR = src
STATIC_OUTDIR=out-static
CPPOBJ = main driver
SOBJ = parser lexer

FILES = $(addprefix $(SOURCE_DIR)/, $(addsuffix .cpp, $(CPPOBJ)))

OBJS  = $(addprefix $(SOURCE_DIR)/, $(addsuffix .o, $(CPPOBJ)))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
	parser.tab.cc parser.tab.hh \
	location.hh position.hh \
	stack.hh parser.output parser.o \
	lexer.o lexer.yy.cc $(EXE)\
	$(addprefix $(SOURCE_DIR)/, parser.tab.cc parser.tab.hh \
	location.hh position.hh \
	stack.hh parser.output parser.o \
	lexer.o lexer.yy.cc $(EXE))

all: wc test

wc: $(FILES)
	echo $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BUILD)/$(EXE) $(OBJS) $(SOURCE_DIR)/parser.o $(SOURCE_DIR)/lexer.o $(LIBS)

parser: $(SOURCE_DIR)/parser.yy
	bison -d -v $(SOURCE_DIR)/parser.yy -o $(SOURCE_DIR)/parser.tab.cc
	$(CXX) $(CXXFLAGS) -c -o $(SOURCE_DIR)/parser.o $(SOURCE_DIR)/parser.tab.cc

lexer: $(SOURCE_DIR)/lexer.l
	flex --outfile=$(SOURCE_DIR)/lexer.yy.cc $<
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/lexer.yy.cc -o $(SOURCE_DIR)/lexer.o

$(STATIC_OUTDIR):
	mkdir $@

unittest: $(STATIC_OUTDIR) $(SOURCE_DIR)/util/unittest_test.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_DIR)/util/unittest_test.cpp -o $(STATIC_OUTDIR)/$@
	./$(STATIC_OUTDIR)/$@

vec: $(SOURCE_DIR)/util/vec_test.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_DIR)/util/vec_test.cpp -o $(STATIC_OUTDIR)/$@
	./$(STATIC_OUTDIR)/$@

# $(STATIC_OUTDIR)/hash_test:util/hash_test.cc $(STATIC_LIBOBJECTS) $(TESTHARNESS)
# 	$(CXX) $(LDFLAGS) $(CXXFLAGS) util/hash_test.cc $(STATIC_LIBOBJECTS) $(TESTHARNESS) -o $@ $(LIBS)

test:
	cd test/global && ./test0.pl

start:
	./$(BUILD)/$(EXE) -o

install:
	cp ./$(BUILD)/$(EXE) ~/bin

clean:
	rm -rf $(CLEANLIST)

.PHONY: clean test all unittest
