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

PurplePlugin *image_upload_plugin = NULL;

static void
conv_dnd_recv(GtkWidget *widget, GdkDragContext *dc, guint x, guint y,
              GtkSelectionData *sd, guint info, guint t,
			                PidginConversation *gtkconv) {

	GdkPixbuf *pb;
	PurpleConversation *conv = 	gtkconv->active_conv;
	purple_conv_im_send (PURPLE_CONV_IM(conv), (const char*)(sd->data));

	
	/*for ( ; files; files = g_list_delete_link(files, files)) {
		g_free(filename);
		g_free(basename);

		filename = files->data;
		basename = g_path_get_basename(filename);

		pb = gdk_pixbuf_new_from_file(filename, NULL);
		if (pb) {
			//purple_notify_message (image_upload_plugin, PURPLE_NOTIFY_MSG_INFO,
			//		"Drag and drop", filename, NULL, NULL,
			//		NULL);

		}
	}*/
}


	static void
conversation_displayed_cb(PidginConversation *gtkconv, void *data)
{
	//	PidginConversation *gtkconv = PIDGIN_CONVERSATION(conv);
	g_signal_connect(G_OBJECT(gtkconv->imhtml), "drag_data_received",
			G_CALLBACK(conv_dnd_recv), gtkconv);

	g_signal_connect(G_OBJECT(gtkconv->entry), "drag_data_received",
			G_CALLBACK(conv_dnd_recv), gtkconv);
}


	static gboolean
plugin_load (PurplePlugin * plugin)
{
	void *conv_handle = pidgin_conversations_get_handle();
	image_upload_plugin = plugin; 

	purple_signal_connect(conv_handle, "conversation-displayed",
			plugin, PURPLE_CALLBACK(conversation_displayed_cb), NULL);

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
