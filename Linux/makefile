CC = g++ 
CFLAGS = -c -O3 -std=c++0x -fexceptions -frtti
LD = $(CC)
LDFLAGS = 
CPPFLAGS = -D__LINUX__=1 -DBOOST_MODE=1 -DBOOST_UTILS=1 -D_DEBUG=1

CWD :=  $(shell readlink -en $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))

LIB_PATH := -L$(CWD)/lib
LIB := -lapiwrapper

INC := -I./
INC += -I$(CWD)/include

MODULE = spGateway 

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CPP_FILES = $(call rwildcard, , *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(CPP_FILES))

all: $(MODULE)

$(MODULE): $(OBJECTS)
	$(LD) $(INC) $(LDFLAGS) $(LIB_PATH) -o $@ $^ $(LIB)

%.o: %.cpp
	$(CC) $(INC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm $(TARGET) $(OBJECTS) $(MODULE)


# CC = g++ 
# # CFLAGS = -c -O3 -std=c++0x -fexceptions -frtti -lmemcached -lmemcachedutil -lredis++ -lhiredis -pthread
# CFLAGS = -c -O3 -std=c++0x -fexceptions -frtti 
# LD = $(CC)
# CPPFLAGS = -D__LINUX__=1 -DBOOST_MODE=1 -DBOOST_UTILS=1 -D_DEBUG=1

# CWD :=  $(shell readlink -en $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))

# LDFLAGS =

# # LIBFLAGS = -lmemcached -lmemcachedutil -lredis++ -lhiredis -pthread
# LIBFLAGS =

# LIB_PATH := -L$(CWD)/lib
# LIB := -lapiwrapper

# INC := -I./
# INC += -I$(CWD)/include

# MODULE = apitester 

# rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# CPP_FILES = $(call rwildcard, , *.cpp)
# OBJECTS = $(patsubst %.cpp, %.o, $(CPP_FILES))

# all: $(MODULE)

# $(MODULE): $(OBJECTS)
# 	$(LD) $(INC) $(LDFLAGS) $(LIB_PATH) -o $@ $^ $(LIB) $(LIBFLAGS)

# %.o: %.cpp
# 	$(CC) $(INC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

# clean:
# 	rm $(TARGET) $(OBJECTS) $(MODULE)
