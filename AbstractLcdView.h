//
// Created by Scott Stark on 6/30/15.
//

#ifndef NATIVESCANNER_ABSTRACTLCDVIEW_H
#define NATIVESCANNER_ABSTRACTLCDVIEW_H

#include "AbstractLcdDisplay.h"

/**
 * A base implementation of the ScannerView display methods that uses the AbstractLcdDisplay methods
 */
class AbstractLcdView : public AbstractLcdDisplay {
protected:
    /** Should the scanner display beacon(true) or status information(false) */
    bool displayBeaconsMode;
    AbstractLcdView() {}

public:

    /**
     * Singleton accessor
     */
    static AbstractLcdView *getLcdDisplayInstance(LcdDisplayType type);

    bool isDisplayBeaconsMode() const {
        return displayBeaconsMode;
    }
    void setDisplayBeaconsMode(bool displayBeaconsMode) {
        AbstractLcdView::displayBeaconsMode = displayBeaconsMode;
    }
    bool toggleDisplayState() {
        displayBeaconsMode = !displayBeaconsMode;
        return displayBeaconsMode;
    }

    /**
     * Display a time string as HH:MM:SS.ss
     */
    void displayTime(int64_t timeInMS, int col, int row);
};


#endif //NATIVESCANNER_ABSTRACTLCDVIEW_H
