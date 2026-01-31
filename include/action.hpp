#ifndef ACTION_HPP
#define ACTION_HPP

#include <string>
#include <vector>
#include "../include/fighter.hpp"
#include "../include/actionType.hpp" 
using namespace std;


class Action {
private:
    ActionType _tipo;
    Fighter& _fighter;
    
public:
    Action(ActionType tipo, int valor, Fighter& fighter);
    
    ActionType getTipo() const;
    Fighter& getFighter() const;
};

#endif