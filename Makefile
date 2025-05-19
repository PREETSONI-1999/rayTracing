CC = g++
CFLAGS = -Wall -Wextra -O2 -std=c++17
LDFLAGS = -lSDL2

SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin


TARGET = $(BIN_DIR)/my_program


SRCS = $(wildcard $(SRC_DIR)/*.cpp)


OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))


all: $(TARGET)


$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

