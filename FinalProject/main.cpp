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

// Helper method prototypes
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
bool mustSell(Player &player, Card *pCard);
bool chainExists(Player &player, Card *pCard);
bool askToPause();
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
    table = makeTable(argc, argv); // new game or load game
    Player* pausePlayer; // whose turn it is
    // Start game loop
    Player* p1 = table->getPlayer1();
    Player* p2 = table->getPlayer2();
    Deck* deck = table->getDeck();
    DiscardPile* discardPile = table->getDiscardPile();
    TradeArea* tradeArea = table->getTradeArea();
    vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    bool pauseGame = false;

    while (deck->size() > 0) {
        if (pauseGame) {
            writeToFile(table);
            exit(0);
        }

        // The main game loop
        for (auto& player : players) {
            cout << endl;
            cout << "************ " << player->getName() << "'s turn! ************************************************* "
                 << endl << endl;
            table->printInGame(cout);
            cout << endl;
            buyExtraChain(*player);  // Prompt to buy third chain?
            cout << "**************************************************************************************************" << endl;
            // Mandatory draw
            player->drawCard(deck->draw());
            cout << "You draw a card." << endl;
            cout << "Your hand: [FRONT] " << *(player->getHand()) << " [BACK]" << endl;

            // Gather from trade area
            addFromTradeArea(*player, *tradeArea, *discardPile);
            cout << "*********************************************" << endl;
            // Play the mandatory and optional cards from hand
            playFromHand(*player);
            cout << "*********************************************" << endl;
            // Optional discard
            discard(*player, *discardPile);
            cout << "*********************************************" << endl;
            // Go over trade area
            drawToTradeAreaFromDeck(*tradeArea, *deck);
            drawToTradeAreaFromDiscardPile(*tradeArea, *discardPile);
            playInTradeArea(*player, *tradeArea);
            cout << "*********************************************" << endl;
            // End of turn draw 2 cards from deck
            drawCardsAfterTurn(*player, *deck);
            cout << "*********************************************" << endl;
            // Set the pause and save flag?
        }
        pauseGame = askToPause();
    }
    string winner;
    table->win(winner);
    // if equal coins, both peopel are winners.
    cout << "Congratulations " << winner << "! You won!!" << endl;
    cout << endl;
    exit(0);
}

void playFromHand(Player& player) {
    string ans;
    char c; // holds first char of ans
    Hand *hand = player.getHand();
    cout << "***You must now play a card from your hand: " << endl;

    // Play the mandatory card, then loop
    do {
        if (hand->getSize() == 0) {
            cout << "Hand is empty. " << endl;
            break;
        }
        if (c == 'n' || c == 'N') {
            break;
        }

        Card* card = hand->play();
        cout << "You play a " + card->getName() << endl;
        cout << "*********************************************" << endl;
        cout << "Your hand is left with: [FRONT]" << *hand << " [BACK]" << endl;

        if (mustSell(player, card)) {
            int chainToSell;
            cout << "You must sell a chain before you continue!" << endl;
            displayChains(player);
            cout << "Please select which chain you want to sell: ";
            cin >> chainToSell;
            while (true) {
                if (!cin.fail()) {
                    if (isValidSale(chainToSell, player)) {
                        break;
                    }
                    cout << "Bad selection! Please enter the number of the chain you wish to sell: ";
                    cin.clear();
                    cin >> chainToSell;
                }
                else {
                    break;
                }
            }
            // Sell the old chain, add the new one
            int index = player.getNumChains()-1;
            sellChain(chainToSell, player);
            player.setNumChains(player.getNumChains()-1);
            Chain_Base* chain = makeChain(*card);
            player.createChain(chain);
            player[index].downcastAndAdd(card);
        }
        else if (chainExists(player, card)) {
            // Add to the existing chain
            for (int i=0; i<player.getNumChains(); ++i) {
                if (player[i].getGemType() == card->getName()) {
                    player[i].downcastAndAdd(card);
                    cout << "Added card to chain." << endl;
                    break;
                }
            }
        }
        else {
            // Create a new chain
            int index = player.getNumChains();
            Chain_Base* chain = makeChain(*card);
            player.createChain(chain);
            player[index].downcastAndAdd(card);
            cout << "You make a chain of " << card->getName() << endl;
        }
        cout << "Your chains: " << endl; displayChains(player); cout << endl;
        cout << "Would you like to keep playing your hand?[Y/N]: ";
        cin >> ans;
        cout << "ANS: " << ans;
        c = ans.at(0);

    } while (true);
}

bool chainExists(Player &player, Card *pCard) {
    for (int i=0; i<player.getNumChains(); ++i) {
        if (player[i].getGemType() == pCard->getName()) {
            return true;
        }
    }
    return false;
}

bool mustSell(Player &player, Card *card) {
    // we don't need to sell if we already have a chain of same type
    for (int i=0; i<player.getNumChains(); ++i) {
        if (player[i].getGemType() == card->getName()) {
            return false;
        }
    }
    // we don't need to sell if we have room for new chain
    if (player.getNumChains() < player.getMaxNumChains()) {
        return false;
    }
    return true;
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
    cout << "**************************************************************************************************" << endl;
    cout << "In this phase you may pick up cards from the trade area, ignore, or place them in the discard pile" << endl;
    cout << endl << "The trade area contains the following cards: " << endl;
    for (auto& card: tradeArea.getCards()) {
        cout << " " << card->getName() << " ";
    }
    cout << endl;
    for (auto& card: tradeArea.getCards()) {
        string c{card->getName()};
        // For each card in the trade area, ignore, discard, or chain it
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
    cout << "*********** End of phase ********************" << endl;
    cout <<  "Trade Area now contains: " << endl;
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
    cout << "Please enter the name of the savefile (e.g. save.txt): ";
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
        p1->makeHand(deck);
        p2->makeHand(deck);
        discardPile = new DiscardPile{};
        tradeArea = new TradeArea{};

    }
    table = new Table{p1, p2, deck, discardPile, tradeArea};
    return table;
}


void playInTradeArea(Player &player, TradeArea &tradeArea) {
    string ans;
    displayChains(player);
    cout << endl << "The trade area contains the following cards: " << endl;
    for (auto& card: tradeArea.getCards()) {
        cout << " " << card->getName() << " ";
    }
    cout << endl;
    for (auto& card: tradeArea.getCards()) {
        // for each card in trade area, chain it or ignore it.
        while (true) {
            cout << "You examine the " << card->getName() << ". Would you like to [I]gnore or [C]hain it? ";
            cin >> ans;
            if (ans.at(0) == 'c' || ans.at(0) == 'C') {
                if (mustSell(player, card)) {
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
                    int index = player.getNumChains() - 1;
                    sellChain(chainToSell, player);
                    player.setNumChains(player.getNumChains() - 1);
                    Chain_Base *chain = makeChain(*card);
                    player.createChain(chain);
                    player[index].downcastAndAdd(card);
                    tradeArea.trade(card->getName());
                    break;
                }
                else if (chainExists(player, card)) {
                    // Add to the existing chain
                    tradeArea.trade(card->getName());
                    for (int i = 0; i < player.getNumChains(); ++i) {
                        if (player[i].getGemType() == card->getName()) {
                            player[i].downcastAndAdd(card);
                            cout << "Added card to chain." << endl;
                            displayChains(player);
                            break;
                        }
                    }
                    break;
                }
                else {
                    // Create a new chain
                    int index = player.getNumChains();
                    Chain_Base *chain = makeChain(*card);
                    player.createChain(chain);
                    player[index].downcastAndAdd(card);
                    cout << "You make a chain of " << card->getName() << endl;
                    displayChains(player);
                    tradeArea.trade(card->getName());
                    break;

                }

            }
            else if (ans.at(0) == 'i' || ans.at(0) == 'I') {
                break;
            }
        }
    }
}

void drawCardsAfterTurn(Player &player, Deck &deck) {
    int numCardsDrawn = 0;
    for (int i = 0; i < 2; i++) {
        if (deck.size() == 0) {
            cout << "The deck is now empty" << endl;
            return;
        }
        player.drawCard(deck.draw());
        numCardsDrawn++;
    }
    cout << "You drew " << numCardsDrawn <<" cards from the deck" << endl << endl;
}

void drawToTradeAreaFromDiscardPile(TradeArea &tradeArea, DiscardPile &discardPile) {
    cout << "Drawing from the discard pile, you got: ";
    Card* cardFromDiscardPile;

    if (!discardPile.isEmpty()) {
        cardFromDiscardPile = discardPile.top();
    } else {
        cout << "The discard pile is empty" << endl;
        return;
    }

    for (Card* card : tradeArea.getCards()) {
        if (cardFromDiscardPile->getName() == card->getName()) {
            cardFromDiscardPile = discardPile.pickUp();
            cout << cardFromDiscardPile->getName() << " ";
            tradeArea.operator+=(cardFromDiscardPile);
        }
    }

    cout << endl;

}

void drawToTradeAreaFromDeck(TradeArea &tradeArea, Deck &deck) {
    cout << "Drawing 3 cards to the trade area: " << endl;
    for (int i = 0; i < 3; i++) {
        if (deck.empty()) {
            cout << "The deck is empty." << endl;
            return;
        }
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
        cout << "Your hand: ";
        vector<Card*>* vec_cards = hand->getHand();
        for (int i=0; i<vec_cards->size(); ++i) {
            cout << "[" << i << "]: " << *(vec_cards->operator[](i)) << ", ";
        }
        cout << "Choose a card to discard or enter 'c' if you don't want to discard a card" << endl;
        cin >> ans;
        cout << endl;
        char a = ans.at(0);
        if (a == 'C' || a == 'c') {
            return;
        }
        indexToDiscard = atoi(ans.c_str());
        cout << "INDEX TO DISCARD: " << indexToDiscard;
        Card* cardToDiscard = hand->operator[](indexToDiscard);
        cout << "You discard the " << cardToDiscard->getName();
        discardPile.operator+=(cardToDiscard);
    } else {
        cout << "You cannot discard because your hand is empty" << endl;
    }
}

bool askToPause() {
    string ans;
    cout << "Would you like to pause and save the game?[Y/N]" << endl;
    cin >> ans;

    char c = ans.at(0);
    if (c == 'Y' || c == 'y') {
        return true;
    }
    else {
        return false;
    }
}