# --- Configurações do Projeto ---
APP_NAME = jogo
SRC_DIR  = src
INC_DIR  = include
OBJ_DIR  = build
BIN_DIR  = bin

# --- Configurações do Compilador ---
CXX      = g++
# -MMD -MP: Cria arquivos .d para rastrear dependências de headers (.hpp) automaticamente
CXXFLAGS = -Wall -Wextra -g -I $(INC_DIR) -std=c++17 -MMD -MP

# --- Detecção Automática (A Mágica) ---
# Encontra TODOS os arquivos .cpp dentro de src/
SOURCES  = $(wildcard $(SRC_DIR)/*.cpp)
# Cria a lista de objetos .o correspondentes em build/
OBJECTS  = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
# Cria a lista de arquivos de dependência .d
DEPS     = $(OBJECTS:.o=.d)

# Detectar Sistema Operacional para definir a extensão do executável e comandos de limpeza
ifeq ($(OS),Windows_NT)
    TARGET = $(BIN_DIR)/$(APP_NAME).exe
    RM = del /Q /F
    FIXPATH = $(subst /,\,$1)
    MKDIR_P = if not exist "$1" mkdir "$1"
else
    TARGET = $(BIN_DIR)/$(APP_NAME)
    RM = rm -f
    FIXPATH = $1
    MKDIR_P = mkdir -p $1
endif

# --- Regras de Compilação ---

all: directories $(TARGET)

# Linkagem final
$(TARGET): $(OBJECTS)
	@echo "Linkando o executavel..."
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Sucesso! Execute: $(TARGET)"

# Compilação dos objetos
# O pipe | directories garante que a pasta exista antes de tentar criar o arquivo
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para criar pastas se não existirem
directories:
	@$(call MKDIR_P,$(OBJ_DIR))
	@$(call MKDIR_P,$(BIN_DIR))

# Incluir as dependências geradas automaticamente
-include $(DEPS)

# --- Comandos Utilitários ---

run: all
	./$(TARGET)

clean:
	@echo "Limpando arquivos temporarios..."
	-$(RM) $(call FIXPATH,$(OBJ_DIR)/*.o)
	-$(RM) $(call FIXPATH,$(OBJ_DIR)/*.d)
	-$(RM) $(call FIXPATH,$(TARGET))

.PHONY: all clean run directories