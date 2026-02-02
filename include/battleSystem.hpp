#ifndef BATTLE_SYSTEM_HPP
#define BATTLE_SYSTEM_HPP

#include <functional>
#include <iostream>
#include <vector>
#include "fighter.hpp"
#include "action.hpp"

using namespace std;

struct TurnResult {
    string descricao;
    int danoJogador1;
    int danoJogador2;
    bool jogador1Knockout;
    bool jogador2Knockout;
    bool batalhaEncerrada;
    int turno;
    // std::vector<std::string> eventos;

    TurnResult(int danoJogador1, int danoJogador2, bool jogador1Knockout, bool jogador2Knockout, int turno);

    string descricaoResult();
};

class BattleSystem {
private:
    Fighter& _P1;
    Fighter& _P2;
    int _turnoAtual;
    vector<TurnResult> _vectorTurnResult;

    TurnResult resolveActions(Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    
public:
    BattleSystem(Fighter& P1, Fighter& P2);
    
    // Executar um turno
    void executarTurno(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2);
    
    // Verificar fim de jogo
    bool isBatalhaEncerrada() const;
    
    // Getters
    int getTurnoAtual() const;

    // Resolvers
    TurnResult resolveAtaqueAtaque(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveAtaqueMagia(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveAtaqueDefesa(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveAtaqueRecarrega(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);

    TurnResult resolveMagiaMagia(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveMagiaAtaque(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveMagiaDefesa(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveMagiaRecarrega(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);

    TurnResult resolveDefesaDefesa(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveDefesaAtaque(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveDefesaMagia(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveDefesaRecarrega(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);

    TurnResult resolveRecarregaRecarrega(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveRecarregaAtaque(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveRecarregaMagia(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);
    TurnResult resolveRecarregaDefesa(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2);

};

#endif  