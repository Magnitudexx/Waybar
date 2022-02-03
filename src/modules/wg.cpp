/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Red Hat, Inc.
 */

/*
 * The example shows how to list connections.  Contrast this example with
 * list-connections-gdbus.c, which is a bit lower level and talks directly to NM
 * using GDBus.
 *
 * Compile with:
 *   gcc -Wall list-connections-libnm.c -o list-connections-libnm `pkg-config --cflags --libs libnm`
 */

#include <glib.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include <NetworkManager.h>

/* Print details of connection */
static void sort_out_wg(const GPtrArray *connections)
{
    NMSettingConnection *s_con;
    NMConnection *connection;
    std::string type;
    std::vector<std::string> wgs;

    for(guint i = 0; i<connections->len; i++)
    {
        connection = (NMConnection *)connections->pdata[i];
        s_con = nm_connection_get_setting_connection(connection);
        if (s_con) {
            type = nm_setting_connection_get_connection_type(s_con);
        }
        if(type.compare("wireguard")==1){
            wgs.push_back(nm_setting_connection_get_id(s_con));
        }
    }
}

int main()
{
    NMClient *       client;
    GError *         error = NULL;
    const GPtrArray *connections;

    if (!(client = nm_client_new(NULL, &error))) {
        g_message("Error: Could not connect to NetworkManager: %s.", error->message);
        g_error_free(error);
        return EXIT_FAILURE;
    }

    if (!nm_client_get_nm_running(client)) {
        g_message("Error: Can't obtain connections: NetworkManager is not running.");
        return EXIT_FAILURE;
    }

    /* Now the connections can be listed. */
    connections = nm_client_get_connections(client);

    printf("Connections:\n===================\n");
    sort_out_wg(connections);
    g_object_unref(client);

    return EXIT_SUCCESS;
}

