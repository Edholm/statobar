/*
 * Copyright 2016 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#include <gio/gio.h>
#include <vector>
#include "generator.hh"

class Bluetooth: public Generator {
private:
    const std::string INTERFACE          = "hci0";
    const std::string BLUEZ_NAME         = "org.bluez";
    const std::string ADAPTER            = BLUEZ_NAME + ".Adapter1";
    const std::string DEVICE             = BLUEZ_NAME + ".Device1";
    const std::string BLUEZ_OBJECT_PATH  = "/org/bluez/" + INTERFACE;
    const std::string DBUS_PROP_INT_NAME = "org.freedesktop.DBus.Properties";

    GDBusProxy* dbus_get_bus(const gchar*, const gchar*, GError*);
    GVariant* dbus_call_method(GDBusProxy*, const gchar*, GVariant*, GError*);
    std::vector<std::string> dbus_list_devices(GDBusProxy*);
    std::vector<std::string> connected_names(std::vector<std::string>*);
    /* Whether or not the bluetooth adapter is powered */
    bool is_powered(GDBusProxy*);
public:
    std::string generate_json();
};
#endif
