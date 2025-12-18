#include<iostream>
using namespace std;
int main(){
    // a^b^b == a
    // make a^b encrypt
    int a = 69;
    int b = 420;
    a ^= b;
    b ^= a;
    a ^= b;

    return 0;
}