#include"../../example/TextSearcher/StrBlob.h"

#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the", };
        b1 = b2;
        b2.push_back("about");
        cout << b2.size() << endl;
    }
    cout << b1.size() <<endl;
    cout << b1.front() << " " << b1.back() <<endl;

    const StrBlob b3 = b1;
    cout<< b3.front() << " " << b3.back() << endl;

    return 0;
}

/* output:
4
4
a about
a about
*/