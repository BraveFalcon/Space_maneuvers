#include "Animation.h"
#include "Planet.hpp"

void Animation::keyboard_event(sf::Event event) {
    using sf::Keyboard;
    if (event.key.alt && event.key.code >= Keyboard::Num0 && event.key.code <= Keyboard::Num9) {
        pos_center = animation_system->get_ptr_pos(event.key.code - Keyboard::Num0);
        x_shift = 0;
        y_shift = 0;
    } else
        switch (event.key.code) {
            case Keyboard::Escape:
                window.close();
                break;
            case Keyboard::Home:
                if (event.key.shift) {
                    pos_center = new Vector3d(0);
                    anim_speed = init_anim_speed;
                    scale = init_scale;
                }
                x_shift = 0;
                y_shift = 0;
                break;
            default:
                animation_system->keyboard_event(event);
                break;
        }
}

void Animation::keyboard_handler() {
    using sf::Keyboard;
    static const float delta_scale = 0.01;
    static const float delta_speed = 0.01;
    static const float delta_shift = 3;

    if (Keyboard::isKeyPressed(Keyboard::Equal)) {
        if (Keyboard::isKeyPressed(Keyboard::RControl))
            scale *= 1 + delta_scale;
        else
            anim_speed *= 1 + delta_speed;
    }
    if (Keyboard::isKeyPressed(Keyboard::Dash)) {
        if (Keyboard::isKeyPressed(Keyboard::RControl))
            scale *= 1 - delta_scale;
        else
            anim_speed *= 1 - delta_speed;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left))
        x_shift -= delta_shift;
    if (Keyboard::isKeyPressed(Keyboard::Right))
        x_shift += delta_shift;
    if (Keyboard::isKeyPressed(Keyboard::Up))
        y_shift -= delta_shift;
    if (Keyboard::isKeyPressed(Keyboard::Down))
        y_shift += delta_shift;
}


void Animation::draw() {
    window.clear();

    window.setView(window.getDefaultView());
    window.draw(background);

    sf::View view(sf::Vector2f(static_cast<float>(pos_center->x), static_cast<float>(pos_center->y)),
                  sf::Vector2f(window.getSize()) / scale);
    view.move(x_shift / scale, y_shift / scale);
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
                                                                 sf::Style::Fullscreen, sf::ContextSettings(0, 0, 16)),
                                                          init_scale(window.getSize().x / 700e9f),
                                                          animation_system(animationSystem),
                                                          scale(init_scale) {
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
            if (event.type == sf::Event::KeyPressed)
                keyboard_event(event);
        }

        keyboard_handler();
        draw();
        window.display();
        animation_system->update(anim_speed);

    }
}