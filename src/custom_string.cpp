#include <cstring> 
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include "custom_string.h"


void String::ensure_capacity(std::size_t min_size) {
    if (min_size <= capacity_) return;
    capacity_= capacity_>0 ? capacity_*2:1;
    if (min_size > capacity_) capacity_ = min_size;
    char* new_str = new char[capacity_+1];
    std::copy(str_, str_+size_, new_str);
    new_str[size_] = '\0';
    delete[] str_;
    str_=new_str;
}

String::String():String("") {}

String::String(const char* str):
    str_{nullptr}, size_{0}, capacity_{1} {
        if (str) 
        {
            size_= std::strlen(str);
            capacity_ = (size_>0)?size_:1;
            str_=new char[capacity_+1];
            std::copy(str, str+size_, str_);
            str_[size_]='\0';
        }
}

String::String(const String& other): 
    str_{other.capacity_>0 ? new char[other.capacity_+1]:nullptr}, 
    size_{other.size_}, 
    capacity_{other.capacity_} {
        if(str_) 
        {
            std::copy(other.str_, other.str_ + size_, str_); 
            str_[size_] = '\0';
        }
}

String& String::operator=(String other){
    swap(*this, other);
    return *this;
}

String::String(String&& other) noexcept:
    str_{other.str_}, size_{other.size_}, capacity_{other.capacity_} 
    {
        other.str_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
}

String::~String(){
    delete[] str_;
}

void String::append(const char* str){
    if(!str) throw std::invalid_argument("Null poiner in append");
    std::size_t len = std::strlen(str);
    ensure_capacity(size_+len);
    std::copy(str, str+len, str_+size_);
    size_+=len;
    str_[size_]='\0';
}

String String::wrap(size_t width) const {
    if (width == 0 || size_ == 0) return String();

    String res = *this;
    std::size_t line_start = 0;
    std::size_t i = 0;

    while (i < size_) {
        std::size_t word_start = i;
        while (i < size_ && str_[i] != ' ') {
            ++i;
        }
        if (i - line_start > width) {
            if (line_start != word_start) {
                res.str_[word_start - 1] = '\n';
                line_start = word_start;
            }

        }
        while (i < size_ && str_[i] == ' ') {
            i++;
        }
    }
    
    return res;
}


void String::print(std::ostream& os) const noexcept {
    if (str_) {
        os << str_;
    }
}

std::size_t String::find(const char* substr) const {
    if (!substr) throw std::invalid_argument("Null pointer in find");
    
    std::size_t substr_len = std::strlen(substr);
    if (substr_len == 0) return 0;
    if (substr_len > size_) return npos;

    for (std::size_t i = 0; i <= size_ - substr_len; ++i) {
        bool found = true;
        for (std::size_t j = 0; j < substr_len; ++j) {
            if (str_[i + j] != substr[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return npos;
}