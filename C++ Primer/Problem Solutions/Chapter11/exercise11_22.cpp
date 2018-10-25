#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

int main(int argc, char const *argv[])
{
    map<string, vector<int> > m;
    cout<<typeid(map<string, vector<int> >::value_type).name()<<endl;
    cout<<typeid(m.insert({"test", {1}})).name()<<endl;

    return 0;
}

/* output:
std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, std::vector<int, std::allocator<int> > >
std::pair<std::_Rb_tree_iterator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, std::vector<int, std::allocator<int> > > >, bool>
*/
