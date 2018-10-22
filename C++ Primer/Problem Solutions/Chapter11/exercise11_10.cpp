#include<map>
#include<vector>
#include<list>

int main(int argc, char const *argv[])
{
    using namespace std;

    map<vector<int>::iterator, int> vector_it_map;
    // map<list<int>::iterator, int> list_it_map; //声明没有问题

    vector<int> int_vector = {1,2,3};
    list<int> int_list = {1,2,3};
    vector_it_map[int_vector.begin()] = 1;
    // list_it_map[int_list.begin()] = 1;
    // error: no match for ‘operator<’ (operand types are ‘const std::_List_iterator<int>’ and ‘const std::_List_iterator<int>’)
    //    { return __x < __y; }
    return 0;
}
