#include <iostream>
#include <fstream>
#include "Models/system.cpp"
#include "Models/resolver.cpp"

using namespace std; 

// program start handler

int main(int argc, char *argv[]) {

    Resolver *resolver = new Resolver( argc, argv ); 

    resolver->validateInputs(); 

    // input file handling 
    fstream input_file; 
  
    input_file.open( resolver->get_file() , fstream::in ); 

    // all controls are ok

    int mblocks, cblocks ,wxb, loads; 

    input_file >> mblocks >> cblocks >> wxb >> loads; 

    // memory buffer array
    string **memory; 
    memory = new string*[ mblocks ];
    for (int i = 0; i < mblocks; i++) {
        memory[i] = new string[wxb]; 
        for(int j = 0; j < wxb; j++)
            input_file >> memory[i][j]; 
    }    

    // get params

    string flow = resolver->get_flowmode(); 
    int sec = resolver->get_execsec();

    // init cache and main memory
    main_memory *m = new main_memory( memory, mblocks, wxb );
    Assoc_cache *c = new Assoc_cache( cblocks, wxb, flow, sec);  
    c->main_memory_attach( m );

    // execution
    for( int i = 0; i < loads; i++ ) {
        string address; 
        input_file >> address;
        c->load( address ); 
    }
    
    return 0; 
}