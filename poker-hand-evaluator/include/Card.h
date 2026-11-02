#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <iomanip>
#include <array>

class Card {
public:
    uint8_t value : 4;
    uint8_t symbole : 3;
    uint8_t isCard : 1;

    Card();
    Card(uint8_t, uint8_t, bool);
    bool operator==(const Card& other) const {
        if (value != other.value)
            return false;
        if (symbole != other.symbole)
            return false;
        return isCard == other.isCard;
    }
    bool operator!=(const Card& other) const {
        return !(*this == other);
    }
    bool operator<(const Card& other) const {
        if (isCard != other.isCard) return isCard < other.isCard;
        if (value != other.value) return value < other.value;
        return symbole < other.symbole;
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        if (card.isCard) {
            os << "Val " << std::left << std::setw(2) << static_cast<int>(card.value) 
               << " Sym " << static_cast<int>(card.symbole);
        }
        return os;
    }
};

template <size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<Card, N>& cards) {
    os << "[ ";
    for (size_t i = 0; i < N; ++i) {
        os << cards[i];
        
        if (i < N - 1 && cards[i + 1].isCard && cards[i].isCard) {
            os << " | ";
        }
    }
    os << " ]";
    return os;
}
#endif