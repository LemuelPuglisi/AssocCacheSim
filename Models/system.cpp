#include <iostream> 
#include <fstream> 
#include <stdlib.h>
#include <thread>
#include <chrono>

// flow modes
#define BRKPOINT "brkpoint"
#define TIMESTEPS "timesteps"
#define QUICKRES "quickres"

// output directive
#define RES "reset lru counter" // reset
#define SEL "block selected" // select
#define INC "increment lru counter" // incr. 
#define REP "Get from main memory" // replace

// output color configs 
#define MMEMCLR "\033[7;31m"
#define LRURCLR "\033[7;32m"
#define SLCTCLR "\033[7;33m"
#define INCRCLR "\033[7;35m"
#define RSETCLR "\033[0m"

// configs
#define TIME_BTW_STEPS 600
#define EMPTY "empty"

using namespace std; 

// string color settings 
const string hclr = "\033[1;32m"; 
const string mclr = "\033[1;31m"; 
const string rclr = "\033[0m"; 

class main_memory {

    private: 

        string **words; // words of main memory
        int blocks; // number of blocks in main memory
        int word_cap; // block capacity [in words]

    public: 

        // constructor
        main_memory( string **mem, int blk, int wrd  ) {
            
            this->blocks = blk; 
            this->word_cap = wrd; 

            words = new string*[ blocks ]; 
            for(int i = 0; i < blocks; i++) {
                words[i] = new string[ word_cap ];
                for(int j = 0; j < word_cap; j++)
                    words[i][j] = mem[i][j]; 
            }

        }

        // get the full block
        string* get_block( string addr ) {

            for(int i = 0; i < blocks; i++) {
                for(int j = 0; j < word_cap; j++) {
                    if( addr == words[i][j] )
                        return words[i]; 
                }
            }
            return NULL;

        }

        // print all words
        void print_memory() {
            for(int i = 0; i < blocks; i++) {
                for(int j = 0; j < word_cap; j++) {
                    cout << words[i][j] << " "; 
                }
                cout << endl; 
            }
            cout << endl; 
        }

}; 

class Assoc_cache {

    private: 

        // program flow attributes
        string flow_mode; 
        string current_state; 

        // cache attributes 
        string **words; // words of memory 
        int blocks; // number of blocks in cache
        int word_cap; // block capacity [in words]
        int cache_size; // total size  
        int indx; // last word filled
        int *lru; // lru counter : block 
        int tbs; // time between seconds 

        // main memory attachment
        main_memory *mm = NULL; 

        // statistics 
        double miss, hits;  

        /* PRIVATE SERVICES */ 

        void print_procedure() {

            system(" clear "); 
            cout << "< CACHE SIMULATOR />" << (hitRate() >= 30 ? hclr : mclr)  <<"  [Hit rate: " << hitRate() << "% ]"<< rclr << endl << endl; 
            cout << "current status: " << this->current_state << endl << endl; 


            for(int i = 0; i < blocks; i++) {
                cout << "BLOCK " << i << " : [ "; 
                for(int j = 0; j < word_cap; j++)
                    cout << words[i][j] << " "; 
                cout << "] LRU : " << lru[i] << endl; 
            }
        }

        void print_procedure( int blk, int wrd, string dir, string clr ) {

            system(" clear "); 
            cout << "< CACHE SIMULATOR />" << (hitRate() >= 30 ? hclr : mclr)  <<"  [Hit rate: " << hitRate() << "% ]"<< rclr << endl << endl; 
            cout << "current status: " << this->current_state << endl << endl; 

            for(int i = 0; i < blocks; i++) {
                if(i != blk) {
                    cout << "BLOCK " << i << " : [ "; 
                    for(int j = 0; j < word_cap; j++)
                        cout << words[i][j] << " "; 
                    cout << "] LRU : " << lru[i] << endl; 
                }
                else {
                    cout << clr << "BLOCK " << i << " : [ "; 
                    for(int j = 0; j < word_cap; j++) {
                        if( j != wrd ) cout << words[i][j] << " "; 
                        else cout << "<" << words[i][j] << ">" << " ";
                    }
                    cout << "] LRU : " << lru[i] << RSETCLR <<" <<< {" << dir << "}" << endl; 
                }
            }

            if(this->flow_mode == BRKPOINT) getchar(); 
            else if (this->flow_mode == TIMESTEPS) 
            this_thread::sleep_for(std::chrono::milliseconds( this->tbs ));   
            return; 
        }

        // cache hit service 
        void cache_hit(int blk, int wrd) {
            
            // select block
            if(this->flow_mode != QUICKRES)
            print_procedure(blk, wrd, SEL, SLCTCLR); 

            // reset lru 
            lru[ blk ] = 0; 
            if(this->flow_mode != QUICKRES)
            print_procedure(blk, wrd, RES, LRURCLR); 

            // increment init. blocks lru
            for(int j = blk + 1; j <  ( indx / word_cap ) ; j++) {
                print_procedure(j, -1, SEL, SLCTCLR);
                lru[j] ++;  
                print_procedure(j, -1, INC, INCRCLR);
            }

        }

        // load from memory, fill empty space
        void load_from_memory ( string adr ) {

            int blk = indx / word_cap; 
            int wrd = indx % word_cap;  
            this->indx += word_cap; 

            // select block
            if(this->flow_mode != QUICKRES)
            print_procedure( blk, -1 , SEL, SLCTCLR);             

            // get block from main memory
            string *newblock = mm->get_block( adr ); 
            for(int i = 0; i < word_cap; i++) words[ blk ][ i ] = newblock[i];
            if(this->flow_mode != QUICKRES)
            print_procedure( blk, -1 , REP, MMEMCLR);

            // next blocks aren't used
            for(int i = 0; i < blk; i++) {

                // select block
                if(this->flow_mode != QUICKRES)
                print_procedure( i, -1 , SEL, SLCTCLR);   

                // increment lru
                lru[i] ++; 
                print_procedure( i, -1, INC, INCRCLR ); 

            }                      

        }

        // load from memory, replace with LRU
        void lru_replace_protocol ( string adr ) {

            // get the oldest block
            int max = 0; 
            for(int i = 0; i < blocks; i++) 
            if( lru[max] < lru[i] ) max = i;

            // select block
            if(this->flow_mode != QUICKRES)
            print_procedure( max, -1 , SEL, SLCTCLR);

            // get block from main memory
            string *newblock = mm->get_block( adr ); 
            for(int i = 0; i < word_cap; i++) words[ max ][ i ] = newblock[i]; 
            if(this->flow_mode != QUICKRES)
            print_procedure( max, -1 , REP, MMEMCLR);

            lru[max] = 0; 
            if(this->flow_mode != QUICKRES)
            print_procedure( max, -1 , RES, LRURCLR);

            // increment the rest
            for(int i = 0; i < blocks; i++) {
                if(i != max) {

                    // select block
                    if(this->flow_mode != QUICKRES)
                    print_procedure( i, -1 , SEL, SLCTCLR);   

                    // increment lru
                    lru[i] ++; 
                    print_procedure( i, -1, INC, INCRCLR ); 

                }
            }

        }

    public:

        // constructor ( n. of blocks, word x block, flow mode, seconds)
        Assoc_cache( int blocks, int wxb, string flow_mode = QUICKRES, int seconds = TIME_BTW_STEPS ) {
            
            this->flow_mode = flow_mode;   

            this->blocks = blocks; 
            this->word_cap = wxb; 
            this->cache_size = blocks * word_cap; 
            this->tbs = seconds; 

            this->miss = 0; 
            this->hits = 0;
            this->indx = 0;
            
            words = new string*[ blocks ]; 
            for(int i = 0; i < blocks; i++) words[i] = new string[word_cap]; 
            lru = new int[ blocks ]; 
        
            this->reset(); 
        }

        // memory attachment
        void main_memory_attach( main_memory* RAM ) { this->mm = RAM; }

        // reset cache memory and lru alg. 
        void reset() {
            for(int i = 0; i < blocks; i++) {
                for(int j = 0; j < word_cap; j++)
                words[i][j] = EMPTY; 
                lru[i] = 0;                 
            }
        }

        // cpu try to load a word of memory
        void load( string address ) {

            if( !this->mm ) {
                cout << "Error: no main memory attached" << endl; 
                return; 
            }

            for(int i = 0; i < blocks; i++) {
                for(int j = 0; j < word_cap; j++) {
                    if( address == words[i][j] ) {

                        // cache hit
                        this->current_state = hclr + "cache hit, addr: " + address + rclr; 
                        this->hits++; 
                        cache_hit( i, j );   
                        print_procedure(); 
                        return;
                    
                    }
                }
            }

            // cache miss
            this->miss++; 

            if( indx < cache_size ) {
                this->current_state = mclr + "cache miss, addr: " + address + rclr; 
                load_from_memory( address ); 
            }
            else {
                this->current_state = mclr + "cache miss [lru replace], addr: " + address + rclr; 
                lru_replace_protocol( address );
            }

            this->current_state = "Memory function completed";
            print_procedure(); 
            return; 

        }

        int hitRate() { return hits / (hits + miss) * 100; }

};