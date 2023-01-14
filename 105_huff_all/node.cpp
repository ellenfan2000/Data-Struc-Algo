#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    assert(left == NULL && right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
  }
  else {
    if (left != NULL) {
      BitString bl = b.plusZero();
      left->buildMap(bl, theMap);
    }
    if (right != NULL) {
      BitString br = b.plusOne();
      right->buildMap(br, theMap);
    }
  }
}
