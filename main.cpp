#include <iostream>
#include <cstdlib>
using namespace std;

void print(float *, int);
void print(int *, int);
void print(char *, int);
void generic_swap(void *, void *, std::size_t);
bool ascendInt(void*, void*);
bool descendInt(void*, void*);
bool ascendFloat(void*, void*);
bool descendFloat(void*, void*);
bool ascendChar(void*, void*);
bool descendChar(void*, void*);
int partition(void*, int, int, int, int, bool(*) (void *, void *));
void qsort(void *, int, int, int, bool(*) (void *, void *));


int main()
{
    int arr[8] = {4, 8, 1, 5, 3, 2, 8, 9};
    float arr_f[6] = {4.3, 6.2, 76.54, 23, 12.3, 4.7};
    char arr_c[4] = {'a', 'b', 'f', 'c'};

    bool (*operations[6]) (void *, void *) = {ascendInt, descendInt,
                                              ascendFloat, descendFloat,
                                              ascendChar, descendChar};
    int byteSize = sizeof(int);
    qsort(arr, 0, 7, sizeof(int), operations[0]);
    print(arr, 8);
    qsort(arr_f, 0, 5, sizeof(float), operations[3]);
    print(arr_f, 6);
    qsort(arr_c, 0, 3, sizeof(char), operations[4]);
    print(arr_c, 4);

    return 0;
}

void generic_swap(void *rha, void *lha, std::size_t byte_size) {
    void *tmp = malloc(byte_size);
    memcpy(tmp, lha, byte_size);
    memcpy(lha, rha, byte_size);
    memcpy(rha, tmp, byte_size);
    free(tmp);
}


int partition(void * arr, int begin, int end, int pivot, int byteSize, bool (* compare) (void *, void *)){
    void * i = ((char*)arr + begin * byteSize);
    void * j = ((char*)arr + end * byteSize);
    while(true){
        while(compare(i, &pivot)){
            begin++;
            i = ((char*)arr + begin * byteSize);
        }
        while(compare(&pivot, j)){
            end--;
            j = ((char*)arr + end * byteSize);
        }
        if (end <= begin)
            return end;
        generic_swap(i, j, byteSize);
        begin++;
        end--;
        i = ((char*)arr + begin * byteSize);
        j = ((char*)arr + end * byteSize);
    }
}


void qsort(void * arr, int begin, int end, int byteSize, bool (* compare) (void *, void *)){
    if(begin >= end){
        return;
    }
    else{
        int pivot =  *(int*)((char*)arr + (begin + (end - begin)/2) * byteSize);
        int pos = partition(arr, begin, end, pivot, byteSize, compare);
        qsort(arr, begin, pos, byteSize, compare);
        qsort(arr, pos + 1, end, byteSize, compare);
    }
}

bool comp_int (void * a, void * b){
    return *(int*)a < *(int*)b;
}


void print(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void print(float *arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void print(double *arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void print(char *arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

bool ascendInt(void * a, void * b) {
    return *(int*)a < *(int*)b;
}

bool descendInt(void * a, void * b) {
    return *(int*)a > *(int*)b;
}

bool ascendFloat(void * a, void * b) {
    return *(float*)a < *(float*)b;
}

bool descendFloat(void * a, void * b) {
    return *(float*)a > *(float*)b;
}

bool ascendChar(void * a, void * b) {
    return *(char*)a < *(char*)b;
}

bool descendChar(void * a, void * b) {
    return *(char*)a > *(char*)b;
}