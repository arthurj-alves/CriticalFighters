#include "../include/action.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

Action::Action(ActionType tipo, Fighter& fighter): _tipo(tipo), _fighter(fighter) {}

ActionType Action::getTipo() const {
    return _tipo;
}

Fighter& Action::getFighter() const {
    return _fighter;
}


