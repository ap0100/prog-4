#ifndef SSO_STRING_H
#define SSO_STRING_H
#include <iostream>
#include <cstdint>
using namespace std;

class SSOString{
    union {
        struct {
            uint8_t sso_flag;
            char txt[15];
        };
        struct {
            char *arr;
            uint16_t _size;
            uint16_t _cap;
        };
    };

    void copy(const SSOString &og);
    bool isSSO() const;

    public:
        SSOString();
        SSOString(const char *str);
        SSOString(const SSOString &og);
        ~SSOString();

        uint16_t size() const;
        uint16_t cap() const;
        SSOString &operator=(const SSOString &og);
        char& operator[](uint16_t index);//read-write
        char operator[](uint16_t index) const;//read only
        char* data();//read-write
        const char* data() const;//read only

        friend SSOString operator+(const SSOString &a, const SSOString &b);
        friend ostream &operator<<(ostream &o, const SSOString &s);
};

#endif //SSO_STRING_H
