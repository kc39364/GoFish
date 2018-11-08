// player.cpp
//
// Created by Kwonwoo Choi on 11/5/2018.
//

#include <cstdlib>     // Provides rand
#include "player.h"

/* FUNCTION - void addCard
    * adds a card to the hand

    input parms - Card c

    output parms - card is added to hand
*/
void Player::addCard(Card c)
{
    myHand.push_back(c);
}

/* FUNCTION - void bookCards
    * Adds cards to book

    input parms - Cards c1 and c2 to book

    output parms - cards are added to book
*/
void Player::bookCards(Card c1, Card c2)
{
    myBook.push_back(c1);
    myBook.push_back(c2);
}

/* FUNCTION - bool checkHandForBook
    * this function will check a players hand for a pair (two cards with the same rank)
    * If a pair is found, it returns true and populates the two variables with the cards that make the pair.

    input parms - Card c1 and c2 to populate with cards to book

    output parms - returns true if pair is found, false if not
                 - two input cards are populated with cards to book
*/
bool Player::checkHandForBook(Card &c1, Card &c2)
{
    vector <Card>::iterator iterCard;
    for(iterCard = myHand.begin(); iterCard != myHand.end(); iterCard++)
    {
        Card firstCard = *iterCard; // this card will be checked with every other card to find a matching rank

        vector <Card>::iterator iterPair;
        for(iterPair = iterCard + 1; iterPair != myHand.end(); iterPair++)
        {
            Card secondCard = *iterPair; // the card to be checked with firstCard

            if(firstCard.getRank() == secondCard.getRank()) // if same rank, then output
            {
                c1 = firstCard;
                c2 = secondCard;
                return true;
            }
        }
    }

    return false;
}


/* FUNCTION - bool rankInHand
    * Check if the player has a card with the same rank as c in her hand

    input parms - Card c to check

    output parms - returns true if card with same rank is in hand, false if not
*/
bool Player::rankInHand(Card c) const
{
    vector <Card>::const_iterator iter;
    for(iter = myHand.begin(); iter != myHand.end(); iter++)
    {
        if((*iter).getRank() == c.getRank()) // checks if rank number is the same
            return true;
    }

    return false;
}

/* FUNCTION - Card chooseCardFromHand
    *uses some strategy to choose one card from the player's
     hand so they can say "Do you have a 4?"

    input parms - none

    output parms - returns Card from player's hand
*/
Card Player::chooseCardFromHand() const
{
    const unsigned int SIZE_HAND = myHand.size();
    return myHand[rand() % SIZE_HAND]; // returns random card from hand
}

/* FUNCTION - bool cardInHand
    * Check if the player has the card c in her hand

    input parms - Card c to check

    output parms - returns true if card  is in hand, false if not
*/
bool Player::cardInHand(Card c) const
{
    vector <Card>::const_iterator iter;
    for(iter = myHand.begin(); iter != myHand.end(); iter++)
    {
        if(*iter == c)
            return true;
    }

    return false;
}

/* FUNCTION - Card removeCardFromHand
    * Remove the card c from the hand and return it to the caller

    input parms - Card c to remove

    output parms - returns card to remove from hand
                 - remove card from hand
*/
Card Player::removeCardFromHand(Card c)
{
    Card removedCard; // card that was removed (empty at first)

    vector <Card>::iterator iter;
    for(iter = myHand.begin(); iter != myHand.end(); iter++)
    {
        if(*iter == c)
        {
            removedCard = *iter;
            myHand.erase(iter); // deletes card from hand
            iter--;
        }
    }

    return removedCard;
}

/* FUNCTION - string showHand
    * returns a string version of all the cards in hand

    input parms - none

    output parms - returns string version of all the cards in hand
*/
string Player::showHand() const
{
    string hand; // contains the string version of all the cards in hand

    vector <Card>::const_iterator iter;
    for(iter = myHand.begin(); iter != myHand.end(); iter++)
    {
        hand += (*iter).toString() + " "; // add each card to string hand
    }

    return hand;
}

/* FUNCTION - string showBooks
    * returns a string version of all the books of the player
    * precondition - a book consists of two cards, so myBook contains even number of cards

    input parms - none

    output parms - returns string version of all the books of the player
*/
string Player::showBooks() const
{
    string books; // contains the string version of all the books of the player

    vector <Card>::const_iterator iter;
    for(iter = myBook.begin(); iter != myBook.end(); iter++)
    {
        // string contains each book together
        books += (*iter).toString() + "-";
        iter++;
        books += (*iter).toString() + " "; // new line after each book
    }

    return books;
}

/* FUNCTION - int getHandSize
    * returns number of cards in hand

    input parms - none

    output parms - returns int number of cards in hand
*/
int Player::getHandSize() const
{
    return myHand.size();
}

/* FUNCTION - int getBookSize
    * returns number of books of the player

    input parms - none

    output parms - returns int number of books of the player
*/
int Player::getBookSize() const
{
    return (myBook.size() / 2); // each book consists of two cards
}
