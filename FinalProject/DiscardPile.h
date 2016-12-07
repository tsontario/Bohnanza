//
// Created by Mark Mroz on 2016-11-16.
//

#ifndef CSI2372PROJECT_DISCARDPILE_H
#define CSI2372PROJECT_DISCARDPILE_H

#include "gemstones.h"
#include "CardFactory.h"
#include <iostream>
#include <vector>

/**
 * The DiscardPile holds cards in a std::vector and is similar to Deck.
 * DiscardPile& operator+=( Card* ) discards the card to the pile.
 * Card* pickUp() returns and removes the top card from the discard pile.
 * Card* top() returns but does not remove the top card from the discard pile.
 * void print( std::ostream& ) to insert all the cards in the DiscardPile to an std::ostream.
 * Also add the insertion operator to insert only the top card of the discard pile to an std::ostream.
 * The DiscardPile needs a constructor which accepts an std::istream and reconstructs the DiscardPile from file. DiscardPile( std::istream&, CardFactory* )
 */

using std::vector;
using std::cout;
using std::string;

class DiscardPile {
    vector <const Card*> d_cards;
public:

    // operators
    const DiscardPile& operator+=(const Card* cardToAdd);

    // constructors
    DiscardPile();
    DiscardPile( std::istream& o, CardFactory* factory);

    // functions
    const Card* pickUp();
    const Card* top() const;
    void print(std::ostream& o) const;
    bool isEmpty() const;
    
    friend std::ostream& operator<<(std::ostream& o, const DiscardPile& d) {
        
        if (d.isEmpty()) {
            o << "Discard pile is empty" << std::endl;
        } else {
            o << *(d.top());
        }
        return o;
    };
    

};


#endif //CSI2372PROJECT_DISCARDPILE_H
