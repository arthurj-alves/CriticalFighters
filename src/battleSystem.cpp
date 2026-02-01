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
    // Defesa vs Defesa ou Defesa vs Recarga ou Recarga vs Recarga ou Recarga vs Defesa
    if ((actionTypeP1 == ActionType::DEFESA && actionTypeP2 == ActionType::DEFESA) ||
        (actionTypeP1 == ActionType::DEFESA && actionTypeP2 == ActionType::RECARREGA) ||
        (actionTypeP1 == ActionType::RECARREGA && actionTypeP2 == ActionType::DEFESA) ||
        (actionTypeP1 == ActionType::RECARREGA && actionTypeP2 == ActionType::RECARREGA)) {
        
        if(actionTypeP1 == ActionType::RECARREGA) P1.setCargaMagia(P1.getCargaMagia()+1);
        if(actionTypeP2 == ActionType::RECARREGA) P2.setCargaMagia(P2.getCargaMagia()+1);
            return TurnResult(0, 0, false, false);
    }

    // Ataque vs Magia ou Magia vs Ataque
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


    switch(actionTypeP1){
        case ActionType::ATAQUE:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Ataque vs Ataque
                    break;
                case ActionType::MAGIA: // Ataque vs Magia CHECK
                    P1.setNegadoMagia(true);
                    danoP2 = P1.getMagia();
                    danoP1 = P2.retornaDano(actionTypeP2);
                    knockoutP1 = P1.isKnockout(danoP1);
                    knockoutP2 = P2.isKnockout(danoP2);
                    return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
                    break;
                case ActionType::DEFESA: // Ataque vs Defesa
                    break;
                case ActionType::RECARREGA: // Ataque vs Recarga
            }
            break;
        case ActionType::MAGIA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Magia vs Ataque CHECK
                    P2.setNegadoMagia(true);
                    danoP2 = P1.getMagia();
                    danoP1 = P2.retornaDano(actionTypeP2);
                    knockoutP1 = P1.isKnockout(danoP1);
                    knockoutP2 = P2.isKnockout(danoP2);
                    return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
                    break;
                case ActionType::MAGIA: // Magia vs Magia
                    break;
                case ActionType::DEFESA: // Magia vs Defesa
                    break;
                case ActionType::RECARREGA: // Magia vs Recarga
            }
            break;
        case ActionType::DEFESA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Defesa vs Ataque
                    break;
                case ActionType::MAGIA: // Defesa vs Magia
                    break;
                case ActionType::DEFESA: // Defesa vs Defesa CHECK
                    break;
                case ActionType::RECARREGA: // Defesa vs Recarga CHECK
            }
            break;
        case ActionType::RECARREGA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Recarga vs Ataque
                    break;
                case ActionType::MAGIA: // Recarga vs Magia
                    break;
                case ActionType::DEFESA: // Recarga vs Defesa CHECK
                    break;
                case ActionType::RECARREGA: // Recarga vs Recarga CHECK
            }
            break;
        
        
    }

}


void BattleSystem::executarTurno(Action& acaoP1, Action& acaoP2) {
    resolveActions(acaoP1, acaoP2);
    _turnoAtual++;
}

TurnResult BattleSystem::resolveAtaqueAtaque(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveAtaqueMagia(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveAtaqueDefesa(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveAtaqueRecarrega(Action& acaoP1, Action& acaoP2){


};

TurnResult BattleSystem::resolveMagiaMagia(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveMagiaAtaque(Action& acaoP1, Action& acaoP2){
    P2.setNegadoMagia(true);
    int danoP2 = P1.getMagia();
    int danoP1 = P2.retornaDano(actionTypeP2);
    bool knockoutP1 = P1.isKnockout(danoP1);
    bool knockoutP2 = P2.isKnockout(danoP2);
    return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
};
TurnResult BattleSystem::resolveMagiaDefesa(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveMagiaRecarrega(Action& acaoP1, Action& acaoP2){


};

TurnResult BattleSystem::resolveDefesaDefesa(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveDefesaAtaque(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveDefesaMagia(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveDefesaRecarrega(Action& acaoP1, Action& acaoP2){


};

TurnResult BattleSystem::resolveRecarregaRecarrega(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveRecarregaAtaque(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveRecarregaMagia(Action& acaoP1, Action& acaoP2){


};
TurnResult BattleSystem::resolveRecarregaDefesa(Action& acaoP1, Action& acaoP2){


};
