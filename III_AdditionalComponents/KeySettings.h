#pragma once

class KeySettings {
public:
    KeySettings();

    int keyOpenClose, keyOpen, keyClose, keyOnOff, keyTurnL, keyTurnR, keyTurnLR, keyTurnOff, keyBootClose;
};

extern KeySettings settings;