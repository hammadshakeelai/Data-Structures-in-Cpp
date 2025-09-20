#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main(){
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
    int num;
    num=153;
    cout<<num%10;
    cout<<(num/10)%10;
    cout<<(num/100)%10;
    //---------------------------------------------------------------
    auto end = high_resolution_clock::now();     // end time
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nExecution time: " << duration.count() << " ms\n";
    return 0;
}