//
// Created by Timothy Smith on 2016-11-15.
//
#include "gemstones.h"
#include <iostream>
/** Quartz Class */

Quartz::Quartz() {};

Quartz* Quartz::create() {
    return new Quartz();
}

std::string Quartz::getName() const {
    return "Quartz";
}

int Quartz::getCoinsPerCard(const int numCards) const {
    switch (numCards) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 0;
        case 4:
        case 5:
            return 1;
        case 6:
        case 7:
            return 2;
        case 8:
        case 9:
            return 3;
        case 10:
            return 10;
        default:
            return 10;
    }
}

void Quartz::print(std::ostream &o) const {
    o << 'Q';
}

/** Hematite Class */

Hematite::Hematite() {};

Hematite* Hematite::create() {
    return new Hematite();
}

std::string Hematite::getName() const {
    return "Hematite";
}

int Hematite::getCoinsPerCard(const int numCards) const {
    switch (numCards) {
        case 0:
        case 1:
        case 2:
            return 0;
        case 3:
        case 4:
        case 5:
            return 1;
        case 6:
        case 7:
            return 2;
        case 8:
            return 3;
        case 9:
        default:
            return 4;
    }
}

void Hematite::print(std::ostream &o) const {
    o << 'H';
}

/** Obsidian Class */

Obsidian::Obsidian() {};

Obsidian* Obsidian::create() {
    return new Obsidian();
}

std::string Obsidian::getName() const {
    return "Obsidian";
}

int Obsidian::getCoinsPerCard(const int numCards) const {
    switch(numCards) {
        case 0:
        case 1:
        case 2:
            return 0;
        case 3:
        case 4:
            return 1;
        case 5:
        case 6:
            return 2;
        case 7:
            return 3;
        case 8:
        default:
            return 4;
    }
}

void Obsidian::print(std::ostream &o) const {
    o << 'O';
}

/** Malachite Class */

Malachite::Malachite() {};

Malachite* Malachite::create() {
    return new Malachite();
}

std::string Malachite::getName() const {
    return "Malachite";
}

int Malachite::getCoinsPerCard(const int numCards) const {
    switch(numCards) {
        case 0:
        case 1:
        case 2:
            return 0;
        case 3:
        case 4:
            return 1;
        case 5:
            return 2;
        case 6:
            return 3;
        case 7:
        default:
            return 4;
    }
}

void Malachite::print(std::ostream &o) const {
    o << 'M';
}

/** Turquoise Class */

Turquoise::Turquoise() {};

Turquoise* Turquoise::create() {
    return new Turquoise();
}

std::string Turquoise::getName() const {
    return "Turquoise";
}

int Turquoise::getCoinsPerCard(const int numCards) const {
    switch(numCards) {
        case 0:
        case 1:
            return 0;
        case 2:
        case 3:
            return 1;
        case 4:
        case 5:
            return 2;
        case 6:
            return 3;
        case 7:
        default:
            return 4;
    }
}

void Turquoise::print(std::ostream &o) const {
    o << 'T';
}

/** Ruby Class */

Ruby::Ruby() {};

Ruby* Ruby::create() {
    return new Ruby();
}

std::string Ruby::getName() const {
    return "Ruby";
}

int Ruby::getCoinsPerCard(const int numCards) const {
    switch(numCards) {
        case 0:
        case 1:
            return 0;
        case 2:
        case 3:
            return 1;
        case 4:
            return 2;
        case 5:
            return 3;
        case 6:
        default:
            return 4;
    }
}

void Ruby::print(std::ostream &o) const {
    o << 'R';
}

/** Amethyst Class */


Amethyst::Amethyst() {};

Amethyst* Amethyst::create() {
    return new Amethyst();
}

std::string Amethyst::getName() const {
    return "Amethyst";
}

int Amethyst::getCoinsPerCard(const int numCards) const {
    switch(numCards) {
        case 0:
        case 1:
            return 0;
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
            return 3;
        case 5:
        default:
            return 4;
    }
}

void Amethyst::print(std::ostream &o) const {
    o << 'A';
}

/** Emerald Class */

Emerald::Emerald() {};

Emerald* Emerald::create() {
    return new Emerald();
}

std::string Emerald::getName() const {
    return "Emerald";
}

int Emerald::getCoinsPerCard(const int numCards) const {
    switch(numCards) {
        case 0:
        case 1:
            return 0;
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            return 3;
    }
}

void Emerald::print(std::ostream &o) const {
    o << 'E';
}