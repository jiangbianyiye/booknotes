#include<iostream>
#include<map>
#include <typeinfo>

class Data{
public:
    Data(){};
    Data(int a):x(a){};

    bool operator <(const Data& other) const {
        return this->x < other.x;
    }

    void test(){};

    int x = 0;

};

bool compare(const Data &a, const Data &b){
    return a.x < b.x;
}
using namespace std;

int main(int argc, char const *argv[])
{
    map<Data, int, decltype(&compare)> data_map(compare);

    std::cout<<typeid(&compare).name()<<std::endl;
    std::cout<<typeid(compare).name()<<std::endl;
    Data d(1);
    data_map[d] = 0;
    return 0;
}

