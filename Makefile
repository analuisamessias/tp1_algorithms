# Nome do executável
EXEC = tp1

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Arquivos fonte e cabeçalhos
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/grafo.cpp $(SRC_DIR)/capital.cpp $(SRC_DIR)/batalhoes.cpp $(SRC_DIR)/patrulhamento.cpp
HEADERS = $(INCLUDE_DIR)/grafo.hpp $(INCLUDE_DIR)/capital.hpp $(INCLUDE_DIR)/batalhoes.hpp $(INCLUDE_DIR)/patrulhamento.hpp
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/grafo.o $(OBJ_DIR)/capital.o $(OBJ_DIR)/batalhoes.o $(OBJ_DIR)/patrulhamento.o

# Compilador e flags
CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror
LDFLAGS =

# Regra padrão
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Regras para criar os arquivos objeto
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/grafo.o: $(SRC_DIR)/grafo.cpp $(INCLUDE_DIR)/grafo.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/grafo.cpp -o $(OBJ_DIR)/grafo.o

$(OBJ_DIR)/capital.o: $(SRC_DIR)/capital.cpp $(INCLUDE_DIR)/capital.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/capital.cpp -o $(OBJ_DIR)/capital.o

$(OBJ_DIR)/batalhoes.o: $(SRC_DIR)/batalhoes.cpp $(INCLUDE_DIR)/batalhoes.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/batalhoes.cpp -o $(OBJ_DIR)/batalhoes.o

$(OBJ_DIR)/patrulhamento.o: $(SRC_DIR)/patrulhamento.cpp $(INCLUDE_DIR)/patrulhamento.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/patrulhamento.cpp -o $(OBJ_DIR)/patrulhamento.o


# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

# Limpeza completa
distclean: clean
	rm -f $(EXEC)