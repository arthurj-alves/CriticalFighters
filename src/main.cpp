#include "../include/fighter.hpp"
#include "../include/action.hpp"
#include "../include/actionType.hpp"
#include "../include/battleSystem.hpp"

#include <iostream>
using namespace std;

int vidaP1 = 50;
int vidaP2 = 45;
int ataqueP1 = 5;
int ataqueP2 = 7;
int magiaP1 = 10;
int magiaP2 = 12;
int maxCargas = 1;


int main(){
Fighter Player1 = Fighter("Jogador1", vidaP1, ataqueP1, magiaP1, maxCargas);
Fighter Player2 = Fighter("Jogador2", vidaP2, ataqueP2, magiaP2, maxCargas);

BattleSystem batalha = BattleSystem(Player1, Player2);

cout << "Batalha entre " << Player1.getNome() << " e " << Player2.getNome() << " começou!" << endl;

while (batalha.isBatalhaEncerrada() == false)
{
    int acao1, acao2;
    cout << "Começando o Turno " << batalha.getTurnoAtual() + 1 << ":\n\n" << endl;
    
    cout << Player1.getNome() << " escolha sua ação (0: Ataque, 1: Magia, 2: Defesa, 3: Recarrega): ";
    cin >> acao1;
    cout << "\n";

    cout << Player2.getNome() << " escolha sua ação (0: Ataque, 1: Magia, 2: Defesa, 3: Recarrega): ";
    cin >> acao2;
    cout << "\n";

    Action acaoP1 = Action(static_cast<ActionType>(acao1), Player1);
    Action acaoP2 = Action(static_cast<ActionType>(acao2), Player2);

    batalha.executarTurno(Player1, Player2, acaoP1, acaoP2);
}

cout << "Batalha encerrada! Vencedor: ";
if (Player1.isKnockout()) {
    cout << Player2.getNome() << endl;
} else {   
    cout << Player1.getNome() << endl;
}

}