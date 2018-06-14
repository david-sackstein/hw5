#include <iostream>

template<typename T>
T sum(T a, T b)
{
    return a + b;
}

template<typename T>
class Array
{
public:
    Array(int size) :
        _data(new T[size]),
        _size(size)
    {
    }

    T& operator[](int index)
    {
        return _data[index];
    }
    
    Array<T> operator+(Array<T> b)
    {
        return b;
    }

    int GetSize() const { return _size; }
private:

    T* _data;
    int _size;
};

typedef Array<int> IntArray;
typedef Array<double> DoubleArray;

int main()
{
    IntArray arr1(10);
    IntArray arr2(10);
    IntArray arr3 = sum(arr1, arr2);

    return 0;
}