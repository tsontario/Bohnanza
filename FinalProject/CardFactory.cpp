//
// Created by Mark Mroz on 2016-11-16.
//
#include <iostream>
#include <random>
#include "CardFactory.h"

using std::string;

CardFactory::CardFactory() {}

CardFactory* CardFactory::getFactory() {
    static CardFactory instance;
    return &instance;
}

Deck CardFactory::getDeck() {
    Deck deck;
    for (int i=0; i<20; i++) {
        Quartz* q = Quartz::create();
        deck.push_back(q);
    }
    for (int i=0; i<18; i++) {
        Hematite* h = Hematite::create();
        deck.push_back(h);
    }
    for (int i=0; i<16; i++) {
        Obsidian* o = Obsidian::create();
        deck.push_back(o);
    }
    for (int i=0; i<14; i++) {
        Malachite* m = Malachite::create();
        deck.push_back(m);
    }
    for (int i=0; i<12; i++) {
        Turquoise* t = Turquoise::create();
        deck.push_back(t);
    }
    for (int i=0; i<10; i++) {
        Ruby* r = Ruby::create();
        deck.push_back(r);
    }
    for (int i=0; i<8; i++) {
        Amethyst* a = Amethyst::create();
        deck.push_back(a);
    }
    for (int i=0; i<6; i++) {
        Emerald* e = Emerald::create();
        deck.push_back(e);
    }

    // shuffling procedure found on Stack Overflow
    std::random_device random_device;
    std::mt19937 seed(random_device());
    std::shuffle(deck.begin(), deck.end(), seed);

    return deck;
}


Card* CardFactory::generateCard(string& name) {
    Card* toAdd{nullptr};
    char c = name.at(0);
    if (c == 'A') {
        toAdd = this->createAmethyst();
    } else if (c == 'H') {
        toAdd = this->createHematite();
    } else if (c == 'O') {
        toAdd = this->createObsidian();
    } else if (c == 'M') {
        toAdd = this->createMalachite();
    } else if (c == 'T') {
        toAdd = this->createTurquoise();
    } else if (c == 'R') {
        toAdd = this->createRuby();
    } else if (c == 'Q') {
        toAdd = this->createQuartz();
    } else if (c == 'E') {
        toAdd = this->createEmerald();
    }
    return toAdd;
}

Ruby* CardFactory::createRuby() {
    Ruby* ruby = Ruby::create();
    return ruby;
};
Quartz* CardFactory::createQuartz() {
    Quartz* quartz = Quartz::create();
    return quartz;
};
Hematite* CardFactory::createHematite() {
    Hematite* hematite = Hematite::create();
    return hematite;
};
Obsidian* CardFactory::createObsidian() {
    Obsidian* obsidian = Obsidian::create();
    return obsidian;
};
Malachite* CardFactory::createMalachite() {
    Malachite* malachite = Malachite::create();
    return malachite;
};
Amethyst* CardFactory::createAmethyst() {
    Amethyst* amethyst = Amethyst::create();
    return amethyst;
};
Emerald* CardFactory::createEmerald() {
    Emerald* emerald = Emerald::create();
    return emerald;
};

Turquoise* CardFactory::createTurquoise() {
    Turquoise* turquoise = Turquoise::create();
    return turquoise;
};
