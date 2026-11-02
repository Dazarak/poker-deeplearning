#ifndef HANDRESULT_H
#define HANDRESULT_H

#include "HandRank.h"
#include "Card.h"
#include "Config.h"
#include <array>

struct HandResult {
    HandRank handRank = HandRank::EMPTY;
    std::array<Card, Config::CARDS_PER_PLAYER> activeCards{};

    friend std::ostream& operator<<(std::ostream& os, const HandResult& hr) {
        os << "cartes : [ ";
        for (size_t i = 0; i < hr.activeCards.size(); ++i) {
            os << hr.activeCards[i] << (i + 1 < hr.activeCards.size() ? " " : "");
        }
        os << " ] rank : " << HandRankToString(hr.handRank);
        return os;
    }
};

#endif