set (TARGET raytracer)

set(SOURCES main.cpp
            vec3.h
            color.h
            ray.h
            sphere.h
            hittable.h
            hittable-list.h
            common.h
            interval.h
            camera.h
    )

add_executable(raytracer ${SOURCES})