#include<string>
#include<iostream>

class HasPtr{
public:
    HasPtr(const std::string &s = std::string())
        :ps(new std::string(s)),i(0){}

    HasPtr(const HasPtr& origin)
        :ps(new std::string(*origin.ps)), i(origin.i){}

    //要能保证能自赋值与异常安全，即使发生异常，左侧对象也应当处于有意义的状态
    HasPtr& operator=(const HasPtr &rhs){
        auto newp = new string(*rhs.ps);
        delete ps;
        ps = newp;
        i = rhs.i;
        return *this;
        /*
        delete this->ps;
        this->ps = new std::string(*rhs.ps);
        this->i = rhs.i;
        return *this;
        */
    }

    ~HasPtr(){delete ps;}

    const std::string& getString() const {return *ps;}
    void changeStr(const std::string &new_str){
        delete ps;
        ps = new std::string(new_str);
    }
private:
    std::string *ps;
    int i;
};

using namespace std;

int main(int argc, char const *argv[])
{
    string str("hello");
    HasPtr a(str);
    HasPtr b(a);
    a.changeStr("Hi");
    cout<<b.getString()<<endl;
    b=a;
    cout<<b.getString()<<endl;
    return 0;
}
