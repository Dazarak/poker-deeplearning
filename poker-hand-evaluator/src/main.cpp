#include "Engine.h"
#include "HandRank.h"
#include <iostream>

using namespace std;

int main( ) {
    Engine pokEn;
    
    std::array<Card, Config::MAX_CARDS> PlayerCard = { Card(0,1,true), Card(1,1,true),Card(2,1,true),Card(3,1,true),Card(4,1,true),Card(5,1,true),Card(6,1,true),Card(),Card(),Card() };

    std::cout << pokEn.EvaluatePlayersHands(PlayerCard) << std::endl;
    

    return 0;
}