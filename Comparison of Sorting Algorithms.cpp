/*
 * HackerRank link: N/A
 * Title: hw7_2.cpp
 * Abstract: displays the performance of three different sorting algorithms (= insertion sort, mergesort, and quick sort) on the screen.
 * Author: Jonathan Welham
 * ID: 6781
 * Date: 03/27/2020
 */

#include <iostream>
#include <ctime>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/insertion-sort/
void insertionSort(int arr[], int n);

//https://www.geeksforgeeks.org/merge-sort/
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);

//https://www.geeksforgeeks.org/quick-sort/
void swap(int* a, int* b);
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);

//My custom output function
void displayTime(int arr1[], int arr2[], int arr3[], int inputSize, int order);

void refill(int arr1[], int arr2[], int arr3[], int inputSize, int order);

//Globals used to measure time from <ctime>
clock_t _START, _END;

bool _FILLED = false;

int main() {

    //Size of dynamic array
    int inputSize;

    //Display order
    int order;

    cout << "Enter input size: ";
    cin >> inputSize;
    cout << "========== Select Order of Input Numbers ==========\n";
    cout << "     1. Ascending Order\n";
    cout << "     2. Descending Order\n";
    cout << "     3. Random Order\n";
    cout << "Choose order: ";
    cin >> order;
    cout << "============================================================\n";

    //create dynamic array
    int *arr1 = new int[inputSize];
    int *arr2 = new int[inputSize];
    int *arr3 = new int[inputSize];

    if(order == 1) {
        cout << "Generate input data in ascending order . . .\n";
    } else if (order == 2){
        cout << "Generate input data in descending order . . .\n";
    } else {
        cout << "Generate input data in Random order . . .\n";
    }

    refill(arr1, arr2, arr3, inputSize, order);

    cout << "Done.\n";
    cout << "============================================================\n\n";

    displayTime(arr1, arr2, arr3, inputSize, order);

    return 0;

} //END PROGRAM

void refill(int arr1[], int arr2[], int arr3[], int inputSize, int order){
    /*
     * These are just value holders for each array. Once the arrays go through the sorting methods they are then sorted
     * which makes the second and third run useless. If _FILLED is true then we just refill the arrays to what the original
     * values were at each index BEFORE sorting.
     */

    int arr1ValueHolder[inputSize];
    int arr2ValueHolder[inputSize];
    int arr3ValueHolder[inputSize];


    if(_FILLED){ //Refill
        for (int i = 0; i < inputSize; i++) {
            arr1[i] = arr1ValueHolder[i];
            arr2[i] = arr2ValueHolder[i];
            arr3[i] = arr3ValueHolder[i];
        }
    } else {
        if (order == 1) {
            for (int i = 0; i < inputSize; i++) {
                arr1[i] = i;
                arr2[i] = i;
                arr3[i] = i;
                arr1ValueHolder[i] = arr1[i];
                arr2ValueHolder[i] = arr2[i];
                arr3ValueHolder[i] = arr3[i];
            }
        } else if (order == 2) {
            int temp = 0;
            for (int i = inputSize; i > 0; i--) {
                arr1[temp] = i;
                arr2[temp] = i;
                arr3[temp] = i;
                arr1ValueHolder[temp] = arr1[temp];
                arr2ValueHolder[temp] = arr2[temp];
                arr3ValueHolder[temp] = arr3[temp];
                temp++;
            }
        } else {
            int random;
            srand(time(NULL));
            for (int i = 0; i < inputSize + 1; i++) {
                random = (rand() % 100000) + 1;
                arr1[i] = random;
                arr2[i] = random;
                arr3[i] = random;
                arr1ValueHolder[i] = arr1[i];
                arr2ValueHolder[i] = arr2[i];
                arr3ValueHolder[i] = arr3[i];
            }
        }
        _FILLED = true;
    }
}

void displayTime(int arr1[], int arr2[], int arr3[], int inputSize, int order){

    double quickAvg;
    double mergeAvg;
    double insertAvg;

    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            cout << "========================== 1st Run =========================\n";
        } else if (i == 1) {
            cout << "========================== 2nd Run =========================\n";
        } else if (i == 2) {
            cout << "========================== 3rd Run =========================\n";
        }

        _START = clock();
        insertionSort(arr1, inputSize);
        _END = clock();
        double insertTime = double(_END - _START) / (double(CLOCKS_PER_SEC) * 1000);
        insertAvg += insertTime;
        cout << "Insertion sort: " << fixed << insertTime << setprecision(5) << " milliseconds\n";


        _START = clock();
        mergeSort(arr2, 0, inputSize - 1);
        _END = clock();
        double mergeTime = double(_END - _START) / (double(CLOCKS_PER_SEC) * 1000);
        mergeAvg += mergeTime;
        cout << "Merge sort:     " << fixed << mergeTime << setprecision(5) << " milliseconds\n";

        _START = clock();
        quickSort(arr3, 0, inputSize - 1);
        _END = clock();
        double quickTime = double(_END - _START) / (double(CLOCKS_PER_SEC) * 1000);
        quickAvg += quickTime;
        cout << "Quick sort:     " << fixed << quickTime << setprecision(5) << " milliseconds\n\n";

        //Refills the array with the original values BEFORE sort at each index
        refill(arr1, arr2, arr3, inputSize, order);
    }

    insertAvg /= 3;
    mergeAvg /= 3;
    quickAvg /= 3;

    cout << "========================== Ranking =========================\n";
    cout << "(1) ";
    if(insertAvg < mergeAvg && insertAvg < quickAvg){
        cout << "Insertion sort\n";
    } else if(mergeAvg < insertAvg && mergeAvg < quickAvg){
        cout << "Merge sort\n";
    } else if(quickAvg < insertAvg && quickAvg < mergeAvg){
        cout << "Quick sort\n";
    }

    cout << "(2) ";
    if((insertAvg > quickAvg && insertAvg < mergeAvg) || (insertAvg > mergeAvg && insertAvg < quickAvg)){
        cout << "Insertion sort\n";
    } else if((mergeAvg > quickAvg && mergeAvg < insertAvg) || (mergeAvg > insertAvg && mergeAvg < quickAvg)){
        cout << "Merge sort\n";
    } else if((quickAvg > insertAvg && quickAvg < mergeAvg) || (quickAvg > mergeAvg && quickAvg < insertAvg)){
        cout << "Quick sort\n";
    }

    cout << "(3) ";
    if(insertAvg > mergeAvg && insertAvg > quickAvg){
        cout << "Insertion sort\n";
    } else if(mergeAvg > insertAvg && mergeAvg > quickAvg){
        cout << "Merge sort\n";
    } else if(quickAvg > insertAvg && quickAvg > mergeAvg){
        cout << "Quick sort\n";
    }

    cout << "============================================================\n";

}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    /* create temp arrays */
    int L[n1], R[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
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
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

