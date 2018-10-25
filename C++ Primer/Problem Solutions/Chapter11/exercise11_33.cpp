#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<map>

using namespace std;

map<string, string> buildMap(istream& map_file)
{
    map<string, string> trans_map;
    string key, value;
    while(map_file>>key && getline(map_file, value)){
        if(value.size()>1)
            trans_map[key] = value.substr(1);
        else
            throw runtime_error("no rule for "+key);
    }
    return trans_map;
}

const string & transform(map<string, string> &trans_map, const string &word)
{
    auto it = trans_map.find(word);
    if(it != trans_map.end()){
        return it->second;
    }
    return word;
}

void word_transform(istream &map_file, istream &input, ostream &output)
{
    auto trans_map = buildMap(map_file);
    string linetext;
    while(getline(input, linetext)){
        istringstream linestream(linetext);
        string word;
        bool isFirstWord = true;
        while(linestream>>word){
            if(isFirstWord)
                isFirstWord = false;
            else
                cout<<" ";
            output<<transform(trans_map, word);
        }
        cout<<endl;
    }
}

int main(int argc, char const *argv[])
{
    fstream in_file(R"(./exercise11_33.cpp)");
    fstream map_file(R"(./map_file.txt)");

    word_transform(map_file, in_file, cout);

    return 0;
}
