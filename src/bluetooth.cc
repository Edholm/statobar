/* Generates the bluetooth icon
 * Reads the info from bluez dbus interface.
 *
 * Copyright 2016 Emil Edholm <emil@edholm.it>
 */
#include <boost/algorithm/string/join.hpp>
#include <gio/gio.h>
#include <vector>
#include "bluetooth.hh"
#include "common.hh"

using namespace std;

#define BLUETOOTH_ICON "\uf293"

GDBusProxy* Bluetooth::dbus_get_bus(const gchar* object_path, const gchar* interface, GError* err) {
    return g_dbus_proxy_new_for_bus_sync(
            G_BUS_TYPE_SYSTEM,
            G_DBUS_PROXY_FLAGS_NONE,
            NULL,
            BLUEZ_NAME.c_str(),
            object_path,
            interface,
            NULL,
            &err);
}

GVariant* Bluetooth::dbus_call_method(GDBusProxy* bus, const gchar* method, GVariant *params, GError *err) {
    return g_dbus_proxy_call_sync(
            bus,
            method,
            params,
            G_DBUS_CALL_FLAGS_NONE,
            -1,
            NULL,
            &err);
}

vector<string> Bluetooth::dbus_list_devices(GDBusProxy *bus) {
    vector<string> devices;
    GError *err = NULL;

    GVariant *result = dbus_call_method(bus,
            "org.freedesktop.DBus.Introspectable.Introspect",
            NULL,
            err);
    if(err) {
        return devices;
    }

    const gchar *xml_data;
    g_variant_get(result, "(&s)", &xml_data);

    err = NULL;
    GDBusNodeInfo *nodes =
        g_dbus_node_info_new_for_xml (xml_data, &err);
    if(err) {
        return devices;
    }

    GDBusNodeInfo **device_node_info = nodes->nodes;
    while(*device_node_info) {
        devices.push_back(string((*device_node_info)->path));
        device_node_info++;
    }

    g_variant_unref(result);
    return devices;
}

bool Bluetooth::is_powered(GDBusProxy *bus) {
    GError *err = NULL;
    GVariant *var =
        dbus_call_method(bus, "Get",
            g_variant_new("(ss)",
                ADAPTER.c_str(),
                "Powered"),
            err);

    if(err) {
        return false;
    }
    GVariant *value;
    g_variant_get(var, "(v)", &value);

    gboolean powered = g_variant_get_boolean(value);
    g_variant_unref(var);
    g_variant_unref(value);
    return powered;
}

/* Get the "pretty" names of all connected bluetooth devices */
vector<string> Bluetooth::connected_names(vector<string>* devices) {
    vector<string> names;
    GError* err = NULL;
    for(auto d : *devices) {
        string obj_path = BLUEZ_OBJECT_PATH + "/" + d;
        GDBusProxy *bus = dbus_get_bus(obj_path.c_str(), DBUS_PROP_INT_NAME.c_str(), err);

        err = NULL;
        GVariant *var =
            dbus_call_method(bus, "GetAll", g_variant_new("(s)", DEVICE.c_str()), err);
        if(err) {
            // FIXME: log maybe baby
            continue;
        }
        GVariant *value = g_variant_get_child_value(var, 0);
        GVariantDict *props = g_variant_dict_new(value);

        gboolean connected;
        g_variant_dict_lookup(props, "Connected", "b", &connected);
        if(connected) {
            const gchar* name;
            g_variant_dict_lookup(props, "Name", "s", &name);
            names.push_back(string(name));
        }

        g_variant_unref(var);
        g_variant_unref(value);
        g_variant_dict_unref(props);
        g_object_unref(bus);
    }
    return names;
}

string Bluetooth::generate_json() {
    GError *err = NULL;
    GDBusProxy* bus = dbus_get_bus(BLUEZ_OBJECT_PATH.c_str(), DBUS_PROP_INT_NAME.c_str(), err);
    if(err || !bus) {
	g_clear_error(&err);
        return "";
    }

    bool powered = is_powered(bus);
    if(!powered) {
        return "";
    }

    vector<string> devices = dbus_list_devices(bus);
    g_object_unref(bus);
    string joinedNames = boost::algorithm::join(connected_names(&devices), ", ");

    string status = BLUETOOTH_ICON;
    string filler = Common::filler_json("");

    map<string, string> m;
    m["full_text"] = "  " + status + " " + joinedNames + " ";

    return filler + ", " + Common::map_to_json(m);
}


