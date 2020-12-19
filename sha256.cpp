#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <bitset>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>

using namespace std;

string TextToBinaryString(string words){
    string binaryString = "";
    for (char& _char : words) {
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
    std::vector<std::uint32_t> k; 
    k.push_back(0x428a2f98);
    k.push_back(0x71374491);
    k.push_back(0xb5c0fbcf);
    k.push_back(0xe9b5dba5);
    k.push_back(0x3956c25b);
    k.push_back(0x59f111f1);
    k.push_back(0x923f82a4);
    k.push_back(0xab1c5ed5);
    k.push_back(0xd807aa98);
    k.push_back(0x12835b01);
    k.push_back(0x243185be);
    k.push_back(0x550c7dc3);
    k.push_back(0x72be5d74);
    k.push_back(0x80deb1fe);
    k.push_back(0x9bdc06a7);
    k.push_back(0xc19bf174);
    k.push_back(0xe49b69c1);
    k.push_back(0xefbe4786);
    k.push_back(0x0fc19dc6);
    k.push_back(0x240ca1cc);
    k.push_back(0x2de92c6f);
    k.push_back(0x4a7484aa);
    k.push_back(0x5cb0a9dc);
    k.push_back(0x76f988da);
    k.push_back(0x983e5152);
    k.push_back(0xa831c66d);
    k.push_back(0xb00327c8);
    k.push_back(0xbf597fc7);
    k.push_back(0xc6e00bf3);
    k.push_back(0xd5a79147);
    k.push_back(0x06ca6351);
    k.push_back(0x14292967);
    k.push_back(0x27b70a85);
    k.push_back(0x2e1b2138);
    k.push_back(0x4d2c6dfc);
    k.push_back(0x53380d13);
    k.push_back(0x650a7354);
    k.push_back(0x766a0abb);
    k.push_back(0x81c2c92e);
    k.push_back(0x92722c85);
    k.push_back(0xa2bfe8a1);
    k.push_back(0xa81a664b);
    k.push_back(0xc24b8b70);
    k.push_back(0xc76c51a3);
    k.push_back(0xd192e819);
    k.push_back(0xd6990624);
    k.push_back(0xf40e3585);
    k.push_back(0x106aa070);
    k.push_back(0x19a4c116);
    k.push_back(0x1e376c08);
    k.push_back(0x2748774c);
    k.push_back(0x34b0bcb5);
    k.push_back(0x391c0cb3);
    k.push_back(0x4ed8aa4a);
    k.push_back(0x5b9cca4f);
    k.push_back(0x682e6ff3);
    k.push_back(0x748f82ee);
    k.push_back(0x78a5636f);
    k.push_back(0x84c87814);
    k.push_back(0x8cc70208);
    k.push_back(0x90befffa);
    k.push_back(0xa4506ceb);
    k.push_back(0xbef9a3f7);
    k.push_back(0xc67178f2);

    std::vector<std::uint32_t> inital; 
    inital.push_back(0x6a09e667);
    inital.push_back(0xbb67ae85);
    inital.push_back(0x3c6ef372);
    inital.push_back(0xa54ff53a);
    inital.push_back(0x510e527f);
    inital.push_back(0x9b05688c);
    inital.push_back(0x1f83d9ab);
    inital.push_back(0x5be0cd19);

    std::vector<std::uint32_t> compress; 
    compress.push_back(0x6a09e667);
    compress.push_back(0xbb67ae85);
    compress.push_back(0x3c6ef372);
    compress.push_back(0xa54ff53a);
    compress.push_back(0x510e527f);
    compress.push_back(0x9b05688c);
    compress.push_back(0x1f83d9ab);
    compress.push_back(0x5be0cd19);

    // std::uint32_t myb=4294967296-5;
    // std::uint32_t t1=0b10101010101010101010101010101010;
    // std::uint32_t t2=0b11111111111111111111111111111111;
    // std::uint32_t t3=0b00000000000000000000000000000000;
    //cout<<std::bitset<32>(majority(&t1,&t2,&t3));
    //cout<<std::bitset<32>(k[0]);
    const char *str="";
    cout<<"The string to be hashed is:\t\t"<<TextToBinaryString(str)<<endl;
    int si=TextToBinaryString(str).size();   //size of string in bits
    cout<<"The size of the string in bits: \t"<<si<<endl;
    int l=512-(si+1+64)%512;  //pading size of zeros to make chunks of 512 bits
    cout<<"how many 0 bits for padding needed:\t"<<l<<endl;

    bitset<512> work{0x0};
    work=work|bitset<512>(TextToBinaryString(str));
    //work=work&(bitset<512>(str));   //error whay?
    work=work<<(512-si);
    work=work.flip(512-si-1);
    work=work^bitset<512>(si);
    cout<<work<<endl;

    vector<std::uint32_t> words;
    string st=work.to_string();
    for (int x=0; x<64; x++){
        string newst=st.substr(0,32);
        words.push_back(std::stoul(newst,nullptr,2));
        //unsigned long bb=std::stoul(newst,nullptr,2);
        //cout<<bitset<32>(bb)<<endl;
        
        st.erase(0,32);
        if(st.size()==0){
            break;
        }
    }
    cout << "\n\n word size before modification: " << words.size() << "\n\n";
    for (int item=0;item<16;item++){
        cout << bitset<32>(words.at(item)) << endl;
    }
    cout<<"\n-------------------- word schedule 64 words:\n";
    for(int w=16; w<64; w++){
        std::uint32_t w2=words.at(w-2);
        std::uint32_t w7=words.at(w-7);
        std::uint32_t w15=words.at(w-15);
        std::uint32_t w16=words.at(w-16);

        sigma1(&w2);
        sigma0(&w15);
        words.push_back(w2+w7+w15+w16);
    }

    for (int item=0; item<64; item++){
        cout << bitset<32>(words.at(item)) << endl;
    }

    for(int w=0; w<64; w++){
        cout << "\n\n--------------- in step: " << w << endl;
        for(int final=0; final<8; final++){   
            cout << bitset<32>(compress.at(final)) << endl;
        }
        std::uint32_t working0=words.at(w);
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
        
        cout << "\n\n task 1+2:  " << bitset<32>(task1+task2) << "\n task1:  " << bitset<32>(task1) << endl;
    }
    
    for(int sum=0; sum<8; sum++){   
        compress.at(sum)+=inital.at(sum); 
    }

    cout<<"\n\n the final hash:-----------------------------"<<endl;
    for(int final=0; final<8; final++){   
        cout << bitset<32>(compress.at(final)) << endl;
    }

    cout<<"\n\nconverting to hex-----------------------------"<<endl;

    for(int final=0; final<8; final++){        
        cout << uppercase << setw(sizeof(std::uint32_t)*2) << std::hex<<compress.at(final);       
    }   
    


    // if(si<512){
    //     //cout<<(std::bitset<512>(TextToBinaryString(str))<<512-si).flip(512-si-1)+std::bitset<512>(si);
    //     //cout<<(std::bitset<512>(TextToBinaryString(str))<<512-si).flip(512-si1);
    // }
    // std::bitset<512> we {TextToBinaryString(str)};
    
    //anothe idea is not to make the 512 bitset at all, instead look at the string in bunchs of 32 bit from the beggining of the process!
    // for (int x=0; x<35; x++)
    // {
    //     // myb=myb>>1;     //shift
    //     // myb=_rotr(myb,1);  //rotate right
    //     // myb=myb^0b00110011001100110011;  //xor
    //     myb=(myb+1) % 4294967296; //modulu 2**32
    //     cout<< std::bitset<32>(myb) <<endl;
    // }
    return 0;
}

