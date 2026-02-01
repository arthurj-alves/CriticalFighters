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

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    switch(actionTypeP1){
        case ActionType::ATAQUE:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Ataque vs Ataque
                    return resolveAtaqueAtaque(acaoP1, acaoP2);
                    break;
                case ActionType::MAGIA: // Ataque vs Magia CHECK
                    return resolveAtaqueMagia(acaoP1, acaoP2);
                    break;
                case ActionType::DEFESA: // Ataque vs Defesa
                    return resolveAtaqueDefesa(acaoP1, acaoP2);
                    break;
                case ActionType::RECARREGA: // Ataque vs Recarga
                    return resolveAtaqueRecarrega(acaoP1, acaoP2);
                    break;
            }
            break;
        case ActionType::MAGIA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Magia vs Ataque CHECK
                    return resolveMagiaAtaque(acaoP1, acaoP2);
                    break;
                case ActionType::MAGIA: // Magia vs Magia
                    return resolveMagiaMagia(acaoP1, acaoP2);
                    break;
                case ActionType::DEFESA: // Magia vs Defesa
                    return resolveMagiaDefesa(acaoP1, acaoP2);
                    break;
                case ActionType::RECARREGA: // Magia vs Recarga
                    return resolveMagiaRecarrega(acaoP1, acaoP2);
                    break;
            }
            break;
        case ActionType::DEFESA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Defesa vs Ataque
                    return resolveDefesaAtaque(acaoP1, acaoP2);
                    break;
                case ActionType::MAGIA: // Defesa vs Magia
                    return resolveDefesaMagia(acaoP1, acaoP2);
                    break;
                case ActionType::DEFESA: // Defesa vs Defesa CHECK
                    return resolveDefesaDefesa(acaoP1, acaoP2);
                    break;
                case ActionType::RECARREGA: // Defesa vs Recarga CHECK
                    return resolveDefesaRecarrega(acaoP1, acaoP2);
                    break;
            }
            break;
        case ActionType::RECARREGA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Recarga vs Ataque
                    return resolveRecarregaAtaque(acaoP1, acaoP2);
                    break;
                case ActionType::MAGIA: // Recarga vs Magia
                    return resolveRecarregaMagia(acaoP1, acaoP2);
                    break;
                case ActionType::DEFESA: // Recarga vs Defesa CHECK
                    return resolveRecarregaDefesa(acaoP1, acaoP2);
                    break;
                case ActionType::RECARREGA: // Recarga vs Recarga CHECK
                    return resolveRecarregaRecarrega(acaoP1, acaoP2);
                    break;
            }
            break;
    }
}


void BattleSystem::executarTurno(Action& acaoP1, Action& acaoP2) {
    resolveActions(acaoP1, acaoP2);
    _turnoAtual++;
}

TurnResult BattleSystem::resolveAtaqueAtaque(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    int danoP1 = P2.retornaDano(actionTypeP2);
    int danoP2 = P1.retornaDano(actionTypeP1);
    bool knockoutP1 = P1.isKnockout(danoP1);
    bool knockoutP2 = P2.isKnockout(danoP2);

    return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
};

TurnResult BattleSystem::resolveAtaqueMagia(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    P1.setNegadoMagia(true);
    int danoP1 = P2.getMagia();
    int danoP2 = P1.retornaDano(actionTypeP2);
    bool knockoutP1 = P1.isKnockout(danoP1);
    bool knockoutP2 = P2.isKnockout(danoP2);

    return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
};

TurnResult BattleSystem::resolveAtaqueDefesa(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    // Balancear no futuro
    int danoP2 = P1.retornaDano(actionTypeP1) / 3; // Defesa reduz dano em 66%
    int danoP1 = P1.retornaDano(actionTypeP1) / 4; // Recebe um contra ataque de 25% do ataque
    bool knockoutP2 = P2.isKnockout(danoP2);
    bool knockoutP1 = P1.isKnockout(danoP1);

    return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
};

TurnResult BattleSystem::resolveAtaqueRecarrega(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    P2.setCargaMagia(P2.getCargaMagia()+1);
    int danoP2 = P1.retornaDano(actionTypeP1) * 1.2;
    bool knockoutP2 = P1.isKnockout(danoP2);

    return TurnResult(0, danoP2, false, knockoutP2);
};


TurnResult BattleSystem::resolveMagiaMagia(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();
    
    int dano1 = P1.getMagia();
    int dano2 = P2.getMagia();
    int knockout1 = P1.isKnockout(dano1);
    int knockout2 = P2.isKnockout(dano2);

    if(dano1 > dano2){
        P2.setNegadoMagia(true);
    }else if(dano2 > dano1){
        P1.setNegadoMagia(true);
    }else{
        P1.setNegadoMagia(true);
        P2.setNegadoMagia(true);
    }

    return TurnResult(dano1, dano2, knockout1, knockout2);
};

TurnResult BattleSystem::resolveMagiaAtaque(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();
    
    P2.setNegadoMagia(true);
    int danoP2 = P1.getMagia();
    int danoP1 = P2.retornaDano(actionTypeP2);
    bool knockoutP1 = P1.isKnockout(danoP1);
    bool knockoutP2 = P2.isKnockout(danoP2);

    return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
};

TurnResult BattleSystem::resolveMagiaDefesa(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    return TurnResult(0, 0, false, false);
};

TurnResult BattleSystem::resolveMagiaRecarrega(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    P2.setCargaMagia(P2.getCargaMagia()+1);
    int danoP1 = P1.getMagia();
    bool knockoutP1 = P1.isKnockout(danoP1);

    return TurnResult(danoP1, 0, knockoutP1, false);
};


TurnResult BattleSystem::resolveDefesaDefesa(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    return TurnResult(0, 0, false, false);
};

TurnResult BattleSystem::resolveDefesaAtaque(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();
    
    // Balancear no futuro
    int danoP1 = P2.retornaDano(actionTypeP2) / 3; // Defesa reduz dano em 66%
    int danoP2 = P2.retornaDano(actionTypeP2) / 4; // Recebe um contra ataque de 25% do ataque
    bool knockoutP2 = P2.isKnockout(danoP2);
    bool knockoutP1 = P1.isKnockout(danoP1);
    return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2);
};

TurnResult BattleSystem::resolveDefesaMagia(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    return TurnResult(0, 0, false, false);
};

TurnResult BattleSystem::resolveDefesaRecarrega(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    P1.setCargaMagia(P1.getCargaMagia()+1);
    return TurnResult(0, 0, false, false);
};


TurnResult BattleSystem::resolveRecarregaRecarrega(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    P1.setCargaMagia(P1.getCargaMagia()+1);
    P2.setCargaMagia(P2.getCargaMagia()+1);
    return TurnResult(0, 0, false, false);
};

TurnResult BattleSystem::resolveRecarregaAtaque(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    P1.setCargaMagia(P1.getCargaMagia()+1);
    int danoP1 = P2.retornaDano(actionTypeP2) * 1.2;
    bool knockoutP1 = P1.isKnockout(danoP1);
    return TurnResult(danoP1, 0, knockoutP1, false);
};

TurnResult BattleSystem::resolveRecarregaMagia(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    P1.setCargaMagia(P1.getCargaMagia()+1);
    int danoP2 = P2.getMagia();
    bool knockoutP2 = P2.isKnockout(danoP2);
    
    return TurnResult(0, danoP2, false, knockoutP2);
};

TurnResult BattleSystem::resolveRecarregaDefesa(Action& acaoP1, Action& acaoP2){
    
    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    P1.setCargaMagia(P1.getCargaMagia()+1);
    return TurnResult(0, 0, false, false);
};

