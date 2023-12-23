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

    bool Hit(Ray const& r, double tmin, double tmax, HitRecord& record) const override
    {
        bool hitAnything = false; 
        double closestT = tmax; 
        HitRecord tempRecord; 

        for(std::shared_ptr<Hittable> const& h: mHittableObjects){
            if (h->Hit(r, tmin, tmax, tempRecord)){
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