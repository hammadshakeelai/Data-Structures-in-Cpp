#include<iostream>
using namespace std;// piece of gold by hammad literally full OG
//goated
void SplitTree(int number){
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
		SplitTree(number-1);//call recursive with even part 
	}
	else if(number%2==0){
		if (number/2==0)
			return;
		cout << "[]" << number/2 << " | " << number/2 << "[]" << endl; 
//		cout<<" "<<number<<endl;
//		cout<<"    / \\"<<endl;
//		cout<<"    "<<number/2<<" "<<number/2<<endl;	
		if (number>1){
			SplitTree(number/2);
			SplitTree(number/2);
		}
	} 
}
void SplitTree_(int number){
    cout << "[]" << number << "[]" << endl;
    SplitTree(number);
}

int main(){
    int n;
    cout<<"enter num: ";
    cin >> n;
	SplitTree_(n);
	
	return 0;
}