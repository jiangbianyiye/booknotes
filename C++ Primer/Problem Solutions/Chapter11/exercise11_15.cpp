#include<iostream>
#include<map>
#include<vector>

using namespace std;

int main(int argc, char const *argv[])
{
    cout<<typeid(map<int, vector<int> >::mapped_type).name()<<endl;
    cout<<typeid(map<int, vector<int> >::key_type).name()<<endl;
    cout<<typeid(map<int, vector<int> >::value_type).name()<<endl;
    return 0;
}

/* output:
std::vector<int, std::allocator<int> >
int
std::pair<int const, std::vector<int, std::allocator<int> > >
*/