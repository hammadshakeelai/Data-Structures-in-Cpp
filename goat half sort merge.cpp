#include <iostream>

using namespace std;
void print(int arr[],int size){
	cout<<"[ ";
	for(int i=0;i<size;i++){
		cout<<arr[i];
		if(i!=size-1){
			cout<<", ";
		}
	}
	cout<<" ]"<<endl;
}
void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i; j < size - 1; j++)
        {
            if (arr[min] > arr[j + 1])
                min = j + 1;
            print(arr,size);
        }
        if (i != min)
            swap(arr[min], arr[i]);
        
    }
}
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    const int n1 = m - l + 1;
    const int n2 = r - m;

    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l == r) // if one element, return (sorted)
        return;

    int m = (l + r) / 2;

    // Sort first and second halves
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
}
void bubbleSort(int arr[],int size)
{
    for (int i = 0; i < (size - 1); i++)
    {
        for (int j = 1; j < (size - i); j++)
        {
            if (arr[j - 1] > arr[j])
                swap(arr[j - 1], arr[j]);
            print(arr,size);
        }
    }
}

int main(int argc, char** argv) {
//	int l=0;
//	int r=8;
//	int mid =(l+r)/2;
	const int size = 9;
	int arr[size]={9,8,7,10,5,4,3,2,1};
	print(arr,9);

//	for(int i=0;i<size/2;i++){
//		selectionSort(arr,i+1);
//		bubbleSort(arr+(size-i-1),i+1)
//	}

//	selectionSort(arr,l,mid);

//	selectionSort(arr,l,mid);
//	bubbleSort(arr,mid+1,r);

	int R[(size/2)+1];
	for (int i=0;i<(size/2)+1;i++){
		R[i] = arr[(size/2)+i];
	}
	print(R,(size/2)+1);
	
	selectionSort(arr,size/2);
	bubbleSort(R,(size/2)+1);
	for (int i=0;i<(size/2)+1;i++){
		arr[(size/2)+i] = R[i];
	}
	print(arr,size);
	//---------------------------------
//	bubbleSort(arr,size);
//	selectionSort(arr,size);
// Do Merge Sortint i, j, k;
    

    int L[size/2];// R

    /* Copy data to temp arrays L[] and R[] */
    for (int i = 0; i < size/2; i++)
        L[i] = arr[i];
    
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < (size/2) && j < ((size/2)+1))
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        print(arr,size);
    }

    while (i < (size/2))
    {
        arr[k] = L[i];
        i++;
        k++;
        print(arr,size);
    }

    while (j < ((size/2)+1))
    {
        arr[k] = R[j];
        j++;
        k++;
        print(arr,size);
    }
    print(arr,size);
	//---------------------------------
	return 0;
}