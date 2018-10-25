#include<iostream>
#include<string>
#include<map>

using namespace std;

int main(int argc, char const *argv[])
{
    map<string, int> m;
    string a("a");
    m[a] = 2;
    cout<<typeid(m[a]).name()<<endl;
    return 0;
}

/* output:
int
*/