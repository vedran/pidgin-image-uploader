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

#define MAX_LENGTH 256


#include <notify.h>
#include <plugin.h>
#include <version.h>
#include <pidgin.h>
#include <gtkconv.h>
#include <string.h>
#include <regex.h>

PurplePlugin *image_upload_plugin = NULL;

//write a function to fix %20 space characters in the filename of an image

static void
conv_dnd_recv(GtkWidget *widget, GdkDragContext *dc, guint x, guint y,
		GtkSelectionData *sd, guint info, guint t, PidginConversation *gtkconv) {

	GdkPixbuf *pb;
 	GList *files = purple_uri_list_extract_filenames((const gchar *)sd->data);
	
	pb = gdk_pixbuf_new_from_file(files->data, NULL);

	if(pb) {

		FILE *fp;
		char curlReturn[MAX_LENGTH];
		char *apikey = "4c24ac856eff938b2af0ff7e4b6cd5e9";
		PurpleConversation *conv = 	gtkconv->active_conv;

		char curlCommand[MAX_LENGTH];
		int prefixLength = strlen("file://");
		int filenameLength = strlen((const char *)(sd->data));

		sd->data[filenameLength-1] = '\0';

		sprintf(curlCommand, "curl -F \"image=@%s\" -F \"key=%s\" http://api.imgur.com/2/upload.xml", &(sd->data[prefixLength]), apikey);
		fp = popen(curlCommand, "r");

		if(fp != NULL) {
			while(fgets(curlReturn, MAX_LENGTH, fp) != NULL) {
				char *linkStart = "<original>";
				char *linkEnd = "</original>";
				char *start = strstr(curlReturn, linkStart);
				char *end = strstr(curlReturn, linkEnd);
				char linkFinal[MAX_LENGTH];
				int i = 0;

				if(start == NULL)
					continue;

				start = &(start[strlen(linkStart)]);

				while(start) {
					if(start == end)
						break;

					linkFinal[i++] = *(start++);
				}

				linkFinal[i] = '\0';

				purple_conv_im_send (PURPLE_CONV_IM(conv), (const char *)(linkFinal));
			}

		}

	}
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
