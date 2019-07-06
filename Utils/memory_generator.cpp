#include <iostream>
#include <fstream>
#include <math.h> 

using namespace std; 

// decimal to hexa
string decToHexa(int n) {    
    string result = ""; 
    char hexaDeciNum[100];       
    int i = 0; 
    while(n!=0) {    
        int temp  = 0;           
        temp = n % 16;           
        if(temp < 10) { 
            hexaDeciNum[i] = temp + 48; 
            i++; 
        } 
        else { 
            hexaDeciNum[i] = temp + 55; 
            i++; 
        } 
        n = n/16; 
    } 
    for(int j=i-1; j>=0; j--) 
        result += hexaDeciNum[j]; 
    return result; 
} 

int main() {

    int byte = 3; 
    int total = pow(16, 3);  
    int limit = 3 * 10; 

    string total_words[ limit ];

    string output = "../memory.txt"; 

    // cout << "insert output file name : " << endl; 
    // cin >> output; 

    fstream outfile;
    outfile.open( output, fstream::out );  

    outfile << limit / 3 << " " << 7 << " " << 3 << " " << 12 << endl << endl; 

    int address = 0; 
    
    for(int i = 0; i < limit; i ++) {

        string result = "0x"; 
        string buffer = decToHexa( address ); 
        address += 4; 

        for(int i = buffer.length(); i < byte; i++) result += "0"; 

        outfile << result + buffer << " "; 

        total_words[i] = result + buffer; 

        if(i % 3 == 2) outfile << endl; 

    }

    outfile << endl; 

    for(int i = 0; i < 12; i++) 
        outfile << total_words[ rand() % limit ] << endl; 

}
