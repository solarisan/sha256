#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <bitset>
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