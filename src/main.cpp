#include <iostream>

#include "../include/engine/States.hpp"
#include "../include/profile/profile.hpp"

using namespace std;

int main(){
    StateMachine sm = StateMachine();
    Profile user = Profile();

    cout << user.getBestAccuracy();

    return 0;
}