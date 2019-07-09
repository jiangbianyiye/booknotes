#include<iostream>
#include<string>

class HasPtr{
public:
    HasPtr(const std::string &s = std::string()):ps(new std::string(s)),i(0){}
    HasPtr(const HasPtr & origin):ps(new std::string(*origin.ps)), i(origin.i){}
    HasPtr& operator=(const HasPtr &rhs);
    HasPtr& operator=(const std::string&rhs);
    std::string &operator*();
    ~HasPtr(){delete ps;}
private:
    std::string *ps;
    int i;
};

inline HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    std::string *newp = new std::string(*rhs.ps);
    delete this->ps;
    this->ps = newp;
    this->i = rhs.i;
    return *this;
}

inline HasPtr& HasPtr::operator=(const std::string &rhs)
{
    *this->ps = rhs;
    return *this;
}

inline std::string& HasPtr::operator*()
{
    return *this->ps;
}

int main(int argc, char const *argv[])
{
    using namespace std;

    HasPtr h("hi tom!");
    HasPtr h2(h);
    HasPtr h3 = h2;
    h2 = "hi peter!";
    h3 = "hi sam!";
    cout<<"h: "<<*h<<endl;
    cout<<"h2: "<<*h2<<endl;
    cout<<"h3: "<<*h3<<endl;
    return 0;
}

/*
h: hi tom!
h2: hi peter!
h3: hi sam!
*/