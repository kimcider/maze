CC=gcc
OBJS=main.o
TARGET=makeMaze

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c
	gcc -c main.c

clean:
	rm *.o
	rm $(TARGET)
