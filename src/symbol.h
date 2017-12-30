#pragma once

#include <cstdio>
#include <iostream>
#include <sstream> 

using namespace std;

class symbol{
   
   private:
   
   string sum_;
   
   friend ostream& operator<<(ostream &output, const symbol&);   
   
   public:
   
   string symbol_;
   
   symbol();
   
   symbol(const char&);
   
   symbol(const string&);
   
   symbol(const symbol&);
   
   ~symbol();
   
   bool is_empty();

   symbol& operator=(const symbol&);

   int operator==(const symbol&) const;

   int operator<(const symbol&) const;
   
};