#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(){
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
	int NumberOfPlayers;
	
	cout<<"how many players are participating: ";
	cin>>NumberOfPlayers;
	int *ptrArray= new int[NumberOfPlayers];
	for(int i=0;i<NumberOfPlayers;i++){
		cout<<"Enter Player Score of Player[ "<<i+1<<" ]: ";
		cin>>ptrArray[i];
	}
	cout<<"\n\n|Now Displaying Player Score|\n";
	for(int i=0;i<NumberOfPlayers;i++){
		cout<<"Score of Player[ "<<i+1<<" ] :";
		cout<<ptrArray[i]<<endl;
	}
	delete [] ptrArray;
    //---------------------------------------------------------------
    auto end = high_resolution_clock::now();     // end time
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nExecution time: " << duration.count() << " ms\n";
    return 0;
}