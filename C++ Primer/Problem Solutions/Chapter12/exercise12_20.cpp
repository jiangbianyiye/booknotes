#include"../../example/TextSearcher/StrBlob.h"
#include"../../example/TextSearcher/StrBlobPtr.h"

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream in_file(R"(./exercise12_20.cpp)");
    if(!in_file){
        cerr<<"can not open file"<<endl;
        return -1;
    }
    string line;
    StrBlob blob;
    while(getline(in_file, line)){
        blob.push_back(line);
    }

    for(auto it=blob.begin(), end=blob.end(); !eq(it,end); it.incr()){
        cout<<it.deref()<<endl;
    }
    return 0;
}

/* output:
#include"../../example/TextSearcher/StrBlob.h"
#include"../../example/TextSearcher/StrBlobPtr.h"

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream in_file(R"(./exercise12_20.cpp)");
    if(!in_file){
        cerr<<"can not open file"<<endl;
        return -1;
    }
    string line;
    StrBlob blob;
    while(getline(in_file, line)){
        blob.push_back(line);
    }

    for(auto it=blob.begin(), end=blob.end(); !eq(it,end); it.incr()){
        cout<<it.deref()<<endl;
    }
    return 0;
}

*/