#include "Animation.h"
#include "Planet.hpp"

void Animation::keyboard_handler() {
    /*
    static const double delta_scale = 0.1;
    static const double delta_speed = 0.1;
    if (key >= '0' && key <= '9' && GLUT_ACTIVE_ALT) {
        pos_center = animation_system->get_ptr_pos(key - '0');
        x_shift = 0;
        y_shift = 0;

    } else
        switch (key) {
            case 27: //escape
                glutDestroyWindow(window);
                exit(0);
            case '=':
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
                    scale *= 1 + delta_scale;
                else
                    anim_speed *= 1 + delta_speed;
                break;
            case '-':
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
                    scale *= 1 - delta_scale;
                else
                    anim_speed *= 1 - delta_speed;
                break;
            default:
                anim_sys->keyboard_event(key, glutGetModifiers());
                break;
        }
*/

}

/*
void Animation::spec_keyboard_event(int key, int x, int y) {
    static const double delta_shift = 10;
    switch (key) {
        case GLUT_KEY_LEFT:
            x_shift -= delta_shift;
            break;
        case GLUT_KEY_RIGHT:
            x_shift += delta_shift;
            break;
        case GLUT_KEY_UP:
            y_shift += delta_shift;
            break;
        case GLUT_KEY_DOWN:
            y_shift -= delta_shift;
            break;
        case GLUT_KEY_HOME:
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
                pos_center = new Vector3d(0);
                anim_speed = init_anim_speed;
                scale = init_scale;
            }
            x_shift = 0;
            y_shift = 0;
            break;
        default:
            anim_sys->keyboard_event(key, glutGetModifiers());
            break;
    }
}
*/

void Animation::draw() {
    window.clear();

    window.setView(window.getDefaultView());
    window.draw(background);

    window.setView(view);
    //glTranslated(0.5 * window_width - scale * pos_center->x - x_shift,
    //             0.5 * window_height - scale * pos_center->y - y_shift, 0);
    //glScaled(scale, scale, 1);

    //glLineWidth(6);

    for (const auto draw_obj : animation_system->get_draw_objects()) {
        window.draw(*draw_obj);
    }

}

//TODO::learn more about MSAA
Animation::Animation(Animation_System *animationSystem) : window(sf::VideoMode::getFullscreenModes()[0], "",
                                sf::Style::Fullscreen, sf::ContextSettings(5, 5, 5)),
                         init_scale(window.getSize().x / 500e9),
                         animation_system(animationSystem),
                         view(sf::View(sf::Vector2f(0.0f, 0.0f),
                                       sf::Vector2f(window.getSize()) /
                                       static_cast<float>(init_scale))) {
    background.setPosition(0, 0);
}

void Animation::set_background(const std::string &image_file) {
    if (!_background_texture.loadFromFile(image_file))
        exit(1);
    background.setTexture(_background_texture);
}

void Animation::run() {
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        keyboard_handler();
        draw();
        window.display();
        animation_system->update(anim_speed);

    }
}