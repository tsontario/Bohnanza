//
// Created by Mark Mroz on 2016-11-16.
//

#include <iostream>
#include <vector>
#include "Chain.h"
#include "Hand.h"

#ifndef CSI2372PROJECT_PLAYER_H
#define CSI2372PROJECT_PLAYER_H

/**
 * Player( std::string& ) constructor that creates a Player with a given name.
 * std:string getName() get the name of the player.
 * int getNumCoins() get the number of coins currently held by the player. Player& operator+=( int ) add a number of coins
 * int getMaxNumChains() returns either 2 or 3.
 * int getNumChains() returns the number of non-zero chains
 * Chain& operator[](int i) returns the chain at position i.
 * void buyThirdChain() adds an empty third chain to the player for two coins. The functions reduces the coin count for the player by two. If the player does not have enough coins then an exception NotEnoughCoins is thrown.
 * void printHand(std::ostream&, bool) prints the top card of the player's hand (with argument false) or all of the player's hand (with argument true) to the supplied std::ostream.
 * Also add the insertion operator to print a Player to an std::ostream. The player's name, the number of coins in the player's possession and each of the chains (2 or 3, some possibly empty) should be printed. Note that the Hand is printed with a separate function. The player printout may look as follows:
 * Jane     3 coins
 * Ruby     R R R R
 * Quartz   Q
 * Player needs a constructor which accepts an std::istream and reconstruct the Player from file. Player( std::istream&, CardFactory* )
 */

using std::string;
using std::vector;

/** Class Definition */
class Player {
    string d_name;
    int d_coins;
    int d_maxChains = 2;
    int d_currentChains = 0;
    Hand* d_hand;
    vector<Chain_Base*> d_chains;

public:
    // constructor
    Player( string& _name);
    Player( std::istream& o, CardFactory* factory);

    // functions
    string getName() const;
    int getNumCoins() const;
    int getMaxNumChains() const;
    int getNumChains() const;
    Hand* getHand();

    void makeHand(Deck* deck);
    void drawCard(Card* c);
    vector<Chain_Base*>& getChains();
    void createChain(Chain_Base* chain);

    // operators
    Player& operator+=(int coins);
    Chain_Base& operator[](int i) const;

    friend std::ostream& operator<<(std::ostream& o, Player& p) {
        o << p.d_name << "    " << p.d_coins << " Coins" << std::endl;

        for (auto& chain : p.getChains()) {
            o << *chain << std::endl;
        }
        return o;
    }

    Chain_Base* makeChain(string type);
    void setNumChains(int x);
};
#endif //CSI2372PROJECT_PLAYER_H
