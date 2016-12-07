//
// Created by Mark Mroz on 2016-11-16.
//

/**
 * CARD HEIRARCHY
 *
 * Create the gemstone card hierarchy. A gemstone card can be printed to console with its first character of its name. The base class Card should be abstract, derived classes Quartz, Hematite, Obsidian, Malachite, Turquoise, Ruby, Amethyst, and Emerald will have to be concrete classes.
 * Card will have the following pure virtual functions:
 * virtual int getCardsPerCoin( int coins ) will implement in the derived classes the above table for how many cards are necessary to receive the corresponding number of coins.
 * virtual string getName() returns the full name of the card (e.g., Ruby).
 * virtual void print(std::ostream& out) inserts the first character for the card into the output stream supplied as argument. You will also need to create a global stream insertion operator for printing any objects of such a class which implements the “Virtual Friend Function Idiom” with the class hierarchy.
 */

#ifndef CSI2372PROJECT_CARD_H
#define CSI2372PROJECT_CARD_H
#include <iostream>

class Card {
public:
    virtual ~Card() {};

    // Pure virtual methods
    virtual int getCoinsPerCard(const int numCards) const = 0;
    virtual std::string getName() const = 0;
    virtual void print(std::ostream& out) const = 0;

    // Polymorphic stream insertion
    friend std::ostream& operator<<(std::ostream& o, const Card& c) {
        o << c.getName() << " ";
        return o;
    };
};


#endif //CSI2372PROJECT_CARD_H
