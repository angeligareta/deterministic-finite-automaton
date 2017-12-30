#include "symbol.h"

symbol::symbol(){
    symbol_="";
    sum_ ="";
}

symbol::symbol(const string &symbol_in){
    symbol_+=symbol_in;
    ostringstream tmp;
    int suma=0;
	for(int i=0;i<symbol_.length();i++)
	    suma+=(int) symbol_in[i];
	tmp << suma;
	this->sum_= tmp.str();
}

symbol::symbol(const symbol &symbol_in){
    symbol_  =symbol_in.symbol_;
	sum_     =symbol_in.sum_;
}

symbol::symbol(const char &symbol_in){
    symbol_+=symbol_in;
    ostringstream tmp;
    int suma=(int) symbol_in;
	tmp << suma;
	this->sum_= tmp.str();
}
   
symbol::~symbol(){
    symbol_.clear();
}
   
bool symbol::is_empty(){
    return (symbol_=="&");
}

ostream& operator<<(ostream &output, const symbol& symbol_in){
    output << symbol_in.symbol_;
    return output;
}

symbol& symbol::operator=(const symbol &symbol_in){
    this->symbol_= symbol_in.symbol_;
    this->sum_= symbol_in.sum_;
    return *this;
}

int symbol::operator==(const symbol &symbol_in) const{
    if( this->symbol_ != symbol_in.symbol_) return 0;
    if( this->sum_   != symbol_in.sum_) return 0;
    return 1;
}

int symbol::operator<(const symbol &symbol_in) const{
    if( this->symbol_.length() == symbol_in.symbol_.length() && this->sum_ < symbol_in.sum_) return 1;
    if( this->symbol_.length() < symbol_in.symbol_.length()) return 1;
    return 0;
}

