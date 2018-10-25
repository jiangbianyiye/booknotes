#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<iterator>

using namespace std;


template<typename T>
void show(T & set){
    for(auto & meta:set){
        std::cout<<meta<<"\t";
    }
    std::cout<<std::endl;
}

int main(int argc, char const *argv[])
{
    multiset<string> c{"1", "3", "5", "7", "9"};
    vector<string> v{"2", "4", "6", "8", "10"};

    copy(v.begin(),v.end(), inserter(c, c.end()));
    show(c);
//copy(v.begin(),v.end(), back_inserter(c));
/*
usr/include/c++/7/bits/stl_iterator.h:489:13: error: ‘class std::multiset<std::__cxx11::basic_string<char> >’ has no member named ‘push_back’
  container->push_back(__value);
  ~~~~~~~~~~~^~~~~~~~~
*/
//show(c);
    copy(c.begin(),c.end(),inserter(v,v.end()));
    show(v);
    copy(c.begin(),c.end(),back_inserter(v));
    show(v);
    
    return 0;
}

/* output:
1       10      2       3       4       5       6       7       8       9
2       4       6       8       10      1       10      2       3       4       5       6       7       8       9
2       4       6       8       10      1       10      2       3       4       5       6       7       8       9       1       10      2       3       4       5       6       7       8       9
*/