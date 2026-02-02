#include "./include/battleSystem.hpp"

TurnResult::TurnResult(int danoJogador1, int danoJogador2, bool jogador1Knockout, bool jogador2Knockout, int turno)
    : danoJogador1(danoJogador1), danoJogador2(danoJogador2),
      jogador1Knockout(jogador1Knockout), jogador2Knockout(jogador2Knockout), turno(turno) {
        if(jogador1Knockout || jogador2Knockout) {
            batalhaEncerrada = true;
        } else {
            batalhaEncerrada = false;
        }
}

string TurnResult::descricaoResult() {
    descricao = "Jogador 1 causou " + std::to_string(danoJogador1) + " de dano. ";
    descricao += "Jogador 2 causou " + std::to_string(danoJogador2) + " de dano. ";
    if(jogador1Knockout) {
        descricao += "Jogador 1 foi nocauteado. ";
    }
    if(jogador2Knockout) {
        descricao += "Jogador 2 foi nocauteado. ";
    }
    cout << "\n\n";
    return descricao;
}


BattleSystem::BattleSystem(Fighter& P1, Fighter& P2)
    : _P1(P1), _P2(P2), _turnoAtual(0) {
}


TurnResult BattleSystem::resolveActions(Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    ActionType actionTypeP1= acaoP1.getTipo();
    ActionType actionTypeP2= acaoP2.getTipo();

    Fighter& P1 = acaoP1.getFighter();
    Fighter& P2 = acaoP2.getFighter();

    switch(actionTypeP1){
        case ActionType::ATAQUE:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Ataque vs Ataque
                    return resolveAtaqueAtaque(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::MAGIA: // Ataque vs Magia CHECK
                    return resolveAtaqueMagia(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::DEFESA: // Ataque vs Defesa
                    return resolveAtaqueDefesa(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::RECARREGA: // Ataque vs Recarga
                    return resolveAtaqueRecarrega(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
            }
            break;
        case ActionType::MAGIA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Magia vs Ataque CHECK
                    return resolveMagiaAtaque(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::MAGIA: // Magia vs Magia
                    return resolveMagiaMagia(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::DEFESA: // Magia vs Defesa
                    return resolveMagiaDefesa(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::RECARREGA: // Magia vs Recarga
                    return resolveMagiaRecarrega(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
            }
            break;
        case ActionType::DEFESA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Defesa vs Ataque
                    return resolveDefesaAtaque(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::MAGIA: // Defesa vs Magia
                    return resolveDefesaMagia(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::DEFESA: // Defesa vs Defesa CHECK
                    return resolveDefesaDefesa(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::RECARREGA: // Defesa vs Recarga CHECK
                    return resolveDefesaRecarrega(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
            }
            break;
        case ActionType::RECARREGA:
            switch(actionTypeP2){
                case ActionType::ATAQUE: // Recarga vs Ataque
                    return resolveRecarregaAtaque(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::MAGIA: // Recarga vs Magia
                    return resolveRecarregaMagia(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::DEFESA: // Recarga vs Defesa CHECK
                    return resolveRecarregaDefesa(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
                case ActionType::RECARREGA: // Recarga vs Recarga CHECK
                    return resolveRecarregaRecarrega(P1, P2, acaoP1, acaoP2, sucessoP1, sucessoP2);
                    break;
            }
            break;
    }
}


void BattleSystem::executarTurno(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2) {

    bool sucessoP1 = P1.isSucesso(acaoP1.getTipo());
    bool sucessoP2 = P2.isSucesso(acaoP2.getTipo());

    cout << P1.getNome() << (sucessoP1 ? " teve sucesso em " : " falhou em ") << "executar a ação.\n";
    cout << P2.getNome() << (sucessoP2 ? " teve sucesso em " : " falhou em ") << "executar a ação.\n";

    _vectorTurnResult.push_back(resolveActions(acaoP1, acaoP2, sucessoP1, sucessoP2));

    cout << _vectorTurnResult.back().descricaoResult() << endl;
    _turnoAtual++;
}

bool BattleSystem::isBatalhaEncerrada() const {
    return _P1.isKnockout() || _P2.isKnockout();
}

int BattleSystem::getTurnoAtual() const {
    return _turnoAtual;
}

TurnResult BattleSystem::resolveAtaqueAtaque(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    int danoP1 = P2.retornaDano(acaoP2.getTipo());
    int danoP2 = P1.retornaDano(acaoP1.getTipo());
    bool knockoutP1 = P1.isKnockout(danoP1);
    bool knockoutP2 = P2.isKnockout(danoP2);

    if(sucessoP1 && sucessoP2){
        return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2, _turnoAtual);
    }else if(sucessoP1 && !sucessoP2){
        return TurnResult(0, danoP2, false, knockoutP2, _turnoAtual);
    }else if(!sucessoP1 && sucessoP2){
        return TurnResult(danoP1, 0, knockoutP1, false, _turnoAtual);
    }else{
        return TurnResult(0, 0, false, false, _turnoAtual);
    }
};

TurnResult BattleSystem::resolveAtaqueMagia(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    P1.setNegadoMagia(true);
    int danoP1 = P2.getMagia();
    int danoP2 = P1.retornaDano(acaoP2.getTipo());
    bool knockoutP1 = P1.isKnockout(danoP1);
    bool knockoutP2 = P2.isKnockout(danoP2);

    if(sucessoP1) {
        return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2, _turnoAtual);
    } else {
        return TurnResult(danoP1, 0, knockoutP1, false, _turnoAtual);
    }
};

TurnResult BattleSystem::resolveAtaqueDefesa(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    // Balancear no futuro
    int danoP2 = P1.retornaDano(acaoP1.getTipo()); // Defesa reduz dano em 66%
    bool knockoutP2 = P2.isKnockout(danoP2);

    if(sucessoP1 && sucessoP2){
        int danoP2 = danoP2 / 3; // Defesa reduz dano em 66%
        int danoP1 = danoP2 / 4; // Recebe um contra ataque de 25% do ataque
        bool knockoutP2 = P2.isKnockout(danoP2);
        bool knockoutP1 = P1.isKnockout(danoP1);
        return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2, _turnoAtual);
    }else if(sucessoP1 && !sucessoP2){
        return TurnResult(0, danoP2, false, knockoutP2, _turnoAtual);
    }else if(!sucessoP1 && sucessoP2){
        return TurnResult(0, 0, false, false, _turnoAtual);
    }else{
        return TurnResult(0, 0, false, false, _turnoAtual);
    }
};

TurnResult BattleSystem::resolveAtaqueRecarrega(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    P2.setCargaMagia(P2.getCargaMagia()+1);
    int danoP2 = P1.retornaDano(acaoP1.getTipo()) * 1.2;
    bool knockoutP2 = P1.isKnockout(danoP2);

    if(sucessoP1){
        return TurnResult(0, danoP2, false, knockoutP2, _turnoAtual);
    }else{
        return TurnResult(0, 0, false, false, _turnoAtual);
    }
};


TurnResult BattleSystem::resolveMagiaMagia(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){
    
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

    return TurnResult(dano1, dano2, knockout1, knockout2, _turnoAtual);
};

TurnResult BattleSystem::resolveMagiaAtaque(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){
    
    P2.setNegadoMagia(true);
    int danoP2 = P1.getMagia();
    int danoP1 = P2.retornaDano(acaoP2.getTipo());
    bool knockoutP1 = P1.isKnockout(danoP1);
    bool knockoutP2 = P2.isKnockout(danoP2);

    if(sucessoP2){
        return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2, _turnoAtual);
    }else{
        return TurnResult(0, danoP2, false, knockoutP2, _turnoAtual);
    }
};

TurnResult BattleSystem::resolveMagiaDefesa(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    if(sucessoP2){
        return TurnResult(0, 0, false, false, _turnoAtual);
    }else{
        int danoP2 = P1.getMagia();
        bool knockoutP2 = P2.isKnockout(danoP2);
        return TurnResult(0, danoP2, false, knockoutP2, _turnoAtual);
    }
};

TurnResult BattleSystem::resolveMagiaRecarrega(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    P2.setCargaMagia(P2.getCargaMagia()+1);
    int danoP1 = P1.getMagia();
    bool knockoutP1 = P1.isKnockout(danoP1);

    return TurnResult(danoP1, 0, knockoutP1, false, _turnoAtual);
};


TurnResult BattleSystem::resolveDefesaDefesa(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    return TurnResult(0, 0, false, false, _turnoAtual);
};

TurnResult BattleSystem::resolveDefesaAtaque(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){
    
    // Balancear no futuro
    int danoP1 = P2.retornaDano(acaoP1.getTipo()); // Defesa reduz dano em 66%
    bool knockoutP1 = P1.isKnockout(danoP1);

    if(sucessoP1 && sucessoP2){
        int danoP2 = danoP1 / 4; // Defesa reduz dano em 66%
        int danoP1 = danoP1 / 3; // Recebe um contra ataque de 25% do ataque
        bool knockoutP2 = P2.isKnockout(danoP2);
        bool knockoutP1 = P1.isKnockout(danoP1);
        return TurnResult(danoP1, danoP2, knockoutP1, knockoutP2, _turnoAtual);
    }else if(!sucessoP1 && sucessoP2){
        return TurnResult(danoP1, 0, knockoutP1, false, _turnoAtual);
    }else if(sucessoP1 && !sucessoP2){
        return TurnResult(0, 0, false, false, _turnoAtual);
    }else{
        return TurnResult(0, 0, false, false, _turnoAtual);
    }
};

TurnResult BattleSystem::resolveDefesaMagia(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    if(sucessoP1){
        return TurnResult(0, 0, false, false, _turnoAtual);
    }else{
        int danoP1 = P2.getMagia();
        bool knockoutP1 = P1.isKnockout(danoP1);
        return TurnResult(danoP1, 0, knockoutP1, false, _turnoAtual);
    }
};

TurnResult BattleSystem::resolveDefesaRecarrega(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    P1.setCargaMagia(P1.getCargaMagia()+1);
    return TurnResult(0, 0, false, false, _turnoAtual);
};


TurnResult BattleSystem::resolveRecarregaRecarrega(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    P1.setCargaMagia(P1.getCargaMagia()+1);
    P2.setCargaMagia(P2.getCargaMagia()+1);
    return TurnResult(0, 0, false, false, _turnoAtual);
};

TurnResult BattleSystem::resolveRecarregaAtaque(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    P1.setCargaMagia(P1.getCargaMagia()+1);
    int danoP1 = P2.retornaDano(acaoP2.getTipo()) * 1.2;
    bool knockoutP1 = P1.isKnockout(danoP1);
    if(sucessoP2){
        return TurnResult(danoP1, 0, knockoutP1, false, _turnoAtual);
    }else{
        return TurnResult(0, 0, 0, false, _turnoAtual);
    }
};

TurnResult BattleSystem::resolveRecarregaMagia(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    P1.setCargaMagia(P1.getCargaMagia()+1);
    int danoP2 = P2.getMagia();
    bool knockoutP2 = P2.isKnockout(danoP2);
    
    return TurnResult(0, danoP2, false, knockoutP2, _turnoAtual);
};

TurnResult BattleSystem::resolveRecarregaDefesa(Fighter& P1, Fighter& P2, Action& acaoP1, Action& acaoP2, bool sucessoP1, bool sucessoP2){

    P1.setCargaMagia(P1.getCargaMagia()+1);
    return TurnResult(0, 0, false, false, _turnoAtual);
};

