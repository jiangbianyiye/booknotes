#include"StrBlob.h"

StrBlob::StrBlob():
    data(std::make_shared<std::vector<std::string> >() )
{
    return;
}

StrBlob::StrBlob(std::initializer_list<std::string> il):
    data(std::make_shared<std::vector<std::string> >(il) )
{
    return;
}

std::string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return this->data->front();
}

const std::string& StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return this->data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return this->data->back();
}

const std::string& StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return this->data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_bakc on empty StrBlob");
    this->data->pop_back();
}

void StrBlob::check(size_type i, const std::string &msg) const
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

StrBlobPtr StrBlob::begin()
{ 
    return StrBlobPtr(*this); 
}

StrBlobPtr StrBlob::end()
{ 
    return StrBlobPtr(*this, this->data->size());
}

ConstStrBlobPtr StrBlob::cbegin()
{ 
    return ConstStrBlobPtr(*this); 
}

ConstStrBlobPtr StrBlob::cend()
{ 
    return ConstStrBlobPtr(*this, this->data->size());
}


