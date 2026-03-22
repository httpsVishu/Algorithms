#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

void printArray(vector<int>& arr){
    for (int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void countSort(vector<int>& arr, long long& operations){
    if (arr.empty()) return;

    int maxVal = arr[0];
    int minVal = arr[0];

    for (int i = 1; i < arr.size(); i++){
        operations++;
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);
    vector<int> output(arr.size(), -1);

    for (int i = 0; i < arr.size(); i++){ //count array values
        count[arr[i] - minVal]++;
        operations++;
    }

    for (int i = 1; i < range; i++){
        count[i] += count[i-1];
        operations++;
    }

    cout << "\n Final Count Array (after prefix sum): \n";
    cout << "Count: ";
    printArray(count);

    cout << "\n Output Array (B): \n";

    for (int i = arr.size() - 1; i >= 0; i--){
        int pos = count[arr[i] - minVal] - 1;
        output[pos] = arr[i];
        count[arr[i] - minVal]--;
        operations++;

        cout << "\n Placed " << arr[i] << " at position " << pos << endl;

        cout << "B: ";
        printArray(output);

        cout << "Updated Count: ";
        printArray(count);
    }

    for (int i = 0; i < arr.size(); i++){
        arr[i] = output[i];
        operations++;
    }
}

int main(){
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1}; 

    long long operations = 0;

    cout << "Original Array: "<< endl;
    printArray(arr);

    countSort(arr, operations);

    cout << "\n Total Operations: " << operations << endl;

    return 0;
}