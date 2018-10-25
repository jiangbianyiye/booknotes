#include<iostream>
#include<string>
#include<set>

//精简定义，只为适用本题
class Sales_data{
public:
    Sales_data(): ISBN(""){}
    Sales_data(std::string isbn):ISBN(isbn){}
    std::string isbn() const{
        return this->ISBN;
    }
private:
    std::string ISBN;
};

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

using namespace std;

int main(int argc, char const *argv[])
{
    //函数指针
    multiset<Sales_data, bool (*) (const Sales_data &lhs, const Sales_data &rhs)> bookstore(compareIsbn);
    multiset<Sales_data, bool (*) (const Sales_data &lhs, const Sales_data &rhs)> ::iterator it = bookstore.begin();
    cout<<typeid(it).name()<<endl;

    //使用typedef
    typedef bool (*fp) (const Sales_data &lhs, const Sales_data &rhs);  
    multiset<Sales_data, fp> bookstore2(compareIsbn);
    multiset<Sales_data, fp>::iterator it2 = bookstore.begin();
    cout<<typeid(it2).name()<<endl;

    return 0;
}

/* output:
std::_Rb_tree_const_iterator<Sales_data>
std::_Rb_tree_const_iterator<Sales_data>
*/