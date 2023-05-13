CXX=g++
CXXFLAGS=-std=c++11
SRC=circular_sector.cpp ellipse.cpp main.cpp sort.cpp triangle.cpp
OBJ=circular_sector.o ellipse.o main.o sort.o triangle.o
EXE=hellomake
all:clean $(EXE)
$(EXE):$(OBJ)
    $(CXX) -o $@ $^
$(OBJ):$(SRC)
    $(CXX) -c $^
clean:
    rm -f $(EXE)
    rm -f $(OBJ)