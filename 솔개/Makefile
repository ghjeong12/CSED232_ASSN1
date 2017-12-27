CC=g++
TARGET=main

all:$(TARGET)

$(TARGET): $(TARGET).o ToppingList.o Topping.o DoughList.o Dough.o Edge.o EdgeList.o
	$(CC) -o $(TARGET) $(TARGET).o ToppingList.o Topping.o DoughList.o Dough.o Edge.o EdgeList.o

main.o: main.cpp
	g++ -c -o main.o main.cpp

EdgeList.o: Edge.o
	g++ -c -o EdgeList.o EdgeList.cpp

Edge.o: Edge.cpp Edge.h
	g++ -c -o Edge.o Edge.cpp

doughlist.o: dough.o
	g++ -c -o doughlist.o doughlist.cpp

dough.o: dough.cpp dough.h
	g++ -c -o dough.o dough.cpp

ToppingList.o: Topping.o
	g++ -c -o ToppingList.o ToppingList.cpp

Topping.o: Topping.cpp Topping.h
	g++ -c -o Topping.o Topping.cpp

clean:
	@rm -rf $(TARGET)
	@rm -rf *.o
