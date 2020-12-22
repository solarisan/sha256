#include <iostream>
#include <cstdint>
#include <string>
#include <sys/stat.h>
#include <time.h>

#include "functions.h"
#include "sha256.h"

using namespace std;


int main(){
    clock_t tStart = clock();
    //snippet to give a file size////////////////////////////////////
    struct stat results;  
    if (stat("input.log", &results) == 0){
        //cout << (results.st_size) << endl; //gives the size of the file in bytes (note if the file is ascii every new line equals two bytes)
    }else{
        cout<<"error in reading file"<<endl;  // An error occurred   
    }

    for (int x=0; x<1000;x++){
    const char *nonce="hello john smith hope you are doing well";
    calculator(nonce);

    }
    //myb=(myb+1) % 4294967296; //modulu 2**32
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}