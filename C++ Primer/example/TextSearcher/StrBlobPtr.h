#pragma once

#include"StrBlob.h"

#include<string>
#include<vector>
#include<memory>

class StrBlob;

class StrBlobPtr{
    friend bool eq(const StrBlobPtr&, const StrBlobPtr&);
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob &a, std::size_t sz = 0);

    std::string& deref() const; //返回值是const的？ 否
    StrBlobPtr& incr();

private:
    std::shared_ptr<std::vector<std::string> > 
        check(std::size_t index, const std::string &msg) const;
    
    std::weak_ptr<std::vector<std::string> > wptr;
    std::size_t curr;
};

