#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    std::pair<K, V> data;
    Node * left;
    Node * right;

    Node() : left(NULL), right(NULL) {}
    //    Node(std::pair<K, V> d) : data(d), left(NULL), right(NULL) {}
    Node(K key, V value) : data(std::pair<K, V>(key, value)), left(NULL), right(NULL) {}
    // Node(std::pair<K, V> d, Node * n, Node * p) : data(d), left(n), right(p) {}
    Node(K key, V value, Node * l, Node * r) :
        data(std::pair<K, V>(key, value), left(l), right(r)) {}
  };

  Node * root;

  Node * add(Node * current, const K & key, const V & value) {
    if (current == NULL) {
      Node * ans = new Node(key, value);
      return ans;
    }
    else {
      if (key < current->data.first) {
        Node * newLeft = add(current->left, key, value);
        current->left = newLeft;
      }
      else if (key == current->data.first) {
        current->data.second = value;
      }
      else {
        Node * newRight = add(current->right, key, value);
        current->right = newRight;
      }
      return current;
    }
  }

  void copy(const Node * current) {
    if (current != NULL) {
      //Node * ans;
      this->add(current->data.first, current->data.second);
      copy(current->left);
      copy(current->right);
    }
  }

  const V & lookup(Node * current, const K & key) const throw(std::invalid_argument) {
    if (current == NULL) {
      throw std::invalid_argument("key does not exist");
    }
    if (current->data.first == key) {
      return current->data.second;
    }
    else {
      if (key > current->data.first) {
        return lookup(current->right, key);
      }
      else {
        return lookup(current->left, key);
      }
    }
  }
  Node * remove(const K & key, Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    if (key == curr->data.first) {
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
        curr->data.first = swap->data.first;
        curr->data.second = swap->data.second;
        temp = remove(key, curr);
      }

      return temp;
    }
    Node * ans;
    if (key < curr->data.first) {
      ans = remove(key, curr->left);
      curr->left = ans;
    }
    if (key > curr->data.first) {
      ans = remove(key, curr->right);
      curr->right = ans;
    }
    return curr;
  }

  void destroyHelper(Node * curr) {
    if (curr == NULL) {
      return;
    }
    destroyHelper(curr->left);
    destroyHelper(curr->right);
    delete curr;
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap<K, V> & rhs) : root(NULL) { copy(rhs.root); }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap<K, V> newmap(rhs);
      destroyHelper(root);
      root = newmap.root;
      newmap.root = NULL;
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) {
    //std::pair<K, V> newData(key, value);
    root = add(root, key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return lookup(root, key);
  }

  virtual void remove(const K & key) { root = remove(key, root); }

  virtual ~BstMap<K, V>() { destroyHelper(root); }
  void printPreorder(Node * curr) {
    if (curr != NULL) {
      std::cout << "(" << curr->data.first << ", " << curr->data.second << " )"
                << " ";
      printPreorder(curr->left);
      printPreorder(curr->right);
    }
  }

  void print() { printPreorder(root); }
};
