//
//  hash.hpp
//  SpellCheck
//
//  Created by Allister Liu on 10/22/20.
//
#ifndef HEAP_HPP_
#define HEAP_HPP_
#include "hash.hpp"

class heap{
public:
      heap(int capacity);
      int insert(const std::string &id, int key, void *pv = NULL);
      int setKey(const std::string &id, int key);
      int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);
      int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);
private:
        int capacity;
        int Heapsize;
        typedef struct {
            std::string id;
            int key;
            void * pv;
        } Node;
        std::vector<Node> data;
        hashTable * mapping;
        void swap(int a,int b);
        int getPos (Node * pn);
        void percolateUp (int posCur);
        void percolateDown (int posCur);
        int left(int index);
        int right(int index);
        int parent(int index);
};

#endif /* HEAP_HPP_ */



