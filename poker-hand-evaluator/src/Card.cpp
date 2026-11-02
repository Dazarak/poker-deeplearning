#include "Card.h"

// Le constructeur : il initialise une "non-carte" par défaut
Card::Card() {
    value = 15;
    symbole = 7;
    isCard = false;
}

Card::Card(uint8_t _value, uint8_t _symbole, bool _isCard) {
    value = _value;
    symbole = _symbole;
    isCard = _isCard;
}