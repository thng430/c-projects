//  This is a Card template written by rick gessner on 10/12/20.

#include "Card.hpp"
#include <iostream>

namespace GT {

  Card::Card(Faces aFace, Suits aSuit) {
    face=aFace;
    suit=aSuit;
  }

  Card::Card(const Card &aCopy) {
    *this=aCopy;
  }

  Card::~Card() {}
  
  Card& Card::operator=(const Card& aCopy) {
    face=aCopy.face;
    suit=aCopy.suit;
    return *this;
  }

  bool Card::operator==(const Card& aCopy) const {
    return (face==aCopy.face) && (suit==aCopy.suit);
  }

  bool Card::operator<(const Card &aCard) const {
    return (int)face<(int)aCard.face;
  }

  std::ostream& operator<<(std::ostream &anOutput, const Card &aCard) {
    static char theFaces[]={' ',' ','2','3','4','5','6','7',
                            '8','9','T','J','Q','K','A'};
    anOutput << theFaces[(int)aCard.face] << (char)aCard.suit;
    return anOutput;
  }

} // end of namespace
