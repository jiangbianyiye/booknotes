#include<iostream>
#include<cctype>

using namespace std;

int main(int argc, char const *argv[])
{
    size_t max_len = 15;
    char *str = new char[max_len+1];

    char c;
    size_t curr = 0;
    while(cin.get(c)){
        if(::isspace(c)){
            break;
        }
        str[curr++] = c;
        if(curr == max_len){
            cerr<<"out of string max length"<<endl;
        }
    }
    str[max_len] = '\0';
    cout<<str<<endl;
    delete []str;
    return 0;
}
