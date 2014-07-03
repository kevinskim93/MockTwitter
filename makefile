#Compiler Variables
CC = g++
CPPFLAGS = -Wall -g -std=c++11

#Location of files
SRC_DIR=src
HEADER_DIR=include
BIN_DIR=bin


CPPFLAGS += -I $(HEADER_DIR)/



all: twitter

twitter: $(BIN_DIR)/twitter.o $(BIN_DIR)/user.o $(BIN_DIR)/tweet.o
	$(CC) $^ $(CPPFLAGS) -o $@
	
$(BIN_DIR)/twitter.o: $(SRC_DIR)/twitter.cpp $(HEADER_DIR)/user.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c -o $(BIN_DIR)/twitter.o $(SRC_DIR)/twitter.cpp

$(BIN_DIR)/user.o: $(SRC_DIR)/user.cpp $(HEADER_DIR)/user.h $(HEADER_DIR)/Set.h $(HEADER_DIR)/tweet.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c -o $(BIN_DIR)/user.o $(SRC_DIR)/user.cpp

$(BIN_DIR)/tweet.o: $(SRC_DIR)/tweet.cpp $(HEADER_DIR)/tweet.h $(HEADER_DIR)/datetime.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c -o $(BIN_DIR)/tweet.o $(SRC_DIR)/tweet.cpp

$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR) && touch $@

.PHONY: clean

clean:
	@rm -f *.o twitter 