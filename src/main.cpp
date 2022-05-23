#include <iostream>

int main()
{
    int const imageWidth = 256; 
    int const imageHeight = 256; 

    std::cout<<"P3\n" <<imageWidth<< ' ' <<imageHeight<<"\n255\n";

    for (int h = imageHeight - 1; h >=0; --h){
        std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;

        for(int w = 0; w < imageWidth; ++w){
            auto r = double (w) / (imageWidth - 1);
            auto g = double (h) / (imageHeight - 1);
            auto b = 0.25; 

            int ir = static_cast<int> (255.999 * r); 
            int ig = static_cast<int> (255.999 * g); 
            int ib = static_cast<int> (255.999 * b); 
            std::cout<< ir << ' ' << ig << ' ' << ib << '\n';
        } 
    }
    std::cerr<<"\nDone.\n";
    return 0; 
}