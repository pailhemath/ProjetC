/*
doc :

//pkg-config --cflags --libs gtk+-2.0
//https://www.mclibre.org/descargar/docs/revistas/magpi-books/raspberry-pi-c-gui-programming-en-201904.pdf 
//c gui programming.pdf
//gcc `pkg-config --cflags --libs gtk+-2.0` test.c -o test
*/

// COMPILATION 
/*
*
*
*
*
sudo apt-get install libgtk2.0-dev //install
gcc test.c $(pkg-config --cflags --libs gtk+-2.0) -o test
*
*
*
*
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *txt;
GtkWidget *txt2;
    void end_program (GtkWidget *wid, gpointer ptr)
    {
        gtk_main_quit ();
    }
    void copy_text (GtkWidget *wid, gpointer ptr)
    {
        const char *input1 = gtk_entry_get_text (GTK_ENTRY (txt));
        const char *input2 = gtk_entry_get_text (GTK_ENTRY (txt2));
        printf("%s\n", input1);printf("%s\n", input2);
        //gtk_label_set_text (GTK_LABEL (ptr), input);
    }

void main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (win, "delete_event", G_CALLBACK (end_program),NULL);
    GtkWidget *lbl = gtk_label_new ("username :");
    GtkWidget *lbl2 = gtk_label_new ("password :");
    GtkWidget *lbl3 = gtk_label_new ("password :");
    GtkWidget *btn2 = gtk_button_new_with_label ("Se Connecter");
    g_signal_connect (btn2, "clicked", G_CALLBACK (copy_text), NULL);
    txt = gtk_entry_new ();
    txt2 = gtk_entry_new ();
    GtkWidget *tab = gtk_table_new (5, 2, TRUE);
    gtk_table_attach_defaults (GTK_TABLE (tab), lbl, 0, 1, 0, 1); // username :
    gtk_table_attach_defaults (GTK_TABLE (tab), txt, 1, 2, 0, 1); //zone de sélection
    gtk_table_attach_defaults (GTK_TABLE (tab), lbl2, 0, 1, 1, 2); // password :
    gtk_table_attach_defaults (GTK_TABLE (tab), txt2, 1, 2, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE (tab), btn2, 1, 2, 2, 4);
    gtk_container_add (GTK_CONTAINER (win), tab);
    gtk_widget_show_all (win);
    gtk_main ();
}