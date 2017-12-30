#pragma once
#include "symbol.h"
#include <sstream>

using namespace std;


class transition{
   
//========================================================================================
// Métodos amigos.
//========================================================================================   
   
   friend ostream &operator<<(ostream &, const transition &);

//========================================================================================
// Métodos públicos.
//========================================================================================   
   
   public:
   
   int number_next_state; //Numero del siguiente estado
   symbol symbol_entry; // Simbolo del estado
   
   transition();
   
   transition(const symbol&,int);
   
   transition(const transition&);
   
   ~transition();
   
   int get_next_state() const;
   
   transition& operator=(const transition&);

   int operator==(const transition&) const;

   int operator<(const transition&) const;
};