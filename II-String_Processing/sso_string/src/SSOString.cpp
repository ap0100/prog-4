#include "../include/SSOString.h"
#include <iostream>
#include <cstdint>
using namespace std;

static uint16_t strlen(const char *s) {
    if (!s) return 0;
    uint16_t len=0;
    while (s[len]!='\0') len++;
    return len;
}

static void strcpy(char *dst, const char *src) {
    uint16_t index=0;
    while (src[index]!='\0') {
        dst[index]=src[index];
        index++;
    }
    dst[index]='\0';
}

SSOString::SSOString() {
    this->sso_flag=1;
    this->txt[0]='\0';
}

SSOString::~SSOString() {
    if (!this->isSSO()) delete [] this->arr;
}

SSOString::SSOString(const char *str) {
    uint16_t len=strlen(str);

    if (len<=14) {
        this->sso_flag=len*2+1;
        if (str) strcpy(this->txt,str);
        else this->txt[0]='\0';
    }else {
        this->arr=new char[len+1];
        strcpy(this->arr,str);
        this->_size=len;
        this->_cap=len;
    }
}

void SSOString::copy(const SSOString &og) {
    if (og.isSSO()) {
        this->sso_flag=1;
        strcpy(this->txt,og.txt);
    }else {
        this->_size=og._size;
        this->_cap=og._cap;
        this->arr=new char[this->_cap+1];
        strcpy(this->arr,og.arr);
    }
}

SSOString::SSOString(const SSOString& og) { this->copy(og); }

SSOString& SSOString::operator=(const SSOString &og) {
    if (this!=&og) {
        if (!this->isSSO()) delete [] this->arr;
        this->copy(og);
    }
    return *this;
}

bool SSOString::isSSO() const { return this->sso_flag%2==1; }

uint16_t SSOString::size() const { return this->isSSO() ? (this->sso_flag/2) : this->_size; }

uint16_t SSOString::cap() const { return this->isSSO() ? 14 : this->_cap; }

const char* SSOString::data() const { return !this->isSSO() ? this->arr : this->txt; }
char* SSOString::data() { return !this->isSSO() ? this->arr : this->txt; }

char& SSOString::operator[](uint16_t index) { return this->data()[index]; }
char SSOString::operator[](uint16_t index) const { return this->data()[index]; }

ostream& operator<<(ostream &o, const SSOString &s) {
    o << s.data();
    return o;
}

SSOString operator+(const SSOString &a, const SSOString &b) {
    SSOString c;
    uint16_t len=a.size()+b.size();

    if (len<=14) {
        c.sso_flag=static_cast<uint8_t>((len<<1)|1);
        strcpy(c.txt,a.data());
        strcpy(c.txt+a.size(),b.data());
        return c;
    }
    c.arr=new char[len+1];
    strcpy(c.arr,a.data());
    strcpy(c.arr+a.size(),b.data());
    c._size=len;
    c._cap=len;
    return c;
}
