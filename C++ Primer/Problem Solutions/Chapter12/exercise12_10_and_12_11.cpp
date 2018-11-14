#include<iostream>
#include<memory>

using namespace std;

void process(shared_ptr<int> ptr)
{
    cout<<"shared_ptr use_count:"<<ptr.use_count()<<endl;
    cout<<*ptr<<endl;
}

int main(int argc, char const *argv[])
{
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p));
    cout<<*p<<endl;

    process(shared_ptr<int>(p.get())); //p所指的空间在函数返回后已经被释放
    cout<<*p<<endl;

    return 0;
}

/* output:
shared_ptr use_count:2
42
42
shared_ptr use_count:1
42
0
*/