//
//  heap.cpp
//  Heap
//
//  Created by Allister Liu on 10/22/20.
//


#include "heap.hpp"

//constructor
heap::heap(int capacity){
    this->capacity=capacity;
    this->Heapsize=0;
    this->data.resize(capacity+1);
    this->mapping=new hashTable(capacity*2);
}

//parent child index
int heap::left(int index){return 2*index;}

int heap::right(int index){return 2*index+1;}

int heap::parent(int index){return index/2;}

void heap::swap(int a, int b){
    Node Temp=data[a];
    data[a]=this->data[b];
    data[b]=Temp;
    mapping->setPointer(data[a].id,&data[a]);
    mapping->setPointer(data[b].id,&data[b]);
}

int heap::insert(const std::string &id, int key, void *pv){
    if (Heapsize == capacity)
    {
        return 1;
    }
    if (mapping->contains(id) == false)
    {
        Heapsize++;
        data[Heapsize].id = id;
        data[Heapsize].key = key;
        data[Heapsize].pv = pv;
        mapping->insert(id, &data[Heapsize]);
        percolateUp(Heapsize);
    }
    else
    {
        return 2;
    }
    return 0;
}

int heap::getPos(Node * pn){
    return (pn - &data[0]);
}

int heap::deleteMin(std::string *pId , int *pKey , void *ppData ){
    if(Heapsize==0){
        return 1;
    }else{
        if (pId != NULL) *pId = data[1].id;
        if (pKey != NULL) *pKey = data[1].key;
        if (ppData != NULL) *(static_cast <void**> (ppData)) = data[1].pv;
        mapping->remove(data[1].id);//lazily deleted
        data[1] = data[this->Heapsize--];
        percolateDown(1);
        return 0;
    }
}

int heap::setKey(const std::string &id, int key){
    if(!mapping->contains(id)){
        return 1;
    }else{
        Node* pn =static_cast<Node *>(mapping->getPointer(id));
        int tempkey=pn->key;
        pn->key=key;
        int index= getPos(pn);
        if (key > tempkey){
            percolateDown(index);
        }else if(key < tempkey){
            percolateUp (index);
        }
        return 0;
    }
}

int heap::remove(const std::string &id, int *pKey , void *ppData ){
    if(!mapping->contains(id)) {
        return 1;
    }else {
        Node* pn= static_cast<Node *>(mapping->getPointer (id));
        if (pKey != nullptr) *pKey = pn->key;
        if (ppData != nullptr) *(static_cast <void**> (ppData)) = pn->pv;
        setKey(id, INT_MIN);
        deleteMin();
        return 0;
    }

}


void heap::percolateUp (int posCur){
    Node Temp=data[posCur];
    int Parent=parent(posCur);
    while(posCur>1 && (Temp.key)<(data[Parent].key)){
        data[posCur] = data[Parent];
        mapping->setPointer(data[posCur].id, &data[posCur]);
        posCur=Parent;
        Parent=parent(posCur);
    }
    data[posCur]=Temp;
    mapping->setPointer(data[posCur].id,&data[posCur]);
}

void heap::percolateDown (int posCur){
    mapping->setPointer(data[posCur].id,&data[posCur]);
    do{
        int j=0;
        int r=right(posCur);
        if( r<=(Heapsize) && data[posCur].key>data[r].key){
            int l=left(posCur);
            if(data[l].key<data[r].key){
                j=l;
            }else{
                j=r;
            }
        }else{
            int l=left(posCur);
            if( l<=(Heapsize) && data[posCur].key>data[l].key){
                j=l;
            }
        }
        if(j>=1) swap(j,posCur);
        posCur=j;
    }while(posCur>=1);

}


