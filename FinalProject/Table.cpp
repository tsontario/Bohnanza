//
// Created by Mark Mroz on 2016-11-16.
//

#include "Table.h"
using std::endl;
using std::string;

Table::Table(Player* player1, Player* player2, Deck* deck, DiscardPile* discardPile, TradeArea* tradeArea) :
        firstPlayer(player1), secondPlayer(player2), deck(deck), discardPile(discardPile), tradeArea(tradeArea)
{
    
}


bool Table::win(string& winner) {
    int one_coins = firstPlayer->getNumCoins();
    int two_coins = secondPlayer->getNumCoins();
    if (one_coins == two_coins) { return false; }
    winner = one_coins > two_coins ? firstPlayer->getName() : secondPlayer->getName();
    return true;
}

/**
 * Prints out the data of the game to file for saving.
 * @param o the output stream, expected to be a file stream
 */
void Table::print(std::ostream& o) {
    //variables
    int p1NumChains = firstPlayer->getNumChains();
    int p1MaxChains = firstPlayer->getMaxNumChains();
    int p2NumChains = secondPlayer->getNumChains();
    int p2MaxChains = secondPlayer->getMaxNumChains();

    //Player data
    o << firstPlayer->getName() << " ~ " << firstPlayer->getNumCoins() << "  ";
    o << p1NumChains << "  " << p1MaxChains << " ~ " << std::endl;
    for (int i=0; i<p1NumChains; ++i) {
        auto& chain = (*firstPlayer)[i];
        o << chain << " ~ " << endl;
    }
    o << *(firstPlayer->getHand()) << " ~ " << endl;

    o << secondPlayer->getName() << " ~ " << secondPlayer->getNumCoins() << "  ";
    o << p2NumChains << "  " << p2MaxChains << " ~ " << std::endl;
    for (int i=0; i<p2NumChains; ++i) {
        o << secondPlayer[i];
    }
    o << *(secondPlayer->getHand()) << " ~ " << endl;

    o << *deck << " ~ ";
    discardPile->print(o);
    o << " ~ ";
    tradeArea->numCards() == 0 ? (o << " ~ ") : (o << *tradeArea << " ~ ");
    o << std::endl;

}

void Table::printInGame(std::ostream& o) {
    o << "*** Current view of the gameboard: ***" << endl;
    o << *firstPlayer << endl;
    o << *secondPlayer << endl;
    o << "Discard Pile: ";
    o << *discardPile;
    o << "Trade Area: ";
    o << *tradeArea << endl;
    o << "***************************" << endl;
}

Player* Table::getPlayer1() {
    return firstPlayer;
}
Player* Table::getPlayer2() {
    return secondPlayer;
}
Deck* Table::getDeck() {
    return deck;
}
DiscardPile* Table::getDiscardPile() {
    return discardPile;
}
TradeArea* Table::getTradeArea() {
    return tradeArea;
}