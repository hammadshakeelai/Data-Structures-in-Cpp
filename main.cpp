#include<iostream>
using namespace std;
int main(){
    int num,fi=0;
    cin>>num;
    fi+=num%100;
    for(int i=10;i<=num*10;i*=10){
        fi+=num/i;
    }

    return 0;
}
