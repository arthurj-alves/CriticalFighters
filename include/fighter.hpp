#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include <string>
#include <vector>
using namespace std;
#include "../include/action.hpp"
#include "../include/actionType.hpp"


class Fighter{
private: 
    string _nome;
    int _vidaTotal;
    int _vidaAtual;
    int _ataque;
    int _magia;
    bool _knockout;
    int _cargaTotal;
    int _cargaMagia;
    bool _negadoMagia;
    int _contadorSequencia;

    ActionType _tipoUltima;

    // vector<ActionType> historicoAcoes;

    
    public:
    Fighter(string nome, int vida,  int ataque, int magia, int cargaTotal);
    
    int retornaDano(ActionType tipo);
    bool isSucesso(ActionType acaoAtual);
    bool isKnockout(int dano); 

    string getNome() const;
    int getVidaAtual() const;
    int getAtaque() const;
    int getMagia() const;
    bool isKnockout() const;
    int getCargaTotal() const;
    int getCargaMagia() const;
    int getVidaTotal() const;
    bool isNegadoMagia() const;
    int getContadorSequencia() const;
    ActionType getTipoUltima() const;

    // Setters
    void setVidaAtual(int vida);
    void setCargaMagia(int carga);
    void setUltimaAcao(Action& acao);
    void setKnockout(bool knockout);
    void setNegadoMagia(bool negado);
};

#endif


