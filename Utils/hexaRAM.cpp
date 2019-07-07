/* 
    CACHE SIMULATOR UTILITY TOOL: 

    * GENERATE A MAIN MEMORY MODULE 
    * GENERATE RANDOM INPUTS WITHOUT ERRORS 
    * EASY TO USE 
*/

// libraries 
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

// standards
#define BYTE_LEN 3

using namespace std; 

// decimal to hexadecimal convert func.

string decToHexa(int n) {    
    char hexaDeciNum[100];       
    int i = 0; 
    while(n!=0) {    

        int temp  = n % 16;           
        if(temp < 10) hexaDeciNum[i++] = temp + 48; 
        else hexaDeciNum[i++] = temp + 55; 
        n /= 16; 
    } 
    string result = ""; 
    for(int j=i-1; j>=0; j--) result += hexaDeciNum[j]; 
    return result; 
} 


int main() {

    fstream file; 

    // input params
    int words, mblocks, cblocks, loads; 
    string file_name; 

    // configurations
    cout << "--configurations \n \n";
    cout << "words : "; cin >> words; 
    cout << "memory blocks : "; cin >> mblocks; 
    cout << "cache blocks : "; cin >> cblocks; 
    cout << "file name : "; cin >> file_name; 
    cout << "loads quantity : "; cin >> loads; 
    cout << "Memory file generated! " << endl;

    // memory params
    int byte = BYTE_LEN; 
    int limit = words * mblocks; 
    string memory[ limit ]; 

    // file opening
    file.open( file_name, fstream::out ); 

    // printing memory blocks, cache blocks, words x block, loads 
    file << mblocks << " " << cblocks << " " << words << " " << loads << endl; 
    
    // generating memory address 
    int address = 0; 
    for(int i = 0; i < limit; i++) {
        string result = "0x"; 
        string buffer = decToHexa( address ); 
        address += 4; 
        for(int j = buffer.length(); j < byte; j++) result += "0"; 
        memory[i] = result + buffer; 
        file << memory[i] << " "; 
        if( i % words == words - 1) file << endl; 
    }

    file << endl; 

    // generating random loads
    for(int i = 0; i < loads; i++) file << memory[ rand() % limit ] << endl; 

    // file closing 
    file.close(); 
}