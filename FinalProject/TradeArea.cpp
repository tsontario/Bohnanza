//
// Created by Mark Mroz on 2016-11-16.
//

#include "TradeArea.h"

// TODO - remove this after the Factory Pattern is implemented
TradeArea::TradeArea() {}
// pushes the given card to the end of the cards list
TradeArea& TradeArea::operator+=(Card* cardToAdd) {
    d_cards.push_back(cardToAdd);
    return *this;
}

// returns true if the cardToCheck is of the same type
bool TradeArea::legal(const Card *cardToCheck) {
    for (auto& card : d_cards) {
        if (card->getName() == cardToCheck->getName()) {
            return true;
        }
    }
    return false;
}

std::list<Card*> TradeArea::getCards() {
    return d_cards;
}

// removes and returns the first occurrence of the given gemstone name otherwise if not found returns nullptr
Card* TradeArea::trade(std::string gemstoneName) {
    std::list<Card*>::iterator it;
    for(auto& it : d_cards)
    {
        Card* card = dynamic_cast<Card*>(it);
        if (card->getName() == gemstoneName) {
            d_cards.remove(it);
            return card;
        }
    }
    return nullptr;
}

// returns the number of elements in the cards list

int TradeArea::numCards() const{
    return static_cast<int>(d_cards.size());
}

TradeArea::TradeArea(std::istream& in, CardFactory *cf) {
    string cards;
    while ((in >> cards)) {
        // Delimiter between objects
        if (cards == "~") {
            break;
        }
        Card *toAdd;
        toAdd = cf->generateCard(cards);
        d_cards.push_back(toAdd); // CLion parsing error
    }
}
