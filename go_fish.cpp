// go_fish.cpp
// main run file

#include <iostream>    // Provides cout and cin
#include <fstream>     // For file access
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
void turn(Player &p1, Player &p2, bool &playerTurn, Deck &d, ofstream &results);

/* FUNCTION - void displayAll
    * prints out each player's hand and books

    input parms - Players 1 and 2

    output parms - each player's hand and books printed
*/
void displayAll(Player &p1, Player &p2, ofstream &results);


int main( )
{
    ofstream results("gofish_results.txt");
    if(!results.is_open())
        cout << "Unable to open write file." << endl;

    cout << "*****Go Fish!*****" << endl << endl;
    results << "*****Go Fish!*****" << endl << endl;
    
    int numCards = 7; // 7 cards are dealt each to two players
    Player p1("Joe");
    Player p2("Jane");
    
    Deck d;  //create a deck of cards
    srand(time(NULL));
    d.shuffle();
    
    cout << "Deal Cards:" << endl;
    results << "Deal Cards:" << endl;
    dealHand(d, p1, numCards); // 7 cards are dealt to the players
    dealHand(d, p2, numCards);
       
    cout << p1.getName() <<"'s hands : " << p1.showHand() << endl;
    cout << p2.getName() <<"'s hands : " << p2.showHand() << endl << endl;
    results << p1.getName() <<"'s hands : " << p1.showHand() << endl;
    results << p2.getName() <<"'s hands : " << p2.showHand() << endl << endl;

    cout << "Any cards to book?" << endl;
    results << "Any cards to book?" << endl;
    //remove all books from hand and add to books
    Card book1, book2;
    while(p1.checkHandForBook(book1, book2))
    {
        p1.bookCards(p1.removeCardFromHand(book1), p1.removeCardFromHand(book2));
    }
    while(p2.checkHandForBook(book1, book2))
    {
        p2.bookCards(p2.removeCardFromHand(book1), p2.removeCardFromHand(book2));
    }

    displayAll(p1, p2, results);


    // GAME IS READY TO PLAY
    cout << "Start Go Fish!" << endl;
    cout << "******************************" << endl;
    results << "Start Go Fish!" << endl;
    results << "******************************" << endl;

    bool playerTurn = true; // true is p1 turn, false is p2 turn
    while(p1.getBookSize() + p2.getBookSize() != 26)
    {
        if(playerTurn)
            turn(p1, p2, playerTurn, d, results);
        else
            turn(p2, p1, playerTurn, d, results);
        
        displayAll(p1, p2, results);
    }

    cout << "The game is over. Who won?" << endl;
    cout << "******************************" << endl;
    cout << p1.getName() << " has " << p1.getBookSize() << " books." << endl;
    cout << p2.getName() << " has " << p2.getBookSize() << " books." << endl << endl;
    results << "The game is over. Who won?" << endl;
    results << "******************************" << endl;
    results << p1.getName() << " has " << p1.getBookSize() << " books." << endl;
    results << p2.getName() << " has " << p2.getBookSize() << " books." << endl << endl;

    // compare the number of books of each player to determine the winner
    if(p1.getBookSize() > p2.getBookSize())
    {
        cout << p1.getName() << " wins!" << endl;
        results << p1.getName() << " wins!" << endl;
    }
    else if(p1.getBookSize() < p2.getBookSize())
    {
        cout << p2.getName() << " wins!" << endl;
        results << p2.getName() << " wins!" << endl;
    }
    else
    {
        cout << p1.getName() << " and " << p2.getName() << " tie!" << endl;
        results << p1.getName() << " and " << p2.getName() << " tie!" << endl;
    }
    
    results.close(); // close the output file
    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}

void turn(Player &p1, Player &p2, bool &playerTurn, Deck &d, ofstream &results)
{
    // Player draws card in the beginning if no cards are in hand
    // This is to continue player's turn
    if((p1.getHandSize() == 0) && (d.size() > 0)) // only if deck still has cards
    {
        Card dealt = d.dealCard();
        cout << "Out of cards! " << p1.getName() << " draws " << dealt.toString() << endl;
        results << "Out of cards! " << p1.getName() << " draws " << dealt.toString() << endl;
        p1.addCard(dealt);
    }
    
    Card chosenC = p1.chooseCardFromHand(); // pick random card from hand to ask for
    cout << p1.getName() << " asks - Do you have a " << chosenC.rankString(chosenC.getRank()) << "?" << endl;
    results << p1.getName() << " asks - Do you have a " << chosenC.rankString(chosenC.getRank()) << "?" << endl;

    if(p2.rankInHand(chosenC)) // opposing player has the rank
    {
        cout << p2.getName() << " says - Yes. I have a " << chosenC.rankString(chosenC.getRank()) << "." << endl;
        results << p2.getName() << " says - Yes. I have a " << chosenC.rankString(chosenC.getRank()) << "." << endl;

        // There is no method for removing a specific rank from hand, so
        // check every suit of the specific rank.
        for(int suit = 0; suit < 4; suit++)
        {
            Card temp(chosenC.getRank(), (Card::Suit)suit);
            if(p2.cardInHand(temp))
            {
                p1.addCard(p2.removeCardFromHand(temp)); // exchange card between players
            }
        }

        // Now player has a book in hand, so remove cards from hand and add to books
        Card book1, book2;
        p1.checkHandForBook(book1, book2);
        p1.bookCards(p1.removeCardFromHand(book1), p1.removeCardFromHand(book2));
        cout << p1.getName() << " books " << book1.toString() + "-" + book2.toString() << endl;
        results << p1.getName() << " books " << book1.toString() + "-" + book2.toString() << endl;

        // Opposing player draws a card if no cards are left in hand
        // This is to continue original player's turn
        if((p2.getHandSize() == 0) && (d.size() > 0)) // only if deck still has cards
        {
            Card dealt = d.dealCard();
            cout << "Out of cards! " << p2.getName() << " draws " << dealt.toString() << endl;
            results << "Out of cards! " << p2.getName() << " draws " << dealt.toString() << endl;
            p2.addCard(dealt);
        }
    }
    else // opposing player does not have the rank
    {
        cout << p2.getName() << " says - Go Fish" << endl;
        results << p2.getName() << " says - Go Fish" << endl;

        // Player draws card if deck still has cards
        if(d.size() > 0)
        {
            Card dealt = d.dealCard();
            cout << p1.getName() << " draws " << dealt.toString() << endl;
            results << p1.getName() << " draws " << dealt.toString() << endl;
            p1.addCard(dealt);

        }

        // If drawn card creates a book, remove cards from hand and add to books
        Card book1, book2;
        if(p1.checkHandForBook(book1, book2))
        {
            p1.bookCards(p1.removeCardFromHand(book1), p1.removeCardFromHand(book2));
            cout << p1.getName() << " books " << book1.toString() + "-" + book2.toString() << endl;
            results << p1.getName() << " books " << book1.toString() + "-" + book2.toString() << endl;

            // Player draws a card if no cards are left in hand
            // This is to allow opposing player to ask for card from player
            if((p1.getHandSize() == 0) && (d.size() > 0)) // only if deck still has cards
            {
                Card dealt = d.dealCard();
                cout << "Out of cards! " << p1.getName() << " draws " << dealt.toString() << endl;
                results << "Out of cards! " << p1.getName() << " draws " << dealt.toString() << endl;
                p1.addCard(dealt);
            }
        }

        playerTurn = !playerTurn; // opposing player's turn
    }
}

void displayAll(Player &p1, Player &p2, ofstream &results)
{
    cout << p1.getName() <<"'s hands : " << p1.showHand() << endl;
    cout << p2.getName() <<"'s hands : " << p2.showHand() << endl;
    cout << p1.getName() <<"'s books : " << p1.showBooks() << endl;
    cout << p2.getName() <<"'s books : " << p2.showBooks() << endl << endl;
    results << p1.getName() <<"'s hands : " << p1.showHand() << endl;
    results << p2.getName() <<"'s hands : " << p2.showHand() << endl;
    results << p1.getName() <<"'s books : " << p1.showBooks() << endl;
    results << p2.getName() <<"'s books : " << p2.showBooks() << endl << endl;
}
