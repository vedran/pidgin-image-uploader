/*
 * Image Uploader Plugin
 *
 * Copyright (C) 2004, Gary Kramlich <grim@guifications.org>,
 *               2007, John Bailey <rekkanoryo@cpw.pidgin.im>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02111-1301, USA.
 *
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* config.h may define PURPLE_PLUGINS; protect the definition here so that we
 * don't get complaints about redefinition when it's not necessary. */
#ifndef PURPLE_PLUGINS
# define PURPLE_PLUGINS
#endif

#include <glib.h>

/* This will prevent compiler errors in some instances and is better explained in the
 * how-to documents on the wiki */
#ifndef G_GNUC_NULL_TERMINATED
# if __GNUC__ >= 4
#  define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
# else
#  define G_GNUC_NULL_TERMINATED
# endif
#endif

#include <notify.h>
#include <plugin.h>
#include <version.h>
#include <pidgin.h>
#include <gtkconv.h>

/* we're adding this here and assigning it in plugin_load because we need
 * a valid plugin handle for our call to purple_notify_message() in the
 * plugin_action_test_cb() callback function */
PurplePlugin *image_upload_plugin = NULL;

static void
conv_dnd_recv(PidginConversation *gtkconv, gpointer data) {
	purple_notify_message (image_upload_plugin, PURPLE_NOTIFY_MSG_INFO,
			"Drag and drop", "drag and drop detected", NULL, NULL,
			NULL);

}

static void
conversation_switched_cb(PurpleConversation *conv, void *data)
{
	PidginConversation *gtkconv = PIDGIN_CONVERSATION(conv);
	g_signal_connect(G_OBJECT(gtkconv->imhtml), "drag_data_received",
                     G_CALLBACK(conv_dnd_recv), gtkconv);

	g_signal_connect(G_OBJECT(gtkconv->entry), "drag_data_received",
                     G_CALLBACK(conv_dnd_recv), gtkconv);

	purple_notify_message (image_upload_plugin, PURPLE_NOTIFY_MSG_INFO,
		"Drag and Drop", "show conversation detected", NULL, NULL,
		NULL);

}


static gboolean
plugin_load (PurplePlugin * plugin)
{
	void *conv_handle = pidgin_conversations_get_handle();
	image_upload_plugin = plugin; 

	purple_signal_connect(conv_handle, "conversation-switched",
                        plugin, PURPLE_CALLBACK(conversation_switched_cb), NULL);

	return TRUE;
}

/* For specific notes on the meanings of each of these members, consult the C Plugin Howto
 * on the website. */
static PurplePluginInfo info = {
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,
	NULL,
	0,
	NULL,
	PURPLE_PRIORITY_DEFAULT,

	"core-image_uploader",
	"Image Uploader!",
	"1.0",
	"Image Uploader Plugin",
	"Image Uploader Plugin",
	"Vedran Budimcic",
	" ",


	plugin_load,
	NULL,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

	static void
init_plugin (PurplePlugin * plugin)
{
}

PURPLE_INIT_PLUGIN (image_uploader, init_plugin, info)
