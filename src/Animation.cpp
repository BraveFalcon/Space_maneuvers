#include "Animation.h"

extern const float INIT_VIEW_SIZE;

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
            case Keyboard::F5:
                std::cout << "p";
                if (event.type == sf::Event::KeyPressed)
                    is_run = !is_run;
                break;
            default:
                animation_system->keyboard_event(event);
                break;
        }
}

void Animation::keyboard_handler(const float fps) {
    using sf::Keyboard;
    float delta_scale = 1.0f / fps;
    float delta_speed = 0.5f / fps;
    float delta_shift = 300.0f / fps;

    if (Keyboard::isKeyPressed(Keyboard::Equal)) {
        if (Keyboard::isKeyPressed(Keyboard::RControl))
            scale *= 1 + delta_scale;
        else if (fps > 1)
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

    animation_system->keyboard_handler(fps);
}


void Animation::draw() {
    window.clear();

    window.setView(window.getDefaultView());
    window.draw(background);
    window.draw(fps_text);

    sf::View view;
    view.setCenter(static_cast<float>(pos_center->x), static_cast<float>(-pos_center->y)); //revert y-axis
    view.setSize(window.getSize().x / scale, window.getSize().y / scale);
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
                                                                 sf::Style::Fullscreen,
                                                                 sf::ContextSettings(0, 0, 16, 3, 0)),
                                                          init_scale(window.getSize().x / INIT_VIEW_SIZE),
                                                          animation_system(animationSystem),
                                                          scale(init_scale) {
    background.setPosition(0, 0);
    if (!_monospacedFont.loadFromFile("../../fonts/monospaced.ttf"))
        exit(1);
    fps_text.setFont(_monospacedFont);
    fps_text.setCharacterSize(50);
    fps_text.setFillColor(sf::Color::Yellow);
    fps_text.setStyle(sf::Text::Bold);
    fps_text.setPosition(0, -20);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
}

void Animation::set_background(const std::string &image_file) {
    if (!_background_texture.loadFromFile(image_file))
        exit(1);
    background.setTexture(_background_texture);
}

void Animation::run() {
    while (window.isOpen()) {
        frame++;
        fps_text.setString(std::to_string(get_fps()));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
                keyboard_event(event);
        }

        keyboard_handler(get_fps());
        draw();
        window.display();
        if (is_run)
            animation_system->update(anim_speed / std::max(get_fps(), 30));

    }
}

int Animation::get_fps() {
    static sf::Clock clock;
    static unsigned long last_frame;
    static float fps = 100;

    if (clock.getElapsedTime().asSeconds() > 0.2) {
        fps = (frame - last_frame) / clock.restart().asSeconds();
        last_frame = frame;
    }
    return static_cast<int>(fps);
}