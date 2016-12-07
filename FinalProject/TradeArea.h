//
// Created by Mark Mroz on 2016-11-16.
//

#ifndef CSI2372PROJECT_TRADEAREA_H
#define CSI2372PROJECT_TRADEAREA_H

#include <list>
#include <string>
#include "gemstones.h"
#include "CardFactory.h"

using std::string;
/**
 * The class TradeArea will have to hold cards openly and support random access insertion and removal. The TradeArea holds cards in a std::list.
 * TradeArea& operator+=( Card* ) adds the card to the trade area but it does not check if it is legal to place the card.
 * bool legal( Card* ) returns true if the card can be legally added to the TradeArea, i.e., a card of the same gemstone is already in the TradeArea.
 * Card* trade( string ) removes a card of the corresponding gemstone name from the trade area.
 * int numCards() returns the number of cards currently in the trade area.
 * Also add the insertion operator to insert all the cards of the trade area to an std::ostream.
 * The TradeArea needs a constructor which accepts an std::istream and reconstruct the TradeArea from file. TradeArea( std::istream&, CardFactory* )
 */

class TradeArea {
    std::list<Card*> d_cards;

public:
    // operators
    TradeArea& operator+=(Card* cardToAdd);

    // constructors
    TradeArea();
    TradeArea( std::istream&, CardFactory* );

    // methods
    bool legal(const Card* cardToCheck);
    Card* trade( std::string gemstoneName );
    int numCards() const;
    std::list<Card*> getCards();
    
    

    friend std::ostream& operator<<(std::ostream& o, const TradeArea& t) {
        
        if (t.d_cards.size() == 0) {
            o << "Trade area is empty" << std:: endl;
        } else {
            for(auto& c : t.d_cards) {
                o << c->getName() << " ";
            }
        }

        return o;
    };

};


#endif //CSI2372PROJECT_TRADEAREA_H
