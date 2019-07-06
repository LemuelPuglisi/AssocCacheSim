#include <iostream>
#include <fstream>
#include "Models/system.cpp"

using namespace std; 

// program start handler

int main(int argc, char *argv[]) {

    // throw no input error
    if(argc < 2 ) 
    {
        cerr << "Fatal Error: no input files (-h helps), instance terminated." << endl; 
        return 0; 
    }

    // throw too many params error
    if(argc > 3) 
    {
        cerr << "Fatal Error: too many params (-h helps), instance terminated." << endl; 
        return 0; 
    }

    // print help list
    if( ( string)argv[1] == "-h" )
    {
        return 0; 
    }

    // input file handling 
    fstream input_file; 
    string file_path = (string)argv[1]; 
    input_file.open( file_path, fstream::in ); 

    // throw invalid file error
    if( !input_file ) 
    {
        cerr << "Fatal Error: invalid input file, instance terminated." << endl; 
        return 0;
    }

    // default mode
    string mode = QUICKRES; 

    // mode checking
    if( argc > 2 ) 
    {
        string s = (string)argv[2]; 

        if( s == "-b" ) mode = BRKPOINT;

        else if( s == "-t" ) mode = TIMESTEPS; 
    
        else if( s == "-q" ) mode = QUICKRES; 

        else
        {
            cerr << "Fatal Error: unknown param " << s << ", instance terminated." << endl; 
            return 0;
        }
        
    }

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

    // init objects
    main_memory *m = new main_memory( memory, mblocks, wxb );
    Assoc_cache *c = new Assoc_cache( cblocks, wxb, mode );  
    c->main_memory_attach( m );

    for( int i = 0; i < loads; i++ ) {
        string address; 
        input_file >> address;
        c->load( address ); 
    }

}