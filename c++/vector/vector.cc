#include <func.h>
#include <assert.h>

#include <iostream>
using namespace std;

template<typename T>
class Vector
{
public:
    Vector()
    :_arr(new T[1]())
    ,_capacity(1)
    ,_size(0)
    {
        cout<< "Vector()"<<endl;
    }

    Vector(int n)
    :_arr(new T[n]())
    ,_capacity(n)
    ,_size(n)
    {
        cout<<"vector(int)"<<endl;
    }
    
    Vector( const Vector<T>& arr )
    {
        cout<< "Vector(const T& arr)"<<endl;

        _arr = new T[arr._capacity]();
        memcpy( _arr, arr._arr, sizeof(arr._capacity * sizeof(T)) );
        _capacity = arr._capacity;
        _size = arr._size;
    }

    const Vector<T>& operator=( const Vector<T>& other )
    {
        if ( this == &other )   return *this;

        delete[] _arr;
        _arr = new T[other._arr]();
        memcpy( _arr, other._arr, sizeof(sizeof(T)*other._arr) );
        _capacity = other._capacity;
        _size = other._size;

        return *this;
    }
    
    T& operator[](int n)
    {
        assert( n < _size);

        return _arr[n];
   }

    Vector<T>& reCapacity()
    {
        if ( _size < _capacity )
        {
            cout<< "不需要扩容"<<endl;
            return *this;
        }

        T* tmp = new T[_capacity * 2]();
        memcpy( tmp, _arr, sizeof(T)*_size );
        _capacity = _capacity * 2;

        // 回收原来的空间
        delete[] _arr;
        _arr = tmp;

        cout<< "扩容成功"<<endl;
    }

    void push_back( const T& other ) 
    {
        if ( _size == _capacity )
        {
            reCapacity();
        }

        memcpy( _arr+_size, &other, sizeof(T) );
        /*
         * 参考的直接使用 _arr[_size++] = other
         * 考虑到other的生命周期，这里直接复制了一份
         * */
        _size++;
    }

    void erase( size_t pos )
    {
        assert( pos < _size );
        
        // 后面的搬过来
        for ( size_t i = pos + 1; i < _size; i++ )
        {
            _arr[i-1] = _arr[i];
        }

        _size--;
    }

    size_t Capacity()
    {
        return _capacity;
    }

    size_t Size()
    {
        return _size;
    }

    void print()
    {
        for(size_t i = 0; i < _size; i++ )
        {
            cout<< _arr[i]<<endl;
        }
    }

    ~Vector()
    {
        if (_arr == nullptr) return;

        delete[] _arr;
        _capacity = 0;
        _size = 0;
    }

private:
    T* _arr;
    size_t _capacity;
    size_t _size;
};

int main()
{
    Vector<int> v1;
    v1.push_back(2);
    v1.push_back(3);
    v1.print();

    cout <<endl;

    cout<<  v1[1] <<endl;

    cout <<endl;

    v1.erase(0);
    cout<<  v1[0] <<endl;

    return 0;
}

