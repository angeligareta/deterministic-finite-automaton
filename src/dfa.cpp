#include "dfa.h"

ostream& operator<<(ostream &output, const dfa &dfa_){
    
    output << dfa_.vector_state.size() << endl;
    
    output << dfa_.get_initial_state().get_identifier() << endl;
    
    for(set<state>::iterator it=dfa_.vector_state.begin(); it!=dfa_.vector_state.end();++it)
        output << *it;
    
    return output;
}

dfa::dfa(){}

dfa::~dfa(){
    destroy();
}

bool dfa::empty(){
    return vector_state.empty();
}

void dfa::destroy(){
    vector_state.clear();
}

istream& operator>>(istream& input,dfa& dfa_){
    
    dfa_.destroy();
    
    bool error=0;
    
    int state_number; input >> state_number;
    
    set<int> set_state_number; // Creo un set de int para introducir todos los estados posibles a los que podemos ir
    for(int i=0;i<state_number;i++)
        set_state_number.insert(i);
        
    int initial_state; input >> initial_state;
    
    int state_count=0,id,transition_number,max_transition_number; bool final;
    
    while(state_count < state_number){
        
        state state_temp;
        
        input >> id;
        
        if(set_state_number.count(id)==0) error=1; // Salgo si el estado en el que estoy no pertenece al set de posibles estados
        
        state_temp.set_identifier(id);
        
        if(id==initial_state) state_temp.set_initial(true);
        
        input >> final;
        
        if(set_state_number.count(final)==0) error=1; // Salgo si el estado final no pertenece al set de posibles estados
        
        if(final==true) state_temp.set_final(true);
        
        input >> transition_number;
        
        if(state_count==0) max_transition_number=transition_number;
        else if(transition_number!=max_transition_number) error=1; // Salgo si hay distinto numero de transiciones entre estados
        
        string symbol_string; int next_state;
        
        for(int i=0;i<transition_number;i++){
            input >> symbol_string; input >> next_state;
            
            if(set_state_number.count(next_state)==0) error=1; // Salgo si el estado siguiente no pertenece al set de posibles estados
            
            symbol symbol_(symbol_string);
            if(state_count==0)
                dfa_.alphabet_.insert(symbol_);
            else if(!dfa_.alphabet_.it_belongs(symbol_)) // Salgo si el simbolo no pertenece al alfabeto
                error=1;
            state_temp.set_transition(symbol_,next_state);
        }
        
        dfa_.vector_state.insert(state_temp);
        
        state_count++;
    }
    
    if(!input.eof()) error=1;   // Salgo si todavia queda cadena de entrada
    
    if(error==1)
        dfa_.destroy();
    
    return input;
    
}
   
void dfa::show_death_state(){
    
    cout << "\nLos estados de muerte son: " << endl;
    
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it)
        if((*it).is_death_state()==true)
            cout << "Estado numero " << (*it).get_identifier() << endl;
}

state dfa::get_state_with_id(const int state_id){
    
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it)
        if((*it).get_identifier()==state_id)
            return (*it);
}

state dfa::get_initial_state() const{
    
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it)
        if((*it).get_initial()==true)
            return (*it);
            
}

division dfa::get_final_state() const{
    division division_;
    
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it)
        if((*it).get_final())
            division_.insert(*it);
            
    return division_;
}

bool dfa::analyze_string(const string& string_in){
    
    cout << "\nCadena de entrada: " << string_in << endl << endl;
    
    cout << "Estado actual\t\t" << "Entrada\t\t" << "Siguiente estado" << endl;
    
    // Me coloco en el estado actual
    
    int number_actual_state=get_initial_state().get_identifier();
    
    //Empiezo a pasar de estado a estado dependiendo de la entrada
    for(int i=0;i<string_in.length();i++){
        cout << number_actual_state << "\t\t\t";
        
        symbol symbol_entry(string_in[i]);
        if(!alphabet_.it_belongs(symbol_entry)) //Si ha introducido una un simbolo que no pertenezca al alfabeto salgo
            return 1;
        cout << symbol_entry << "\t\t\t";
        
        //Saltamos al siguiente estado
        number_actual_state=get_state_with_id(number_actual_state).get_next_state(symbol_entry);
        
        cout << number_actual_state << endl;
    }
    
    is_string_accepted(number_actual_state);

    return 0;
}

void dfa::is_string_accepted(const int number_actual_state) const{
    
    //Veo en que estado me he quedado
    bool accepted=false;
    
    //Miro si para el estado que estoy la cadena esta aceptada
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it)
        if((*it).get_identifier()==number_actual_state) //Veo en que estado me he quedado
            if((*it).get_final()) //Si me he quedado en un estado de aceptación devuelvo true
                accepted=true;
    
    if(accepted==true)
        cout << endl << "¡LA CADENA ESTA ACEPTADA!" << endl;
    else
        cout << endl << "LA CADENA NO ESTA ACEPTADA" << endl;
        
}

void dfa::print_set_state(const division& vector_state_in){
    
    set<state>::iterator it=vector_state_in.begin();
    
    cout << " { ";
    while(it!=vector_state_in.end()){
        cout << (*it).get_identifier();
        ++it;
        if(it!=vector_state_in.end())
            cout << " , ";
        else
            cout << " } ";
    }
}

void dfa::print_set_division(const vector<division> &vector_division){
    
    //Imprimimos el vector_division actual
    cout << "{ ";
    for(int i=0; i<vector_division.size();i++){
        print_set_state(vector_division[i]);
        cout << " ";
    }
    cout << "}\n" << endl;
}

vector<division> dfa::merge_vector_division(const vector<division> &vector_division_1,const vector<division> &vector_division_2){
    
    vector<division> vector_division;
    
    set_union(vector_division_1.begin(), vector_division_1.end(), vector_division_2.begin(), vector_division_2.end(), inserter(vector_division, vector_division.begin()));
    
    return vector_division;
}

bool dfa::it_belongs_division(const division &actual_division,const int &actual_state){
    
    for(division::iterator it=actual_division.begin();it!=actual_division.end();++it)
        if(actual_state==(*it).get_identifier())
            return 1;
    return 0;
    
}

void dfa::change_value_set_state(const int old_value,const int new_value){
    
    state new_state=get_state_with_id(old_value);
    new_state.set_identifier(new_value);
    
    vector_state.erase(get_state_with_id(old_value));
    vector_state.insert(new_state);
    
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
        state state_aux=*it;
        for(set<transition>::iterator it2=state_aux.vector_transition.begin();it2!=state_aux.vector_transition.end();++it2){
            transition transition_aux=*it2;
                if(transition_aux.number_next_state==old_value)
                    transition_aux.number_next_state=new_value;
            state_aux.vector_transition.erase(*it2);
            state_aux.vector_transition.insert(transition_aux);
        }
        vector_state.erase(*it);
        vector_state.insert(state_aux);
    }        
}

void dfa::update(const vector<division> &vector_division){
    
    //Eliminamos los repetidos y las transiciones que los tengan las cambiamos a correctas
    for(int i=0;i<vector_division.size();i++){
        division::iterator it=vector_division[i].begin(); int correct_state=(*it).get_identifier(); it++;
        while(it!=vector_division[i].end()){
            int wrong_value=(*it).get_identifier();
            change_value_set_state(wrong_value,correct_state);
            it++;        
        }
    }
    
    int identifier=0;
    
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
        if(identifier!=(*it).get_identifier())
            change_value_set_state((*it).get_identifier(),identifier);    
        identifier++;
    }
    
}

void dfa::minimize(){
    
    vector<division> vector_division;
    
    //Introducimos los estados finales
    vector_division.push_back(get_final_state());
    
    //Introducimos el resto de estados
    division division_aux;
    set_difference(vector_state.begin(), vector_state.end(), vector_division[0].begin(), vector_division[0].end(), inserter(division_aux, division_aux.begin()));
    vector_division.push_back(division_aux);
    
    //Cambiamos de orden los dos
    swap(vector_division[0],vector_division[1]);
    
    cout << "Grupo Inicial\n" << endl; print_set_division(vector_division);
    
    vector<division> vector_division_old;
    
    do{
        vector_division_old = vector_division;
        vector_division = create_new_partition(vector_division_old);
    }while(vector_division!=vector_division_old);
    
    cout << "FIN\n" << endl;    update(vector_division);
}

vector<division> dfa::create_new_partition(const vector<division> &vector_division_old){
    
    vector<division> vector_division=vector_division_old;
    
    for(set<symbol>::iterator it=alphabet_.alphabet_.begin();it!=alphabet_.alphabet_.end();++it){
        vector<division> vector_division_aux;
        cout << "Para " << *it << ":\n"<< endl;
        
        for(int i=0; i<vector_division.size();i++){
            if(vector_division[i].size()>1)
                vector_division_aux=merge_vector_division(vector_division_aux,part(vector_division[i],*it,vector_division_old));
            else
                vector_division_aux.push_back(vector_division[i]);
        }
            
        
        vector_division=vector_division_aux;   
        print_set_division(vector_division);
    }
    
    return vector_division;
}

vector<division> dfa::part(const division& actual_division, const symbol& actual_symbol,const vector<division> &vector_division_old){
    
    vector<division> vector_division;
    
    for(int i=0;i<vector_division_old.size();i++){
        division temp_division;
        for(division::iterator it=actual_division.begin();it!=actual_division.end();++it){
            int actual_state= (*it).get_next_state(actual_symbol);
            if(it_belongs_division(vector_division_old[i],actual_state)) // La funcion me dice si el estado siguiente esta en la division
                temp_division.insert(*it);        
        }
        if(!temp_division.empty()) // Si no ponemos esto bucle infinito
            vector_division.push_back(temp_division); 
    }
    
    return vector_division;
    
}