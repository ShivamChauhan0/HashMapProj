/*
  Shivam Chauhan and Estevan Bedolla 
  */ 

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
  map = new hashNode *[11]; // is 11 right? 
  for(int i = 0; i< 11; i++) {
    map[i] = NULL;
  }
  first = "";
  numKeys = 0;
  mapSize = 11;
  hashfn = hash1;
  collfn = coll1;
  collisions = 0;
  hashcoll = 0;
}
void hashMap::addKeyValue(string k, string v) {
  int index = getIndex(k);
  if(map[index]==NULL) {
    map[index] = new hashNode(k,v);
    numKeys++;
  }
  else if(map[index] !=NULL && map[index]->keyword.compare(k) == 0) {
    map[index]->addValue(v);
  }
  if(first == "") {
    first = k;
  }
  double load = (double)numKeys / (double)mapSize;
  if(load > 0.7) { // greater load means rehash
    reHash();
  }
}
int hashMap::getIndex(string k) {
  if(hashfn) {
    int index = calcHash1(k);
    if(map[index] != NULL && map[index]->keyword.compare(k)!= 0 && collfn) {
      collisions++;
      int numofloops = 0;
      while(map[index] != NULL && map[index]->keyword.compare(k)!= 0){
        index = coll1(index, numofloops, k);
        numofloops++;
      }
      hashcoll = hashcoll+(numofloops-1);
    }
    else if(map[index] != NULL && map[index]->keyword.compare(k)!= 0 && !collfn) {
       collisions++;
      int numofloops = 0;
      while(map[index] != NULL && map[index]->keyword.compare(k)!= 0){
        index = coll2(index, numofloops, k);
        numofloops++;
      }
      hashcoll = hashcoll+(numofloops-1);
    }
    return index;
  }
  else{
    int index = calcHash2(k);
    if(map[index] != NULL && map[index]->keyword.compare(k)!= 0 && collfn) {
      collisions++;
      int numofloops = 0;
      while(map[index] != NULL && map[index]->keyword.compare(k)!= 0){
        index = coll1(index, numofloops, k);
        numofloops++;
      }
      hashcoll = hashcoll+(numofloops-1);
    }
    else if(map[index] != NULL && map[index]->keyword.compare(k)!= 0 && !collfn) {
       collisions++;
      int numofloops = 0;
      while(map[index] != NULL && map[index]->keyword.compare(k)!= 0){
        index = coll2(index, numofloops, k);
        numofloops++;
      }
      hashcoll = hashcoll+(numofloops-1);
    }
    return index;
  }
  }
int hashMap::calcHash2(string k){
  int len = k.size();
  int sum = 0;
  int temp;
  if(len < 3) {
    temp = len;
  }
  else {
    temp = 3;
  }
  for(int i =0; i<temp; i++) {
    sum = sum+pow(27, i)*(int)k[i];
  }
  int hash = sum%mapSize;
  return hash;
}
int hashMap::calcHash1(string k){
  int len = k.size();
  int sum = 0;
  int temp;
  if(len < 3) {
    temp = len;
  }
  else {
    temp = 3;
  }
  for(int i =0; i<temp; i++) {
    sum = sum+pow((int)k[i], i+1);
    }
  int hash = sum%mapSize;
  return hash;
}
void hashMap::getClosestPrime() {
  int test = mapSize;
  bool nofact = true;
  while(nofact) {
    test++;
    bool insidefactors = false;
    for(int i = 2; i<test; i++) {
      if(test%i == 0) {
        insidefactors = true;
      }
    }
    if(insidefactors == false){
      nofact = false;
    }
  }
  mapSize = test;
}
void hashMap::reHash() {
  int temp = mapSize;
  hashNode *old[temp];
  for(int i=0; i<temp; i++) {
    old[i] = map[i];
  }
  mapSize = mapSize*2;
  getClosestPrime();

  map  = new hashNode*[mapSize];
  for(int i =0; i<mapSize; i++) {
    map[i] = NULL;
  }
  first = "";
  numKeys = 0;

  for(int i=0; i<temp; i++) {
    if(old[i] != NULL) {
      string k = old[i]->keyword;
      int test = 0;
      while(old[i]->values[test] != ""){
        addKeyValue(k, old[i]->values[test]);
        test++;
      }
    }
  }
}
int hashMap::coll1(int h, int i, string k) {
  if(h+1 == mapSize) {
    return 0;
    }
  else{
    return h+1;
  }
}
int hashMap::coll2(int h, int i, string k) {
  int changednum = (i+1)^2;
  if(h+changednum >= mapSize) {
    return (h+changednum)%mapSize;
  }
  else{
    return h+changednum;
  }
}

void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


