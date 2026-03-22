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

void processArray(vector<int> arr, char type, int arrayNum, ofstream &fout, long long &sumOps, int& batchCount){
    long long operations = 0;

    countSort(arr, operations);  //array sorted

    fout << arrayNum << "," << type << "," << arr.size() << "," 
           << operations << endl;

    sumOps += operations;
    batchCount++;

    if (batchCount == 10){
        fout << "AVG,AVG," <<arr.size()<<","<<(double)sumOps/10 <<"\n";

        batchCount = 0;
        sumOps = 0;
    }
}

int main(){
    ifstream fin("arrays.csv");
    ofstream fout("count_results.csv");

    if (!fin || !fout){
        cout << "file error :/";
        return 0;
    }

    fout << "Array_No,Type,Size,Operations\n";

    int arrayNum =  1;
    int batchCount = 0;

    long long sumOps = 0;

    while (true){
        vector<int> arr;
        char type; int size;
        int number;
        char comma;

        if (!(fin >> type >> comma >> size >> comma)) break;

        while (fin>>number){
            arr.push_back(number);
            if (fin.peek() == ','){
                fin.ignore();
            } else{
                break;
            }
        }

        char ch;
        while (fin.get(ch) && ch != '\n');

        processArray(arr, type, arrayNum, fout, sumOps, batchCount);
        arrayNum++;
    }

    fin.close();
    fout.close();

    cout<<"Count sort completed :)";
    return 0;
}