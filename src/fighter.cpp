#include "../include/fighter.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include <iomanip>
using namespace std;

// Construtor
Fighter::Fighter(string nome, int vida, int ataque, int magia, int cargaTotal)
    : _nome(nome), _vidaTotal(vida), _vidaAtual(vida), _ataque(ataque), 
      _magia(magia), _knockout(false), _cargaTotal(cargaTotal), 
      _cargaMagia(0), _negadoMagia(false), _contadorSequencia(0),
      _tipoUltima(ActionType::NENHUMA) {}

bool Fighter::verificarSucesso(ActionType acaoAtual){
    ActionType tipoUltima = _tipoUltima;
    ActionType tipoAtual = acaoAtual;
    
    if(tipoUltima != tipoAtual){
        _contadorSequencia = 0;
    }else{
        _contadorSequencia++;
    }

    if((acaoAtual == ActionType::MAGIA) || (acaoAtual == ActionType::RECARREGA)) return true;

    int chance = 0; 
    switch (tipoAtual)
    {
    case ActionType::ATAQUE:
        double chance = pow(0.7, _contadorSequencia);
        break;
    case ActionType::DEFESA:
        double chance = pow(0.5, _contadorSequencia);    
    default:
        break;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    return dis(gen) <= chance;
}

int Fighter::retornaDano(ActionType tipo){
    if(verificarSucesso(tipo)) {
        switch (tipo)
        {
        case ActionType::ATAQUE:
            return _ataque;
            break;
        case ActionType::MAGIA:
            return _magia;
        case ActionType::DEFESA:
            return 1;
        case ActionType::RECARREGA:
            return 1;        
        default:
            break;
        }
    }else{
        return 0;
    }    
}

bool Fighter::isKnockout(int dano){
    if(dano >= _vidaAtual) return true;
    return false;
}

// ========== GETTERS ==========

string Fighter::getNome() const {
    return _nome;
}

int Fighter::getVidaTotal() const {
    return _vidaTotal;
}

int Fighter::getVidaAtual() const {
    return _vidaAtual;
}

int Fighter::getAtaque() const{
    return _ataque;
}

int Fighter::getMagia() const {
    return _magia;
}

bool Fighter::isKnockout() const {
    return _knockout;
}

int Fighter::getCargaTotal() const {
    return _cargaTotal;
}

int Fighter::getCargaMagia() const {
    return _cargaMagia;
}

bool Fighter::isNegadoMagia() const {
    return _negadoMagia;
}

int Fighter::getContadorSequencia() const {
    return _contadorSequencia;
}

ActionType Fighter::getTipoUltima() const {
    return _tipoUltima;
}

// ========== SETTERS ==========

void Fighter::setVidaAtual(int vidaAtual) {
    _vidaAtual = max(0, min(vidaAtual, _vidaTotal));
    if (_vidaAtual <= 0) {
        _knockout = true;
    }
}

void Fighter::setKnockout(bool knockout) {
    _knockout = knockout;
    if (knockout && _vidaAtual > 0) {
        _vidaAtual = 0;
    }
}

void Fighter::setCargaMagia(int cargaMagia) {
    _cargaMagia = max(0, min(cargaMagia, _cargaTotal));
}

void Fighter::setNegadoMagia(bool negado) {
    _negadoMagia = negado;
}

void Fighter::setTipoUltima(Action& acao) {
    _tipoUltima = acao.getTipo();
}
