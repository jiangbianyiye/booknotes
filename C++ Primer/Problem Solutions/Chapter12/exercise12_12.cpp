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
    auto p = new int();
    auto sp = make_shared<int>();
    process(sp);
    //process(new int()); 
    // error: could not convert ‘(operator new(4), (<statement>, ((int*)<anonymous>)))’ from ‘int*’ to ‘std::shared_ptr<int>’
    //process(p);
    // error: could not convert ‘p’ from ‘int*’ to ‘std::shared_ptr<int>’
    process(shared_ptr<int>(p));
}

/* output:
shared_ptr use_count:2
0
shared_ptr use_count:1
0
*/