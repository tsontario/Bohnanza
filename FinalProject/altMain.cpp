#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Card.h"
#include "CardFactory.h"
#include "chain.h"
#include "Hand.h"
#include "Player.h"
#include "Table.h"

Table *makeTable(int, char*[]);
void writeToFile(Table* pTable);
void buyExtraChain(Player& pPlayer);
void addFromTradeArea(Player& pPlayer, TradeArea& tradeArea, DiscardPile& discardPile);
bool chainCard(Player &player, Card&card);
Chain_Base* makeChain(Card &card);
void playFromHand(Player &pPlayer);
void displayChains(Player &player);
bool isValidSale(int sell, Player &player);
void sellChain(int sell, Player &player);
void discard(Player &player, DiscardPile &discardPile);
void drawToTradeAreaFromDeck(TradeArea &tradeArea, Deck &deck);
void drawToTradeAreaFromDiscardPile(TradeArea &tradeArea, DiscardPile &discardPile);
void playInTradeArea(Player &player, TradeArea &tradeArea);
void drawCardsAfterTurn(Player &player, Deck &deck) ;

Table* table;

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::cout;
using std::cin;
using std::fstream;

int main(int argc, char* argv[]) {
    // Init variables
    string winningMessage = "The winner is: ";
    bool pauseGame = false;
    table = makeTable(argc, argv);
    // Start game loop
    Player* p1 = table->getPlayer1();
    Player* p2 = table->getPlayer2();
    Deck* deck = table->getDeck();
    DiscardPile* discardPile = table->getDiscardPile();
    TradeArea* tradeArea = table->getTradeArea();
    vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    *tradeArea += deck->draw();
    *tradeArea += deck->draw();
    *tradeArea += deck->draw();
    table->print(cout);

    while (deck->size() > 0) {
        if (pauseGame) {
            writeToFile(table);
            exit(0);
        }

        // The main game loop
        for (auto& player : players) {
            cout << "************ " << player->getName() << "'s turn! ************ " << endl << endl;
            table->printInGame(cout);
            cout << "Your hand: [FRONT] " << *(player->getHand()) << " [BACK]" << endl;
            buyExtraChain(*player);
            player->drawCard(deck->draw());
            addFromTradeArea(*player, *tradeArea, *discardPile);
            playFromHand(*player);
            discard(*player, *discardPile);
            drawToTradeAreaFromDeck(*tradeArea, *deck);
            drawToTradeAreaFromDiscardPile(*tradeArea, *discardPile);
            playInTradeArea(*player, *tradeArea);
            drawCardsAfterTurn(*player, *deck);

            cout << "DONE PLAYING FROM HAND";
        }
        break;
    }

    table->win(winningMessage);

    cout << endl;
}

void playInTradeArea(Player &player, TradeArea &tradeArea) {
    string ans;
    cout << "The trade area contains the following cards: " << endl;
    for (auto& card: tradeArea.getCards()) {
        cout << " " << card->getName() << " ";
    }
    cout << endl;
    for (auto& card: tradeArea.getCards()) {
        string c{card->getName()};

        while (true) {
            cout << "You examine the " << c << ". Would you like to [I]gnore or [C]hain it??";
            cin >> ans;
            if (ans.at(0) == 'c' || ans.at(0) == 'C') {
                tradeArea.trade(card->getName());
                chainCard(player, *card);

                break;
            }
            else if (ans.at(0) == 'i' || ans.at(0) == 'I') {
                break;
            }
            else {
                cout << endl << "Invalid selection, please try again: ";
            }

        }
    }
}

void drawCardsAfterTurn(Player &player, Deck &deck) {

    int numCardsDrawn = 0;

    for (int i = 0; i < 2; i++) {
        if (deck.size() == 0) {
            cout << "The deck is now empty";
            return;
        }
        player.drawCard(deck.draw());
        numCardsDrawn++;
    }

    cout << "You drew " << numCardsDrawn <<" cards from the deck";
}

void drawToTradeAreaFromDiscardPile(TradeArea &tradeArea, DiscardPile &discardPile) {
    cout << "Drawing from the discard pile, you got: ";

    Card* cardFromDiscardPile;

    if (!discardPile.isEmpty()) {
        cardFromDiscardPile = discardPile.top();
    } else {
        return;
    }

    while(!discardPile.isEmpty() && tradeArea.legal(cardFromDiscardPile)) {
        cardFromDiscardPile = discardPile.pickUp();
        cout << cardFromDiscardPile->getName();
        tradeArea.operator+=(cardFromDiscardPile);
    }

    cout << endl;

}

void drawToTradeAreaFromDeck(TradeArea &tradeArea, Deck &deck) {
    cout << "Drawing 3 cards to the trade area: ";
    for (int i = 0; i < 3; i++) {
        Card* drawnCard = deck.draw();
        cout << drawnCard->getName() << " ";
        tradeArea.operator+=(drawnCard);
    }

    cout << endl;
}

void discard(Player &player, DiscardPile &discardPile) {
    string ans;
    Hand* hand = player.getHand();
    int indexToDiscard;
    bool canDiscrad = hand->getSize() != 0;
    if (canDiscrad) {
        cout << "Your hand: [FRONT] " << *(player.getHand()) << " [BACK]" << endl;
        cout << "Select a card index to discard (C to cancel) : " << endl;
        cin >> ans;
        cout << endl;
        char a = ans.at(0);
        if (ans == 'C' || ans == 'c') {
            return;
        }
        indexToDiscard = atoi(ans.c_str());
        Card* cardToDiscard = hand->operator[](indexToDiscard);
        discardPile.operator+=(cardToDiscard);
    } else {
        cout << "You cannot discard because your hand is empty" << endl;
    }
}

void playFromHand(Player& player) {
    string ans;
    char c; // holds first char of ans
    Hand* hand = player.getHand();
    bool canChain = true;
    cout << "***You must now play a card from your hand: " << endl;
    do {
        if (hand->getSize() == 0) {
            cout << "Hand is empty. " << endl;
            break;
        }
        if (c == 'n' || c == 'N') {
            break;
        }
        // Get the card;
        Card* card = hand->operator[](0);


        cout << "Your hand: [FRONT] " << *(player.getHand()) << " [BACK]" << endl;
        cout << "You play a " << card->getName() << endl;
        cout << "Press any key to proceed" << endl;
        cin >> ans;
        cout << endl;
        // If a chain exists, chain the card
        for (int i=0; i<player.getNumChains(); ++i) {
            cout << endl;

            cout << "You play a " << card->getName() << endl;
            cout << "Press any key to proceed" << endl;

            if (player[i].getGemType() == card->getName()) {
                player[i].downcastAndAdd(card);
                cout << "Added card to chain." << endl;
                canChain = false;
                break;
            }
            else if (player.getNumChains() < player.getMaxNumChains()) {
                int index = player.getNumChains();
                Chain_Base* chain = makeChain(*card);
                player.createChain(chain);
                player[index].downcastAndAdd(card);
                cout << "You make a chain of " << card->getName() << endl;
                canChain = false;
                break;
            }
                // we have to sell a chain
            else {
                int chainToSell;
                cout << "You must sell a chain before you continue!" << endl;
                displayChains(player);
                cout << "Please select which chain you want to sell: ";
                cin >> chainToSell;
                while (!isValidSale(chainToSell, player)) {
                    cout << "Bad selection! Please enter the number of the chain you wish to sell: ";
                    cin >> chainToSell;
                }
                // Sell the old chain, add the new one
                int index = player.getNumChains()-1;
                sellChain(chainToSell, player);
                player.setNumChains(player.getNumChains()-1);
                Chain_Base* chain = makeChain(*card);
                player.createChain(chain);
                player[index].downcastAndAdd(card);
                displayChains(player);
                break;
            }
        }
        if (canChain) {
            canChain = false;
            int index = player.getNumChains();
            Chain_Base* chain = makeChain(*card);
            player.createChain(chain);
            player[index].downcastAndAdd(card);
            cout << "You make a chain of " << card->getName() << endl;

        }

        cout << "Your chains: " << endl; displayChains(player); cout << endl;
        cout << "Would you like to keep playing your hand?[Y/N]: ";
        cin >> ans;
        cout << "ANS: " << ans << endl;
        c = ans.at(0);
    } while (true);
}


void sellChain(int sell, Player &player) {
    int coinsEarned = player[sell].sell();
    player += coinsEarned;
    cout << "You earned " << coinsEarned << " coins!" << endl;
    vector<Card*>& chain = player[sell].getCards();
    vector<Chain_Base*>& chains = player.getChains();
    DiscardPile* discardPile = table->getDiscardPile();
    for (Card* card : chain) {
        *discardPile += card;
    }
    chains.erase(chains.begin() + sell);
}

bool isValidSale(int selection, Player &player) {
    return (selection >= 0 && selection < player.getNumChains());
}

void displayChains(Player &player) {
    for (int i=0; i<player.getNumChains(); ++i) {
        cout << "Chain [" << i << "]: "; player[i].print(cout); cout << endl;
    }
    cout << endl;
}

void addFromTradeArea(Player& player, TradeArea& tradeArea, DiscardPile& discardPile) {
    string ans;
    cout << "***************************" << endl;
    cout << "The trade area contains the following cards: " << endl;
    for (auto& card: tradeArea.getCards()) {
        cout << " " << card->getName() << " ";
    }
    cout << endl;
    for (auto& card: tradeArea.getCards()) {
        string c{card->getName()};

        while (true) {
            cout << "You examine the " << c << ". Would you like to [I]gnore, [D]iscard it or [C]hain it??";
            cin >> ans;
            if (ans.at(0) == 'd' || ans.at(0) == 'D') {
                discardPile += tradeArea.trade(card->getName());
                cout << "You discard the " << c << " card." << endl;
                break;
            }
            else if (ans.at(0) == 'c' || ans.at(0) == 'C') {
                tradeArea.trade(card->getName());
                chainCard(player, *card);
                break;
            }
            else if (ans.at(0) == 'i' || ans.at(0) == 'I') {
                break;
            }
            else {
                cout << endl << "Invalid selection, please try again: ";
            }

        }
    }
    cout << endl << "Trade Area now contains: " << endl;
    for (auto& card: tradeArea.getCards()) {
        cout << " " << card->getName() << " ";
    }
    cout << endl;

}

bool chainCard(Player& player, Card&card) {
    bool chainExists = false;
    for (int i=0; i<player.getNumChains(); ++i) {
        if (player[i].getGemType() == card.getName()) {
            player[i].downcastAndAdd(&card);
            chainExists = true;
            cout << "You add the " << card.getName() << " to your existing chain." << endl;
        }
    }

    if (!chainExists) {
        if (player.getNumChains() < player.getMaxNumChains()) {
            int indexToAdd = player.getNumChains();
            Chain_Base* chain = makeChain(card);
            player.createChain(chain);
            player[indexToAdd].downcastAndAdd(&card);
            cout << "You create a new chain of " << card.getName() << "s" << endl;
        }
        else {
            cout << "You have too many chains already. Discarding card instead." << endl;
            return false;
        }
    }
    cout << player;
    return true;
}

Chain_Base* makeChain(Card &card) {
    char c = card.getName().at(0);

    if (c == 'A') {
        Chain<Amethyst>* chain = new Chain<Amethyst>(card.getName());
        return chain;
    }
    else if (c == 'H') {
        Chain<Hematite>* chain = new Chain<Hematite>(card.getName());
        return chain;
    }
    else if (c == 'O') {
        Chain<Obsidian>* chain = new Chain<Obsidian>(card.getName());
        return chain;
    }
    else if (c == 'M') {
        Chain<Malachite>* chain = new Chain<Malachite>(card.getName());
        return chain;
    }
    else if (c == 'T') {
        Chain<Turquoise>* chain = new Chain<Turquoise>(card.getName());
        return chain;
    }
    else if (c == 'R') {
        Chain<Ruby>* chain = new Chain<Ruby>(card.getName());
        return chain;
    }
    else if (c == 'Q') {
        Chain<Quartz>* chain = new Chain<Quartz>(card.getName());
        return chain;
    }
    else if (c == 'E') {
        Chain<Emerald>* chain = new Chain<Emerald>(card.getName());
        return chain;
    }
    return nullptr;

}

void buyExtraChain(Player& player) {
    if (player.getNumChains() == 2 && player.getMaxNumChains() < 3 && player.getNumCoins() >=3) {
        string ans;
        cout << endl << "Would you like to buy a third chain for 3 coins[Y/N]? ";
        while (true) {
            cin >> ans;
            if (ans.at(0) == 'y' || ans.at(0) == 'Y') {
                player.setNumChains(3);
                cout << "You now have a third chain." << endl << endl;
                player += (-3);
                break;
            }
            else if (ans.at(0) == 'n' || ans.at(0) == 'N') {
                cout << "The maximum number of chains you can have is 2" << endl;
                break;
            }
            else {
                cout << endl << "Would you like to buy a third chain for 3 coins[Y/N]? ";
            }
        }
        cout << endl << endl;

    }
}

void writeToFile(Table *pTable) {
    string saveFile;
    cout << endl;
    cout << "Please enter the name of the savefile: ";
    cin >> saveFile;
    fstream file;
    file.open(saveFile, fstream::out);
    pTable->print(file);
    cout << "File saved successfully! To reload provide " << saveFile << " as commandline argument" << endl;
    file.close();
}

Table *makeTable(int argc, char*argv[]) {
    string p1_name;
    string p2_name;
    CardFactory* cf = CardFactory::getFactory();
    Player* p1;
    Player* p2;
    Deck* deck;
    DiscardPile* discardPile;
    TradeArea* tradeArea;
    Table* table;

    if (argc > 1) {
        fstream file;
        string fName{argv[1]};
        file.open(fName, std::__1::ios_base::in);

        // Construct from file
        p1 = new Player{file, cf};
        p2 = new Player{file, cf};
        deck = new Deck{file, cf};
        discardPile = new DiscardPile{file, cf};
        tradeArea = new TradeArea{file, cf};

    }
    else {
        cout << "******* Welcome to Bohnanza! *******" << endl;
        cout << "Please enter Player 1's name: ";
        getline(cin, p1_name);
        cout << "Please enter Player 2's name: ";
        getline(cin, p2_name);
        cout << endl;

        p1 = new Player{p1_name};
        p2 = new Player{p2_name};

        // Make and set the hands
        deck = new Deck(cf->getDeck());
        cout << "POINTER TO DECK " << endl;
        p1->makeHand(deck);
        p2->makeHand(deck);
        discardPile = new DiscardPile{};
        tradeArea = new TradeArea{};

    }
    table = new Table{p1, p2, deck, discardPile, tradeArea};
    return table;
}