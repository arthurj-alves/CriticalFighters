#ifndef BATTLE_SYSTEM_HPP
#define BATTLE_SYSTEM_HPP

#include <functional>
#include <vector>
#include "fighter.hpp"
#include "action.hpp"

using namespace std;

struct TurnResult {
    std::string descricao;
    int danoJogador1;
    int danoJogador2;
    bool jogador1Knockout;
    bool jogador2Knockout;
    std::vector<std::string> eventos;

    TurnResult(int danoJogador1, int danoJogador2, bool jogador1Knockout, bool jogador2Knockout);
};

class BattleSystem {
private:
    Fighter& _P1;
    Fighter& _P2;
    int _turnoAtual;

    TurnResult resolveActions(Action& acaoP1, Action& acaoP2);
    
public:
    BattleSystem(Fighter& P1, Fighter& P2);
    
    // Executar um turno
    void executarTurno(Action& acaoP1, Action& acaoP2);
    
    // Verificar fim de jogo
    bool isBatalhaEncerrada() const;
    Fighter& getVencedor() const;
    
    // Getters
    int getTurnoAtual() const;

};

#endif  