#include <iostream>
#include <vector>
#include <fstream>
#include "Table.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::cout;
using std::cin;
using std::fstream;

int main() {
    // Init variables
    string p1_name;
    string p2_name;
    bool pauseGame = false;
    // build out startnew and loadold then we'll extract the methods.
    cout << "******* Welcome to Bohnanza! *******" << endl;
    cout << "Please enter Player 1's name: ";
    getline(cin, p1_name);
    cout << "Please enter Player 2's name: ";
    getline(cin, p2_name);
    cout << endl;

    Player player_1{p1_name};
    Player player_2{p2_name};
    Player players[]{player_1, player_2};

    // Initialize the deck
    Deck deck{CardFactory::getFactory()->getDeck()};

    // Make and set the hands
    player_1.makeHand(deck);
    player_2.makeHand(deck);
    CardFactory *cf = CardFactory::getFactory();
    Deck d = cf->getDeck();
    DiscardPile discardPile;
    TradeArea tradeArea{};

    Ruby *r = cf->createRuby();
    Chain<Ruby> chain{r};
    chain += (cf->createRuby());
    player_1.createChain(&chain);
    tradeArea.operator+=(cf->createAmethyst());
    tradeArea.operator+=(cf->createAmethyst());
    tradeArea.operator+=(cf->createTurquoise());
    discardPile.operator+=(cf->createAmethyst());
    discardPile.operator+=(cf->createAmethyst());
    discardPile.operator+=(cf->createEmerald());


    // Add to the table
    Table table{&player_1, &player_2, &deck, &discardPile, &tradeArea};

    table.print(cout);

    /**
     * Loading from pause:
     * 1. Player
     * 2. Chains
     * 3. Deck
     * 4. Hands
     * 5. Discard Pile
     * 6. TradeArea
     */
    cout << endl;
    cout << "TESTING" << endl;
    fstream file;
    file.open("new.txt", fstream::out);
    table.print(file);
    file.close();
    file.open("new.txt", fstream::in);

    Player player_3{file, cf};
    Player player_4{file, cf};
    Deck deck2{file, cf};
    DiscardPile discardPile2{file, cf};
    TradeArea tradeArea2{file, cf};

    cout << player_3 << endl;
    cout << *(player_3.getHand())<< endl;
    cout << player_4 << endl;
    cout << *(player_4.getHand()) << endl;
    cout << deck2 << endl;
    discardPile2.print(std::cout);
    cout << endl;
    cout << tradeArea2;
    cout << endl;


    file.close();
}
