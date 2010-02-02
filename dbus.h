/*-*- Mode: C; c-basic-offset: 8 -*-*/

#ifndef foodbushfoo
#define foodbushfoo

#include <dbus/dbus.h>

#include "manager.h"

typedef int (*BusPropertyCallback)(Manager *m, DBusMessageIter *iter, const char *property, void *data);

typedef struct BusProperty {
        const char *interface;           /* interface of the property */
        const char *property;            /* name of the property */
        BusPropertyCallback append;      /* Function that is called to serialize this property */
        const char *signature;
        void *data;                      /* The data of this property */
} BusProperty;

#define BUS_PROPERTIES_INTERFACE                                        \
        " <interface name=\"org.freedesktop.DBus.Properties\">"         \
        "  <method name=\"Get\">"                                       \
        "   <arg name=\"interface\" direction=\"in\" type=\"s\"/>"      \
        "   <arg name=\"property\" direction=\"in\" type=\"s\"/>"       \
        "   <arg name=\"value\" direction=\"out\" type=\"v\"/>"         \
        "  </method>"                                                   \
        "  <method name=\"GetAll\">"                                    \
        "   <arg name=\"interface\" direction=\"in\" type=\"s\"/>"      \
        "   <arg name=\"properties\" direction=\"out\" type=\"a{sv}\"/>" \
        "  </method>"                                                   \
        " </interface>"

#define BUS_INTROSPECTABLE_INTERFACE                                    \
        " <interface name=\"org.freedesktop.DBus.Introspectable\">"     \
        "  <method name=\"Introspect\">"                                \
        "   <arg name=\"data\" type=\"s\" direction=\"out\"/>"          \
        "  </method>"                                                   \
        " </interface>"

int bus_init(Manager *m);
void bus_done(Manager *m);

void bus_dispatch(Manager *m);

void bus_watch_event(Manager *m, Watch *w, int events);
void bus_timeout_event(Manager *m, Watch *w, int events);

DBusHandlerResult bus_default_message_handler(Manager *m, DBusMessage *message, const char* introspection, const BusProperty *properties);

DBusHandlerResult bus_send_error_reply(Manager *m, DBusMessage *message, DBusError *bus_error, int error);

int bus_property_append_string(Manager *m, DBusMessageIter *i, const char *property, void *data);
int bus_property_append_strv(Manager *m, DBusMessageIter *i, const char *property, void *data);
int bus_property_append_bool(Manager *m, DBusMessageIter *i, const char *property, void *data);
int bus_property_append_uint32(Manager *m, DBusMessageIter *i, const char *property, void *data);
int bus_property_append_uint64(Manager *m, DBusMessageIter *i, const char *property, void *data);

extern const DBusObjectPathVTable bus_manager_vtable;
extern const DBusObjectPathVTable bus_job_vtable;
extern const DBusObjectPathVTable bus_unit_vtable;

#endif
