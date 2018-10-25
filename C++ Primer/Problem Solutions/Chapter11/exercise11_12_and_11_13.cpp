#include<iostream>
#include<string>
#include<vector>
#include<utility>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<pair<string,int> > data;
    string str;
    int num;
    while(cin>>str>>num){
        data.push_back(pair<string,int>(str,num) );
        data.push_back(make_pair(str,num));
        data.push_back({str,num});
    }
    for(pair<string, int> &entry : data){
        cout<<entry.first<<" "<<entry.second<<std::endl;
    }
    return 0;
}
