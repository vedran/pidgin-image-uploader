pidginsrcdir=~/Coding/pidgin-src/pidgin-2.7.11/

all:
	/bin/bash $(pidginsrcdir)libtool --silent --mode=compile gcc -DHAVE_CONFIG_H -I $(pidginsrcdir)pidgin -I $(pidginsrcdir)libpurple -I $(pidginsrcdir) -DDATADIR=\"/usr/local/share\" -I$(pidginsrcdir)libpurple/ -I/$(pidginsrcdir)libpurple -Wall  -DPURPLE_DISABLE_DEPRECATED -DPIDGIN_DISABLE_DEPRECATED -DFINCH_DISABLE_DEPRECATED -DGNT_DISABLE_DEPRECATED -Waggregate-return -Wcast-align -Wdeclaration-after-statement -Wendif-labels -Werror-implicit-function-declaration -Wextra -Wno-sign-compare -Wno-unused-parameter -Wformat-security -Werror=format-security -Winit-self -Wmissing-declarations -Wmissing-noreturn -Wmissing-prototypes -Wpointer-arith -Wundef -Wp,-D_FORTIFY_SOURCE=2 -pthread -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pixman-1   -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/gstreamer-0.10 -I/usr/include/libxml2    -g -g -O2 -c pidgin-image-uploader.c -o tmppidgin-image-uploader.so.lo 
	/bin/bash $(pidginsrcdir)libtool --silent --mode=link    gcc -g -g -O2 -o libtmppidgin-image-uploader.so.la -rpath /usr/local/lib/pidgin tmppidgin-image-uploader.so.lo -lnsl -lresolv   -module -avoid-versio
	rm -f *tmppidgin-image-uploader*
	cp .libs/libtmppidgin-image-uploader.so.so pidgin-image-uploader.so
	rm -rf .libs/*
	cp pidgin-image-uploader.so ~/.purple/plugins/

clean:
	rm -rf .libs/*
	rm pidgin-image-uploader.so
	rm ~/.purple/plugins/pidgin-image-uploader.so
