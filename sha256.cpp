#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <bitset>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>

using namespace std;

string TextToBinaryString(string word){
    string binaryString = "";
    for (char& _char : word) {
        binaryString +=bitset<8>(_char).to_string();
    }
    return binaryString;
}

void sigma0(std::uint32_t* v){
    //sigma0 does 2 rotations and one shift and then xor the result
    std::uint32_t r1=_rotr(*v,7);
    std::uint32_t r2=_rotr(*v,18);
    std::uint32_t s1=*v>>3;
    *v=r1^r2^s1;   
}

void sigma1(std::uint32_t* v){
    //sigma0 does 2 rotations and one shift and then xor the result
    std::uint32_t r1=_rotr(*v,17);
    std::uint32_t r2=_rotr(*v,19);
    std::uint32_t s1=*v>>10;
    *v=r1^r2^s1;
}

std::uint32_t capsigma0(const std::uint32_t v){
    //sigma0 does 2 rotations and one shift and then xor the result
    std::uint32_t r1=_rotr(v,2);
    std::uint32_t r2=_rotr(v,13);
    std::uint32_t r3=_rotr(v,22);
    return r1^r2^r3;
}

std::uint32_t capsigma1(const std::uint32_t v){
    //sigma0 does 2 rotations and one shift and then xor the result
    std::uint32_t r1=_rotr(v,6);
    std::uint32_t r2=_rotr(v,11);
    std::uint32_t r3=_rotr(v,25);
    return r1^r2^r3;
}

std::uint32_t choice(std::uint32_t* x, std::uint32_t* y, std::uint32_t* z){
    std::bitset<32> v;
    for(std::size_t i=0;i<32;i++){      
        v[i]=std::bitset<32>(*x).test(i)? std::bitset<32>(*y).test(i): std::bitset<32>(*z).test(i); 
    }
    return static_cast<std::uint32_t>(v.to_ulong());
}

std::uint32_t majority(std::uint32_t* x, std::uint32_t* y, std::uint32_t* z){
    std::bitset<32> v;
    for(std::size_t i=0;i<32;i++){  
        v[i]=(std::bitset<32>(*x).test(i) & (std::bitset<32>(*y).test(i) | std::bitset<32>(*z).test(i))) | (std::bitset<32>(*y).test(i) & std::bitset<32>(*z).test(i));
    }
    return static_cast<std::uint32_t>(v.to_ulong());
}

int main(){

    //snippet to give a file size////////////////////////////////////
    struct stat results;  
    if (stat("input.log", &results) == 0){
        //cout << (results.st_size) << endl; //gives the size of the file in bytes (note if the file is ascii every new line equals two bytes)
    }else{
        cout<<"error in reading file"<<endl;  // An error occurred   
    }

    //constant values for SHA256   ////////////////////////////////////////////////////////////
    std::vector<std::uint32_t> k{   0x428a2f98,    0x71374491,    0xb5c0fbcf,    0xe9b5dba5,
                                    0x3956c25b,    0x59f111f1,    0x923f82a4,    0xab1c5ed5,
                                    0xd807aa98,    0x12835b01,    0x243185be,    0x550c7dc3,
                                    0x72be5d74,    0x80deb1fe,    0x9bdc06a7,    0xc19bf174,
                                    0xe49b69c1,    0xefbe4786,    0x0fc19dc6,    0x240ca1cc,
                                    0x2de92c6f,    0x4a7484aa,    0x5cb0a9dc,    0x76f988da,
                                    0x983e5152,    0xa831c66d,    0xb00327c8,    0xbf597fc7,
                                    0xc6e00bf3,    0xd5a79147,    0x06ca6351,    0x14292967,
                                    0x27b70a85,    0x2e1b2138,    0x4d2c6dfc,    0x53380d13,
                                    0x650a7354,    0x766a0abb,    0x81c2c92e,    0x92722c85,
                                    0xa2bfe8a1,    0xa81a664b,    0xc24b8b70,    0xc76c51a3,
                                    0xd192e819,    0xd6990624,    0xf40e3585,    0x106aa070,
                                    0x19a4c116,    0x1e376c08,    0x2748774c,    0x34b0bcb5,
                                    0x391c0cb3,    0x4ed8aa4a,    0x5b9cca4f,    0x682e6ff3,
                                    0x748f82ee,    0x78a5636f,    0x84c87814,    0x8cc70208,
                                    0x90befffa,    0xa4506ceb,    0xbef9a3f7,    0xc67178f2}; 

    std::vector<std::uint32_t> inital{  0x6a09e667,    0xbb67ae85,    0x3c6ef372,    0xa54ff53a,
                                        0x510e527f,    0x9b05688c,    0x1f83d9ab,    0x5be0cd19}; 

    std::vector<std::uint32_t> compress{0x6a09e667,    0xbb67ae85,    0x3c6ef372,    0xa54ff53a,
                                        0x510e527f,    0x9b05688c,    0x1f83d9ab,    0x5be0cd19}; 

    const char *str="";
    int stringLen=TextToBinaryString(str).size();   //size of string in bits
    int padding=512-(stringLen+1+64)%512;  //pading size of zeros to make chunks of 512 bits

    cout<<"The string to be hashed is:\t\t"<<TextToBinaryString(str)<<endl;
    cout<<"The size of the string in bits: \t"<<stringLen<<endl;
    cout<<"how many 0 bits for padding needed:\t"<<padding<<endl;

    bitset<512> workBitset{0x0};
    workBitset=workBitset|bitset<512>(TextToBinaryString(str));
    workBitset=workBitset<<(512-stringLen);
    workBitset=workBitset.flip(512-stringLen-1);
    workBitset=workBitset^bitset<512>(stringLen);
    cout<<workBitset<<endl;

    vector<std::uint32_t> wordsSchedule;
    string stringWorkSet=workBitset.to_string();
    for (int x=0; x<64; x++){
        string newString=stringWorkSet.substr(0,32);
        wordsSchedule.push_back(std::stoul(newString,nullptr,2));
        stringWorkSet.erase(0,32);
        if(stringWorkSet.size()==0){
            break;
        }
    }

    cout << "\n\n word size before modification: " << wordsSchedule.size() << "\n\n";
    for (int item=0;item<16;item++){
        cout << bitset<32>(wordsSchedule.at(item)) << endl;
    }
    cout<<"\n-------------------- word schedule 64 words:\n";
    for(int w=16; w<64; w++){
        std::uint32_t w2=wordsSchedule.at(w-2);
        std::uint32_t w7=wordsSchedule.at(w-7);
        std::uint32_t w15=wordsSchedule.at(w-15);
        std::uint32_t w16=wordsSchedule.at(w-16);

        sigma1(&w2);
        sigma0(&w15);
        wordsSchedule.push_back(w2+w7+w15+w16);
    }

    for (int item=0; item<64; item++){
        cout << bitset<32>(wordsSchedule.at(item)) << endl;
    }

    for(int w=0; w<64; w++){
        cout << "\n\n--------------- in step: " << w << endl;
        for(int z=0; z<8; z++){   
            cout << bitset<32>(compress.at(z)) << endl;
        }
        std::uint32_t working0=wordsSchedule.at(w);
        std::uint32_t key0=k.at(w);
        std::uint32_t zero=0x0;
        std::uint32_t a=compress.at(0);   //a
        std::uint32_t b=compress.at(1);   //b
        std::uint32_t c=compress.at(2);   //c
        std::uint32_t e=compress.at(4);   //e
        std::uint32_t f=compress.at(5);   //f
        std::uint32_t g=compress.at(6);   //g
        std::uint32_t h=compress.at(7);   //h

        std::uint32_t ee=capsigma1(e);
        std::uint32_t task1=ee+choice(&e,&f,&g)+h+key0+working0;
        std::uint32_t aa=capsigma0(a);
        std::uint32_t task2=aa+majority(&a,&b,&c);

        compress.emplace(compress.begin(),zero);
        compress.at(0)=task1+task2;
        compress.at(4)+=task1;

        cout << "\n\n task 1+2:\t" << bitset<32>(task1+task2) << "\n task1:\t\t" << bitset<32>(task1) << endl;
    }
    
    for(int sum=0; sum<8; sum++){   
        compress.at(sum)+=inital.at(sum); 
    }

    cout<<"\n\n the final hash:-----------------------------"<<endl;
    for(int z=0; z<8; z++){   
        cout << bitset<32>(compress.at(z)) << endl;
    }

    cout<<"\n\nconverting to hex-----------------------------"<<endl;

    for(int z=0; z<8; z++){        
        cout << uppercase << setw(sizeof(std::uint32_t)*2) << std::hex << compress.at(z) << endl;       
    }   

    //myb=(myb+1) % 4294967296; //modulu 2**32

    return 0;
}

