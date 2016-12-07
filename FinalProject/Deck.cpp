//
// Created by Mark Mroz on 2016-11-16.
//

#include "Deck.h"

using std::istream;
using std::cout;
using std::endl;
using std::string;
using std::getline;

Deck::Deck(const Deck& otherDeck) {
    for (auto otherCard : otherDeck) {
        this->push_back(otherCard);
    }
}

Card* Deck::draw() {
    // If deck is not empty
    if (size() > 0) {
        Card* card = this->at(0);
        erase(begin());
        return card;
    }

    else {
        return nullptr;
    }
}

void Deck::print() {
    for (auto& i : *this) {
        std::cout << *i;
    }
}

// Make sure the order is right!
Deck::Deck(istream& in, CardFactory* cf) {
    string cards;
    while ((in >> cards)) {
        // Delimiter between objects
        if (cards == "~") {
            break;
        }
        char c = cards.at(0);
        Card* toAdd;

        if (c == 'A') {
            string name{"Amethyst"};
            toAdd = cf->createAmethyst();
        }
        else if (c == 'H') {
            string name{"Hematite"};
            toAdd = cf->createHematite();
        }
        else if (c == 'O') {
            string name{"Obsidian"};
            toAdd = cf->createObsidian();
        }
        else if (c == 'M') {
            string name{"Malachite"};
            toAdd = cf->createMalachite();
        }
        else if (c == 'T') {
            string name{"Turquoise"};
            toAdd = cf->createTurquoise();
        }
        else if (c == 'R') {
            string name{"Ruby"};
            toAdd = cf->createRuby();
        }
        else if (c == 'Q') {
            string name{"Quartz"};
            toAdd = cf->createQuartz();
        }
        else if (c == 'E') {
            string name{"Emerald"};
            toAdd = cf->createEmerald();
        }
        this->push_back(toAdd);

    }
}


