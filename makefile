#Compiler Variables
CC = g++
CPPFLAGS = -Wall -g -std=c++11

#Location of files
SRC_DIR=src
HEADER_DIR=include
BIN_DIR=bin


CPPFLAGS += -I $(HEADER_DIR)/



all: twitter

twitter: twitter.o user.o tweet.o
	$(CC) $^ $(CPPFLAGS) -o $@
	
$(BIN_DIR)/twitter.o: $(SRC_DIR)/twitter.cpp $(HEADER_DIR)/user.h
	$(CC) -c $< -o $@ $(CPPFLAGS) -I$(BIN_DIR)/

$(BIN_DIR)/user.o: $(SRC_DIR)/user.cpp $(HEADER_DIR)/user.h $(HEADER_DIR)/Set.h $(HEADER_DIR)/tweet.h
	$(CC) -c $< -o $@ $(CPPFLAGS) -I$(BIN_DIR)/

$(BIN_DIR)/tweet.o: $(SRC_DIR)/tweet.cpp $(HEADER_DIR)/tweet.h $(HEADER_DIR)/datetime.h
	$(CC) -c $< -o $@ $(CPPFLAGS) -I$(BIN_DIR)/

.PHONY: clean

clean:
	@rm -f *.o twitter 