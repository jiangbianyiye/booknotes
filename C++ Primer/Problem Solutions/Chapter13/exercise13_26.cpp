#include"../../example/TextSearcher/StrBlob.h"
#include"../../example/TextSearcher/StrBlobPtr.h"

#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    StrBlob b1;
    {
        StrBlob b2 = { "a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        cout<<"b2 size: "<<b2.size()<<endl;
        cout<<"b2 front and back: "<<b2.front()<<" "<<b2.back()<<endl;
    }
    cout<<"b1 size: "<<b1.size() <<endl;
    cout<<"b1 front and back: "<<(b1.front())<<" "<<b1.back()<<endl;

    StrBlob b3 = b1;
    b3.push_back("next");
    cout<<"b3 size: "<<b3.size()<<endl;
    cout<<"b3 front and back: "<<b3.front()<<" "<<b3.back()<<endl;

    for(auto it = b1.begin(); !eq(it, b1.end()); it.incr()){
        cout<<it.deref()<<endl;
    }

    auto it = b1.begin();
    it.deref() = "new first word"; 

    cout<<"all elements in b1:"<<endl;
    for(auto it = b1.begin(); !eq(it, b1.end()); it.incr()){
        cout<<it.deref()<<endl;
    }

    return 0;
}

/* output:
b2 size: 4
b2 front and back: a about
b1 size: 3
b1 front and back: a the
b3 size: 4
b3 front and back: a next
a
an
the
all elements in b1:
new first word
an
the
*/