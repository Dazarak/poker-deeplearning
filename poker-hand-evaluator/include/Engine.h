#ifndef ENGINE_H
#define ENGINE_H

#include "HandRank.h"
#include "HandResult.h"
#include "Card.h"
#include "Config.h"

#include <iostream>
#include <algorithm> 
#include <random>
#include <array>

using namespace std;

// 10 Royal flush
// 9  Straight flush
// 8  Four of kind
// 7  Full house
// 6  Flush
// 5  Straight
// 4  Three of kind
// 3  Two pair
// 2  Pair
// 1  Highcard
// 0  Empty

class Engine
{
    public:
        HandResult EvaluatePlayersHands(std::array<Card, Config::MAX_CARDS> allCards);

    private:
        std::array<Card, Config::CARDS_PER_PLAYER> isRoyalFlush(array<Card, Config::MAX_CARDS>&);
        std::array<Card, Config::CARDS_PER_PLAYER> isStraightFlush(std::array<Card, Config::MAX_CARDS>&);
        std::array<Card, Config::CARDS_PER_PLAYER> isFourOfKind(array<Card, Config::MAX_CARDS>&);
        std::array<Card, Config::CARDS_PER_PLAYER> isFullHouse(array<Card, Config::MAX_CARDS>&);
        std::array<Card, Config::CARDS_PER_PLAYER> isFlush(array<Card, Config::MAX_CARDS>&);
        std::array<Card, Config::CARDS_PER_PLAYER> isStraight(array<Card, Config::MAX_CARDS>&);
        std::array<Card, Config::CARDS_PER_PLAYER> isThreeOfKind(array<Card, Config::MAX_CARDS>&);
        std::array<Card, Config::CARDS_PER_PLAYER> isTwoPair(array<Card, Config::MAX_CARDS>&);
        std::array<Card, Config::CARDS_PER_PLAYER> isPair(array<Card, Config::MAX_CARDS>&);

        void SortCards(array<Card, Config::MAX_CARDS>&);
        void SortCardsBySymbole(array<Card, Config::MAX_CARDS>&);
}; 

#endif