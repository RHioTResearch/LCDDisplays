
#include "AbstractLcdView.h"
#include "WiringPiLcdDisplay.h"
#include "MiniLcdPCD8544.h"

/**
 * Singleton accessor
 */
AbstractLcdView *AbstractLcdView::getLcdDisplayInstance(LcdDisplayType type) {
    AbstractLcdView *display = nullptr;
    switch(type) {
        case HD44780U:
            display = new WiringPiLcdDisplay();
            break;
        case PCD8544:
            display = new MiniLcdPCD8544();
            break;
    }
    return display;
}


static inline void truncateName(string& name) {
    size_t length = name.length();
    if(length > 8) {
        name.resize(8);
        name.replace(7, 1, 1, '.');
    }
}

void AbstractLcdView::displayTime(int64_t timeInMS, int col, int row) {
    char timestr[256];
    struct timeval  tv;
    struct tm      *tm;

    tv.tv_sec = timeInMS / 1000;
    tv.tv_usec = timeInMS * 1000 - tv.tv_sec * 1000000;
    tm = localtime(&tv.tv_sec);

    size_t length = strftime(timestr, 128, "%T", tm);
    snprintf(timestr+length, 128-length, ".%ld", tv.tv_usec/1000);
    displayText(timestr, col, row);
}
