#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>

#include "PokerAI.h"

int main() {
    int nbPlayers = 10;
    Holdem game(nbPlayers, 1000, 10);

    int numInputs = 16;
    int numOutputs = 5;   // Fold, Check, Call, Raise, AllIn
    int outputAct = 3;    // 3 = Linéaire (parfait pour des Q-values libres)

    vector<int> hiddenSizes = { numInputs, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, numOutputs };     // 2 couches cachées de 8 et 6 neurones
    vector<int> hiddenActs =  {             4,  4,  4,  4,  4,  4,  4,  4,  4,  4, outputAct  };      // 4 = leakyRelu pour les deux couches cachées

    // Instanciation propre
    NeuralNetwork NN(hiddenSizes, hiddenActs);
    int epoch = 0;
    while (epoch < 2000)
    {
        Holdem game(nbPlayers, 1000, 10);

        vector<PokerAI> listPlayer;
        for (int i = 0; i<nbPlayers; i++) 
            listPlayer.push_back(PokerAI(1,1000, &NN));
        
        std::random_device rd;
        std::mt19937 gen(rd());
        while (!game.PartyEnded) {
            while (!game.HandEnded)
            {
                PlayerContext plcntx = game.GetPlayerTurnInformations();
                game.ExecutePossibleAction(listPlayer[plcntx.gameContext.currentTurn].ChooseAction(plcntx));
                game.GoToNextPlayer();
            }
            if (game.HandEnded && !game.PartyEnded)
            {
                vector<PlayerContext> plrCntxtList = game.GetPlayersInformation();
                for(int i = 0; i<nbPlayers; i++)
                {
                    listPlayer[i].LearnFromActions(plrCntxtList[i]);
                }
                game.RestartGame();
            }
        }

        epoch++;
        std::cout << "epoch : " << static_cast<int>(epoch) << std::endl;
    }
    NN.saveNetwork("nn.dat");

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <random>
// #include <fstream>

// #include "PokerAI.h"

// int main() {
//     int nbPlayers = 2;
//     int numInputs = 16;

//     vector<int> hiddenSizes = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, };     // 2 couches cachées de 8 et 6 neurones
//     vector<int> hiddenActs = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };      // 4 = leakyRelu pour les deux couches cachées


//     int numOutputs = 5;   // Fold,Check, Call, Raise, AllIn
//     int outputAct = 3;    // 3 = Linéaire (parfait pour des Q-values libres)

//     // Instanciation propre
//     NeuralNetwork NN1(numInputs, hiddenSizes, hiddenActs, numOutputs, outputAct);
//     NeuralNetwork NN2(numInputs, hiddenSizes, hiddenActs, numOutputs, outputAct);

//     NN1.loadNetwork("nn.dat");
//     NN2.loadNetwork("nn3.dat");
    
//     int epoch = 0;
    
//     while (epoch < 1)
//     {
//         Holdem game(nbPlayers, 1000, 10);

//         PokerAI player1(1,1000, &NN1);
//         PokerAI player2(1,1000, &NN2);

//         vector<PokerAI> listPlayer = { player1, player2 };
        
//         std::random_device rd;
//         std::mt19937 gen(rd());

//         while (!game.PartyEnded) {
//             while (!game.HandEnded)
//             {
//                 PlayerContext plcntx = game.GetPlayerTurnInformations();
            
//                 game.ExecutePossibleAction(listPlayer[plcntx.gameContext.currentTurn].ChooseAction(plcntx));

//                 game.GoToNextPlayer();
//             }
//             if (game.HandEnded && !game.PartyEnded)
//             {
//                 vector<PlayerContext> plrCntxtList = game.GetPlayersInformation();

//                 std::cout << plrCntxtList[0] << std::endl;
//                 std::cout << plrCntxtList[1] << std::endl; 
                
//                 std::cout<<std::endl;
//                 game.RestartGame();
//             }
//         }

//         epoch++;
//     }

//     return 0;
// }