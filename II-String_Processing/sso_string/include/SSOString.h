#ifndef SSO_STRING_H
#define SSO_STRING_H
#include <iostream>
using namespace std;

class SSOString{
    union {
        char txt[16];
        char *arr;
    };
    short _size;
    short _cap;

    void copy(const SSOString &og);
    bool isSSO() const;

    public:
        SSOString();
        SSOString(const char *str);
        SSOString(const SSOString &og);
        ~SSOString();

        short size() const;
        short cap() const;
        SSOString &operator=(const SSOString &og);
        char& operator[](short index);//read-write
        char operator[](short index) const;//read only
        char* data();//read-write
        const char* data() const;//read only

        friend SSOString operator+(const SSOString &a, const SSOString &b);
        friend ostream &operator<<(ostream &o, const SSOString &s);
};

#endif //SSO_STRING_H
