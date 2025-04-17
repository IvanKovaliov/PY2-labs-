#include "ArrayLib.h"

extern "C" __declspec(dllexport) int SumArray(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
