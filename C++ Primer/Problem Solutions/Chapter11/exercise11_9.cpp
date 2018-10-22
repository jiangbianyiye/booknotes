#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<list>
#include<string>

class WordLineno{
public:
    void read_file(std::istream & in){
        size_t lineno = 0;
        std::string line;
        while(std::getline(in, line)){
            analyseWordInLine(line,++lineno);
        }
    }

    void print() const{
        for(auto & word_lineno : data){
            std::cout<<word_lineno.first<<" appears in line: ";
            for(auto lineno : word_lineno.second){
                std::cout<<lineno<<", ";
            }
            std::cout<<std::endl;
        }
    }
private:
    void analyseWordInLine(const std::string & line, size_t lineno){
        bool inWord = false;
        auto wordBeg = line.end();
        auto wordEnd = line.end();

        for(auto beg = line.begin(), end = line.end(); beg!=end; ++beg){
            if(!inWord && (::isalnum(*beg) || *beg == '_') ){
                inWord = true;
                wordBeg = beg;
            }
            else if(inWord && !(::isalnum(*beg) || *beg == '_')){
                inWord = false;
                wordEnd = beg;
                if(wordBeg != wordEnd){
                    std::string word(wordBeg,wordEnd);
                    this->data[word].push_back(lineno);
                }  
            }
        }
    }

private:
    std::map<std::string, std::list<size_t> > data;
};
int main(int argc, char const *argv[])
{
    std::ifstream in_file("./exercise11_9.cpp");
    if(!in_file){
        std::cout<<"文件打开失败"<<std::endl;
        return -1;
    }
    WordLineno wl;
    wl.read_file(in_file);
    wl.print();
    return 0;
}


