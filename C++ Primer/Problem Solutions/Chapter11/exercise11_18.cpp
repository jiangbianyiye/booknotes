#include<iostream>
#include<map>

using namespace std;

int main(int argc, char const *argv[])
{
    map<string, size_t> word_count;
    auto map_it = word_count.begin();
    cout<<typeid(map_it).name()<<endl;
    cout<<typeid(*map_it).name()<<endl;

    map<string, size_t>::iterator map_it2 = word_count.begin();
//pair<string, size_t>::iterator map_it3 = word_count.begin();
/*
exercise11_18.cpp:13:27: error: ‘iterator’ is not a member of ‘std::pair<std::__cxx11::basic_string<char>, long unsigned int>’
     pair<string, size_t>::iterator map_it3 = word_count.begin();
*/
    cout<<typeid(*map_it2).name()<<endl;
    return 0;
}

/* output:
std::_Rb_tree_iterator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, unsigned long> >
std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, unsigned long>
std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, unsigned long>
*/