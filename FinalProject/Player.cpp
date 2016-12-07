//
// Created by Mark Mroz on 2016-11-16.
//

#include <vector>
#include "Player.h"
using std::string;
using std::vector;
using std::cout;
using std::endl;

/** Constructors */

Player::Player( string& _name) : d_name(_name), d_coins(2)
{
    d_hand = new Hand();
}


//Player( std::istream& o, CardFactory* factory) {
//
//}

/** Access and Modifiers */

string Player::getName() const {
    return d_name;
}

int Player::getNumCoins() const {
    return d_coins;
}

int Player::getNumChains() const {
    return d_currentChains;
}

int Player::getMaxNumChains() const {
    return d_maxChains;
}

Hand* Player::getHand()  {
    return d_hand;
}

void Player::makeHand(Deck* deck) {
    for (int i=0; i<5; ++i) {
       *d_hand += (deck->draw());
    }
}

void Player::buyThirdChain() {
    try {
        if (d_maxChains == 3) {
            throw new MaxChainException();;
        }
        else if (d_coins < 2) {
            throw new NotEnoughCoinsException();
        }
        else {
            d_maxChains = 3;
            d_coins -= 2;
        }
    }
    catch (MaxChainException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (NotEnoughCoinsException& e) {
        std::cout << e.what() << std::endl;
    }
}

void Player::drawCard(Card *c) {
    *d_hand += c;
}

vector<Chain_Base*>& Player::getChains() {
    return d_chains;
}

void Player::createChain(Chain_Base *chain) {
    if (d_currentChains < d_maxChains) {
        d_chains.push_back(chain);
        ++d_currentChains;
    }
}

void Player::setNumChains(int x) {
    d_currentChains = x;
}
/**
 * Prints either one or all cards in the Player's hand
 *
 * @param o The output stream
 * @param completeList if false, print top of hand, otherwise print all
 *          card in hand
 */
void Player::printHand(std::ostream& o, bool completeList) {
    if (!completeList) {
        o << d_hand->top()->getName();
    }
    else {
        o << d_hand;
    }
}

/** operators */
Player& Player::operator+=( int coins) {
    d_coins += coins;
    return *this;
}

Chain_Base& Player::operator[](int index) const{
    return *(d_chains[index]);
}

Player::Player(std::istream& in, CardFactory* cf) {
    string data;
    d_hand = new Hand();
    if (!in.good()) {
        return;
    }
    string buf;
    in >> d_name;
    in >> buf;
    in >> d_coins;
    in >> d_currentChains;
    in >> d_maxChains;
    in >> buf;
    //make the chains
    for (int i=0; i < d_currentChains; ++i) {
        // What kind of chain?
        in >> buf;
        Chain_Base* chain = makeChain(buf); // create
        d_chains.push_back(chain); // link
        string type = chain->getGemType();
        in >> buf; // redundant card; created automatically with a chain
        while (true) {
            in >> buf;
            if (buf == "~") { break; }
            else {
                Card* toAdd = cf->generateCard(type);
                chain->downcastAndAdd(toAdd);
            }
        }
    }
    // Make the hand
    while (true) {
        in >> buf;
        if (buf == "~") { break; }
        else {
            Card* toAdd = cf->generateCard(buf);
            this->drawCard(toAdd);
        }
    }
    return;
}

Chain_Base* Player::makeChain(std::string buf) {
    CardFactory* cf = CardFactory::getFactory();
    char c = buf.at(0);
    if (c == 'A') {
        Amethyst* gem = cf->createAmethyst();
        Chain<Amethyst>* chain = new Chain<Amethyst>(gem);
        return chain;
    }
    else if (c == 'H') {
        Hematite* gem = cf->createHematite();
        Chain<Hematite>* chain = new Chain<Hematite>(gem);
        return chain;
    }
    else if (c == 'O') {
        Obsidian* gem = cf->createObsidian();
        Chain<Obsidian>* chain = new Chain<Obsidian>(gem);
        return chain;
    }
    else if (c == 'M') {
        Malachite* gem = cf->createMalachite();
        Chain<Malachite>* chain = new Chain<Malachite>(gem);
        return chain;
    }
    else if (c == 'T') {
        Turquoise* gem = cf->createTurquoise();
        Chain<Turquoise>* chain = new Chain<Turquoise>(gem);
        return chain;
    }
    else if (c == 'R') {
        Ruby* gem = cf->createRuby();
        Chain<Ruby>* chain = new Chain<Ruby>(gem);
        return chain;
    }
    else if (c == 'Q') {
        Quartz* gem = cf->createQuartz();
        Chain<Quartz>* chain = new Chain<Quartz>(gem);
        return chain;
    }
    else if (c == 'E') {
        Emerald* gem = cf->createEmerald();
        Chain<Emerald>* chain = new Chain<Emerald>(gem);
        return chain;
    }
    return nullptr;
}
