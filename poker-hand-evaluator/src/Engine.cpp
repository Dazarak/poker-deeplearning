#include "Engine.h"

// ######################### EVALUATE HANDS #########################

HandResult Engine::EvaluatePlayersHands(std::array<Card, Config::MAX_CARDS> allCards)
{
    std::array<Card, Config::CARDS_PER_PLAYER> dft{};
    HandResult result;

    auto activeCards = isRoyalFlush(allCards);
    if (dft != activeCards)
    {
        result.handRank = ROYAL_FLUSH;
        result.activeCards = activeCards;
        return result;
    }

    activeCards = isStraightFlush(allCards);
    if (dft != activeCards)
    {
        result.handRank = STRAIGHT_FLUSH;
        result.activeCards = activeCards;
        return result;
    }

    activeCards = isFourOfKind(allCards);
    if (dft != activeCards)
    {
        result.handRank = FOUR_OF_A_KIND;
        result.activeCards = activeCards;
        return result;
    }

    activeCards = isFullHouse(allCards);
    if (dft != activeCards)
    {
        result.handRank = FULL_HOUSE;
        result.activeCards = activeCards;
        return result;
    }

    activeCards = isFlush(allCards);
    if (dft != activeCards)
    {
        result.handRank = FLUSH;
        result.activeCards = activeCards;
        return result;
    }

    activeCards = isStraight(allCards);
    if (dft != activeCards)
    {
        result.handRank = STRAIGHT;
        result.activeCards = activeCards;
        return result;
    }

    activeCards = isThreeOfKind(allCards);
    if (dft != activeCards)
    {
        result.handRank = THREE_OF_A_KIND;
        result.activeCards = activeCards;
        return result;
    }

    activeCards = isTwoPair(allCards);
    if (dft != activeCards)
    {
        result.handRank = TWO_PAIR;
        result.activeCards = activeCards;
        return result;
    }

    activeCards = isPair(allCards);
    if (dft != activeCards)
    {
        result.handRank = PAIR;
        result.activeCards = activeCards;
        return result;
    }

    SortCards(allCards);
    for (int j = Config::MAX_CARDS - 1, idx = 0; j >= 0 && idx < 5; j--) {
        if (allCards[j].isCard) {
            result.activeCards[idx++] = allCards[j];
        }
    }
    result.handRank = HIGH_CARD;

    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isRoyalFlush(array<Card, Config::MAX_CARDS>& Cards) {

    array<Card, Config::MAX_CARDS> suitBuckets[4]; 
    uint8_t bucketSizes[4] = {0, 0, 0, 0};

    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };

    for (uint8_t i = 0; i < Config::MAX_CARDS; i++) { // Trie par couleur des cartes
        if (Cards[i].isCard) {
            uint8_t s = Cards[i].symbole;
            suitBuckets[s][bucketSizes[s]] = Cards[i];
            bucketSizes[s]++;
        }
    }

    for (uint8_t s = 0; s < 4; s++) { // Pour chaque couleur
        if (bucketSizes[s] >= 5) { // Si il y a 5 cartes ou plus de la même couleur
            bool has10 = false, hasJ = false, hasQ = false, hasK = false, hasA = false;
            for (uint8_t j = 0; j < bucketSizes[s]; j++) { // Vérifier si il y a les carte de la suite royal dans la couleur
                if (suitBuckets[s][j].value == 8) has10 = true;
                if (suitBuckets[s][j].value == 9) hasJ = true;
                if (suitBuckets[s][j].value == 10) hasQ = true;
                if (suitBuckets[s][j].value == 11) hasK = true;
                if (suitBuckets[s][j].value == 12) hasA = true;
            }
            if (has10 && hasJ && hasQ && hasK && hasA)
            {
                for (uint8_t j = 0; j < bucketSizes[s]; j++) { 
                    if (suitBuckets[s][j].value == 12) result[0] = suitBuckets[s][j]; // As
                    if (suitBuckets[s][j].value == 11) result[1] = suitBuckets[s][j]; // Roi
                    if (suitBuckets[s][j].value == 10) result[2] = suitBuckets[s][j]; // Dame
                    if (suitBuckets[s][j].value == 9)  result[3] = suitBuckets[s][j]; // Valet
                    if (suitBuckets[s][j].value == 8)  result[4] = suitBuckets[s][j]; // 10
                }
                return result; // Retourne les cartes du joueur qui compose la quinte flush royale
            }
        }
    }
    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isStraightFlush(std::array<Card, Config::MAX_CARDS>& Cards) {
    std::array<Card, Config::MAX_CARDS> suitBuckets[4]; 
    uint8_t bucketSizes[4] = {0, 0, 0, 0};

    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };

    // On sépare les cartes par couleur
    for (uint8_t i = 0; i < Config::MAX_CARDS; i++) { 
        if (Cards[i].isCard) {
            uint8_t s = Cards[i].symbole;
            if (s < 4) {
                suitBuckets[s][bucketSizes[s]] = Cards[i];
                bucketSizes[s]++;
            }
        }
    }

    for (uint8_t s = 0; s < 4; s++) { 
        if (bucketSizes[s] >= 5) {
            result = isStraight(suitBuckets[s]);
            
            if (result[0].isCard) {
                return result;
            }
        }
    }

    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isFourOfKind(array<Card, Config::MAX_CARDS>& Cards)
{
    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };
    SortCards(Cards);
    
    for (int8_t i = Config::MAX_CARDS - 4; i >= 0; i--) {
        if (Cards[i].isCard && Cards[i+3].isCard) { 
            if (Cards[i].value == Cards[i+3].value) { 
                result[0] = Cards[i];
                result[1] = Cards[i+1];
                result[2] = Cards[i+2];
                result[3] = Cards[i+3];

                for (int8_t j = Config::MAX_CARDS - 1; j >= 0; j--) {
                    if (Cards[j].isCard && Cards[j].value != Cards[i].value) {
                        result[4] = Cards[j];
                        break;
                    }
                }
                return result;
            }
        }
    }
    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isFullHouse(array<Card, Config::MAX_CARDS>& Cards) {

    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };
    SortCards(Cards); 
    
    int8_t vBrelan = -1;
    uint8_t brelanIndex = 0;

    // On cherche le brelan le plus fort en partant de la fin
    for (int8_t i = Config::MAX_CARDS - 3; i >= 0; i--) {
        if (Cards[i].isCard && Cards[i+2].isCard) {
            if (Cards[i].value == Cards[i+2].value) {
                vBrelan = Cards[i].value;
                brelanIndex = i;
                break;
            }
        }
    }

    if (vBrelan == -1) return result;

    // On cherche la paire la plus forte (hors du brelan) en partant de la fin
    for (int8_t j = Config::MAX_CARDS - 2; j >= 0; j--) {
        if (Cards[j].isCard && Cards[j+1].isCard) {
            if (Cards[j].value == Cards[j+1].value && Cards[j].value != vBrelan) {
                // On remplit le Brelan
                result[0] = Cards[brelanIndex];
                result[1] = Cards[brelanIndex + 1];
                result[2] = Cards[brelanIndex + 2];
                // On remplit la Paire
                result[3] = Cards[j];
                result[4] = Cards[j+1];
                return result; 
            }
        }
    }

    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isFlush(array<Card, Config::MAX_CARDS>& Cards)
{
    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };

    SortCardsBySymbole(Cards);

    for (int8_t i = Config::MAX_CARDS - 5; i >= 0; i--) {
        if (Cards[i].isCard && Cards[i+4].isCard) { 
            if (Cards[i].symbole == Cards[i+4].symbole) { 
                result = { Cards[i+4], Cards[i+3], Cards[i+2], Cards[i+1], Cards[i] };
                return result; 
            }
        }
    }

    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isStraight(std::array<Card, Config::MAX_CARDS>& Cards) {

    std::array<Card, Config::MAX_CARDS> sortedCards = Cards;
    SortCards(sortedCards);

    std::array<Card, Config::MAX_CARDS> uniqueCards;
    uint8_t uniqueCount = 0;

    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };

    // Déduplication en gardant l'objet Card complet
    for (uint8_t i = 0; i < Config::MAX_CARDS; i++) {
        if (sortedCards[i].isCard) {
            if (uniqueCount == 0 || uniqueCards[uniqueCount - 1].value != sortedCards[i].value) {
                uniqueCards[uniqueCount] = sortedCards[i];
                uniqueCount++;
            }
        }
    }

    if (uniqueCount < 5) return result;

    // Recherche de la suite classique 
    uint8_t sequence = 1;
    for (int8_t i = uniqueCount - 2; i >= 0; i--) { // On parcourt la liste à l'envers pour trouver la suite la plus grande
        if (uniqueCards[i+1].value == uniqueCards[i].value + 1) {
            sequence++;
            if (sequence >= 5) {
                result[0] = uniqueCards[i + 4];
                result[1] = uniqueCards[i + 3];
                result[2] = uniqueCards[i + 2];
                result[3] = uniqueCards[i + 1];
                result[4] = uniqueCards[i];
                return result;
            }
        } else {
            sequence = 1;
        }
    }

    // Cas particulier de la petite suite As-2-3-4-5
    if (uniqueCards[uniqueCount - 1].value == 12) { // Si la valeur la plus grande de la liste est un As
        int8_t idx2 = -1, idx3 = -1, idx4 = -1, idx5 = -1;

        for (uint8_t i = 0; i < uniqueCount; i++) {
            if (uniqueCards[i].value == 0) idx2 = i; 
            if (uniqueCards[i].value == 1) idx3 = i; 
            if (uniqueCards[i].value == 2) idx4 = i; 
            if (uniqueCards[i].value == 3) idx5 = i;
        }

        if (idx2 != -1 && idx3 != -1 && idx4 != -1 && idx5 != -1) {
            result[0] = uniqueCards[idx5];
            result[1] = uniqueCards[idx4];
            result[2] = uniqueCards[idx3];
            result[3] = uniqueCards[idx2];
            result[4] = uniqueCards[uniqueCount - 1];
            return result;
        }
    }

    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isThreeOfKind(array<Card, Config::MAX_CARDS>& Cards) {

    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };
    SortCards(Cards);

    for (uint8_t i = 0; i < Config::MAX_CARDS - 2; i++) {
        if (Cards[i].isCard && Cards[i+2].isCard) { 
            if (Cards[i].value == Cards[i+2].value) {
                result[0] = Cards[i];
                result[1] = Cards[i+1];
                result[2] = Cards[i+2];

                for (int8_t j = Config::MAX_CARDS - 1; j >= 0; j--) {
                    if (Cards[j].isCard && Cards[j].value != Cards[i].value) {
                        result[3] = Cards[j];
                        break;
                    }
                }
                for (int8_t j = Config::MAX_CARDS - 1; j >= 0; j--) {
                    if (Cards[j].isCard && Cards[j].value != Cards[i].value && Cards[j].value != result[3].value) {
                        result[4] = Cards[j];
                        break;
                    }
                }
            }
        }
    }
    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isTwoPair(array<Card, Config::MAX_CARDS>& Cards) {

    std::array<Card, 2> FirstPair;
    std::array<Card, 2> SecondPair;
    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };
    SortCards(Cards);

    uint8_t nbPair = 0;
    for (uint8_t i = 0; i < Config::MAX_CARDS - 1; i++) 
        if (Cards[i].isCard && Cards[i+1].isCard) 
            if (Cards[i].value == Cards[i+1].value) {
                if (nbPair == 0) {
                    FirstPair = {Cards[i], Cards[i+1]};
                }
                else if (nbPair == 1) {
                    SecondPair = {Cards[i], Cards[i+1]};
                }
                else {
                    FirstPair = SecondPair;
                    SecondPair = {Cards[i], Cards[i+1]};
                }

                nbPair++;
                i++; 
            }

    if (nbPair >= 2) {
        result = { SecondPair[0], SecondPair[1], FirstPair[0], FirstPair[1] };

        for (int8_t j = Config::MAX_CARDS - 1; j >= 0; j--)
            if (Cards[j].isCard && Cards[j].value != result[0].value && Cards[j].value != result[2].value) {
                result[4] = Cards[j];
                break;
            }
    }
    return result;
}

std::array<Card, Config::CARDS_PER_PLAYER> Engine::isPair(array<Card, Config::MAX_CARDS>& Cards) {
    std::array<Card, Config::CARDS_PER_PLAYER> result = { Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false), Card(15,7,false) };
    SortCards(Cards);
    for (uint8_t i = 0; i < Config::MAX_CARDS - 1; i++) 
        if (Cards[i].isCard && Cards[i+1].isCard) 
            if (Cards[i].value == Cards[i+1].value) {
                result = { Cards[i], Cards[i+1] };

                for (int8_t j = Config::MAX_CARDS - 1; j >= 0; j--)
                    if (Cards[j].isCard && Cards[j].value != Cards[i].value) {
                        result[2] = Cards[j];
                        break;
                    }
                
                for (int8_t j = Config::MAX_CARDS - 1; j >= 0; j--) 
                    if (Cards[j].isCard && Cards[j].value != Cards[i].value && Cards[j].value != result[2].value) {
                        result[3] = Cards[j];
                        break;
                    }
                
                for (int8_t j = Config::MAX_CARDS - 1; j >= 0; j--) 
                    if (Cards[j].isCard && Cards[j].value != Cards[i].value && Cards[j].value != result[2].value && Cards[j].value != result[3].value) {
                        result[4] = Cards[j];
                        break;
                    }
                
            }

    return result;
}

// ######################### SORT FUNCTION #########################

void Engine::SortCards(std::array<Card, Config::MAX_CARDS>& Cards) {
    std::sort(Cards.begin(), Cards.end(), [](const Card& a, const Card& b) {
        return a.value < b.value; // Tri par valeur croissante
    });
}

void Engine::SortCardsBySymbole(std::array<Card, Config::MAX_CARDS>& Cards) {
    std::sort(Cards.begin(), Cards.end(), [](const Card& a, const Card& b) {
        if (a.symbole != b.symbole) {
            return a.symbole < b.symbole;
        }
        return a.value < b.value; // Tri secondaire par valeur
    });
}