// card.cpp
//
// Created by Kwonwoo Choi on 11/5/2018.
//

#include <sstream>
#include "card.h"

// Default constructor
// Ace of Spades
Card::Card()
{
    myRank = 1;
    mySuit = spades;
}

//Constructor with parameters
//The user of the class will pass in a rank and suit
//  o suit must be valid
//  o rank must be from 1 to 13
Card::Card(int rank, Suit s)
{
    myRank = rank;
    mySuit = s;
}

/* FUNCTION - string toString
    * returns string version of the card
        o e.g. Ac 4h Js

    input parms - none

    output parms - returns string version of the card
*/
string Card::toString() const
{
    return (rankString(myRank) + suitString(mySuit));
}

/* FUNCTION - bool sameSuitAs
    * check if this card has the same suit as Card c
        o true if suit same as c

    input parms - Card c

    output parms - returns true if suit same as c
                 - returns false if not
*/
bool Card::sameSuitAs(const Card& c) const
{
    return (mySuit == c.mySuit);
}

/* FUNCTION - int getRank
    * returns rank as an int
        o return rank, 1..13

    input parms - none

    output parms - returns rank as an int
*/
int Card::getRank() const
{
    return myRank;
}

/* FUNCTION - string suitString
    * returns suit as a string
        o return "s", "h",...

    input parms - suit of the card

    output parms - returns suit as a string
*/
string Card::suitString(Suit s) const
{
    if(s == spades)
        return "s";
    if(s == hearts)
        return "h";
    if(s == diamonds)
        return "d";
    return "c"; // If nothing else, the suit is a club
}

/* FUNCTION - string rankString
    * returns rank as a string
        o return "A", "2", ..."Q"

    input parms - integer rank of the card

    output parms - returns rank as a string
*/
string Card::rankString(int r) const
{
    if(r == 1)
        return "A";
    if(r == 11)
        return "J";
    if(r == 12)
        return "Q";
    if(r == 13)
        return "K";
    
    // return the rank as a string
    ostringstream ss;
    ss << r;
    return ss.str();
}

// overload == operator
// compare suit and rank
bool Card::operator == (const Card& rhs) const
{
    if((sameSuitAs(rhs)) && (myRank == rhs.myRank))
        return true;
    return false;
}

// overload != operator
// compare suit and rank
bool Card::operator != (const Card& rhs) const
{
    if((sameSuitAs(rhs)) && (myRank == rhs.myRank))
        return false;
    return true;
}



ostream& operator << (ostream& out, const Card& g)
{
      out << g.toString();
      return out;
}
