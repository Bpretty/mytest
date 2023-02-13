#include "line.h"
#include <iostream>
using namespace std;

class Line::LineImpl
{
public:
    LineImpl(int x, int y, int z)
    :_x(x)
    ,_y(y)
    ,_z(z)
    {
        cout<< "LineImpl(int,int,int)"<<endl;
    }

    ~LineImpl()
    {
        cout<< "~LineImpl()"<<endl;
    }
    
    void printLine() const
    {
        cout<< "LineImpl->("<<_x
            <<","<<_y
            <<","<<_z
            <<")"<<endl;
    }
private:
    int _x;
    int _y;
    int _z;
};

Line::Line(int x, int y, int z)
:_pImpl(new LineImpl(x, y, z))
{
    cout<< "Line(int, int, int)"<<endl;
}

Line::~Line()
{
    if (_pImpl != nullptr)
        delete _pImpl;

    cout<< "~Line()"<<endl;
}

void Line::printLine() const
{
    _pImpl->printLine();
}
