#include "Animation.h"

Animation *Animation::instance_wrap = nullptr;

void Animation::keyboard_event(unsigned char key, int x, int y) {
    static const double delta_scale = 0.1;
    static const double delta_speed = 0.1;
    if (key >= '0' && key <= '9' && GLUT_ACTIVE_ALT) {
        pos_center = anim_sys->get_ptr_pos(key - '0');
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


}

void Animation::keyboard_event_wrap(unsigned char key, int x, int y) {
    instance_wrap->keyboard_event(key, x, y);
}

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

void Animation::spec_keyboard_event_wrap(int key, int x, int y) {
    instance_wrap->spec_keyboard_event(key, x, y);
}

void Animation::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    background.draw(scale);

    glTranslated(0.5 * window_width - scale * pos_center->x - x_shift,
                 0.5 * window_height - scale * pos_center->y - y_shift, 0);
    glScaled(scale, scale, 1);

    glLineWidth(6);

    for (const auto draw_obj : anim_sys->get_draw_objects()) {
        draw_obj->draw(scale);
    }

    anim_sys->update(anim_speed);

    glutSwapBuffers();
}

void Animation::display_wrap() {
    instance_wrap->display();
}

Animation::Animation(Animation_System *animation_system,
                     const std::string &background_image) : anim_sys(animation_system) {

    instance_wrap = this;

    int argc = 0;
    char *argv = "";
    glutInit(&argc, &argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_ALPHA);

    window = glutCreateWindow("");
    glutFullScreen();

    glutDisplayFunc(display_wrap);
    glutIdleFunc(display_wrap);
    glutKeyboardFunc(keyboard_event_wrap);
    glutSpecialFunc(spec_keyboard_event_wrap);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);
    glClearColor(0, 0, 0, 1);

    background = Rectangle(0, 0, 1920, 1080, background_image);

}

void Animation::run() {
    glutMainLoop();
}
