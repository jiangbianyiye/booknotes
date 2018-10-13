#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<set>

class WordCount{
public:
    static void run()
    {
        std::map<std::string, size_t> word_count;
        std::string word;
        while(std::cin >> word){
            ++word_count[word];
        }
        
        for(auto &pair : word_count){
            std::cout << pair.first << " occurs " << pair.second
                      << (pair.second>1 ? "times":"time") << std::endl;
        }
    }
};

int main(int argc, char const *argv[])
{
    std::ifstream inf;
    auto back_cin_buf = std::cin.rdbuf();
    inf.open("exercise11_3.cpp");
    if(inf){
        std::cin.rdbuf(inf.rdbuf());
        WordCount::run();
        std::cin.rdbuf(back_cin_buf);
    }else{
        std::cout<<"Can not open file!"<<std::endl;
    }
    return 0;
}
