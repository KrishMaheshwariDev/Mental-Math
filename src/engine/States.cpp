#include "../include/engine/States.hpp"

using namespace std;

States StateMachine::getCurrentState() const{
    return this->state;
}

bool StateMachine::transitTo(const States next){
    if(isValidTransition(next)){
        this->state = next;
        logs.push_back(this->state);

        cout << "State is changed" << endl;
        return true;
    }
    else{
        // TODO: throw an error of INVALID STATE TRANISTION, and move the system to ERROR_RESOLVING state
        return false;
    }
}

const std::vector<States>* StateMachine::getStateLogs() const{
    return &logs;
}

bool StateMachine::isValidTransition(const States next){
    return this->ValidTransitions[this->state].contains(next);
}

string enum_to_string(States state){
    switch(state){
        case States::EXIT: return "EXIT";
        case States::STARTUP: return "STARTUP";
        default: return "NO STATE";
    }
}