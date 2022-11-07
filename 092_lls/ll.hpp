#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
class Tester;
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node() : data(0), next(NULL), prev(NULL) {}
    Node(T d) : data(d), next(NULL), prev(NULL) {}
    //Node(Node & rhs) : data(rhs.data), next(NULL), prev(NULL) {}
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };
  Node * head;
  Node * tail;
  int size;

  Node * remove(const T & d, Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    if (d == curr->data) {
      Node * temp = curr->next;
      if (temp != NULL) {
        temp->prev = NULL;
      }
      else {
        tail = curr->prev;
      }
      delete curr;
      return temp;
    }
    Node * ans = remove(d, curr->next);
    curr->next = ans;
    if (ans != NULL) {
      ans->prev = curr;
    }
    return curr;
  }

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      this->addBack(curr->data);
      curr = curr->next;
    }
    // this->addBack(curr->data);
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      // LinkedList * ll = new LinkedList();
      // Node * curr = rhs.head;
      // while (curr != NULL) {
      //   ll->addBack(curr->data);
      //   curr = curr->next;
      // }
      // this->~LinkedList();

      // head = ll->head;
      // tail = ll->tail;
      // size = ll->size;
      // this = ll;
      Node * newhead = new Node(rhs.head->data);
      Node * newtail = newhead;
      Node * curr = rhs.head;
      while (curr->next != NULL) {
        curr = curr->next;
        newtail->next = new Node(curr->data, NULL, newtail);
        newtail = newtail->next;
      }
      this->~LinkedList();
      head = newhead;
      tail = newtail;
      size = rhs.size;
    }
    return *this;
  }
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    if (this->find(item) == -1) {
      return false;
    }
    head = remove(item, head);
    size--;
    return true;
  }

  T & operator[](int index) const {
    if (index >= size) {
      exit(EXIT_FAILURE);
    }
    Node * curr = head;
    int i = 0;
    while (i < index) {
      curr = curr->next;
      i++;
    }
    return curr->data;
  }

  int find(const T & item) const {
    Node * curr = head;
    int index = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      else {
        curr = curr->next;
      }
      index++;
    }
    return -1;
  }

  int getSize() const { return size; }
  friend class Tester;
};

//YOUR CODE GOES HERE

#endif
