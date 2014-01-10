#ifndef KMBASE64_H
#define KMBASE64_H

#include <iostream>

using namespace std;

string base64_encode(const string& input);
string base64_encode(unsigned char const* , unsigned int len);
string base64_decode(string const& s);

#endif // KMBASE64_H
