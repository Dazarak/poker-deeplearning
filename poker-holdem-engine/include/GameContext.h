#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Config.h"
#include "Card.h"

#include <cstdint>
#include <array>

enum class GameStep : uint8_t {
    PreFlop,
    Flop,
    Turn,
    River,
    Showdown
};

class GameContext {
public:
    std::array<Card, Config::COMMUNITY_CARDS> visibleCommunCards{};
    uint8_t currentTurn;       // Siège du joueur actif (0 à 9)
    uint8_t dealerPos;         // Siège du bouton
    uint8_t nbPlayer;
    uint32_t initialMoney;
    uint8_t nbPlayerInGame;
    uint32_t currentBet;       // La mise globale à égaler
    uint32_t lastBet;          // Mise qui précèdent la dernière mise
    uint32_t pot;              // Pot total
    uint32_t smallBlind;
    uint32_t bigBlind;
    
    GameStep currentStep = GameStep::PreFlop;
    uint32_t minBet();
    void setCommunnityCards(Card, uint8_t);
    void setVisibleCommunityCards(GameStep);

    bool operator==(const GameContext& other) const {
        // Compare les cartes
        int i = 0;
        for (auto& card : visibleCommunCards)
        {
            if (card != other.visibleCommunCards[i])
            {
                return false;
            }
            i++;
        }
        if (visibleCommunCards != other.visibleCommunCards)
            return false;
        if (currentTurn != other.currentTurn)
            return false;
        if (dealerPos != other.dealerPos)
            return false;
        if (nbPlayer != other.nbPlayer)
            return false;
        if (initialMoney != other.initialMoney)
            return false;
        if (nbPlayerInGame != other.nbPlayerInGame)
            return false;
        if (currentBet != other.currentBet)
            return false;
        if (lastBet != other.lastBet)
            return false;
        if (pot != other.pot)
            return false;
        if (smallBlind != other.smallBlind)
            return false;
        if (bigBlind != other.bigBlind)
            return false;
        return currentStep == other.currentStep;
    }

    bool operator!=(const GameContext& other) const {
        return !(*this == other);
    }

    bool operator<(const GameContext& other) const {
        if (visibleCommunCards != other.visibleCommunCards) return visibleCommunCards < other.visibleCommunCards;
        if (communCards != other.communCards) return communCards < other.communCards;
        if (currentTurn != other.currentTurn) return currentTurn < other.currentTurn;
        if (dealerPos != other.dealerPos) return dealerPos < other.dealerPos;
        if (nbPlayer != other.nbPlayer) return nbPlayer < other.nbPlayer;
        if (initialMoney != other.initialMoney) return initialMoney < other.initialMoney;
        if (nbPlayerInGame != other.nbPlayerInGame) return nbPlayerInGame < other.nbPlayerInGame;
        if (currentBet != other.currentBet) return currentBet < other.currentBet;
        if (lastBet != other.lastBet) return lastBet < other.lastBet;
        if (pot != other.pot) return pot < other.pot;
        if (smallBlind != other.smallBlind) return smallBlind < other.smallBlind;
        if (bigBlind != other.bigBlind) return bigBlind < other.bigBlind;
        return currentStep < other.currentStep;
    }
private:
    std::array<Card, Config::COMMUNITY_CARDS> communCards{};
};

#endif