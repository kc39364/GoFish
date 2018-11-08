// go_fish.cpp
// main run file

#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS, srand
#include <ctime>       // Provides time
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;


// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);

/* FUNCTION - void turn
    * implements a player's full turn for Go Fish game

    input parms - Player whose turn it is, opposite player, and deck of cards

    output parms - Go Fish turn is played
*/
void turn(Player &p1, Player &p2, bool &playerTurn, Deck &d);

/* FUNCTION - void displayAll
    * prints out each player's hand and books

    input parms - Players 1 and 2

    output parms - each player's hand and books printed
*/
void displayAll(Player &p1, Player &p2);


int main( )
{
    cout << "Go Fish Game" << endl << endl;
    int numCards = 5;
    
    Player p1("Joe");
    Player p2("Jane");
    
    Deck d;  //create a deck of cards
    srand(time(NULL));
    d.shuffle();
    
    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);
       
    cout << p1.getName() <<"'s hands : " << p1.showHand() << endl;
    cout << p2.getName() <<"'s hands : " << p2.showHand() << endl << endl;

    cout << "Any cards to book?" << endl;
    //remove books from hand and add to books
    Card book1, book2;
    while(p1.checkHandForBook(book1, book2))
    {
        p1.bookCards(p1.removeCardFromHand(book1), p1.removeCardFromHand(book2));
    }
    while(p2.checkHandForBook(book1, book2))
    {
        p2.bookCards(p2.removeCardFromHand(book1), p2.removeCardFromHand(book2));
    }

    displayAll(p1, p2);


    // GAME IS READY TO PLAY
    bool playerTurn = true; // true is p1 turn, false is p2 turn
    while(p1.getBookSize() + p2.getBookSize() != 26)
    {
        if(playerTurn)
            turn(p1, p2, playerTurn, d);
        else
            turn(p2, p1, playerTurn, d);
    }

    cout << "The game is over. Who won?" << endl;
    cout << "******************************" << endl;
    cout << p1.getName() << " has " << p1.getBookSize() << " books." << endl;
    cout << p2.getName() << " has " << p2.getBookSize() << " books." << endl << endl;

    if(p1.getBookSize() > p2.getBookSize())
        cout << p1.getName() << " wins!" << endl;
    else if(p1.getBookSize() < p2.getBookSize())
        cout << p2.getName() << " wins!" << endl;
    else
        cout << p1.getName() << " and " << p2.getName() << " tie!" << endl;
    
    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}

void turn(Player &p1, Player &p2, bool &playerTurn, Deck &d)
{
    Card chosenC = p1.chooseCardFromHand();
    cout << p1.getName() << " asks -  Do you have a " << chosenC.getRank() << "?" << endl;

    if(p2.rankInHand(chosenC))
    {
        while(p2.rankInHand(chosenC))
        {
            
        }

        Card book1, book2;
        p1.checkHandForBook(book1, book2);
        p1.bookCards(p1.removeCardFromHand(book1), p1.removeCardFromHand(book2));
    }
    else
    {
        cout << p2.getName() << "says - Go Fish" << endl;

        if(d.size() > 0)
            p1.addCard(d.dealCard());
        Card book1, book2;
        if(p1.checkHandForBook(book1, book2))
        {
            p1.bookCards(p1.removeCardFromHand(book1), p1.removeCardFromHand(book2));
        }

        playerTurn = !playerTurn;
    }

    displayAll(p1, p2);
}

void displayAll(Player &p1, Player &p2)
{
    cout << p1.getName() <<"'s hands : " << p1.showHand() << endl;
    cout << p2.getName() <<"'s hands : " << p2.showHand() << endl;
    cout << p1.getName() <<"'s books : " << p1.showBooks() << endl;
    cout << p2.getName() <<"'s books : " << p2.showBooks() << endl << endl;    
}
