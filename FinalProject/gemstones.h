//
// Created by Timothy Smith on 2016-11-15.
//

#ifndef CSI2372_CARD_H
#define CSI2372_CARD_H

#include <iostream>
#include <string>

#include "Card.h"




class Quartz : public Card {
    Quartz();
public:

    virtual void print ( std::ostream& o) const override;
    virtual std::string getName() const override;
    virtual int getCoinsPerCard(const int numCards) const override;

    static Quartz* create();

};


class Hematite : public Card {
    Hematite();
public:

    virtual void print ( std::ostream& o) const override;
    virtual std::string getName() const override;
    virtual int getCoinsPerCard(const int numCards) const override;

    static Hematite* create();
};


class Obsidian : public Card {
    Obsidian();
public:

    virtual void print ( std::ostream& o) const override;
    virtual std::string getName() const override;
    virtual int getCoinsPerCard(const int numCards) const override;

    static Obsidian* create();
};


class Malachite : public Card {
    Malachite();
public:

    virtual void print ( std::ostream& o) const override;
    virtual std::string getName() const override;
    virtual int getCoinsPerCard(const int numCards) const override;

    static Malachite* create();
};


class Turquoise : public Card {
    Turquoise();
public:

    virtual void print ( std::ostream& o) const override;
    virtual std::string getName() const override;
    virtual int getCoinsPerCard(const int numCards) const override;

    static Turquoise* create();
};


class Ruby : public Card {
    Ruby();
public:

    virtual void print ( std::ostream& o) const override;
    virtual std::string getName() const override;
    virtual int getCoinsPerCard(const int numCards) const override;

    static Ruby* create();
};


class Amethyst : public Card {
    Amethyst();
public:

    virtual void print ( std::ostream& o) const override;
    virtual std::string getName() const override;
    virtual int getCoinsPerCard(const int numCards) const override;

    static Amethyst* create();
};


class Emerald : public Card {
    Emerald();
public:

    virtual void print ( std::ostream& o) const override;
    virtual std::string getName() const override;
    virtual int getCoinsPerCard(const int numCards) const override;

    static Emerald* create();
};
#endif //CSI2372_CARD_H
