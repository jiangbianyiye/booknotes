#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>

class UniqueWordVector{
public:
    // std::vector<std::string>::const_iterator find(std::string key) const{
    //     // for(auto & word:data){
    //     //     if(word == key){
    //     //         //怎么返回 iterator
    //     //     }
    //     // }

    //     for(auto beg=this->data.cbegin(), end=this->data.cend(); beg!=end; ++beg){
    //         if(*beg == key){
    //             return beg;
    //         }
    //     }
    //     return this->data.cend();
    // }

    void add_word(std::string word){
        if(std::find(this->data.cbegin(), this->data.cend(), word) == this->data.cend() ){
            this->data.push_back(word);
        }
    }

    void print() const{
        for(auto & word:data){
            std::cout<<word<<std::endl;
        }
    }

private:
    std::vector<std::string> data;
};

int main(int argc, char const *argv[])
{
    UniqueWordVector words;
    words.add_word("hello");
    words.add_word("hello");
    words.add_word("world");
    words.print();
    return 0;
}
