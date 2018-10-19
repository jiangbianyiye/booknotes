#include<iostream>
#include<bitset>


int main(int argc, char const *argv[])
{
    int x = 1;
    std::cout<<std::bitset<sizeof(int)*8>(x)<<"\t"<<x<<std::endl;
    //x = x >> 35;
    x = +x++;
    std::cout<<std::bitset<sizeof(int)*8>(x)<<"\t"<<x<<std::endl;
    return 0;
}
