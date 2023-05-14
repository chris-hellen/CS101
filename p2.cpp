#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

void merge(int a[], int a1[], int a2[], int n){

    int n1 = n/2, n2 = n-n/2;
    int p1 = 0, p2 = 0, i = 0;

    while (p1 < n1 && p2 < n2){
        a[i++] = a1[p1]<a2[p2] ? a1[p1++] : a2[p2++];
    }

    while (p1 < n1){
        a[i++] = a1[p1++];
    }

    while (p2 < n2){
        a[i++] = a2[p2++];
    }
}

void mergesort(int a[], int n){
    if (n <= 1){
        return;
    }

    int *a1 = new int [n/2];
    int *a2 = new int[n-(n/2)];

    for (int i = 0; i < n/2; i++){
        a1[i] = a[i];
    }

    for (int i = n/2; i<n; i++){
        a2[i-n/2] = a[i];
    }

    mergesort(a1, n/2);
    mergesort(a2, n-n/2);

    merge(a, a1, a2, n);
}

int partition(string strings[], int i, int k) {
    int midpoint = i + (k - i) / 2;
    string pivot = strings[midpoint];

    int l = i;
    int h = k;
    while (1) {
        while (strings[l] < pivot){
            ++l;
        }

        while (strings[h] > pivot){
            --h;
        }

        if (l >= h){
            return h;
        }

        swap(strings[l], strings[h]);
        ++l;
        --h;
   }
}

void quicksort(string strings[], int i, int k){
    if (i >= k){
        return;
    }
    int j = partition(strings, i, k);

    quicksort(strings, i, j);
    quicksort(strings, j + 1, k);

}

int main(int argc, char *argv[]){

    string fileType = argv[1];

    ifstream infile1(argv[2]);
    ifstream infile2(argv[3]);

    if (fileType == "i"){
        int arr1[20000];
        int arr2[20000];
        int currentNum, arr1Size = 0, arr2Size = 0;

        while(infile1 >> currentNum){
            arr1[arr1Size] = currentNum;
            arr1Size++;
        }

        mergesort(arr1, arr1Size);

        while(infile2 >> currentNum){
            arr2[arr2Size] = currentNum;
            arr2Size++;
        }

        mergesort(arr2, arr2Size);

        for (int i = 0; i < arr1Size; i++){
            for (int j = 0; j < arr2Size; j++){
                if (arr1[i] == arr2[j] && arr2[j] != arr2[j - 1] && arr1[i] != arr1[i - 1]){
                    cout << arr2[j] << endl;
                }
            }
        }
    }

    if (fileType == "s"){
        string arr1[20000];
        string arr2[20000];

        string currentStr;
        int arr1Size = 0, arr2Size = 0;

        while(infile1 >> currentStr){
            arr1[arr1Size] = currentStr;
            arr1Size++;
        }

        quicksort(arr1, 0, arr1Size);

        while(infile2 >> currentStr){
            arr2[arr2Size] = currentStr;
            arr2Size++;
        }

        quicksort(arr2, 0, arr2Size);

        for (int i = 0; i < arr1Size; i++){
            for (int j = 0; j < arr2Size; j++){
                if (arr1[i] == arr2[j] && arr2[j] != arr2[j - 1] && arr1[i] != arr1[i - 1]){
                    cout << arr2[j] << endl;
                }
            }
        }
    }

}