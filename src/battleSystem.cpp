#include "./include/battleSystem.hpp"

TurnResult::TurnResult(int danoJogador1, int danoJogador2, bool jogador1Knockout, bool jogador2Knockout)
    : danoJogador1(danoJogador1), danoJogador2(danoJogador2),
      jogador1Knockout(jogador1Knockout), jogador2Knockout(jogador2Knockout) {}


BattleSystem::BattleSystem(Fighter& P1, Fighter& P2)
    : _P1(P1), _P2(P2), _turnoAtual(0) {
}


TurnResult BattleSystem::resolveActions(Action& acaoP1, Action& acaoP2){

    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter P1 = acaoP1.getFighter();
    Fighter P2 = acaoP2.getFighter();
    
    int danoP1, danoP2;
    bool knockoutP1, knockoutP2;
    
    if ((actionTypeP1 == ActionType::DEFESA && actionTypeP2 == ActionType::DEFESA) ||
        (actionTypeP1 == ActionType::DEFESA && actionTypeP2 == ActionType::RECARREGA) ||
        (actionTypeP1 == ActionType::RECARREGA && actionTypeP2 == ActionType::DEFESA) ||
        (actionTypeP1 == ActionType::RECARREGA && actionTypeP2 == ActionType::RECARREGA)) {
        
        if(actionTypeP1 == ActionType::RECARREGA) P1.setCargaMagia(P1.getCargaMagia()+1);
        if(actionTypeP2 == ActionType::RECARREGA) P2.setCargaMagia(P2.getCargaMagia()+1);
            return TurnResult(0, 0, false, false);
    }

    if ((actionTypeP1 == ActionType::ATAQUE && actionTypeP2 == ActionType::MAGIA) ||
        (actionTypeP1 == ActionType::MAGIA && actionTypeP2 == ActionType::ATAQUE)) {
        
        if(actionTypeP1 == ActionType::MAGIA) {
            P2.setNegadoMagia(true);
            danoP2 = P1.getMagia();
        }else{
            danoP2 = P1.retornaDano(actionTypeP1);
            knockoutP2 = P2.isKnockout(danoP2);
        }
        if(actionTypeP2 == ActionType::MAGIA){
            P1.setNegadoMagia(true);
            danoP1 = P2.getMagia();
        }else{
            danoP1 = P2.retornaDano(actionTypeP2);
            knockoutP1 = P1.isKnockout(danoP1);
        } 
        return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
    }


    //switch(actionTypeP1){
        //case ActionType::ATAQUE:
        // IMPLEMENTAR CASOS ESPECÍFICOS

    //}

}


void BattleSystem::executarTurno(Action& acaoP1, Action& acaoP2) {
    resolveActions(acaoP1, acaoP2);
    _turnoAtual++;
}