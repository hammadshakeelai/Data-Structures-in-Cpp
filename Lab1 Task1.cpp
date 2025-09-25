#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main(){
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
	int EQ,LQ,CQ;
	int*ptr1,*ptr2,*ptr3;
    cout<<"Enter Expresso Quantity: ";
    cin>>EQ;
    cout<<"Enter Latte Quantity: ";
    cin>>LQ;
    cout<<"Enter Cappucino Quantity: ";
    cin>>CQ;
    cout<<"\n------ Cafe Bill ------\n";
    ptr1 = &EQ;
    ptr2 = &LQ;
    ptr3 = &CQ;
    cout<<"Expresso ("<<*ptr1<<" x 200) = "<<*ptr1*200<<endl;
    cout<<"Latte ("<<*ptr2<<" x 250) = "<<*ptr2*250<<endl;
    cout<<"Cappuccino ("<<*ptr3<<" x 300) = "<<*ptr3*300<<endl;
    cout<<"\n-----------------------";
    cout<<"\nTotal Bill : "<<((*ptr1)*200)+((*ptr2)*250)+((*ptr3)*300)<<endl;
    //---------------------------------------------------------------
    auto end = high_resolution_clock::now();     // end time
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nExecution time: " << duration.count() << " ms\n";
    return 0;
}