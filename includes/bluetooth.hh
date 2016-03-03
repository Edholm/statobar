/*
 * Copyright 2016 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#include "generator.hh"

class Bluetooth: public Generator {
private:
    const char* INTERFACE          = "hci0";
    const char* BLUEZ_NAME         = "org.bluez";
    const char* ADAPTER            = "org.bluez.Adapter1";
    const char* BLUEZ_OBJECT_PATH  = "/org/bluez/hci0";
    const char* DBUS_PROP_INT_NAME = "org.freedesktop.DBus.Properties";

    /* Whether or not the bluetooth adapter is powered */
    bool is_powered();
public:
    std::string generate_json();
};
#endif
