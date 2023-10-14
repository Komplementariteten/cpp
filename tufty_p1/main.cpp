// #include "pico_explorer.hpp"
// #include "drivers/st7789/st7789.hpp"
// #include "libraries/pico_graphics/pico_graphics.hpp"
#include "main.hpp"

using namespace pimoroni;

Tufty2040 tufty;

ST7789 st7789(Tufty2040::WIDTH, Tufty2040::HEIGHT, ROTATE_0, ParallelPins {
    Tufty2040::LCD_CS,
    Tufty2040::LCD_DC,
    Tufty2040::LCD_WR,
    Tufty2040::LCD_RD,
    Tufty2040::LCD_D0,
    Tufty2040::BACKLIGHT
});

PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

Button button_a(Tufty2040::A);
Button button_b(Tufty2040::B);
Button button_c(Tufty2040::C);
Button button_up(Tufty2040::UP);
Button button_down(Tufty2040::DOWN);

uint32_t time() {
  absolute_time_t t = get_absolute_time();
  return to_ms_since_boot(t);
}

int main() {
    st7789.set_backlight(128);
    Pen WHITE = graphics.create_pen(255,255,255);
    Pen BG = graphics.create_pen(120, 40, 60);

    graphics.
}