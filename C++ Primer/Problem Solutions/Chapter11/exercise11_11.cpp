#include<iostream>
#include<string>
#include<set>

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

int main(int argc, char const *argv[])
{
    using namespace std;

    //函数指针
    multiset<Sales_data, bool (*) (const Sales_data &lhs, const Sales_data &rhs)> bookstore(compareIsbn);
    bookstore.insert(Sales_data("123456"));
    for(auto & sales_data : bookstore){
        std::cout<<sales_data.isbn()<<std::endl;
    }

    //使用typedef
    typedef bool (*fp) (const Sales_data &lhs, const Sales_data &rhs);  
    multiset<Sales_data, fp> bookstore2(compareIsbn);
    bookstore2.insert(Sales_data("345678"));
    for(auto & sales_data : bookstore2){
        std::cout<<sales_data.isbn()<<std::endl;
    }
    return 0;
}
