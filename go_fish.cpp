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




int main( )
{
    int numCards = 5;
    
    Player p1("Joe");
    Player p2("Jane");
    
    Deck d;  //create a deck of cards
    srand(time(NULL));
    d.shuffle();
    
    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);
       
    cout << p1.getName() <<" has : " << p1.showHand() << endl;
    cout << p2.getName() <<" has : " << p2.showHand() << endl;

    Card c(4, (Card::Suit)(1));
    Card e(4, (Card::Suit)(1));
    Card f(5, (Card::Suit)(3));

    if(c == e)
        cout << 1;
    if(c != f)
        cout << 2;
    
    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}
