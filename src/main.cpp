#include <iostream>

#include "../include/engine/States.hpp"
#include "../include/profile/profile.hpp"
#include "../include/profile/profileRepo.hpp"
#include "../include/questions/DifficultyModel.hpp"

using namespace std;

int main(){
    int ratings[] = {300, 700, 1100, 1700, 2500, 2700};

    for(int i = 300; i <= 3000; i = i +  50){
        D_model model = D_model(i);
        model.compute();
        DifficultyParams params = model.getPrams();

        cout << "Rating: " << i << endl;
        cout << "Digit1 count: " << params.digitCount1 << endl;
        cout << "Digit2 count: " << params.digitCount2 << endl;
        cout << "Add weight: " << params.addWeight << endl;
        cout << "Sub weight: " << params.subWeight << endl;
        cout << "Mul weight: " << params.mulWeight << endl;
        cout << "Div weight: " << params.divWeight << endl;
        cout << "Carry Prob: " << params.CarryProb << endl;
        cout << "Carry propagation: " << params.CarryPropagation << endl;
        cout << "Complexity level: " << params.complexityLevel << endl;
        cout << endl << endl;
    }

    return 0;
}