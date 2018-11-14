#include<iostream>
#include<vector>

using namespace std;

vector<int> *new_vector()
{
    return new(nothrow) vector<int>;
}

void read_ints(vector<int> *pv)
{
    int num;
    while(cin>>num){
        pv->push_back(num);
    }
}

void print_vector(vector<int> *pv)
{
    for(const auto &num : *pv){
        cout<<num<<" ";
    }
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    vector<int> *pv = new_vector();
    if(pv == nullptr){
        cout << "内存分配失败" <<endl;
        return -1;
    }
    read_ints(pv); 
    print_vector(pv);   

    delete pv; pv=nullptr;

    return 0;
}
