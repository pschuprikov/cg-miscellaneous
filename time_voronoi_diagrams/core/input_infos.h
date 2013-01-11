#ifndef INPUT_INFOS_H
#define INPUT_INFOS_H

#include "../input_listener.h"

namespace tvd
{

struct input_info_t
    : i_input_info
{
    input_info_t(int x, int y);

    bool alt_pressed() const { return alt_; }
    bool ctrl_pressed() const { return ctrl_; }
    bool shift_pressed() const { return shift_; }

    int x() const { return x_; }
    int y() const { return y_; }

private:
    bool alt_;
    bool ctrl_;
    bool shift_;

    int x_;
    int y_;
};

struct keyborad_input_info_t
    : i_keyboard_input_info
{
    keyborad_input_info_t(char key, int x, int y);

    // i_input_info
public:
    bool alt_pressed() const { return info_.alt_pressed(); }
    bool ctrl_pressed() const { return info_.ctrl_pressed(); }
    bool shift_pressed() const { return info_.shift_pressed(); }

    int x() const { return info_.x(); }
    int y() const { return info_.y(); }

    // i_keyboard_input_info
public:
    unsigned char key_pressed() const { return key_; }

private:
    input_info_t info_;
    unsigned char key_;
};

struct mouse_input_info_t
    : i_mouse_input_info
{
    mouse_input_info_t(int button, int x, int y);

    // i_input_info
public:
    bool alt_pressed() const { return info_.alt_pressed(); }
    bool ctrl_pressed() const { return info_.ctrl_pressed(); }
    bool shift_pressed() const { return info_.shift_pressed(); }

    int x() const { return info_.x(); }
    int y() const { return info_.y(); }

    // i_mouse_input_info
public:
    mouse_button_t button() const { return btn_; }

private:
    input_info_t info_;
    mouse_button_t btn_;
};

}

#endif // INPUT_INFOS_H
