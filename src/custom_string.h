#pragma once
#include <cstddef>
#include <utility>
#include <iostream>
class String {
    private:
        char* str_;
        std::size_t size_;
        std::size_t capacity_;
        
        void ensure_capacity(std::size_t min_size);
        friend void swap(String& first, String& second) noexcept
        {
            using std::swap;
            swap(first.str_, second.str_);
            swap(first.size_, second.size_);
            swap(first.capacity_, second.capacity_);
        }

    public:
        String();
        explicit String(const char* str);
        String(const String& other);
        String& operator=(String other);
        String(String&& other) noexcept;
        ~String();
        void append(const char* str);
        String wrap(size_t width) const;
        std::size_t size() const {return size_;}
        std::size_t capacity() const {return capacity_;}
        void print(std::ostream& os) const noexcept;
        static constexpr std::size_t npos = -1;
        std::size_t find(const char* substr) const;
};
