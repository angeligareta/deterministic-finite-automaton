#include "state.h"

state::state(){
    identifier=-1;
    initial=0;
    final=0;
}

state::state(const state& state_in){
    identifier= state_in.identifier;
    initial= state_in.initial;
    final=state_in.final; 
    vector_transition = state_in.vector_transition;
}
   
state::~state(){
    destroy();
}

void state::destroy(){
    vector_transition.clear();
}

void state::set_transition(const symbol& symbol_in,int num_in){
    transition transition_temp(symbol_in,num_in);  
    vector_transition.insert(transition_temp);
}
   
void state::set_identifier(int identifier_in){
    identifier=identifier_in;
}
   
void state::set_initial(bool initial_in){
    initial=initial_in;
}
   
void state::set_final(bool final_in){
    final = final_in;
}

int state::get_number_transition() const{
    return vector_transition.size();
}
   
int state::get_identifier() const{
    return identifier;
}

int state::get_next_state(const symbol& symbol_in) const{
    
    int next_state=-1;
    
    for(set<transition>::iterator it=vector_transition.begin(); it!=vector_transition.end();++it){
        transition transition_temp = *it;
        if(transition_temp.symbol_entry==symbol_in)
            next_state=transition_temp.get_next_state();
    }    
    
    return next_state;
}
   
bool state::get_initial() const{
    return initial;
}
   
bool state::get_final() const{
    return final;
}

bool state::is_death_state() const{
    if(final!=true){
        for(set<transition>::iterator it=vector_transition.begin(); it!=vector_transition.end();++it){
            transition transition_temp = *it;
            if(transition_temp.get_next_state()!=identifier)
                return false;
        }
        return true;
    }
    else 
        return false;
}

ostream& operator<<(ostream &output, const state& state_){
    output << state_.get_identifier() << " ";
    output << state_.get_final() << " ";
    output << state_.get_number_transition();
    for(set<transition>::iterator it=state_.vector_transition.begin(); it!=state_.vector_transition.end();++it)
        output << *it;
    output << endl;
}

state& state::operator=(const state &state_in){
    this->identifier= state_in.identifier;
    this->initial= state_in.initial;
    this->final=state_in.final;
    this->vector_transition = state_in.vector_transition;
        
    return *this;
}

int state::operator==(const state &state_in) const{
    if(this->identifier != state_in.identifier) return 0;
    if(this->initial != state_in.initial) return 0;
    if(this->final != state_in.final) return 0;
    if(this->vector_transition.size() != state_in.vector_transition.size()) return 0;
    
    set<transition>::iterator iter1=vector_transition.begin();
    set<transition>::iterator iter2=state_in.vector_transition.begin();
    while(iter1!=vector_transition.end()){
        if(!(*iter1 ==*iter2))
            return 0;
        iter1++; iter2++;
    }
    return 1;
}

int state::operator<(const state &state_in) const{
    return (identifier < state_in.identifier);
}