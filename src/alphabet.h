#pragma once

#include "symbol.h"
#include <set>
#include <cstdio>
#include <iostream>

using namespace std;

class alphabet{
   
   friend ostream &operator<<(ostream &,const alphabet &);
   
   public:
   
   set<symbol> alphabet_;
   
   alphabet();
   
   ~alphabet();
   
   void clear();
   
   int size();
   
   bool it_belongs(const symbol&);
   
   void insert(symbol);
   
   void print();
   
};