#include "alphabet.h"

alphabet::alphabet(){
}

alphabet::~alphabet(){
    clear();
}

void alphabet::insert(symbol character){
    alphabet_.insert(character);
}

void alphabet::clear(){
    alphabet_.clear();
}

int alphabet::size(){
    return alphabet_.size();
}

bool alphabet::it_belongs(const symbol& symbol_in){
    
    for(set<symbol>::iterator it=alphabet_.begin();it!=alphabet_.end();++it){
        symbol symbol_temp=*it;
        if(symbol_temp==symbol_in)
            return true;
    }
    
    return false;
}

ostream &operator<<(ostream &output,const alphabet &alphabet_){
    output << endl << "Su alfabeto es: { ";
    set<symbol>::iterator it=alphabet_.alphabet_.begin();
    while(it!=alphabet_.alphabet_.end()){
        output << *it;
        it++;
        if(it!=alphabet_.alphabet_.end())
            output << " , ";
        else
            output << " }" << endl;
    }    
}

