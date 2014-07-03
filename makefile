#Compiler Variables
CC = g++
CPPFLAGS = -Wall -g -std=c++11

#Location of files
SRC_DIR=src
HEADER_DIR=include


CPPFLAGS += -I $(HEADER_DIR)/


all: twitter

twitter: twitter.o user.o tweet.o
	$(CC) $(CPPFLAGS) -o twitter twitter.o user.o tweet.o

twitter.o: $(SRC_DIR)/twitter.cpp $(HEADER_DIR)/Map.h $(HEADER_DIR)/Set.h $(HEADER_DIR)/AList.h $(HEADER_DIR)/tweet.h 
	$(CC) $(CPPFLAGS) -c -o twitter.o $(SRC_DIR)/twitter.cpp

user.o: $(SRC_DIR)/user.cpp $(HEADER_DIR)/user.h $(HEADER_DIR)/tweet.h $(HEADER_DIR)/datetime.h
	$(CC) $(CPPFLAGS) -c -o user.o $(SRC_DIR)/user.cpp

tweet.o: $(SRC_DIR)/tweet.cpp $(HEADER_DIR)/tweet.h $(HEADER_DIR)/datetime.h
	$(CC) $(CPPFLAGS) -c -o tweet.o $(SRC_DIR)/tweet.cpp


##twitter.o: $(HEADER_DIR)/twitter.h
##	$(CC) $(CPPFLAGS) -c -o twitter.o $(HEADER_DIR)/twitter.h
	
.PHONY: clean

clean:
	@rm -f *.o twitter 