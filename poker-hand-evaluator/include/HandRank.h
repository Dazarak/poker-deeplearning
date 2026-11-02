#ifndef HANDRANK_H
#define HANDRANK_H

#include <cstdint>
#include <string_view>

// 10 Royal flush
// 9  Straight flush
// 8  Four of kind
// 7  Full house
// 6  Flush
// 5  Straight
// 4  Three of kindkind
// 3  Two pair
// 2  Pair
// 1  Highcard
// 0  Empty

enum HandRank : uint8_t {
    EMPTY = 0,
    HIGH_CARD = 1,
    PAIR = 2,
    TWO_PAIR = 3,
    THREE_OF_A_KIND = 4,
    STRAIGHT = 5,
    FLUSH = 6,
    FULL_HOUSE = 7,
    FOUR_OF_A_KIND = 8,
    STRAIGHT_FLUSH = 9,
    ROYAL_FLUSH = 10
};

constexpr std::string_view HandRankToString(HandRank rank) {
    switch (rank) {
        case HIGH_CARD:       return "High Card";
        case PAIR:            return "Pair";
        case TWO_PAIR:        return "Two Pair";
        case THREE_OF_A_KIND: return "Three of a Kind";
        case STRAIGHT:        return "Straight";
        case FLUSH:           return "Flush";
        case FULL_HOUSE:      return "Full House";
        case FOUR_OF_A_KIND:  return "Four of a Kind";
        case STRAIGHT_FLUSH:  return "Straight Flush";
        case ROYAL_FLUSH:     return "Royal Flush";
        case EMPTY:           return "Empty";
        default:              return "Empty";
    }
}

inline std::ostream& operator<<(std::ostream& os, HandRank rank) {
    return os << HandRankToString(rank);
}

#endif
