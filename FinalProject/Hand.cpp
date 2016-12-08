//
//  Hand.cpp
//  C++ProjectXCode
//
//  Created by Mark Mroz on 2016-11-19.
//  Copyright © 2016 MarkMroz. All rights reserved.
//
#include <vector>
#include "Hand.h"

// Constructors
Hand::Hand() {}
// Adds the cardToAdd to the end of the vector

Hand& Hand::operator+=(Card *cardToAdd) {
    d_cards.push_back(cardToAdd);
    return *this;
}

// Gets the card at the given index

Card* Hand::operator[](int index) {
    if (index > d_cards.size()) {
        return nullptr;
    }
    else {
        Card* card = d_cards[index];
        d_cards.erase(d_cards.begin() + index);
        return card;
    }
}

vector<Card*>* Hand::getHand() {
    return &d_cards;
}

// returns and removes the top card from the player's hand

Card* Hand::play() {
    Card* cardToReturn = d_cards.front();
    d_cards.erase(d_cards.begin());

    return cardToReturn;
}

// get size
int Hand::getSize() const {
    int size = d_cards.size();
    return size;
}

//returns but does not remove the top card from the player's hand
Card* Hand::top() {
    return d_cards.front();
}

// prints all
void Hand::print(std::ostream &o) const {

    for (auto& c : d_cards) {
        o << c->getName() << " ";
    }
}

Hand::Hand( std::istream& in, CardFactory* cf) {
    string cards;
    while ((in >> cards)) {
        // Delimiter between objects
        if (cards == "~") {
            break;
        }
        Card *toAdd;
        toAdd = cf->generateCard(cards);
        d_cards.push_back(toAdd);
    }
}
