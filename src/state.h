#pragma once
#include "transition.h"

#include <set>
#include <cstdio>
#include <iostream>

using namespace std;

class state{
   
//========================================================================================
// Métodos amigos.
//========================================================================================   
   
   friend ostream& operator<<(ostream &, const state&);
   
   private:
   
   int identifier;
   bool initial;
   bool final;
   
   public:
   
//========================================================================================
// Métodos públicos.
//========================================================================================   
   
   set<transition> vector_transition;
   
   state();
   
   state(const state&);
   
   ~state();
   
   void destroy();
   
   void set_identifier(int);
   
   void set_initial(bool);
   
   void set_final(bool);
   
   void set_transition(const symbol&,int);
   
   int get_number_transition() const;
   
   int get_identifier() const;
   
   bool get_initial() const;
   
   bool get_final() const;
   
   bool is_death_state() const;
   
   int get_next_state(const symbol&) const;
   
   state& operator=(const state &state_in);

   int operator==(const state &state_in) const;

   int operator<(const state &state_in) const;
   
};