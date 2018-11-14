#include<iostream>
#include<string>
#include<memory>

using namespace std;

int main(int argc, char const *argv[])
{
    allocator<string> string_alloc;
    size_t maxlen = 10;
    string *ptr = string_alloc.allocate(maxlen);
    string s;
    string *p = ptr;
    while(cin>>s && p!=ptr+maxlen){
        string_alloc.construct(p++, s);
    }
    const size_t size = p - ptr;

    for(auto it=ptr; it!=ptr+size; ++it){
        cout<<*it<<endl;
    }

    while(p!=ptr){
        string_alloc.destroy(--p);
    }
    string_alloc.deallocate(ptr, maxlen);

    return 0;
}
