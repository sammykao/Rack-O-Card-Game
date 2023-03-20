/*
 * hand.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: Sammy Kao
 * Date: 11/17/22
 * Purpose: Implement the methods for the Hand class in the Rack-O game.
 *
 */
#include "card.h"
#include "hand.h"
#include <iostream>

using namespace std;


// Constructor: Store the provided card pointers in our hand.
Hand::Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5) {
  cards[0] = c1;
  cards[1] = c2;
  cards[2] = c3;
  cards[3] = c4;
  cards[4] = c5;
}


// Destructor: Deallocate any cards in our hand
Hand::~Hand() {
  for (int i = 0; i < HAND_SIZE; i++) {
    delete cards[i];
  }
}

// isWinningHand()
// Input: No input needed
// Description: Check to see if the players hand
// is a winner by checking their number values of
// the cards
// Output: returns true if winner hand, else returns false
bool Hand::isWinningHand() {
  // we cannot directly get the numbers of cards
  // we must use the public getter functions
  if (cards[0]->getNum() < cards[1]->getNum()) {
    if (cards[1]->getNum() < cards[2]->getNum()) {
      if (cards[2]->getNum() < cards[3]->getNum()) {
        if (cards[3]->getNum() < cards[4]->getNum()) {
          return true;
        }
      }
    }
  }
  // all other conditions return false
  return false;
}


// replaceCard()
// Input: pointer to a card (we are passing in a card)
// Description: replace a card in the hand by
// asking the user what card they want to replace
// Output: returns the replaced card 
Card *Hand::replaceCard(Card *newCard) {
  cout << endl;
  print();
  cout << endl;
  // assign random value to cin integer
  int card_replacement = 6;
  while (card_replacement < 0 || card_replacement > 4) {
    cout << "Enter the index of the card you'd like to discard: ";
    cin >> card_replacement;
  }
  // make new card to hold replaced card
  Card *replaced_card = cards[card_replacement];
  cards[card_replacement] = newCard;
  cout << endl << "Your new hand:" << endl;
  print(); 

  // return the replaced card
  return replaced_card;
}

/*
 * Everything below this comment is purely for "drawing" hands on the screen.
 * Students won't need to read through or modify any of these methods.
 *
 */

void Hand::print() {
  for (int i = 0; i < HAND_SIZE; i++) {
    if (cards[i] == NULL) {
      cerr << "ERROR: hand does not have " << HAND_SIZE << " cards!" << endl;
      exit(EXIT_FAILURE);
    }
  }

  // print Top Edge
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getTopEdge();
  }
  cout << endl;

  // print Blank Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBlankLine();
  }
  cout << endl;

  // print Number Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getNumberLine();
  }
  cout << endl;

  // print Blank Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBlankLine();
  }
  cout << endl;

  // print Bottom Edge
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBottomEdge();
  }
  cout << endl;

  // print index numbers
  for (int i = 0; i < HAND_SIZE; i++) {
    cout << "   ";
    if (i > 0) {
      cout << "    ";
    }
    cout << i;
  }
  cout << endl;
}
