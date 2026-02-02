# Nome do executável
TARGET = bin/programa

# Compilador e flags
CXX = g++
CXXFLAGS = -I./include -Wall -Wextra -std=c++17
LDFLAGS = 

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Encontra todos os arquivos .cpp e .hpp
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.hpp)

# Gera lista de objetos (substitui src/ por build/ e .cpp por .o)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Regra principal
all: $(BIN_DIR) $(BUILD_DIR) $(TARGET)

# Linka objetos para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

# Compila cada .cpp em .o, dependendo dos .hpp
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria diretórios se não existirem
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Recompilar tudo
rebuild: clean all

# Informações
info:
	@echo "Fontes: $(SOURCES)"
	@echo "Cabeçalhos: $(HEADERS)"
	@echo "Objetos: $(OBJECTS)"

.PHONY: all clean rebuild info