//
// Created by Mark Mroz on 2016-11-16.
//

#ifndef CSI2372PROJECT_TABLE_H
#define CSI2372PROJECT_TABLE_H

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "CardFactory.h"


/**
 * Table will manage all the game components. It will hold two objects of type Player, the Deck and the DiscardPile, as well as the TradeArea.
 * bool win( std::string& ) returns true when a player has won. The name of the player is returned by reference (in the argument). The winning condition is that all cards from the deck must have been picked up and then the player with the most coins wins.
 * void print(std::ostream&) prints the complete table with all content. Intented for serialization to file.
 * Also add the insertion operator to print a Table to an std::ostream. The two players, the discard pile, the trading area should be printed. This is the top level print out. Note that a complete output with all cards for the pause functionality is printed with the separate function print above.
 * Table needs a constructor which accepts an std::istream and reconstruct the Table from file. Player( std::istream&, CardFactory* )
 */
using std::string;

class Table {

    Player* firstPlayer;
    Player* secondPlayer;
    Deck* deck;
    DiscardPile* discardPile;
    TradeArea* tradeArea;
    
public:
    
    Table(const Table &other) = delete;
    Table& operator=(const Table &other) = delete;

    // constructors
    Table(Player* player1, Player* player2, Deck* deck, DiscardPile* discardPile, TradeArea* tradeArea);

    // functions
    bool win(string& winner);
    void print(std::ostream& o);
    void printInGame(std::ostream& o);
    void printForPause(std::ostream& o);

    Player* getPlayer1();
    Player* getPlayer2();
    TradeArea* getTradeArea();
    DiscardPile* getDiscardPile();
    Deck* getDeck();

};


#endif //CSI2372PROJECT_TABLE_H
