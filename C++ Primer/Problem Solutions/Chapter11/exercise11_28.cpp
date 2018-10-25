#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

int main(int argc, char const *argv[])
{
    map<string, vector<int> > m;
    m["a"] = {1};
    map<string, vector<int> >::iterator it = m.find("a");
    cout<<it->first<<"\t"<<it->second[0]<<endl;
    return 0;
}

/* output:
a       1
*/