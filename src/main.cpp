#include <iostream>

#include "../include/engine/States.hpp"

using namespace std;

int main(){
    StateMachine sm = StateMachine();
    int input;
    while(sm.getCurrentState() != States::EXIT){
        cout << "press 1 to exit" << endl;
        cin >> input;

        if(input == 1){
            sm.transitTo(States::EXIT);
            cout << "Current State: " << enum_to_string(sm.getCurrentState()) << endl;
            cout << "Exiting from the Program";
            continue;
        }
    }

    return 0;
}