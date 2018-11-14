#include<iostream>
#include<memory>

using namespace std;

int get_size()
{
    return -12;
}

int main(int argc, char const *argv[])
{
    int * a = (int*)malloc(0);
    cout<<a<<endl;
    int *pia = new int[0];
    *pia = 6;
    cout<<*pia<<endl;
    return 0;
}
