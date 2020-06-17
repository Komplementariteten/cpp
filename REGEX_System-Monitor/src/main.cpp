#include "ncurses_display.h"
#include "system.h"
#include <linux_parser.h>

int main() {
  System system;
  system.Processes();
  assert(system.Processes().size() > 0);
  // NCursesDisplay::Display(system);
}