#include<iostream>
using namespace std;// piece of gold by hammad literally full OG
//goated
void SplitTree_(int number){
	if (number<=0){//base case 1 or 0 so no recursive
		return;
	}
	if(number%2==1){//if odd print odd-1 == even and 1
        if(number==1)
            return;
		cout << "[]" << number-1 << " | " << 1 << "[]" <<endl; 
//		cout<<"   "<<number<<endl;
//		cout<<"  / \\"<<endl;
//		cout<<" "<<1<<"  ";
		SplitTree_(number-1);//call recursive with even part 
	}
	else if(number%2==0){
		if (number/2==0)
			return;
		cout << "[]" << number/2 << " | " << number/2 << "[]" << endl; 
//		cout<<" "<<number<<endl;
//		cout<<"    / \\"<<endl;
//		cout<<"    "<<number/2<<" "<<number/2<<endl;	
		if (number>1){
			SplitTree_(number/2);
			SplitTree_(number/2);
		}
	} 
}
void SplitTree(int number){
    cout << "[]" << number << "[]" << endl;
    SplitTree_(number);
}
int main(){
    int n;
    cout<<"enter num: ";
    cin >> n;
	SplitTree(n);
	return 0;
}