#include<iostream>
#include<string>

class Employee{
    static size_t no;
public:
    Employee():id(no++){}
    Employee(const std::string &name):id(no++),name(name){}
    Employee(const Employee &orign):id(no++), name(orign.name){}

    Employee & operator=(const Employee other){
        this->name = other.name; return *this;
    }

    void sayHello(){
        std::cout<<"Hello I'm "<<this->name<<", my id is "<<this->id<<std::endl;
    }
private:
    size_t id;
    std::string name;
};

size_t Employee::no = 0; 

int main(int argc, char const *argv[])
{
    using namespace std;

    Employee a;
    Employee b("kangkang");
    a.sayHello();
    b.sayHello();
    a = b;
    a.sayHello();
    return 0;
}