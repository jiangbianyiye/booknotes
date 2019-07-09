#include<iostream>
#include<string>

void f(std::string str){}

void f(std::string &str){}

int main(int argc, char const *argv[])
{
    std::string a("A");
    //f(a);

    return 0;
}
