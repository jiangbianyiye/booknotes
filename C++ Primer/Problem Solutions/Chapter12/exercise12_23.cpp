#include<string>
#include<cstring>
#include<iostream>

using namespace std;

char * stradd(const char *lstr,const char *rstr)
{
    int two_str_len = ::strlen(lstr) + ::strlen(rstr);
    int newstr_len = ::strlen(lstr) + ::strlen(rstr)+1;
    char * ret = new char[newstr_len];
    strcpy(ret, lstr);
// strncpy(ret, lstr, max_str_len);
// destination is padded with zeros until a total of num characters have been written to it.
    strcat(ret, rstr);
    return ret;
}

char * stringadd(const string &a, const string &b)
{
    char *ret = new char[a.size()+b.size()];
    strcpy(ret, (a+b).c_str());
    return ret;
}

int main(int argc, char const *argv[])
{
    char *str = stradd("Hello ", "World!");
    cout<<str<<endl;
    delete []str;

    string a = "Hi ";
    string b = "maple!";
    char * strb = stringadd(a,b);
    cout<<strb<<endl;
    delete []strb;
    
    return 0;
}
