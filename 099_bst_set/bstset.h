#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T data;
    Node * left;
    Node * right;

    Node() : left(NULL), right(NULL) {}
    Node(T d) : data(d), left(NULL), right(NULL) {}
    Node(T d, Node * l, Node * r) : data(d), left(l), right(r) {}
  };

  Node * root;

  Node * add(Node * current, const T d) {
    if (current == NULL) {
      Node * ans = new Node(d);
      return ans;
    }
    else {
      if (d < current->data) {
        Node * newLeft = add(current->left, d);
        current->left = newLeft;
      }
      else if (d == current->data) {
        current->data = d;
      }
      else {
        Node * newRight = add(current->right, d);
        current->right = newRight;
      }
      return current;
    }
  }

  bool lookup(Node * current, const T & key) const {
    if (current == NULL) {
      return 0;
    }
    if (current->data == key) {
      return 1;
    }
    else {
      if (key > current->data) {
        return lookup(current->right, key);
      }
      else {
        return lookup(current->left, key);
      }
    }
  }

  Node * remove(const T & key, Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    if (key == curr->data) {
      Node * temp;
      if (curr->left == NULL) {
        temp = curr->right;
        delete curr;
      }
      else if (curr->right == NULL) {
        temp = curr->left;
        delete curr;
      }
      else {
        //find the largest item smaller than key;
        Node * swap = curr->left;
        while (swap->right != NULL) {
          swap = swap->right;
        }
        curr->data = swap->data;
        swap->data = key;
        curr->left = remove(key, curr->left);
        temp = curr;
      }
      return temp;
    }
    Node * ans;
    if (key < curr->data) {
      ans = remove(key, curr->left);
      curr->left = ans;
    }
    if (key > curr->data) {
      ans = remove(key, curr->right);
      curr->right = ans;
    }
    return curr;
  }
  void copy(const Node * current) {
    if (current != NULL) {
      //Node * ans;
      this->add(current->data);
      copy(current->left);
      copy(current->right);
    }
  }

  void destroy(Node * curr) {
    if (curr == NULL) {
      return;
    }
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
  }

 public:
  BstSet<T>() : root(NULL) {}
  BstSet<T>(const BstSet & rhs) : root(NULL) { copy(rhs.root); }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet<T> newset(rhs);
      destroy(root);
      root = newset.root;
      newset.root = NULL;
    }
    return *this;
  }
  virtual void add(const T & key) { root = add(root, key); }
  virtual bool contains(const T & key) const { return lookup(root, key); }
  virtual void remove(const T & key) { root = remove(key, root); }
  virtual ~BstSet<T>() { destroy(root); }
  void printPreorder(Node * curr) {
    if (curr != NULL) {
      std::cout << curr->data << " ";
      printPreorder(curr->left);
      printPreorder(curr->right);
    }
  }

  void print() { printPreorder(root); }
};
