#include<iostream>
#include<string>

class HasPtr{
public:
    HasPtr(const std::string &s = std::string() )
        :ps(new std::string(s)), i(0), use(new size_t(1)){}
    HasPtr(const HasPtr &origin)
        :ps(origin.ps), use(origin.use), i(origin.i){ ++*this->use; }

    HasPtr& operator=(const HasPtr &rhs){
        ++*rhs.use;
        if(--*use == 0){
            delete this->ps;
            delete this->use;
        }
        this->ps = rhs.ps;
        this->use = rhs.use;
        this->i = rhs.i;
    }
    HasPtr& operator=(const std::string &str){
        *ps = str;
        return *this;
    }
    std::string& operator*(){
        return *ps;
    }
    ~HasPtr(){
        if(--*use == 0){
            delete use;
            delete ps;
        }
    }
private:
    std::string *ps;
    int i;
    size_t *use;
};

int main(int argc, char const *argv[])
{
    using namespace std;
    HasPtr h("hi peter!");
    HasPtr h2 = h;
    h = "hi maple!";
    cout<<"h: "<<*h<<endl;
    cout<<"h2: "<<*h2<<endl;
    return 0;
}

/* output:
h: hi maple!
h2: hi maple!
*/