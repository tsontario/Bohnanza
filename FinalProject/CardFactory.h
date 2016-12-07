//
// Created by Mark Mroz on 2016-11-16.
//

#ifndef CSI2372PROJECT_CARDFACTORY_H
#define CSI2372PROJECT_CARDFACTORY_H

#include <vector>
#include <iostream>
#include <string>
#include "Deck.h"
#include "gemstones.h"
class Deck; // forward declaration
/**
 * The card factory serves as a factory for all the gemstone cards. In the constructor for CardFactory all the cards need to be created in the numbers needed for the game (see the above table). Ensure that no copies can be made of CardFactory and that there is at most one CardFactory object in your program.
 * static CardFactory* getFactory() returns a pointer to the only instance of CardFactory.
 * Deck getDeck() returns a deck with all 104 gemstone cards. Note that the 104 gemstone cards are always the same but their order in the deck needs to be different every time. Use std::shuffle to achieve this.
 */

using std::vector;

class CardFactory {
    vector<Card*> d_cards;
    CardFactory();
public:
    // Remove copy c_tor and assignment operator
    CardFactory(const CardFactory&) = delete;
    CardFactory operator=(const CardFactory&) = delete;

    // Singleton pattern
    static CardFactory* getFactory();

    Card *generateCard(std::string &name); // This function delegates to the specific createGem method
    Ruby* createRuby();
    Quartz* createQuartz();
    Hematite* createHematite();
    Obsidian* createObsidian();
    Malachite* createMalachite();
    Amethyst* createAmethyst();
    Emerald* createEmerald();
    Turquoise* createTurquoise();

    // Factory methods
    Deck getDeck();


};


#endif //CSI2372PROJECT_CARDFACTORY_H
