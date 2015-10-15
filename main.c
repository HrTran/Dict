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


// int AddEntryClicked(BTA*b, char* wordFind, char* defnTemp)
// {
//     return (!btins(b,wordFind,defnTemp,sizeof(char)*6500));
// }

// static void on_addok_clicked(GtkWidget *button, Widgets *A, BTA *b)
// {
//     GtkTextIter start, end;
//     GtkTextBuffer *buffer = gtk_text_view_get_buffer (A->defnview);
//     gchar *texte;
//     gchar *textd;

//     gtk_text_buffer_get_bounds (buffer, &start, &end);

//     btinit();
//     b = btopn("BTdata", 0, 0);

//     texte = gtk_entry_get_text(GTK_ENTRY(A->entry));
//     textd = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

//     AddEntryClicked(b,texte,textd);
//     gtk_entry_set_text(A->entry,"");
//     gtk_text_buffer_set_text(buffer,"", -1);

//     btcls(b);
// }
#define BlockSize 64
void CopybyBlock(FILE *fin, FILE *fout)
{
    int num;
    char buff[BlockSize + 1];
    while (!feof(fin))
    {
        num = fread(buff, sizeof(char),BlockSize, fin);
        buff[num * sizeof(char)] = '\0';
        fwrite(buff, sizeof(char), num, fout);
    }
}

void RestoreDataFile()
{
    btcls(tree);
    remove("data/tudienanhviet.dat");
    FILE* ori = fopen("data/tudienanhviet.old","rb");
    FILE* cur = fopen("data/tudienanhviet.dat", "wb");
    CopybyBlock(ori, cur);
    //tree = btopn("BTdata", 0, 0);
    fclose(ori);
    fclose(cur);
}
void doRestore(GtkWidget *button, Widgets *app){
    RestoreDataFile();
    GtkTextBuffer *textbuffer;
    gtk_entry_set_text(app->searchentry,"");
    gtk_text_buffer_set_text(textbuffer,"",-1);
    gtk_widget_hide(del);
    gtk_widget_hide(edit);
    gtk_widget_hide(add);
    btcls(tree); 
}
void doEdit(GtkWidget *button, Widgets *app){
    tree = btopn("data/tudienanhviet.dat", 0, 0);
    GtkTextIter start, end;
    gchar *text,*btext;
    GtkTextBuffer *textbuffer;
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->textview));
    text = gtk_entry_get_text(GTK_ENTRY(app->searchentry));
    gtk_text_buffer_get_bounds (textbuffer, &start, &end);
    btext=gtk_text_buffer_get_text(textbuffer,&start,&end ,FALSE);
    long value;
    if (bfndky(tree,text,&value)==0)  
    {
        btupd(tree,text,btext,strlen(btext)+1);   
    }
    gtk_entry_set_text(app->searchentry,"");
    gtk_text_buffer_set_text(textbuffer,"",-1);
    gtk_widget_hide(del);
    gtk_widget_hide(edit);
    gtk_widget_hide(add);
    btcls(tree); 
}
void doAdd(GtkWidget *button, Widgets *app){
    tree = btopn("data/tudienanhviet.dat", 0, 0);
    GtkTextIter start, end;
    gchar *text,*btext;
    GtkTextBuffer *textbuffer;
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->textview));
    text = gtk_entry_get_text(GTK_ENTRY(app->searchentry));
    gtk_text_buffer_get_bounds (textbuffer, &start, &end);
    btext=gtk_text_buffer_get_text(textbuffer,&start,&end ,FALSE);

    //printf("%s",btext);
    long value;
    if (bfndky(tree,text,&value)!=0)  //Neu s1 khong co
    {
        //printf("\n%s-%s-%d",s1,s3,strlen(s3));
        btins(tree,text,btext,strlen(btext)+1);   //insert vao btree
    }


    gtk_entry_set_text(app->searchentry,"");
    gtk_text_buffer_set_text(textbuffer,"",-1);
    gtk_widget_hide(del);
    gtk_widget_hide(edit);
    gtk_widget_hide(add);
    btcls(tree); 
}
void doRemove(GtkWidget *button, Widgets *app)
{
    tree = btopn("data/tudienanhviet.dat", 0, 0);
    gchar *text;
    GtkTextBuffer *textbuffer;
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->textview));
    text = gtk_entry_get_text(GTK_ENTRY(app->searchentry));

    //printf("%s",text);
    char defnFind[6500];
    int rsize;
    long value;
    //int exist = btsel(tree, text, defnFind, sizeof(defnFind), &rsize);
    int exist = bfndky(tree,text,&value);
    //printf("%d",exist);
    if (exist == 0)
    {
         bdelky(tree, text);
         //printf("Del %s",text);
    }


    gtk_entry_set_text(app->searchentry,"");
    gtk_text_buffer_set_text(textbuffer,"",-1);
    gtk_widget_hide(del);
    gtk_widget_hide(edit);
    gtk_widget_hide(add);
    btcls(tree); 
}
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
    //printf("%s",textget);
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

