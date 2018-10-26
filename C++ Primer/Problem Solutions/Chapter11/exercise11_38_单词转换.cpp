#include<iostream>
#include<fstream>
#include<sstream>
#include<unordered_map>

using std::istream; using std::ostream; using std::ifstream; using std::istringstream;
using std::cout; using std::endl; using std::cin;
using std::string;
using std::runtime_error;
using std::unordered_map;

unordered_map<string, string> buildMap(istream &map_file)
{
    unordered_map<string, string> trans_map;
    string key;
    string value;
    while(map_file>>key && getline(map_file, value)){
        if(value.size()>1){
            trans_map[key] = value.substr(1);
        }
        else{
            throw runtime_error("no rule for " + key);
        }
    }
    return trans_map;
}

void showTransMap(unordered_map<string,string> const &trans_map)
{
    cout<<"Here is transformation map:"<<endl;
    for(auto entry:trans_map){
        cout<<"\t"<<entry.first<<"    -->    "<<entry.second<<endl;
    }
    cout<<endl;
}

const string & transform(unordered_map<string,string> const &trans_map, string const &key)
{
    auto it = trans_map.find(key);
    if(it != trans_map.end()){
        return it->second;
    }
    return key;
}

void word_transform(istream &map_file, istream &input, ostream &output)
{
    auto trans_map = buildMap(map_file);
    showTransMap(trans_map);

    string linetext;
    while(getline(input, linetext)){
        istringstream linestream(linetext);
        string word;
        bool isFirstWord = true;
        while(linestream>>word){
            if(isFirstWord)
                isFirstWord = !isFirstWord;
            else
                output<<" ";
            output<<transform(trans_map,word);
        }
        output<<endl;
    }
}

int main(int argc, char const *argv[])
{
    ifstream in_file(R"(./exercise11_38_单词转换.cpp)");
    if(!in_file){
        throw runtime_error("error: no input file");
    }

    ifstream map_file(R"(./map_file.txt)");
    if(!map_file){
        throw runtime_error("error: no transformation");
    }

    word_transform(map_file, in_file, cout);

    return 0;
}
