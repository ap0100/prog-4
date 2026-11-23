#include "../include/SSOString.h"
#include <iostream>
using namespace std;

static int strlen(const char *s) {
    int len=0;
    while (s[len]!='\0') len++;
    return len;
}

static void strcpy(char *dst, const char *src) {
    int index=0;
    while (src[index]!='\0') {
        dst[index]=src[index];
        index++;
    }
    dst[index]='\0';
}

SSOString::SSOString() {
    this->_size = 0;
    this->_cap = 15;
    this->txt[0] = '\0';
}

SSOString::~SSOString() {
    if (!this->isSSO()) delete [] this->arr;
}

SSOString::SSOString(const char *str) {
    int len=strlen(str);
    this->_size=len;

    if (len<=15) {
        this->_cap=15;
        strcpy(this->txt,str);
    }else {
        this->_cap=len;
        this->arr=new char[this->_cap+1];
        strcpy(this->arr,str);
    }
}

void SSOString::copy(const SSOString &og) {
    this->_size=og._size;

    if (og.isSSO()) {
        this->_cap=15;
        strcpy(this->txt,og.txt);
    }else {
        this->_cap=og._cap;
        this->arr=new char[this->_cap+1];
        strcpy(this->arr,og.arr);
    }
}

SSOString::SSOString(const SSOString &og) { this->copy(og); }

SSOString& SSOString::operator=(const SSOString &og) {
    if (this!=&og) {
        if (!isSSO()) delete [] this->arr;
        this->copy(og);
    }
    return *this;
}

short SSOString::size() const { return this->_size; }

short SSOString::cap() const { return this->_cap; }

bool SSOString::isSSO() const { return this->_cap<=15; }

const char* SSOString::data() const { return !isSSO() ? this->arr : this->txt; }
char* SSOString::data() { return !isSSO() ? this->arr : this->txt; }

char& SSOString::operator[](short index) { return this->data()[index]; }
char SSOString::operator[](short index) const { return this->data()[index]; }

ostream& operator<<(ostream &o, const SSOString &s) {
    o << s.data();
    return o;
}

SSOString operator+(const SSOString &a, const SSOString &b) {
    SSOString c;
    int size=a.size()+b.size();

    if (size<=15) {
        strcpy(c.txt,a.data());
        strcpy(c.txt,b.data());
        c._size=size;
        c._cap=15;
        return c;
    }
    c.arr=new char[size+1];
    strcpy(c.arr,a.data());
    strcpy(c.arr,b.data());
    c._size=size;
    c._cap=size;
    return c;
}
