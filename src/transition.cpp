#include "transition.h"

transition::transition(){
    number_next_state=0;
}

transition::transition(const symbol &symbol_in,int num_in){
    number_next_state=num_in;
    symbol_entry=symbol_in;
}

transition::transition(const transition &transition_in){
    number_next_state=transition_in.number_next_state;
    symbol_entry=transition_in.symbol_entry; 
}
   
transition::~transition(){}

int transition::get_next_state() const{
    return number_next_state;    
}

ostream &operator<<(ostream &output, const transition& transition_){
   output << " " << transition_.symbol_entry << " " << transition_.number_next_state;
   return output;
}

transition& transition::operator=(const transition &transition_in){
    this->symbol_entry= transition_in.symbol_entry;
    this->number_next_state= transition_in.number_next_state;
    return *this;
}

int transition::operator==(const transition &transition_in) const{
    if( this->number_next_state  != transition_in.number_next_state) return 0;
    if( !(this->symbol_entry       == transition_in.symbol_entry)) return 0;
    return 1;
}

int transition::operator<(const transition &transition_in) const{
    return (symbol_entry < transition_in.symbol_entry);
}