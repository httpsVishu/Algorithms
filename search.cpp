#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bubbleSort(vector<int>& arr){
    int n = arr.size();
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i-1; j++){
            if (arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

int linearSearch(const vector<int>& arr, int target, int& comparisons){
    comparisons = 0;
    for (int i = 0; i < arr.size(); i++){
        comparisons++;
        if (arr[i] == target){
            return i;
        }
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int target, int& comparisons){
    comparisons = 0;
    int left = 0, right = arr.size()-1;

    while (left <= right){
        int mid = left + (right-left)/2;
        comparisons++;
        if (arr[mid] == target){
            return mid;
        }
        else if (arr[mid] < target){
            left = mid+1;
        }
        else{
            right = mid-1;
        }
    }
    return -1;
}

void compareSearches(vector<int> arr, int size, int target){
    cout<<"Provided Array: [";
    for (int i = 0; i < size; i++){
        cout<<arr[i];
        if (i != size-1) cout<<" , ";
    }
    cout<<"]"<<endl;

    int linearComp = 0;
    int binaryComp = 0;

    int linearIndex = linearSearch(arr, target, linearComp);

    bubbleSort(arr);
    int binaryIndex = binarySearch(arr, target, binaryComp);

    cout<<"RESULTS: "<<endl;
    cout<<"Linear Search Comparisons: "<<linearComp<<endl;
    cout<<"Binary Search Comparisons: "<<binaryComp<<endl;

    if (linearIndex != -1){
        cout<<"Target found in Linear Search at index: "<<linearIndex<<endl;
    }else{
        cout<<"Target NOT found in Linear Search, index: -1"<<endl;
    }

    if (binaryIndex != -1){
        cout<<"Target found in Binary Search at index: "<<binaryIndex<<endl;
    }else{
        cout<<"Target NOT found in Binary Search, index: -1"<<endl;
    }
}

int main(){
    vector<int> arr;
    int size, elem, target;
    cout << "Enter the number of elements in array: ";
    cin >> size;
    for (int i =0; i < size; i++){
        cout<<"Enter element "<<i+1<<": ";
        cin>>elem;
        arr.push_back(elem);
    }

    cout<<"Enter the target: ";
    cin>>target;

    compareSearches(arr, size, target);

    return 0;
}