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
    GtkWidget *suggests;
} Widgets;


BTA *tree,*sug;

GtkWidget  *restore, *about, *dev;
GtkWidget  *search;
GtkWidget  *add, *edit, *del;
GtkWidget *treeview;
GtkWidget *aboutdialog;

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

void closeAbout(GtkWidget *button, Widgets *app){
    gtk_widget_hide(aboutdialog);
}

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

#define size 512
void RestoreDataFile()
{
    btcls(tree);
    remove("data/tudienanhviet.dat");
    FILE* ori = fopen("data/tudienanhviet.old","rb");
    FILE* cur = fopen("data/tudienanhviet.dat", "wb");
    //CopybyBlock(ori, cur);
    int n;
    char buffer[512];
    while (!feof(ori))
    {
        n=fread(buffer,1,size,ori);
        //if (n==0) break;
        fwrite(buffer,1,n,cur);
    }
    fclose(ori);
    fclose(cur);
    tree = btopn("data/tudienanhviet.dat", 0, 0);
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
    // gtk_entry_set_text(app->searchentry,"");
    // gtk_text_buffer_set_text(textbuffer,"",-1);
    //gtk_widget_hide(del);
    //gtk_widget_hide(edit);
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


    // gtk_entry_set_text(app->searchentry,"");
    // gtk_text_buffer_set_text(textbuffer,"",-1);
    //gtk_widget_hide(del);
    //gtk_widget_hide(edit);
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


#define NUMBERSUGGEST 10
#define MAXSUGGESTCHAR 80
void SearchSuggest(BTA*b, int n, char* wordFind, Widgets *app)
{
    GtkTreeIter  iter;
    int i, rsize;
    char tmp[85];
    strcpy(tmp, wordFind);
    char defnFind[6500];
    char pre[85], now[85];
    char suggests[100];
    strcpy(suggests,"");
    int check;
    for(i=0; i<n; i++)
    {
        check=btseln(b, wordFind, defnFind, 6500, &rsize);
        if(check!=0){   //neu ko tim dc tu nao thi ko suggest
            gtk_entry_set_text(app->suggests,""); 
            return;
        }
        strcpy(now, wordFind);
        if (strcmp(pre,now)==0) break;
        strncat(suggests,now,strlen(now));
        strncat(suggests,"  ",2);
        strcpy(pre,now);
        if(strlen(suggests)>=MAXSUGGESTCHAR) break;
        // if(btseln(b,wordFind,defnFind,100,&rsize)==0) strncat(suggests,wordFind,100);
        // strncat(suggests,"  ",2);
    }
    gtk_entry_set_text(app->suggests,suggests);
    strcpy(wordFind,tmp);
}


void
doSearch (GtkButton *button,Widgets *app){
    char suggestword[85];
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
    strcpy(suggestword, textget);
    GtkTreeIter  iter;
    if (strcmp(textget,"")==0){     //neu search entry == null
        gtk_text_buffer_set_text(textbuffer,"",-1); //xoa text view
        
    }
    else{
        check=btsel(tree, textget, defnTemp, sizeof(defnTemp), &rsize);
        if (/**strcmp(defnTemp,"")==0*/check){  //neu khong tim duoc
            gtk_text_buffer_set_text(textbuffer,"Not found.\nInput to add",-1);
            gtk_widget_show(add);
            SearchSuggest(tree,NUMBERSUGGEST,suggestword,app);
            
        }
        else{   //neu tim duoc
            gtk_text_buffer_set_text(textbuffer,defnTemp,-1);
            gtk_list_store_append(app->foundlist, &iter);
            gtk_list_store_set (app->foundlist, &iter, 0, textget, -1);
            gtk_widget_show(del);
            gtk_widget_show(edit);

        }
    }
    
    btcls(tree); 
}

void quickSuggest(GtkButton *button,Widgets *app){
    char suggestword[85];
    gtk_widget_hide(del);
    gtk_widget_hide(edit);
    gtk_widget_hide(add);
    int check=1;

    char suggests[200];
    strcpy(suggests,"");

    //tree = btopn("data/tudienanhviet.dat", 0, 0);
    char defnTemp[6500];
    int rsize;
    gchar *textget;
    GtkTextBuffer *textbuffer;
    textget = gtk_entry_get_text(GTK_ENTRY(app->searchentry));
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->textview));
    //printf("%s",textget);
    strcpy(suggestword, textget);
    GtkTreeIter  iter;
    if (strcmp(textget,"")==0){     //neu search entry == null
        gtk_text_buffer_set_text(textbuffer,"",-1); //xoa text view
        
    }
    else{
        check=btsel(sug, textget, defnTemp, sizeof(defnTemp), &rsize);
        if (/**strcmp(defnTemp,"")==0*/check){  //neu khong tim duoc
            // gtk_text_buffer_set_text(textbuffer,"Not found.\nInput to add",-1);
            // gtk_widget_show(add);
            //SearchSuggest(tree,NUMBERSUGGEST,suggestword,app);
            SearchSuggest(sug,NUMBERSUGGEST,suggests,app);
            
        }
        else{   //neu tim duoc
            // gtk_text_buffer_set_text(textbuffer,defnTemp,-1);
            // gtk_list_store_append(app->foundlist, &iter);
            // gtk_list_store_set (app->foundlist, &iter, 0, textget, -1);
            // gtk_widget_show(del);
            // gtk_widget_show(edit);

        }
    }
    //btcls(tree); 
    
}
void key_enter(GtkButton *button,Widgets *app){
    tree = btopn("data/tudienanhviet.dat", 0, 0);
    int check=1;
    char defnTemp[6500];
    int rsize;
    gchar *textget;
    GtkTextBuffer *textbuffer;
    textget = gtk_entry_get_text(GTK_ENTRY(app->searchentry));
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->textview));
    GtkTreeIter  iter;

    if (strcmp(textget,"")==0){     //neu search entry == null
        gtk_text_buffer_set_text(textbuffer,"",-1); //xoa text view
        
    }
    else{
        check=btsel(tree, textget, defnTemp, sizeof(defnTemp), &rsize);
        if (/**strcmp(defnTemp,"")==0*/check){  //neu khong tim duoc
             gtk_text_buffer_set_text(textbuffer,"Not found.\nInput to add",-1);
             gtk_widget_show(add);
            //SearchSuggest(tree,NUMBERSUGGEST,suggestword,app);
            
        }
        else{   //neu tim duoc
            gtk_text_buffer_set_text(textbuffer,defnTemp,-1);
            gtk_list_store_append(app->foundlist, &iter);
            gtk_list_store_set (app->foundlist, &iter, 0, textget, -1);
            gtk_widget_show(del);
            gtk_widget_show(edit);

        }
    }
    btcls(tree); 
}

void selectRow(GtkButton *button,Widgets *app){
    // tree = btopn("data/tudienanhviet.dat", 0, 0);
    // GtkTreeSelection * select = gtk_tree_view_get_selection (treeview);

    // char text[50];
    // GtkTreeIter iter ;
    // GtkTreeModel * tm = gtk_tree_view_get_model(treeview);
    // GtkTreePath *path = gtk_tree_selection_get_selected_rows (select,&tm);
    // gtk_tree_model_get_iter(tm,&iter,path);
    // gtk_tree_model_get(tm,&iter,0,text,-1);
    // gtk_entry_set_text(app->searchentry,text);
    // btcls(tree); 
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
    sug = btopn("data/sug.dat", 0, 0);


    //khoi tao builder va cac widget
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "dict.glade", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));

aboutdialog = GTK_WIDGET (gtk_builder_get_object (builder, "aboutdialog"));

    restore = GTK_WIDGET (gtk_builder_get_object (builder, "restore"));
    about = GTK_WIDGET (gtk_builder_get_object (builder, "about"));
	   dev = GTK_WIDGET (gtk_builder_get_object (builder, "dev"));

	   search = GTK_WIDGET (gtk_builder_get_object (builder, "search"));

	   add = GTK_WIDGET (gtk_builder_get_object (builder, "add"));
	   edit = GTK_WIDGET (gtk_builder_get_object (builder, "edit"));
	   del = GTK_WIDGET (gtk_builder_get_object (builder, "del"));
       treeview=GTK_WIDGET (gtk_builder_get_object (builder, "treeview"));
	   widget->searchentry = GTK_WIDGET( gtk_builder_get_object( builder, "searchentry" ) );
    widget->textview = GTK_WIDGET( gtk_builder_get_object( builder, "textview" ) );
    widget->foundlist = GTK_LIST_STORE( gtk_builder_get_object( builder, "foundlist" ) );
    widget->suggests = GTK_WIDGET( gtk_builder_get_object( builder, "suggests" ) );
    //widget->suggestslist = GTK_LIST_STORE( gtk_builder_get_object( builder, "suggestslist" ) );
   
    //g_signal_connect(G_OBJECT(search) , "clicked", G_CALLBACK(doSearch), (gpointer) widget);


    //tao cac signal cho widget
    gtk_builder_connect_signals (builder, widget);

    g_object_unref (G_OBJECT (builder));
        
    gtk_widget_show (window);   

    gtk_main ();
    //close btree
    btcls(tree);   
    btcls(sug);
    return 0;
}

