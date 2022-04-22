/*
  Shivam Chauhan and Estevan Bedolla 
  */ 

#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;



hashNode::hashNode(string s){
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(){
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(string s, string v){
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v) {
	// adding a valu to the end of the value array associated 
	// with a key
  int count = 0;
  while(values[count] != "") { // finds last empty value
    count++;
  }
  values[count] = v;
  currSize++;
  cerr << currSize << "/" << valuesSize << endl;
  if(currSize == valuesSize) {
    dblArray();
  }
}
void hashNode::dblArray() {
	// when the value array gets full, you need to make a new 
	// array twice the size of the old one (just double, no 
	//going to next prime) and then copy over the old values 
	//to the new values, then de-allocate the old array.  
	//Again, just copying over, no hash functiosn involved 
	//here.
  valuesSize = valuesSize*2;
  string *values2 = new string[valuesSize];
  for(int i =0; i<(currSize); i++) {
    values2[i] = values[i]; // copies over
    cerr << i << endl;
  }
  cerr << "deleting original values array" << endl;
  delete[] values;
  cerr << "original values deleted" << endl;
  values = values2;
  cerr << "new values done" << endl;
}

string hashNode::getRandValue() {
	//Every key has a values array - an array of words that 
	// follow that key in the text document.  You're going to 
	//randomly select one of those words and return it.  That 
	//will be the word that follows your key in your output 
	//function, and it will also be the next key.
  int randomnum = rand()%currSize;
  return values[randomnum];
}
