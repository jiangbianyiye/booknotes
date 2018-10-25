#include<iostream>
#include<string>
#include<map>

using namespace std;

void add_children(multimap<string, string> &families,const string &second_name,const string &first_name)
{
    families.insert(make_pair(second_name, first_name));
}

void show_families(multimap<string, string> &families)
{
    for(auto &name : families){
        cout<<name.first<<name.second<<endl;
    }
}

int main(int argc, char const *argv[])
{
    multimap<string, string> families;
    
    add_children(families, "张", "三");
    add_children(families, "李", "四");
    add_children(families, "张", "三.一");

    show_families(families);
    return 0;
}

/* output:
张三
张三.一
李四
*/