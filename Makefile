CC = g++
CFLAGS = -Wall -Wextra -Ofast -std=c++17 #-Ofast as sphere was rendering real slow
LDFLAGS = -lSDL2

SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin


TARGET = $(BIN_DIR)/my_program


SRCS = $(wildcard $(SRC_DIR)/*.cpp)


OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)) \
$(patsubst %.cpp,%.o,$(wildcard ./qbRay/*.cpp))


all: $(TARGET)


$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@
	
.PHONEY:
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

