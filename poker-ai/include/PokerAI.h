#include <string>
#include <map>
#include <vector>
#include "Holdem.h"
#include "NN.h"

class PokerAI {
private:
    int id = 0;
    double last_money;
    int numInputs = 16;
    int numOutputs = 5;   // Fold,Check, Call, Raise, AllIn
    int outputAct = 3;    // 3 = Linéaire (parfait pour des Q-values libres)
    NeuralNetwork* NN;
    vector<std::pair<PlayerContext, vector<float>>> moveHistory;

    // Methode IA
    double CalculeReward(double current_money, double total_table_money);
    vector<float> GetInputFromContext(const PlayerContext& plrContext);

public:
    PokerAI(int id, double initial_money, NeuralNetwork* NN);
    PlayerAction ChooseAction(const PlayerContext& plrContext);
    void LearnFromActions(PlayerContext& plrCntxt);
};