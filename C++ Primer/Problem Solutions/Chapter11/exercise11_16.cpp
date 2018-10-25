#include<iostream>
#include<map>

using namespace std;

int main(int argc, char const *argv[]){
    map<int,int> m;
    m[1] = 1;
    map<int,int>::iterator it = m.begin();   
    it->second = 2;
    cout<<it->second<<"\t" << it->first<< endl;
}

/* output:
2       1
*/
