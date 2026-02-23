
#ifndef STATES_H
#define STATES_H
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>

enum class States {
    STARTUP,
    PROFILE_CHECK,
    CALIBRAT,
    MENU,
    MODE_SELECTION,
    GENRATING_SESSION,
    ACTIVE_SESSION,
    POST_SESSION,
    ANALYSING,
    DATA_SAVING,
    EXIT,
    ERROR_RESOLVING,
    EXCEPTION_RESOLVING
};

class StateMachine{
    public:
        StateMachine(): state(States::STARTUP){};   // its either STARTUP when the main() is called
        StateMachine(States st): state(st){};       // or its defined by the main() 

        States getCurrentState() const;           // returns the immutable state
        bool transitTo(const States next);  // transit to the next state if possible
        const std::vector<States>* getStateLogs() const; // get the logs of the states, states changes as per the index increases. no time recorded
        private:
        States state;   // current state of the system
        std::vector<States> logs;   // Saving state transitions
        std::map<States, std::set<States>> ValidTransitions = { // Map for Valid Transitions
            {
                States::STARTUP, {States::PROFILE_CHECK, States::EXIT}
            },
            {
                States::PROFILE_CHECK, {States::CALIBRAT, States::MENU}
            },
            {
                States::CALIBRAT, {States::MENU}
            },
            {
                States::MENU, {States::MODE_SELECTION, States::EXIT, States::ERROR_RESOLVING, States::EXCEPTION_RESOLVING, States::EXIT}
            },
            {
                States::MODE_SELECTION, {States::GENRATING_SESSION, States::MENU}
            },
            {
                States::GENRATING_SESSION, {States::ACTIVE_SESSION, States::ERROR_RESOLVING, States::EXCEPTION_RESOLVING}
            },
            {
                States::ACTIVE_SESSION, {States::POST_SESSION, States::ERROR_RESOLVING, States::EXCEPTION_RESOLVING}
            },
            {
                States::POST_SESSION, {States::DATA_SAVING, States::ANALYSING, States::MENU, States::ERROR_RESOLVING, States::EXCEPTION_RESOLVING}
            },
            {
                States::DATA_SAVING, {States::MENU, States::ERROR_RESOLVING, States::EXCEPTION_RESOLVING}
            },
            {
                States::ANALYSING, {States::MENU, States::ERROR_RESOLVING, States::EXCEPTION_RESOLVING}
            }
        };    
        
        bool isValidTransition(const States next);  // check the validity
    };
    
std::string enum_to_string(States state);
#endif