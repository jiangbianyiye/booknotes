#include<iostream>

using namespace std;

class Test{
public:
    Test():data(0){}
    Test(const Test& orign) = delete;
private: 
    int data;
};

int main(int argc, char const *argv[])
{
    Test a;
    Test b(a);
    return 0;
}
