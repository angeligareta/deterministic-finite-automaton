#include "dfa.h"

#include <cstdio>
#include <cstdlib> //Para system clear
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

int main(){
    
    dfa dfa_;
    
    int opcion;
    
    // Menú
    do{
        cout << "\n\n" << "╔" << string(40, '-') << " Selecciona una opción " << string(40, '-') << "╗" <<  "\n" << endl;
        
        cout << "\t⬤ Opción 0: Salir" << endl;
        cout << "\t⬤ Opción 1: Leer DFA (OBLIGATORIO)" << endl;
        cout << "\t⬤ Opción 2: Mostrar DFA"<< endl;
        cout << "\t⬤ Opción 3: Identificar estados de muerte" << endl;
        cout << "\t⬤ Opción 4: Analizar cadena" << endl;
        cout << "\t⬤ Opción 5: Minimizar DFA" << endl;
        cout << "\t⬤ Opción 6: Exportar DFA" << endl;
        
        cout << "\n" << "╚" << string(103, '-') << "╝" << endl;
        cin >> opcion;
        system("clear");
        
        switch(opcion){
                case 1:
                {
                
                cout << "Introduce el nombre del fichero .dfa" << endl;
                
                string fich_string;
                cin >> fich_string;
                
                //Compruebo si el archivo que ha introducido ya acaba en .dfa, si no se lo pongo
                string string_aux="";
                for(int i=(fich_string.length()-4);i<fich_string.length();i++)
                    string_aux+=fich_string[i];
                
                if(string_aux!=".dfa")
                    fich_string+=".dfa";
                
                cout << "\nBuscando el fichero " << fich_string << "... " << endl;
                
                char *fich = new char [fich_string.length()+1]; strcpy (fich, fich_string.c_str());
                
                ifstream dfa_file;
	            dfa_file.open(fich);
	            
	            if(dfa_file.is_open())
	                cout << "\nFICHERO ABIERTO" << endl;
	            else
	                cout << "\nERROR - Debe introducir un fichero.dfa correcto primero" << endl;
	            
	            dfa_file >> dfa_;
	            
	            if(dfa_.empty())
	                cout << "\nERROR- El fichero introducido tiene formato incorrecto" << endl;
	            
	            // Cerramos el fichero
	            dfa_file.close();
	            
                break;
                }
                case 2: 
                {
                    if(dfa_.empty()==false){
                        cout << dfa_.alphabet_;
                        cout << endl << "Este es el DFA introducido: \n" << endl;
                        cout << dfa_;
                    }
                    else
                        cout << "ERROR - Debe introducir un fichero.dfa correcto primero" << endl;
                    break;
                }
                case 3:
                {
                    if(dfa_.empty()==false) 
                        dfa_.show_death_state(); 
                    else
                        cout << "ERROR - Debe introducir un fichero.dfa correcto primero" << endl;
                    break;
                }
                case 4:
                {  
                    if(dfa_.empty()==false){
                        string string_in;
                        cin >> string_in;
                        // Si la cadena tiene simbolos que no pertenecen al alfabeto
                        if(dfa_.analyze_string(string_in))
                            cout << "ERROR - La cadena tiene simbolos que no pertenecen al alfabeto" << endl;    
                    }
                    else
                        cout << "ERROR - Debe introducir un fichero.dfa correcto primero" << endl;
                    break;    
                }
                case 5:
                {  
                    if(dfa_.empty()==false){
                        dfa_.minimize();
                    }
                    else
                        cout << "ERROR - Debe introducir un fichero.dfa correcto primero" << endl;
                    break;    
                }
                case 6:
                {  
                    if(dfa_.empty()==false){
                        
                        cout << "Introduce el nombre del archivo '.dfa' donde quieres que se guarde:" << endl;
                        string fich_string;
                        cin >> fich_string;
                        
                        //Compruebo si el archivo que ha introducido ya acaba en .dfa, si no se lo pongo
                        string string_aux="";
                        for(int i=(fich_string.length()-4);i<fich_string.length();i++)
                            string_aux+=fich_string[i];
                
                        if(string_aux!=".dfa")
                            fich_string+=".dfa";
                        
                        char *fich = new char [fich_string.length()+1]; strcpy (fich, fich_string.c_str());
                        
                        ofstream dfa_file;
	                    dfa_file.open(fich);
	                    
	                    if(dfa_file.is_open())
	                        cout << "\nFICHERO EXPORTADO" << endl;
	                    else
	                        cout << "\nERROR - Debe introducir un fichero.dfa correcto primero" << endl;
	                    dfa_file << dfa_;
	                    
	                    dfa_file.close();
                    }
                    else
                        cout << "ERROR - Debe introducir un fichero.dfa correcto primero" << endl;
                    break;    
                }
                default: opcion=0;
                
        }
        
    }while (opcion!=0); 
	
}