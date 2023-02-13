#pragma once

class Line
{
    class LineImpl;
public:
    Line(int x, int y, int z);
    ~Line();


    void printLine() const;
private:
    LineImpl* _pImpl;
};

