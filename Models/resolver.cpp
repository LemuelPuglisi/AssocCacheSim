#include <iostream> 
#include <fstream>
#include <stdlib.h>
using namespace std; 

// flow modes
#define BRKPOINT "brkpoint"
#define TIMESTEPS "timesteps"
#define QUICKRES "quickres"

class Resolver {

    int n; // number of args 
    char **v; // args array
    string* params; // args -> strings

    // configs 
    int sec; 

    // init. attr. 
    string output_file; 
    string flow_mode; 
    string flow_sec; 

    // init. argv string array 
    void convertArgv() {
        for(int i = 1; i < n; i++)
        params[i - 1] = (string)v[i]; 
        this->n --; 
    }

    // test on output file given 
    bool test_output_file() {
        fstream outfile;
        outfile.open( this->output_file, fstream::in );
        if( !outfile ) return false;
        outfile.close();  
        return true; 
    }

    // test on params 
    bool test_flow_mode() {
        if( this->flow_mode == "-b" ) flow_mode = BRKPOINT;
        else if( this->flow_mode == "-t" ) flow_mode = TIMESTEPS; 
        else if( this->flow_mode == "-q" ) flow_mode = QUICKRES; 
        else return false; 
        return true; 
    }

    // test on sec. 
    bool test_flow_sec() {
        int sec = atoi( this->flow_sec.c_str() );
        if( sec >= 200 && sec <= 1000 ) {
            this->sec = sec;   
            return true;  
        }  
        return false; 
    }

    public: 

        // constructor
        Resolver ( int n, char** v )
        {
            this->n = n; 
            this->v = v; 
            this->sec = 400; 
            this->flow_mode = QUICKRES; 
            this->params = new string[ n-1 ]; 

        }

        bool validateInputs() {

            if(n < 1 ) {
                cerr << "Fatal Error: no input files (-h helps), instance terminated." << endl; 
                return false; 
            }

            if(n > 4) 
            {
                cerr << "Fatal Error: too many params (-h helps), instance terminated." << endl; 
                return 0; 
            }
            
            this->convertArgv(); 

            this->output_file = params[0]; 
            this->flow_mode = params[1]; 
            if( n > 2 ) this->flow_sec = params[2]; 

            if( ! test_output_file() ) {
                cerr << "Fatal Error: invalid input file, instance terminated." << endl; 
                return 0;
            }

            if( ! test_flow_mode() ) {
                cerr << "Fatal Error: unknown param " << this->flow_mode << ", instance terminated." << endl; 
                return 0;
            }

            if( n > 2 && this->flow_mode != TIMESTEPS) {
                cerr << "Timing between steps allowed only with timesteps flow mode, instance terminated." << endl; 
                return 0; 
            }

            if( n > 2 && !test_flow_sec() ) {
                cerr << "Fatal Error: seconds range must stay between 200 and 1000, instance terminated." << endl; 
                return 0;
            }

            // validation passed 
            return true; 

        }

            string get_file() { return this->output_file; }

            string get_flowmode() { return this->flow_mode; }

            int get_execsec() { return this->sec; }

}; 