// deck.cpp
//
// Created by Kwonwoo Choi on 11/5/2018.
//

#include <cstdlib>  // rand
#include "deck.h"

// Default constructor
// pristine, sorted deck
Deck::Deck()
{
    myIndex = 0;

    // add sorted cards into deck
    for(int suit = 0; suit < 4; suit++)
    {
        for(int rank = 0; rank < 13; rank++)
        {
            Card c(rank+1, (Card::Suit)suit); // (Card::Suit) converts casts int as a Suit
            myCards[myIndex] = c; // add card to deck

            myIndex++;
        }
    }

    myIndex = 0; // reset to "top" of deck
}

/* FUNCTION - void shuffle
    * shuffle the cards in the current deck

    input parms - none

    output parms - deck is shuffled
*/
void Deck::shuffle()
{
    const unsigned int NUM_CARDS = size(); // swap cards NUM_CARDS times

    if(NUM_CARDS > 1)
    {
        for(int i = 0; i < NUM_CARDS; i++)
        {
            // get two random positions for cards to switch
            int rand1 = rand() % NUM_CARDS;
            int rand2 = rand() % NUM_CARDS;
            while(rand1 == rand2) // make sure rand1 and rand2 are different
                rand2 = rand() % NUM_CARDS;
            
            // cards swap places
            Card temp = myCards[rand1];
            myCards[rand1] = myCards[rand2];
            myCards[rand2] = temp;
        }
    }
}

/* FUNCTION - Card dealCard
    * get a card, after 52 are dealt, fail
    * precondition - only call 52 times (or the number of cards in the deck)
                   - after 52 calls, don't call again 
    
    input parms - none

    output parms - returns card from the deck
*/
Card Deck::dealCard()
{
    if(size() > 0)
        return myCards[myIndex++];
    else // Deck has no more cards. Return useless card
    {
        Card c;
        return c;
    }
}

/* FUNCTION - int size
    * returns the number of cards left in the deck

    input parms - none

    output parms - returns int number of cards left in the deck
*/
int Deck::size() const
{
    return SIZE - myIndex;
}
