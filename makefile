SRCDIR=./src/
debug ?= 0

SOURCE = $(shell find $(SRCDIR) -name "*.cpp")
OBJS = $(SOURCE:.cpp=.o)
EXE=depth
CXX=g++
FLAGS=-pedantic -Wall -std=c++17 -I./src -I./external/include/
LDFLAGS= -L./external/lib/ -lGL -lglfw -lfreetype -lspdlog #-Xlinker -v

ifeq ($(debug), 1)
	$(FLAGS) +=-g -DDEPTH_DEBUG
endif

.PHONY: all

all: $(SOURCE) $(EXE)

$(EXE): $(OBJS)
	@echo "Build" $@
	@$(CXX) $(FLAGS) $(LDFLAGS) $(OBJS) -o $@

.cpp.o:
	@echo "Compiling" $@
	@$(CXX) -c $(FLAGS) $< -o $@


clean:
	@echo "Cleaning Objects"
	@rm $(OBJS) $(EXE)
