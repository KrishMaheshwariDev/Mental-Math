
#ifndef STATES_H
#define STATES_H
#include <vector>

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
        std::vector<States> getStateLogs(); // get the logs of the states, states changes as per the index increases. no time recorded
    private:
        States state;   // current state of the system
        std::vector<States> logs;   // Saving state transitions

        bool isValidTransition(const States next);  // check the validity
};

#endif