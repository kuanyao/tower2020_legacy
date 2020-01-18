#ifndef __SCREEN_H
#define __SCREEN_H

namespace screen {
    void set_notif_handler(void (*handler)(const char *, const char *));
    void setup_screen();
}

#endif
