SOURCES = src/matrix.cpp src/main.cpp 
INCLUDES = include

CC 	= g++
CFLAGS = -I$(INCLUDES)

OBJS = $(SOURCES:.cpp=.o)
TARGET = main

%.o : %.cpp
	$(CC) -c $(CFLAGS) -o  $@ $^


$(TARGET).out :$(OBJS)
	$(CC) -o $(CFLAGS) $(TARGET).out  $(OBJS) 

matrix.o : matrix.h
main.o : matrix.o

