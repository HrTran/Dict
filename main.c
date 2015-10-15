//gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0` -w libbt.a -rdynamic

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


BTA *tree;

GtkWidget  *restore, *about, *dev;
GtkWidget  *search;
GtkWidget  *add, *edit, *del;

void
doSearch (GtkButton *button,Widgets *app){
    gtk_widget_hide(del);
    gtk_widget_hide(edit);
    gtk_widget_hide(add);
    int check=1;
    tree = btopn("data/tudienanhviet.dat", 0, 0);
    char defnTemp[6500];
    int rsize;
    gchar *textget;
    GtkTextBuffer *textbuffer;
    textget = gtk_entry_get_text(GTK_ENTRY(app->searchentry));
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->textview));
    
    if (strcmp(textget,"")==0){ 
        gtk_text_buffer_set_text(textbuffer,"",-1);
        
    }
    else{
        check=btsel(tree, textget, defnTemp, sizeof(defnTemp), &rsize);
        if (/**strcmp(defnTemp,"")==0*/check){
            gtk_text_buffer_set_text(textbuffer,"Not found",-1);
            gtk_widget_show(add);
        }
        else{
            gtk_text_buffer_set_text(textbuffer,defnTemp,-1);
            gtk_widget_show(del);
            gtk_widget_show(edit);
        }
    }
    btcls(tree); 
}



int
main (int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    

    Widgets *widget = g_slice_new(Widgets);
    

    gtk_init (&argc, &argv);
    //init btree, mo file .dat
    btinit();
    //tree = btopn("data/tudienanhviet.dat", 0, 0);



    //khoi tao builder va cac widget
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

	   widget->searchentry = GTK_WIDGET( gtk_builder_get_object( builder, "searchentry" ) );
    widget->textview = GTK_WIDGET( gtk_builder_get_object( builder, "textview" ) );
    widget->foundlist = GTK_LIST_STORE( gtk_builder_get_object( builder, "foundlist" ) );
    widget->suggestslist = GTK_LIST_STORE( gtk_builder_get_object( builder, "suggestslist" ) );

    //g_signal_connect(G_OBJECT(search) , "clicked", G_CALLBACK(doSearch), (gpointer) widget);


    //tao cac signal cho widget
    gtk_builder_connect_signals (builder, widget);

    g_object_unref (G_OBJECT (builder));
        
    gtk_widget_show (window);   

    gtk_main ();
    //close btree
    btcls(tree);   

    return 0;
}

