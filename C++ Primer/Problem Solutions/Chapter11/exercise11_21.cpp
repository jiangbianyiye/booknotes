#include<iostream>
#include<string>
#include<map>
#include<fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    // ifstream in_file(R"(./exercise11_21.cpp)");
    // cin.rdbuf(in_file.rdbuf());
    map<string, size_t> word_count;
    string word;
    while(cin>>word){
        ++word_count.insert({word,0}).first->second;
    }

    for(auto word_pair : word_count){
        cout<<word_pair.first<<"    \t"<<word_pair.second<<endl;
    }
    return 0;
}
