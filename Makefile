CXX   =  g++
CXXFLAGS = -Wall -Wno-strict-aliasing -Wno-unused-variable 

INCPATHS += -I ./include/ -I /usr/local/include 
SOURCE = $(wildcard $(dir)*.cpp)

OBJS = $(patsubst %.cpp,%.o,$(SOURCE))

EXE = cart 

all:$(EXE)

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(INCPATHS) 

$(OBJS):%.o:%.cpp
	$(CXX)  -c -o $@ $<  $(INCPATHS) -pipe -g -Wall

.PHONY:clean
clean:
	rm -rf $(OBJS)
	rm -rf $(EXE)
