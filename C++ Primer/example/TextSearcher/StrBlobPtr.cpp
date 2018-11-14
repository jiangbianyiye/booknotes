#include"StrBlobPtr.h"

bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    auto lsptr = lhs.wptr.lock(), rsptr = rhs.wptr.lock();
    if(lsptr == rsptr){
        return lsptr==nullptr || lhs.curr==rhs.curr;
    }
    return false;
}

StrBlobPtr::StrBlobPtr(StrBlob &a, std::size_t sz)
        :wptr(a.data), curr(sz) 
{
}

std::string& StrBlobPtr::deref() const
{
    auto sptr = this->check(curr, "dereference pass end");
    return (*sptr)[this->curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increament pass end of StrBlobPtr");
    ++this->curr;
    return *this;
}

std::shared_ptr<std::vector<std::string> > 
StrBlobPtr::check(std::size_t index, const std::string& msg) const
{
    auto sptr = this->wptr.lock();
    if(!sptr){
        throw std::runtime_error("unbound StrBlobPtr");
    }
    if(index >= sptr->size()){
        throw std::out_of_range(msg);
    }
    return sptr;
}

