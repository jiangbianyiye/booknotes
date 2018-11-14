#include<memory>

using namespace std;

int main(int argc, char const *argv[])
{
    unique_ptr<int> a(new int(1));
    unique_ptr<int> b(a);
    unique_ptr<int> c;
    c = a;
    return 0;
}

/* error output:
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
     unique_ptr<int> b(a);
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
     c = a;
*/