#Compiler Variables
CC = g++
CPPFLAGS = -Wall -g -std=c++11

#Location of files
SRC_DIR=src
HEADER_DIR=header


CPPFLAGS += -I $(HEADER_DIR)/


all: twitter

twitter: twitter_unit.o
	$(CC) $(CPPFLAGS) -o twitter_unit twitter_unit.o

twitter_unit.o: $(SRC_DIR)/twitter_unit.cpp $(HEADER_DIR)/twitter.h
	$(CC) $(CPPFLAGS) -c -o twitter_unit.o $(SRC_DIR)/twitter_unit.cpp


##twitter.o: $(HEADER_DIR)/twitter.h
##	$(CC) $(CPPFLAGS) -c -o twitter.o $(HEADER_DIR)/twitter.h
	
.PHONY: clean

clean:
	@rm -f *.o twitter 