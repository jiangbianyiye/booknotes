#include<iostream>
#include<string>
#include<memory>

using namespace std;

int main(int argc, char const *argv[])
{
    auto p = make_shared<int>(1);
    weak_ptr<int> wp(p);
    weak_ptr<int> wp2(wp);

    unique_ptr<string> up(new string("test"));
    up.reset();

    cout<<up.get()<<endl;
    return 0;
}
