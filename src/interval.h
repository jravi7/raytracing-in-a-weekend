#pragma once

#include <limits>

class Interval 
{
public:
    static double constexpr infinity = std::numeric_limits<double>::infinity(); 

    Interval(): mMin(infinity), mMax(-infinity){}
    Interval(double min, double max): mMin(min), mMax(max){}

    bool Contains(double t) const 
    {
        return t >= mMin && t <= mMax; 
    }

    bool Surrounds(double t) const
    {
        return t > mMin && t < mMax; 
    }

    double Min() const
    {
        return mMin;
    }

    double Max() const
    {
        return mMax;
    }

private: 
    double mMin; 
    double mMax; 
};