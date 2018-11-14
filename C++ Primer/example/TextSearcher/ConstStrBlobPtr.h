#pragma once

#include"StrBlob.h"
#include"StrBlobPtr.h"

#include<string>
#include<vector>
#include<memory>

class StrBlob;

class ConstStrBlobPtr{
    
    friend bool eq(const ConstStrBlobPtr&, const ConstStrBlobPtr&);

public:
    ConstStrBlobPtr():curr(0){}
    ConstStrBlobPtr(const StrBlob&, std::size_t sz = 0);

    const std::string& deref() const;
    ConstStrBlobPtr& incr();

private:
    std::shared_ptr<std::vector<std::string> >
        check(std::size_t index, const std::string &msg) const;

    std::weak_ptr<std::vector<std::string> > wptr;
    std::size_t curr;
};