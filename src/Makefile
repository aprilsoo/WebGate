CC = g++
TARGET = a.out
SRC = $(wildcard  ./http/*.cpp ./pool/*.cpp ./server/*.cpp ./tool/*.cpp)
OBJ = $(patsubst %.cpp, %.o , $(SRC))

$(TARGET):$(OBJ)
	$(CC) $^ -lpthread -lmysqlclient -o $@ 

%.o:%.cpp
	$(CC) -c $< -o $@

clean:$(OBJ)
	rm $(OBJ)