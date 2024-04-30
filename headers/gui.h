#include <gtk/gtk.h>

// Function to create the header label
GtkWidget *create_header_label();

// Function to create the key label and entry
void create_key_widgets(GtkWidget *vbox, GtkWidget **key_entry);

// Function to create the input label and entry
void create_input_widgets(GtkWidget *vbox, GtkWidget **input_entry);

// Function to create the spacer widget
GtkWidget *create_spacer();

// Function to create the copy button
GtkWidget *create_copy_button();

// Function to create the result label wrapper and result label
void create_result_widgets(GtkWidget *vbox);

// Function to create the submit button
GtkWidget *create_submit_button(GtkWidget *input_entry, GtkWidget *key_entry, GtkWidget *encrypt_button, GtkWidget *result_label);

char *SerpentGuiEnc(const gchar *key, const gchar *input);

// Function to handle button clicks (submission)
void on_submit_button_clicked(GtkWidget *button, gpointer user_data);
// Function to copy text to clipboard
void on_copy_button_clicked(GtkWidget *button, gpointer user_data);
// Function to create the radio buttons
void create_radio_buttons(GtkWidget *vbox);

void on_toggle_button_toggled(GtkToggleButton *toggle_button, gpointer user_data);

char *SerpentGuiDec(const gchar *key, const gchar *input);

void on_toggle_button_toggled_mode(GtkToggleButton *toggle_button, gpointer opposite_button);
// Main function to create the user interface
void create_ui(GtkWidget *window);
