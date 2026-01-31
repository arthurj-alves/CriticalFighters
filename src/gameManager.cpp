/* #ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include "fighter.hpp"
#include "battleSystem.hpp"

class GameManager {
private:
    std::vector<Fighter> _lutadores;
    BattleSystem* _batalhaAtual;
    bool _jogoAtivo;
    
public:
    GameManager();
    ~GameManager();
    
    // Gerenciamento de lutadores
    void criarLutador(const std::string& nome, int vida, int ataque, int magia);
    void removerLutador(int indice);
    
    // Batalha
    void iniciarBatalha(int indiceJogador1, int indiceJogador2);
    void encerrarBatalha();
    
    // Interface
    void mostrarMenuPrincipal();
    void mostrarLutadores() const;
    
    // Controle do jogo
    void executar();
    void sair();
};

#endif */