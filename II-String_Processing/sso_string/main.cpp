#include "include/SSOString.h"
#include<iostream>
using namespace std;

int main() {
    //basic get funcs & c-tor
    //actual short strings, saved directly in the SSOString object
    SSOString a("Hello");
    SSOString b(", World!");
    cout << "a: " << a.data() << " | " << a.size() << " | " << a.cap() << '\n'
    << "b: " << b << " | " << b.size() << " | " << b.cap() << '\n';

    //concatenate
    SSOString c=a+b;
    cout << "a+b: " << c << " | " << c.size()
         << " | " << c.cap() << '\n';

    //long string
    SSOString d("This string is way too long to fit in the buffer.");
    cout << "d: " << d << " | " << d.size() << " | " << d.cap() << '\n';

    //copy c-tor
    SSOString e(d);
    //operator [], read-write
    e[0]='X';
    cout << "e: " << e << '\n'
    << "d unchanged: " << d << '\n';

    //operator =
    SSOString f;
    f=c;
    cout << "f: " << f << '\n';


    return 0;
}