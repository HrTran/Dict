//gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0` -w libbt.a

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/btree.h"
#include <gtk/gtk.h>

typedef struct
{
    GtkWidget *searchentry;
    GtkWidget *textview;
    GtkListStore *foundlist;
    GtkListStore *suggestslist;
} Widgets;


int
main (int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    GtkWidget  *restore, *about, *dev;
    GtkWidget  *search;
    GtkWidget  *add, *edit, *del;

    Widgets *wg = g_slice_new(Widgets);
    

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "dict.glade", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));

    restore = GTK_WIDGET (gtk_builder_get_object (builder, "restore"));
    about = GTK_WIDGET (gtk_builder_get_object (builder, "about"));
	dev = GTK_WIDGET (gtk_builder_get_object (builder, "dev"));

	search = GTK_WIDGET (gtk_builder_get_object (builder, "search"));

	add = GTK_WIDGET (gtk_builder_get_object (builder, "add"));
	edit = GTK_WIDGET (gtk_builder_get_object (builder, "edit"));
	del = GTK_WIDGET (gtk_builder_get_object (builder, "del"));

	wg->searchentry = GTK_WIDGET( gtk_builder_get_object( builder, "searchentry" ) );
    wg->textview = GTK_WIDGET( gtk_builder_get_object( builder, "textview" ) );
    wg->foundlist = GTK_WIDGET( gtk_builder_get_object( builder, "foundlist" ) );
    wg->suggestslist = GTK_LIST_STORE( gtk_builder_get_object( builder, "suggestslist" ) );

    gtk_builder_connect_signals (builder, NULL);

    g_object_unref (G_OBJECT (builder));
        
    gtk_widget_show (window);                
    gtk_main ();

    return 0;
}
