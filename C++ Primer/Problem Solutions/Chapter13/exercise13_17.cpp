#include<iostream>

class numbered{
private:
    static int seq;
public:
    numbered(){mysn = seq++;}
    //13.15
    numbered(numbered &n){mysn = seq++;}
    int mysn;
};

int numbered::seq = 0;

using namespace std;

//void f(numbered s)
//13.16
void f(const numbered& s)
{
    cout << s.mysn <<endl;
}

int main(int argc, char const *argv[])
{
    numbered a, b = a, c = b;
    f(a); f(b), f(c);
    return 0;
}

/* 13.14 output:
0
0
0
*/

/* 13.15 output:
3
4
5
*/

/* 1.16 output:
0
1
2
*/


