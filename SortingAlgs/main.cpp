#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

int PartitionMidPoint(int numbers[], int i, int k) {
   int low;
   int midpoint;
   int high;
   int pivot;
   int temp;
   bool found;

   //The middle element is a pivot
   midpoint = i + (k - i) / 2;
   pivot = numbers[midpoint];

   found = false;
   low = i;
   high = k;

   while (!found) {
      while (numbers[low] < pivot) {
         low++;
      }
      while (pivot < numbers[high]) {
         high--;
      }
      if (low >= high) {
         found = true;
      }
      else {
         temp = numbers[low];
         numbers[low] = numbers[high];
         numbers[high] = temp;

         low++;
         high--;
      }
   }
   return high;
}

int PartitionMedianOfThree(int numbers[], int i, int k) {
    
    int low;
    int high;
    int medIndex;
    int pivot;
    int temp;
    bool found;

    int toSort[] = {numbers[i], numbers[(i+k)/2], numbers[k]};
    sort(toSort, toSort+3);
    if(toSort[1] == numbers[i])
    medIndex = i;
    else if(toSort[1] == numbers[k])
        medIndex = k;
    else
        medIndex = (i+k)/2;
    pivot = numbers[medIndex];

    found = false;
    low = i;
    high = k;

    while (!found) {
      while (numbers[low] < pivot) {
         low++;
      }
      while (pivot < numbers[high]) {
         high--;
      }
      if (low >= high) {
         found = true;
      }
      else {
          //Swap low and high
         temp = numbers[low];
         numbers[low] = numbers[high];
         numbers[high] = temp;

         low++;
         high--;
      }
   }
   return high;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
   int j;
   // Base case
   if (i >= k) {
      return;
   }

   // Partition data in array
   j = PartitionMidPoint(numbers, i, k);

   // Sort low partition (i to j) and high partition (j + 1 to k) (Recursively)
   Quicksort_midpoint(numbers, i, j);
   Quicksort_midpoint(numbers, j + 1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
    int j;
    //Base case
    if (i >= k) {
        return;
    }

    j = PartitionMedianOfThree(numbers, i, k);
    Quicksort_medianOfThree(numbers, i, j);
    Quicksort_medianOfThree(numbers, j + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
   int i;
   int j;
   int temp;      

   for (i = 1; i < numbersSize; ++i) {
      j = i;
      while (j > 0 && numbers[j] < numbers[j - 1]) {

         // Swap numbers[j] and numbers[j - 1]
         temp = numbers[j];
         numbers[j] = numbers[j - 1];
         numbers[j - 1] = temp;
         j--;
      }
   }
}

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

//Provided by zyBooks
void fillArrays(int arr1[], int arr2[],int arr3[]) {
    for(int i = 0; i < NUMBERS_SIZE; ++i) {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int main()
{
    srand(time(NULL))
    int arr1[NUMBERS_SIZE], arr2[NUMBERS_SIZE], arr3[NUMBERS_SIZE];
    fillArrays(arr1, arr2, arr3);

    clock_t start1 = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    clock_t end1 = clock();
    int elapsedTime1 = (end1 - start1) / CLOCKS_PER_MS;
    cout << elapsedTime1 << endl;

    for(int i = 0; i < 10; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    clock_t start2 = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    clock_t end2 = clock();
    int elapsedTime2 = (end2 - start2) / CLOCKS_PER_MS;
    cout << elapsedTime2 << endl;

    for(int i = 0; i < 10; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    clock_t start3 = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    clock_t end3 = clock();
    int elapsedTime3 = (end3 - start3) / CLOCKS_PER_MS;
    cout << elapsedTime3 << endl;

    for(int i = 0; i < 10; i++) {
        cout << arr3[i] << " ";
    }
    cout << endl;

    return 0;
}
