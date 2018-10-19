#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
#include<cctype>

class WordCounter{
public:
    typedef std::map<std::string,size_t> WordCount;
    WordCount getWordCount(std::istream & in);
private:
    void analyseWordInLine(const std::string & line);

private:
    WordCount wordCount;
};

WordCounter::WordCount WordCounter::getWordCount(std::istream & in){
    std::string line;
    while(std::getline(in, line)){
        analyseWordInLine(line);
    }
    return wordCount;
}

void WordCounter::analyseWordInLine(const std::string & line){
    
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
                ++this->wordCount[word];
            }  
        }
    }
}

int main(int argc, char const *argv[])
{
    std::string fileName(R"(./exercise11_4_pro.cpp)");

    std::ifstream inFile;
    inFile.open(fileName);
    WordCounter wc;
    auto wordCount = wc.getWordCount(inFile);

    auto longestWordSize = std::max_element(wordCount.cbegin(), wordCount.cend(),
        [](WordCounter::WordCount::value_type const& left, 
                WordCounter::WordCount::value_type const& right){
            return left.first.size() < right.first.size();
        })->first.size();

    for(auto const & entry : wordCount){
        std::cout<<std::setw(longestWordSize+1)<<std::left<<entry.first
                 <<"|"<<std::setw(10)<<std::right<<entry.second<<std::endl;
    }
    return 0;
}
