#include"ConstStrBlobPtr.h"

bool eq(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{
    auto lsptr = lhs.wptr.lock(), rsptr = rhs.wptr.lock();
    if(lsptr == rsptr){
        if(lsptr == nullptr || lhs.curr == rhs.curr){
            return true;
        }
    }
    return false;
}

ConstStrBlobPtr::ConstStrBlobPtr(const StrBlob& a, std::size_t sz)
    :wptr(a.data), curr(sz)
{
}

const std::string& ConstStrBlobPtr::deref() const
{
    auto sptr = check(curr, "dereference out of range");
    return (*sptr)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    check(curr, "inctrase pass over range");
    ++this->curr;
    return *this;
}

std::shared_ptr<std::vector<std::string> > 
ConstStrBlobPtr::check(std::size_t index, const std::string &msg) const{
    auto sptr = this->wptr.lock();
    if(sptr == nullptr){
        throw std::runtime_error("unbound StrBlobPtr");
    }
    if(curr >= sptr->size()){
        throw std::out_of_range(msg);
    }
    return sptr;
}


/* output:
Hello
World
!
*/