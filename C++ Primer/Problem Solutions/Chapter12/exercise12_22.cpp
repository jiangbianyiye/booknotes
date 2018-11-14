#include"../../example/TextSearcher/StrBlob.h"
#include"../../example/TextSearcher/ConstStrBlobPtr.h"
//#include"../../example/TextSearcher/StrBlobPtr.h"

#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    StrBlob b = {"Hello", "World", "!"};

    for(auto it=b.cbegin(), end=b.cend(); !eq(it,end); it.incr()){
        cout<<it.deref()<<endl;
    }

    return 0;
}
