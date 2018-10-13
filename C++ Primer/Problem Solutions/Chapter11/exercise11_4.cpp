#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<cctype>
#include<map>

class WordCountV2{
public:
    static void run()
    {
        std::map<std::string, size_t> word_count;
        std::string word;
        while(std::cin >> word){
            if(trans(word) == ""){
                continue;
            }
            ++word_count[word];
        }
        
        for(auto &pair : word_count){
            std::cout << pair.first << " occurs " << pair.second
                      << (pair.second>1 ? "times":"time") << std::endl;
        }
    }

private:
    static std::string & trans(std::string & str){
        str.erase(std::remove_if(str.begin(),str.end(),::ispunct),str.end());
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
};

int main(int argc, char const *argv[])
{
    std::ifstream inf;
    auto back_cin_buf = std::cin.rdbuf();
    inf.open("exercise11_3.cpp");
    if(inf){
        std::cin.rdbuf(inf.rdbuf());
        WordCountV2::run();
        std::cin.rdbuf(back_cin_buf);
    }else{
        std::cout<<"Can not open file!"<<std::endl;
    }
    return 0;
}
