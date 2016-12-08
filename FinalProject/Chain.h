//
// Created by Timothy Smith on 2016-11-15.
//

#ifndef CSI2372_CHAIN_H
#define CSI2372_CHAIN_H
//
// Created by Timothy Smith on 2016-11-15.
//


#include <iostream>
#include <vector>
#include <string>
#include "gemstones.h"
#include "CardFactory.h"
#include "DiscardPile.h"


using std::vector;
using std::string;

class Chain_Base {
protected:
    string d_gemType;
    vector<Card*> d_chain;

public:
    Chain_Base(string _gemType) : d_gemType(_gemType) {};
    virtual ~Chain_Base() = default;
    virtual int sell() = 0;
    string getGemType() {
        return d_gemType;
    }
    virtual void print(std::ostream&) const = 0;
    Chain_Base& downcastAndAdd(Card *c);

    // Overload global insertion operator for all chains
    friend std::ostream& operator<<(std::ostream& o, Chain_Base& chain) {
        o << chain.getGemType() << "\t";
        chain.print(o);
        return o;
    };
    virtual vector<Card*>& getCards() {
        return d_chain;
    }

};

template<class T> class Chain : public Chain_Base {
public:
    Chain(std::string _gemType) : Chain_Base(_gemType) {}
    Chain(T* t) :
            Chain_Base(t->getName()) {
        d_chain.push_back(t);
    };

    virtual ~Chain() {
        d_chain.erase(d_chain.begin(), d_chain.end());
    }

    virtual Chain<T>& operator+=(T* gem) {
        d_chain.push_back(gem);
        return *this;
    }

    virtual int sell() override {
        int numCards = static_cast<int>(d_chain.size());
        return d_chain[0]->getCoinsPerCard(numCards);
    }

    virtual void print(std::ostream& o) const override{
        for (auto& c : d_chain) {
            c->print(o);
            o << " ";
        }
    }

    Chain(std::istream& in, CardFactory* cf) : Chain_Base("") {
        string buf;
        in >> d_gemType;
        in >> buf;
        while (in.good()) {
            in >> buf;
            if (buf == "~") { break; }
            else {
                *this += cf->generateCard(d_gemType);
            }
        }
    }
};



#endif //CSI2372_CHAIN_H
