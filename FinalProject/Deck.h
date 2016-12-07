//
// Created by Mark Mroz on 2016-11-16.
//

#ifndef CSI2372PROJECT_DECK_H
#define CSI2372PROJECT_DECK_H

/**
 * Deck is a simple derived class from std::vector.
 * Card* draw() returns and removes the top card from the deck.
 * Also add the insertion operator to insert all the cards in the deck to an std::ostream.
 * The Deck needs a constructor which accepts an std::istream and reconstructs the deck from file. Deck( std::istream&, CardFactory* )
 */

#include <vector>
#include <iostream>
#include "gemstones.h"
#include "CardFactory.h"
class CardFactory; // forward declaration


using std::vector;

class Deck : public vector<Card*> {

    friend class CardFactory;
public:
    
    Deck& operator=(const Deck &other) = default;
    Deck(std::istream&, CardFactory*);
    Deck(const Deck& otherDeck);
    Card* draw();

    friend std::ostream& operator<<(std::ostream& o, const Deck& deck) {
        if (deck.size() == 0) {
            return o;
        } else {
            for (auto& iter : deck) {
                o << *iter;
            }
        }
        return o;
    }

    void print();
    
private:
    Deck(){};
};


#endif //CSI2372PROJECT_DECK_H
