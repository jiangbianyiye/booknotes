#include<iostream>
#include<vector>

struct X{
    X() {std::cout<<"X()"<<std::endl;}
    X(const X&){std::cout<<"X(const X&)"<<std::endl;}
    X& operator=(const X&){std::cout<<"X& operator=(const X&)"<<std::endl;return *this;}
    ~X(){std::cout<<"~X()"<<std::endl;}
};

void f1(X x)
{

}

void f2(X &x)
{

}

using namespace std;
int main(int argc, char const *argv[])
{
    cout<<"局部变量"<<endl;
    X x;
    cout<<endl;

    cout<<"非引用参数传递："<<endl;
    f1(x);
    cout<<endl;

    cout<<"引用参数传递"<<endl;
    f2(x);
    cout<<endl;

    cout<<"动态分配"<<endl;
    X *px = new X;
    cout<<endl;

    cout<<"添加到容器"<<endl;
    vector<X> vx;
    vx.push_back(x);
    cout<<endl;

    cout<<"释放动态分配对象："<<endl;
    delete px;
    cout<<endl;

    cout<<"间接初始化和赋值："<<endl;
    X y = x;
    y=x;
    cout<<endl;

    cout<<"程序结束"<<endl;
    return 0;
}

/* output:
局部变量
X()

非引用参数传递：
X(const X&)
~X()

引用参数传递

动态分配
X()

添加到容器
X(const X&)

释放动态分配对象：
~X()

间接初始化和赋值：
X(const X&)
X& operator=(const X&)

程序结束
~X()
~X()
~X()
*/