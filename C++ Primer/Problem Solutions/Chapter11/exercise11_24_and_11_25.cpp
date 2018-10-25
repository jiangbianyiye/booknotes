#include<iostream>
#include<vector>
#include<map>

using namespace std;

int main(int argc, char const *argv[])
{
    map<int, int> m;
    m[0] = 1;
    //创建关键字为0，元素值为0的键值对，插入m中，之后将元素值赋值为1

    vector<int> v;
//v[0] = 1;
//Segmentation fault (core dumped)

    return 0;
}

