#include<iostream>
#include<memory>

using namespace std;

class TestClass{
public:
    int a; //内置类型不会默认初始化
    weak_ptr<int> wptr;
};

void test1()
{
    TestClass c;
    cout<<c.a<<" "<<c.wptr.lock()<<endl;
}

int main(int argc, char const *argv[])
{
    test1();
    return 0;
}
