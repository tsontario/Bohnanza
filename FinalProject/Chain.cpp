//
// Created by Timothy Smith on 2016-12-04.
//
#include "Chain.h"

Chain_Base& Chain_Base::downcastAndAdd(Card* card) {
    char c = card->getName().at(0);
    if (c == 'A') {
        Chain<Amethyst>* chain = dynamic_cast<Chain<Amethyst>*>(this);
        Amethyst* gem = dynamic_cast<Amethyst*>(card);
        *chain += gem;
    }
    else if (c == 'H') {
        Chain<Hematite>* chain = dynamic_cast<Chain<Hematite>*>(this);
        Hematite* gem = dynamic_cast<Hematite*>(card);
        *chain += gem;
    }
    else if (c == 'O') {
        Chain<Obsidian>* chain = dynamic_cast<Chain<Obsidian>*>(this);
        Obsidian* gem = dynamic_cast<Obsidian*>(card);
        *chain += gem;
    }
    else if (c == 'M') {
        Chain<Malachite>* chain = dynamic_cast<Chain<Malachite>*>(this);
        Malachite* gem = dynamic_cast<Malachite*>(card);
        *chain += gem;
    }
    else if (c == 'T') {
        Chain<Turquoise>* chain = dynamic_cast<Chain<Turquoise>*>(this);
        Turquoise* gem = dynamic_cast<Turquoise*>(card);
        *chain += gem;
    }
    else if (c == 'R') {
       Chain<Ruby>* chain = dynamic_cast<Chain<Ruby>*>(this);
        Ruby* gem = dynamic_cast<Ruby*>(card);
        *chain += gem;
    }
    else if (c == 'Q') {
        Chain<Quartz>* chain =  dynamic_cast<Chain<Quartz>*>(this);
        Quartz* gem = dynamic_cast<Quartz*>(card);
        *chain += gem;
    }
    else if (c == 'E') {
        Chain<Emerald>* chain = dynamic_cast<Chain<Emerald>*>(this);
        Emerald* gem = dynamic_cast<Emerald*>(card);
        *chain += gem;
    }

    return *this;
}

