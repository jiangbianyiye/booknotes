#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>

using Families =  std::map<std::string, std::vector<std::string> >;

void add_family(Families &families, const std::string &family_name)
{
    // 检查家庭是否存在，防止覆盖已有家庭
    // if(families.find(family_name) == families.end()){
    //     families[family_name] = std::vector<std::string>();
    //     //families.insert(std::make_pair(family_name, std::vector<std::string>() ) );
    // }

    //此种方式不需要检查
    families[family_name];
}

void add_child(Families &families, const std::string &family_name, const std::string &child_name){
    if(families.find(family_name) != families.end() ){
        families[family_name].push_back(child_name);
    }
}


int main(int argc, char const *argv[])
{
    Families families;
    add_family(families, "张");
    add_child(families, "张", "三");
    add_child(families, "张", "三.一");
    add_family(families, "张");

    add_family(families, "王");
    add_child(families, "王", "五");

    add_child(families,"李", "四");

    for(auto const & family : families){
        std::cout << family.first << "家的孩纸：";
        for(auto const & child_name : family.second){
            std::cout<<family.first<<child_name<<", ";
        }
        std::cout<<std::endl;
    }
    return 0;
}
