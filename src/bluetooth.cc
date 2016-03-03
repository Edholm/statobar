/* Generates the bluetooth icon
 * Reads the info from bluez dbus interface.
 *
 * Copyright 2016 Emil Edholm <emil@edholm.it>
 */
#include <gio/gio.h>
#include "bluetooth.hh"
#include "common.hh"

using namespace std;

#define BLUETOOTH_ICON "\uf293"

bool Bluetooth::is_powered() {
    GError *err = NULL;
    GDBusProxy* bus_proxy =
        g_dbus_proxy_new_for_bus_sync(
            G_BUS_TYPE_SYSTEM,
            G_DBUS_PROXY_FLAGS_NONE,
            NULL,
            BLUEZ_NAME,
            BLUEZ_OBJECT_PATH,
            DBUS_PROP_INT_NAME,
            NULL,
            &err);

    if(err) {
        return false;
    }
    err = NULL;
    GVariant *var =
        g_dbus_proxy_call_sync(
            bus_proxy,
            "Get",
            g_variant_new("(ss)",
                ADAPTER,
                "Powered"),
            G_DBUS_CALL_FLAGS_NONE,
            -1,
            NULL,
            &err);


    if(err) {
        return false;
    }
    GVariant *value;
    g_variant_get(var, "(v)", &value);

    gboolean powered = g_variant_get_boolean(value);
    g_object_unref(bus_proxy);
    g_variant_unref(var);
    g_variant_unref(value);
    return powered;
}

string Bluetooth::generate_json() {
    bool powered = is_powered();
    if(!powered) {
        return "";
    }

    string status = BLUETOOTH_ICON;
    string filler = Common::filler_json("");

    map<string, string> m;
    m["full_text"] = status + " ";

    return filler + ", " + Common::map_to_json(m);
}


