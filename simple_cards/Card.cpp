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

  std::ostream& operator<<(std::ostream &anOutput, const Card &aCard) {
    anOutput << (int)aCard.face << (char)aCard.suit << "\n";
    return anOutput;
  }

}// end of namespace 
