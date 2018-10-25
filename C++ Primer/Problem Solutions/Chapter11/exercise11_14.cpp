#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

void add_family(map<string, vector<pair<string,string> > > & families, const string & family_name){
    families[family_name];
}

void add_child(map<string, vector<pair<string,string> > > & families, const string & family_name, const string &child_name, const string &birthday){
    if(families.find(family_name) != families.end()){
        families[family_name].emplace_back(child_name, birthday);
    }
}
int main(int argc, char const *argv[])
{
    map<string, vector<pair<string,string> > > families;

    add_family(families, "张");
    add_child(families, "张", "三", "1990-1-1");
    add_child(families, "张", "三.一", "1990-1-1");

    add_family(families, "王");
    add_child(families, "王", "五", "1990-1-1");

    for(auto & family : families){
        cout<<family.first<<"家的孩子有："<<endl;
        for(auto & child : family.second){
            cout<<"\t"<<family.first<<child.first<<"\t"<<child.second<<endl;
        }
        cout<<endl;
    }
    return 0;
}

/* output:
张家的孩子有：
        张三    1990-1-1
        张三.一 1990-1-1

王家的孩子有：
        王五    1990-1-1

*/ 