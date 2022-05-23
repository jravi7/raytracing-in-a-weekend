set (TARGET raytracer)

set(SOURCES main.cpp
            vec3.h
            color.h
            ray.h
    )

add_executable(raytracer ${SOURCES})