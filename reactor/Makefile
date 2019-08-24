include config.mk
OPT ?= -g2
CXXFLAGS += $(PLATFORM_CXXFLAGS) -lhandy $(PLATFORM_LDFLAGS)

CFLAGS +=  $(OPT) 

SRC_C_FILES=$(wildcard *.c)
PROG_C_FILES=$(SRC_C_FILES:.c=)

SRCS=$(wildcard *.cpp)
PROGS=$(SRCS:.cpp=)


OBJ=$(SRCS:.cpp=.o)  $(PROG_C_FILES:.c=.o)

all:$(OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)


$(PROG_C_FILES):%:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGS):%:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(PROGS) $(PROG_C_FILES)



