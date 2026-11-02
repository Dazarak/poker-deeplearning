#include "PokerAI.h"
#include <random>
#include <algorithm>

PokerAI::PokerAI(int _id, double initial_money, NeuralNetwork* _NN)
{
    id=_id;
    last_money=initial_money;
    NN=_NN;
}

double PokerAI::CalculeReward(double current_money, double total_table_money) {
    if (total_table_money == 0.0) return 0.0;
    double reward = (current_money - last_money) / total_table_money;
    last_money = current_money;
    return reward;
}

vector<float> PokerAI::GetInputFromContext(const PlayerContext& plrContext) // TODO : Normaliser entre 0 et 1 les inputs
{
    vector<float> inputs {};
    inputs.push_back(static_cast<float>(plrContext.money));
    for (int i = 0; i<plrContext.cards.size();i++)
    {
        if (plrContext.cards[i].isCard)
        {
            inputs.push_back(plrContext.cards[i].value);
            inputs.push_back(plrContext.cards[i].symbole);
        }
    }
    for (int i = 0; i<plrContext.gameContext.visibleCommunCards.size();i++)
    {
        if (plrContext.cards[i].isCard)
        {
            inputs.push_back(plrContext.cards[i].value);
            inputs.push_back(plrContext.cards[i].symbole);
        }
    }
    if (inputs.size() < numInputs-1)
    {
        while (inputs.size() < numInputs-1)
        {
            inputs.push_back(-1);
        }
    }
    inputs.push_back(plrContext.minRaiseAmount);

    return inputs;
}

PlayerAction PokerAI::ChooseAction(const PlayerContext& plrContext)
{
    vector<float> outputs = NN->feedForward(GetInputFromContext(plrContext));
    
    int best_index = -1;
    float biggest_value = -1e9f;

    for (int i = 0; i < outputs.size(); i++)
    {
        // On vérifie directement si l'action i est permise
        if (plrContext.actionsPossible[i].isAllow)
        {
            if (outputs[i] > biggest_value)
            {
                best_index = i;
                biggest_value = outputs[i];
            }
        }
    }

    moveHistory.push_back(std::pair(plrContext, outputs)); // Garde l'action en mémoire

    // Si aucune action n'était autorisée (sécurité), on Fold par défaut
    if (best_index == -1)
    {
        return PlayerAction{Action::Fold, 0};
    }

    switch (best_index)
    {
        case 0: // Fold
            return PlayerAction{Action::Fold,0};
            break;
        case 1: // Check
            return PlayerAction{Action::Check,0};
            break;
        case 2: // Call
            return PlayerAction{Action::Call,0};
            break;
        case 3: // Raise
            return PlayerAction{Action::Raise, plrContext.minRaiseAmount};
            break;
        case 4: // All-In
            return PlayerAction{Action::AllIn, 0};
            break;
        default:
            return PlayerAction{Action::Fold,0};
    }
}

void PokerAI::LearnFromActions(PlayerContext& plrCntxt)
{
    int maxMonney = plrCntxt.gameContext.nbPlayerInGame * plrCntxt.gameContext.initialMoney;
    float score = static_cast<float>(plrCntxt.money - last_money) / maxMonney;
    
    for (auto& context : moveHistory)
    {
        PlayerContext pc = context.first;
        vector<float> outputs = context.second; 

        int best_index = -1;
        float biggest_value = -1e9f;

        for (int i = 0; i < outputs.size(); i++)
        {
            // On vérifie directement si l'action i était permise
            if (pc.actionsPossible[i].isAllow)
            {
                if (outputs[i] > biggest_value)
                {
                    best_index = i;
                    biggest_value = outputs[i];
                }
            }
        }

        vector<float> expectedOutputs(outputs.size());
        for (int i = 0; i < outputs.size(); i++)
        {
            // On vérifie directement si l'action i est permise
            if (!pc.actionsPossible[i].isAllow)
            {
                expectedOutputs[i] = outputs[i]-0.1f; // Apprends a ne pas faire d'action interdite (Peux faire de l'apprentissage inutile, donc score bas, surement pas a garder)
            }else 
            {
                if (score > 0)
                {
                    if (i == best_index) // Si gagné suite à cette action
                    {    expectedOutputs[i] = outputs[i]+1.0f;
                    }else // Si cette action n'a pas été choisie et qu'on a gagné
                    {
                        expectedOutputs[i] = outputs[i]-0.5f;
                    }
                } else
                {
                    if (i == best_index) // Si perdu suite à cette action
                    {    expectedOutputs[i] = outputs[i]-1.0f;
                    }else // Si cette action n'a pas été choisie et qu'on a perdu
                    {
                        expectedOutputs[i] = outputs[i]+0.5f;
                    }
                }
            }
        }
        NN->feedForward(GetInputFromContext(pc));
        NN->backPropagation( expectedOutputs, 0.0001);
    }
    last_money = plrCntxt.money;
    moveHistory.clear();
}

//Je t'aime my love
/*
Je t'aime my lovito, t'aime t'aime, je t'aime je t'aime, t'aime !
Twa a d'acco , Bah voui, t'aime t'aime !
Je t'aime je t'aime, je t'aime je t'aime ! :)
*/
//Je t'aime fort, twa a trop fortito !
