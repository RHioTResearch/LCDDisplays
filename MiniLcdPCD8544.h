//
// Created by Scott Stark on 6/30/15.
//

#ifndef NATIVESCANNER_MINILCDPCD8544_H
#define NATIVESCANNER_MINILCDPCD8544_H

#include "AbstractLcdView.h"

/**
 * A  84 * 48, this Mini LCD screen that has an expander that fits directly over the first 26 gpio header pins
 * of the raspberrypi.
 *
 * http://www.sunfounder.com/index.php?c=show&id=66&model=PCD8544%20Mini%20LCD
 * https://www.adrive.com/public/T6ahCT/PCD8544.zip
 */
class MiniLcdPCD8544 : public AbstractLcdView {
public:
    /**
     * Singleton accessor
     */
    static MiniLcdPCD8544 *getLcdDisplayInstance();

    /**
     * Initialize the display to the given size
     */
    virtual int init(int rows = 6, int cols = 14);

    /**
     * Erase the display
     */
    virtual void clear();

    /**
     * Display a text string starting at the given position. This will wrap around if the string is greater
     * than the number of columns on the display.
     */
    virtual void displayText(const string &text, int col, int row);
};


#endif //NATIVESCANNER_MINILCDPCD8544_H
