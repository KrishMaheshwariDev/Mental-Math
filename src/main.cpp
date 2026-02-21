#include <iostream>

#include "../include/engine/States.hpp"
#include "../include/profile/profile.hpp"
#include "../include/profile/profileRepo.hpp"

using namespace std;

int main(){
    StateMachine sm = StateMachine();
    Profile user = Profile();
    ProfileRepo repo = ProfileRepo();
    repo.load(user);
    cout << user.getRating();
    user.setRating(200);
    repo.save(user);

    repo.load(user);
    cout << user.getRating();

    return 0;
}