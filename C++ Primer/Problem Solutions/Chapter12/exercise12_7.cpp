#include<iostream>
#include<memory>
#include<vector>

using namespace std;

shared_ptr<vector<int> > new_vector()
{
    return make_shared<vector<int> >();
}

void read_to_vector(shared_ptr<vector<int> > spv)
{
    int num;
    while(cin>>num){
        spv->push_back(num);
    }
}

void print_vector(shared_ptr<vector<int> > spv)
{
    for(const auto &num : *spv){
        cout<<num<<" ";
    }
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    shared_ptr<vector<int> > spv = new_vector();
    read_to_vector(spv);
    print_vector(spv);
    return 0;
}