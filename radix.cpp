#include <iostream>
#include <vector>
using namespace std;

void printArray(vector<int>& arr){
    for (int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Counting Sort based on digit (used in Radix Sort)
void countSortDigit(vector<int>& arr, int exp, long long& operations){
    int n = arr.size();

    vector<int> output(n, 0);
    vector<int> count(10, 0); // digits 0–9

    // Count occurrences
    for (int i = 0; i < n; i++){
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
        operations++;
    }

    // Prefix sum
    for (int i = 1; i < 10; i++){
        count[i] += count[i - 1];
        operations++;
    }

    cout << "\nCount Array (after prefix sum): ";
    printArray(count);

    cout << "\nBuilding Output Array:\n";

    // Build output (stable, reverse traversal)
    for (int i = n - 1; i >= 0; i--){
        int digit = (arr[i] / exp) % 10;
        int pos = count[digit] - 1;

        output[pos] = arr[i];
        count[digit]--;

        operations++;

        cout << "Placed " << arr[i] << " at position " << pos << endl;

        cout << "B: ";
        printArray(output);

        cout << "Updated Count: ";
        printArray(count);
    }

    // Copy back
    for (int i = 0; i < n; i++){
        arr[i] = output[i];
        operations++;
    }

    cout << "\nArray after this pass: ";
    printArray(arr);
}

// Radix Sort
void radixSort(vector<int>& arr, long long& operations){
    int maxVal = arr[0];

    // Find max
    for (int i = 1; i < arr.size(); i++){
        if (arr[i] > maxVal) maxVal = arr[i];
        operations++;
    }

    // Apply counting sort for each digit
    for (int exp = 1; maxVal / exp > 0; exp *= 10){
        cout << "\n=============================";
        cout << "\nSorting for Digit Place: " << exp;
        cout << "\n=============================\n";

        countSortDigit(arr, exp, operations);
    }
}

int main(){
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    long long operations = 0;

    cout << "Original Array:\n";
    printArray(arr);

    radixSort(arr, operations);

    cout << "\nFinal Sorted Array:\n";
    printArray(arr);

    cout << "\nTotal Operations: " << operations << endl;

    return 0;
}