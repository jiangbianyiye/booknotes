## 28. 实现 strStr()

```c++
class Solution {
public:
    int strStr(string haystack, string needle) {
        if ( haystack.size() < needle.size() ) {
            return -1;
        }
        for (string::size_type pos = 0; pos < haystack.size() - needle.size() + 1; ++pos) {
            bool isPair = true;
            for (string::size_type pairPos = 0; pairPos < needle.size(); ++pairPos) {
                if (haystack[pos + pairPos] != needle[pairPos]) {
                    isPair = false;
                    break;
                }
            }
            if (isPair) {
                return pos;
            }
        }
        return -1;
    }
};
```

> TODO:
> - 双指针法 
> - KMP https://zhuanlan.zhihu.com/p/83334559
