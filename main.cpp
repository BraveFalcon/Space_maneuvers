//#define TEST_SETUP

#ifndef TEST_SETUP


#include "Animation.h"
#include "Solar_System.hpp"
#include <SFML/Graphics.hpp>

//TODO::make file with planets params
//TODO::add future rocket trajectory (planets?)

const float INIT_VIEW_SIZE = 700e9;
int main() {

    Solar_System solar_system(
            Rocket(Vector3d(-1.50169e+11, -6.42522e+09, 0), Vector3d(1320.77, -36868.7, 0), 10e3, 20e3, 0.5, 1e3,
                   sf::Color::Red, "../../images/rocket.png", "../../images/rocket_run.png"),
            {
                    Planet(Vector3d(0, 0, 0), Vector3d(0, 0, 0), 1.9885e+30, 695500e3,
                           sf::Color(255, 255, 0), 3.0, "../../images/sun.png"),
                    Planet(Vector3d(2.895e+10, 5.01429e+10, 0), Vector3d(-41462, 23938.1, 0), 3.33e+23, 2500e3,
                           sf::Color(255, 222, 173), 0.5, "../../images/mercury.png"),
                    Planet(Vector3d(-7.6509e+10, -7.6509e+10, 0), Vector3d(24764.5, -24764.5, 0), 4.8675e+24, 6400e3,
                           sf::Color(222, 184, 135), 0.95, "../../images/venus.png"),
                    Planet(Vector3d(-1.49863e+11, -6.41213e+09, 0), Vector3d(1271.52, -29717.7, 0), 5.9726e+24, 6700e3,
                           sf::Color(20, 100, 255), 1.0, "../../images/earth.png"),
                    Planet(Vector3d(1.97402e+11, -1.1397e+11, 0), Vector3d(12064.7, 20896.8, 0), 6.4171e+23, 3500e3,
                           sf::Color(255, 69, 0), 0.7, "../../images/mars.png"),
                    Planet(Vector3d(3.89274e+11, -6.74242e+11, 0), Vector3d(11307, 6528.09, 0), 1.8986e+27, 71500e3,
                           sf::Color(218, 165, 32), 3.0, "../../images/jupiter.png"),
                    Planet(Vector3d(1.37368e+12, 3.95193e+11, 0), Vector3d(-2664.04, 9260.09, 0), 5.6846e+26, 60300e3,
                           sf::Color(205, 133, 63), 5, "../../images/saturn.png"),
                    Planet(Vector3d(1.43834e+12, -2.49128e+12, 0), Vector3d(5882.25, 3396.12, 0), 8.6832e+25, 25600e3,
                           sf::Color(169, 169, 169), 4.0, "../../images/uranus.png"),
                    Planet(Vector3d(-1.17236e+12, 4.34817e+12, 0), Vector3d(-5241.41, -1413.19, 0), 1.0243e+26, 24800e3,
                           sf::Color(0, 0, 255), 1.9, "../../images/neptune.png")
            });
    Animation animation(&solar_system);
    animation.set_background("../../images/background.jpg");
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
