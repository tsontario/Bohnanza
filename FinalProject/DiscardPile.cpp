//
// Created by Mark Mroz on 2016-11-16.
//

#include "DiscardPile.h"

DiscardPile::DiscardPile() {}

DiscardPile& DiscardPile::operator+=(Card* cardToAdd) {
    d_cards.push_back(cardToAdd);
    return *this;
}

Card* DiscardPile::pickUp() {
    auto& cardToReturn = *(d_cards.end()-1);
    d_cards.pop_back();
    return cardToReturn;
}

Card* DiscardPile::top() {
    if (d_cards.size() != 0) {
        Card* c = *(d_cards.end()-1);
        return c;
    }
    return nullptr;
}

bool DiscardPile::isEmpty() const {
    return d_cards.size() == 0;
}

void DiscardPile::print(std::ostream& o) const {
    for (auto& card : d_cards) {
        o << card->getName() << " ";
    }
}

DiscardPile::DiscardPile(std::istream &in, CardFactory *cf) {
    string cards;
    while ((in >> cards)) {
        // Delimiter between objects
        if (cards == "~") {
            break;
        }
        Card *toAdd;
        toAdd = cf->generateCard(cards);
        *this += toAdd;
    }
}


