# pragma once

#include "hittable.h"

#include <memory>
#include <vector>


class HittableList: public Hittable
{
public: 
    HittableList() = default; 
    HittableList(std::shared_ptr<Hittable> h)
    {
        Add(h); 
    }

    void Add(std::shared_ptr<Hittable> h)
    {
        mHittableObjects.push_back(h); 
    }

    void Clear()
    {
        mHittableObjects.clear(); 
    }

    bool Hit(Ray const& r, Interval const& rayT, HitRecord& record) const override
    {
        bool hitAnything = false; 
        double closestT = rayT.Max(); 
        HitRecord tempRecord; 

        for(std::shared_ptr<Hittable> const& h: mHittableObjects){
            if (h->Hit(r, rayT, tempRecord)){
                hitAnything = true; 
                closestT = tempRecord.t; 
                record = tempRecord; 
            }
        }
        return hitAnything;
    }

private: 
    std::vector<std::shared_ptr<Hittable>> mHittableObjects; 
};