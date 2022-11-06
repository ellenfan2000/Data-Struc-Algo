#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il;
    il.addFront(10);
    il.addFront(20);
    assert(il.head->data == 20);
    assert(il.tail->data == 10);
    assert(il.head->next->data == 10);
    assert(il.head->prev == NULL);
    assert(il.head->next->prev->data == 20);
    // WRITE ME
  }

  void testAddBack() {
    IntList il;
    il.addBack(20);
    il.addBack(10);
    assert(il.head->data == 20);
    assert(il.tail->data == 10);
    assert(il.head->next->data == 10);
    assert(il.head->prev == NULL);
    assert(il.head->next->prev->data == 20);
  }
  // many more tester methods

  void testRuleodThree() {
    IntList il;
    il.addBack(30);
    il.addFront(20);
    il.addBack(40);
    IntList il2(il);
    assert(il2.head->data == 20 && il2.getSize() == 3 && il2.tail->data == 40);
    il2.addBack(50);
    il = il2;  // 20 30 40 50
    assert(il.getSize() == 4);

    il2.addFront(10);
    il2.addFront(1);  //1 10 20 30 40 50
    assert(il2.head->data == 1);
    assert(il.head->data == 20);
  }

  void testRemove() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(10);
    il.addBack(20);

    il.remove(30);
    assert(il.remove(1));
    //2 10 20
    assert(!il.remove(11));

    assert(il.getSize() == 3);
    assert(il.head->data == 2);
    assert(il.head->next->data == 10);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 20);

    il.remove(20);
    // 2 10
    assert(il.tail->data == 10);
    assert(il.tail->next == NULL);

    il.addBack(30);
    il.addBack(40);
    //2 10 30 40

    il.remove(10);
    //2 30 40
    il.remove(1);

    assert(il.head->next->data == 30);
    assert(il.head->next->prev->data == 2);

    IntList il2;
    il2.addBack(1);
    il2.remove(1);
    assert(il2.head == NULL);
    assert(il2.tail == NULL);
    assert(il2.getSize() == 0);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRuleodThree();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
