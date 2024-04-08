#include <string.h>

#include <iostream>
using namespace std;

template <typename T>
class Vector
{
public:
    Vector(size_t Capacity = 1)
    :_size(0)
    ,_capacity(Capacity)
    ,_ptr(nullptr)
    {
        cout<< "Vector(int Capacity)" <<endl;
    }

    Vector(const Vector<T>& vec)
    :_size(vec._size)
    ,_capacity(vec._capacity)
    ,_ptr(new T[vec._capacity]())
    {
        if(_size > 0)
        {
            memcpy(_ptr, vec._ptr, sizeof(T)*_size);
        }
        
        cout<< "Vector(const T&)" <<endl;
    }

    Vector<T>& operator=(const Vector<T>& vec)
    {
        if (&vec == this)
            return *this;

        delete[] _ptr;
        _size = vec._size;
        _capacity = vec._capacity;
        _ptr = new T[_capacity]();
        memcpy(_ptr, vec._ptr, sizeof(T)*_capacity);

        cout<< "operator=(const T&)" <<endl;
    }

    ~Vector()
    {
        if (_ptr != nullptr)
        {
            delete[] _ptr;
            _ptr = nullptr;
        }

        cout<< "~Vector()"<<endl;
    }

private:
    size_t _capacity;
    size_t _size;
    T* _ptr;
};

int main()
{
    Vector<int> vec1;
    Vector<int> vec2 = vec1;

    return 0;
}

