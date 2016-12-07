//
// Created by Mark Mroz on 2016-11-16.
//

#ifndef CSI2372PROJECT_HAND_H
#define CSI2372PROJECT_HAND_H

#include "Card.h"
#include "gemstones.h"
#include <list>
#include <queue>
#include "CardFactory.h"
#include <iostream>

using std::string;
/*
 *
 * Hand& operator+=(Card*) adds the card to the rear of the hand
 * Card* play() returns and removes the top card from the player's hand.
 * Card* top() returns but does not remove the top card from the player's hand.
 * Card* operator[](int) returns and removes the Card at a given index.
 * Also add the insertion operator to print Hand on an std::ostream. The hand should print all the cards in order.
 * Hand needs a constructor which accepts an std::istream and reconstruct the Hand from file. Hand( std::istream&, CardFactory* )
 * */

class Hand {
    vector<Card*> d_cards;

public:
    // operators
    Hand& operator+=(Card* cardToAdd);
    Card* operator[](int);

    //constructors
    Hand();
    Hand(std::istream& stream, CardFactory* cardFactory);

    //functions
    Card* play();
    Card* top();
    void print(std::ostream& out) const;
    vector<Card*>* getHand();
    const bool isEmpty();
    int getSize() const;


    friend std::ostream& operator<<(std::ostream& o,  Hand& h) {

        const vector<Card*>* cards = h.getHand();
        for (auto& card : *cards) {
            o << card->getName() << " ";
        }
        return o;
    };

};

#endif //CSI2372PROJECT_HAND_H
