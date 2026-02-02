@echo off
echo Compilando projeto...

rem Cria diretórios se não existirem
if not exist build mkdir build
if not exist bin mkdir bin

rem Compila todos os arquivos .cpp
g++ -I./include -Wall -Wextra -std=c++17 -c src/action.cpp -o build/action.o
g++ -I./include -Wall -Wextra -std=c++17 -c src/actionType.cpp -o build/actionType.o
g++ -I./include -Wall -Wextra -std=c++17 -c src/battleSystem.cpp -o build/battleSystem.o
g++ -I./include -Wall -Wextra -std=c++17 -c src/fighter.cpp -o build/fighter.o
g++ -I./include -Wall -Wextra -std=c++17 -c src/main.cpp -o build/main.o

rem Linka todos os objetos
g++ build/*.o -o bin/programa.exe

echo Compilacao concluida! Executavel em bin/programa.exe