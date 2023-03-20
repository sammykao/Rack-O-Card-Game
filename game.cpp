/*
 * game.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/9/2022
 * Edited for HW10 by: Sammy Kao
 * Date: 11/17/22
 * Purpose: Implement the methods for the Game class in the Rack-O game.
 *
 */
#include "game.h"
#include <iostream>

using namespace std;

// Constructor: initialize the deck, player hands, and the discard pile with new
// objects allocated on the heap
Game::Game(string deckFileName) {
  deck = new Deck(deckFileName);
  for (int i = 0; i < NUM_PLAYERS; i++) {
    hands[i] = new Hand(deck->draw(),
                        deck->draw(),
                        deck->draw(),
                        deck->draw(),
                        deck->draw());
  }
  discard = new DiscardPile(deck->draw());
}

// Destructor: deallocate all of the objects ''owned'' by the Game object
Game::~Game() {
  for (int i = 0; i < NUM_PLAYERS; i++) {
    delete hands[i];
  }
  delete discard;
  delete deck;
}


// play
// Input: none 
// Description: Play through a game of rack-o!
// Output: None
void Game::play() {
  int playerNum = 0;

  // Take the first turn
  cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
  takeTurn(playerNum);
  cout << endl;

  // Keep taking turns until either one player wins, or the deck runs out of
  // cards.
  while (!didPlayerWin(playerNum) && !deck->isEmpty()) {
    playerNum = (playerNum + 1) % NUM_PLAYERS;
    cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
    takeTurn(playerNum);
    cout << endl;
  }

  if (didPlayerWin(playerNum)) {
    // A player won!
    cout << "CONGRATULATIONS PLAYER " << playerNum + 1 << "! YOU WIN!!" << endl;
  } else {
    // deck is empty
    cout << "The deck is empty. IT'S A TIE!" << endl;
  }
}

// takeTurn
// Input: integer of player number
// Description: ask the player what he chooses 
// to do, and do that move based on the answer
// Output: None, only cout statements and printing
// out the players hand
void Game::takeTurn(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }
  // print player hand and discard pile
  cout << "Your hand:" << endl;
  hands[playerNum]->print();
  cout << endl << "Discard pile:" << endl;
  discard->print();
  int PlayerTurn = 8;
  while (PlayerTurn != 1 && PlayerTurn != 2) {
    cout << endl << "Would you like to" << endl;
    cout << " 1. take the top discard?" << endl;
    cout << " 2. draw from the deck?" << endl;
    cout << "Enter the number for your choice: ";
    cin >> PlayerTurn;
  }
  // pass it onto these functions based on user answer
  if (PlayerTurn == 1) {
    takeDiscard(playerNum);
  }
  if (PlayerTurn == 2) {
    drawFromDeck(playerNum);
  }
}


/// takeDiscard
// Input: integer of player number
// Description: take the top of the discard pile
// and pass that card into the replacecard function
// so the user can replace card in their hand
// it will then make the replaced card top of
// discard pile
// Output: None

void Game::takeDiscard(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }
  // take top of discard pile
  Card *replacementCard = discard->takeDiscard();
  // place that card into hand
  Card *new_discarded = hands[playerNum]->replaceCard(replacementCard);
  // discard whatever chosen card
  discard->discard(new_discarded);
  return;
}


/// drawFromDeck
// Input: integer of player number
// Description: draw a card from deck and 
// ask the user if they would like to keep 
// or not, and then call to replace card
// and then discard the replaced card
// Output: None
void Game::drawFromDeck(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }
  string playerdrawDecision;
  // show what card they drew
  cout << endl << "You drew:" << endl;
  Card *drawn_card = deck->draw();
  cout << drawn_card->toString() << endl;
  // ask what they would like to do
  while (playerdrawDecision != "y" && playerdrawDecision != "n") {
    cout << "Would you like to keep this card? (y/n) ";
    cin >> playerdrawDecision;
  }
  // run these functions based on user input
  if (playerdrawDecision == "y") {
    Card *new_discarded = hands[playerNum]->replaceCard(drawn_card);
    discard->discard(new_discarded);
  }
  if (playerdrawDecision == "n") {
    discard->discard(drawn_card);
    cout << endl;
    cout << endl << "Your new hand:" << endl;
    hands[playerNum]->print();
  }
}


// didPlayerWin
// Input: The player whose turn it is.
// Description: Check if the player has triggered the win condition
// Output: True if the given player has won; false otherwise.
bool Game::didPlayerWin(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }

  return hands[playerNum]->isWinningHand();
}
