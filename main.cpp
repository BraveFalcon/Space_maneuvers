//#define TEST_SETUP

#ifndef TEST_SETUP


#include "Animation.h"
#include "Solar_System.hpp"



int main() {
    Solar_System solar_system{
            Planet(Vector3d(0, 0, 0), Vector3d(0, 0, 0), 1.9885e+30,
                   Color(255, 255, 0), "../../images/sun.png"),
            Planet(Vector3d(2.895e+10, 5.01429e+10, 0), Vector3d(-41462, 23938.1, 0), 3.33e+23,
                   Color(255, 222, 173), "../../images/mercury.png"),
            Planet(Vector3d(-7.6509e+10, -7.6509e+10, 0), Vector3d(24764.5, -24764.5, 0), 4.8675e+24,
                   Color(222, 184, 135), "../../images/venus.png"),
            Planet(Vector3d(-1.49863e+11, -6.41213e+09, 0), Vector3d(1271.52, -29717.7, 0), 5.9726e+24,
                   Color(20, 100, 255), "../../images/earth.png"),
            Planet(Vector3d(1.97402e+11, -1.1397e+11, 0), Vector3d(12064.7, 20896.8, 0), 6.4171e+23,
                   Color(255, 69, 0), "../../images/mars.png"),
            Planet(Vector3d(3.89274e+11, -6.74242e+11, 0), Vector3d(11307, 6528.09, 0), 1.8986e+27,
                   Color(218, 165, 32), "../../images/jupiter.png"),
            Planet(Vector3d(1.37368e+12, 3.95193e+11, 0), Vector3d(-2664.04, 9260.09, 0), 5.6846e+26,
                   Color(205, 133, 63), "../../images/saturn.png"),
            Planet(Vector3d(1.43834e+12, -2.49128e+12, 0), Vector3d(5882.25, 3396.12, 0), 8.6832e+25,
                   Color(169, 169, 169), "../../images/uranus.png"),
            Planet(Vector3d(-1.17236e+12, 4.34817e+12, 0), Vector3d(-5241.41, -1413.19, 0), 1.0243e+26,
                   Color(0, 0, 255), "../../images/neptune.png")
    };

    Animation animation(&solar_system, "../../images/uranus.png");
    animation.run();
    return 0;
}

#else

#include "List.hpp"
#include "Vector3.hpp"

double DT = 20;
double G = 6.67408e-11;

int main(){
    List<Vector3d> list;
    list.append(Vector3d(0));
    list.clear();
}

#endif
