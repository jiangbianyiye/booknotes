#include<iostream>
#include<string>
#include<map>

using namespace std;

void remove_author(multimap<string, string> &authors, const string &author_name)
{
    auto pos = authors.equal_range(author_name);
    authors.erase(pos.first, pos.second);
}

void show_authors(multimap<string,string> &authors){
    for(auto & author : authors){
        cout<<author.first<<"\t"<<author.second<<endl;
    }
}

int main(int argc, char const *argv[])
{
    multimap<string, string> authors;
    authors.insert({"Barth John", "Lost in the Funhouse"});
    authors.insert({"Barth John", "Sot-Weed Factor"});
    authors.insert({"maple", "maple"});

    show_authors(authors);
    cout<<endl;
    remove_author(authors, "Barth John");
    remove_author(authors, " 王二麻子");

    show_authors(authors);

    return 0;
}

/* output:
Barth John      Lost in the Funhouse
Barth John      Sot-Weed Factor
maple   maple

maple   maple
*/