#include "../headers/gui.h" // Include necessary headers here
#include "../headers/serpent_functions.h"
#include <glib.h>
GtkWidget *result_label; // Declare the result label globally for accessibility

int flagEnc = 1;

// Function to create the header label
GtkWidget *create_header_label()
{
    return gtk_label_new("Roei's App");
}

// Function to create the key label and entry
void create_key_widgets(GtkWidget *parent, GtkWidget **key_entry)
{
    // Create the key label and entry widgets
    GtkWidget *key_label = gtk_label_new("Key:");
    *key_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(*key_entry), 32); // Limit to 32 characters

    // Pack the key label and entry into the parent widget
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox), key_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), *key_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(parent), hbox, FALSE, FALSE, 0);
}

// Function to create the input label and entry
void create_input_widgets(GtkWidget *vbox, GtkWidget **input_entry)
{
    GtkWidget *input_label = gtk_label_new("Input:");
    *input_entry = gtk_entry_new();

    gtk_box_pack_start(GTK_BOX(vbox), input_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), *input_entry, FALSE, FALSE, 0);
}

// Function to create the spacer widget
GtkWidget *create_spacer()
{
    GtkWidget *spacer = gtk_label_new(NULL);
    gtk_widget_set_size_request(spacer, -1, 10); // Set height to 10 units

    return spacer;
}

// Function to create the copy button
GtkWidget *create_copy_button()
{
    return gtk_button_new_with_label("Copy to Clipboard");
}

// Global variable to hold the result label
GtkWidget *result_label = NULL;

// Function to create the result label wrapper and result label
void create_result_widgets(GtkWidget *vbox)
{
    GtkWidget *result_frame = gtk_frame_new(NULL);
    gtk_widget_set_name(result_frame, "result-frame");
    gtk_box_pack_start(GTK_BOX(vbox), result_frame, FALSE, FALSE, 0);

    GtkWidget *result_label_wrapper = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(result_frame), result_label_wrapper);

    // Initialize result_label with default text
    result_label = gtk_label_new("Result will appear here");
    gtk_label_set_xalign(GTK_LABEL(result_label), 0.5); // Set horizontal alignment to center
    gtk_label_set_yalign(GTK_LABEL(result_label), 0.5); // Set vertical alignment to center
    gtk_box_pack_start(GTK_BOX(result_label_wrapper), result_label, TRUE, TRUE, 0);
}

// Function to create the submit button
GtkWidget *create_submit_button(GtkWidget *input_entry, GtkWidget *key_entry, GtkWidget *encrypt_button, GtkWidget *result_label)
{
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");

    g_object_set_data(G_OBJECT(submit_button), "input_entry", (gpointer)input_entry);
    g_object_set_data(G_OBJECT(submit_button), "key_entry", (gpointer)key_entry);
    g_object_set_data(G_OBJECT(submit_button), "encrypt_button", (gpointer)encrypt_button);
    g_object_set_data(G_OBJECT(submit_button), "result_label", (gpointer)result_label); // Store the result label

    return submit_button;
}

char *SerpentGuiEnc(const gchar *key, const gchar *input)
{
    if (!key || !input)
    {
        printf("Error: Key, Input is NULL\n");
        return NULL;
    }
    // Assuming serpent_encrypt_standard and serpent_decrypt_standard now handle text
    unsigned char *encrypted_string = (unsigned char *)malloc(16 * sizeof(char));
    serpent_encrypt_standard(input, key, encrypted_string, 16);
    char *result_string = strdup(binary_to_hexstr(encrypted_string, 16));
    // Free the allocated memory for encrypted_string

    return result_string;
}

char *SerpentGuiDec(const gchar *key, const gchar *input)
{
    if (!key || !input)
    {
        printf("Error: Key, Input is NULL\n");
        return NULL;
    }

    unsigned char *decrypted_string = (unsigned char *)malloc(16 * sizeof(char));
    // Encrypt the input into encrypted_string using serpent_encrypt_standard
    // Make sure to replace this with your actual encryption logic
    size_t input_length;
    unsigned char *bb;
    hexstr_to_binary(input, &bb, &input_length);
    serpent_decrypt_standard(bb, key, decrypted_string, 16);

    return decrypted_string;
}

void on_submit_button_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *key_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "key_entry"));
    printf("%s", key_entry);
    if (!GTK_IS_ENTRY(key_entry))
    {
        // Print the type of the widget for debugging
        printf("Type of user data: %s\n", G_OBJECT_TYPE_NAME(key_entry));

        g_critical("Key entry is not a valid entry widget");
        return;
    }

    const gchar *key_text = gtk_entry_get_text(GTK_ENTRY(key_entry));

    GtkWidget *encrypt_button = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "encrypt_button"));

    // Get the input entry widget directly from the user data
    GtkWidget *input_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "input_entry"));

    if (!GTK_IS_ENTRY(input_entry))
    {
        g_critical("Input entry is not a valid entry widget");
        return;
    }
    const gchar *input_text = gtk_entry_get_text(GTK_ENTRY(input_entry));
    GtkWidget *result_label = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "result_label"));

    // Proceed if it's a toggle button
    if (!flagEnc)
    {
        gtk_label_set_text(GTK_LABEL(result_label), (const gchar *)SerpentGuiEnc(key_text, input_text));
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(result_label), (const gchar *)SerpentGuiDec(key_text, input_text));
    }
}

// Function to copy text to clipboard
void on_copy_button_clicked(GtkWidget *button, gpointer user_data)
{
    // Get text from result_label
    const gchar *result_text = gtk_label_get_text(GTK_LABEL(result_label));

    // Copy text to clipboard
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    gtk_clipboard_set_text(clipboard, result_text, -1);
}

// Function to create the radio buttons (toggle buttons)
void create_radio_buttons(GtkWidget *vbox)
{
    GtkWidget *radio_label = gtk_label_new("Options:");
    gtk_box_pack_start(GTK_BOX(vbox), radio_label, FALSE, FALSE, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);    // Make rows homogeneous
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE); // Make columns homogeneous
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    GtkWidget *encrypt_button = gtk_toggle_button_new_with_label("Encrypt");
    GtkWidget *decrypt_button = gtk_toggle_button_new_with_label("Decrypt");

    gtk_grid_attach(GTK_GRID(grid), encrypt_button, 0, 0, 1, 1); // Attach encrypt button at row 0, column 0
    gtk_grid_attach(GTK_GRID(grid), decrypt_button, 1, 0, 1, 1); // Attach decrypt button at row 0, column 1

    // Connect signals for toggling
    g_signal_connect(decrypt_button, "toggled", G_CALLBACK(on_toggle_button_toggled), encrypt_button);
    g_signal_connect(encrypt_button, "toggled", G_CALLBACK(on_toggle_button_toggled), decrypt_button);

    // Set Encrypt button as default
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(encrypt_button), TRUE);
}

void create_mode_radio_buttons(GtkWidget *vbox)
{
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);    // Make rows homogeneous
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE); // Make columns homogeneous
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    GtkWidget *serpentMode = gtk_toggle_button_new_with_label("Serpent");
    GtkWidget *graphMode = gtk_toggle_button_new_with_label("Graphs");

    gtk_grid_attach(GTK_GRID(grid), serpentMode, 0, 0, 1, 1); // Attach encrypt button at row 0, column 0
    gtk_grid_attach(GTK_GRID(grid), graphMode, 1, 0, 1, 1);   // Attach decrypt button at row 0, column 1

    // Connect signals for toggling
    g_signal_connect(serpentMode, "toggled", G_CALLBACK(on_toggle_button_toggled), serpentMode);
    g_signal_connect(graphMode, "toggled", G_CALLBACK(on_toggle_button_toggled), graphMode);

    // Set Encrypt button as default
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(serpentMode), TRUE);
}

// Callback function for toggle button toggling
void on_toggle_button_toggled(GtkToggleButton *toggle_button, gpointer opposite_button)
{
    if (gtk_toggle_button_get_active(toggle_button))
    {
        const gchar *label_text = gtk_button_get_label(GTK_BUTTON(toggle_button));
        printf("%s button toggled\n", label_text);

        // Deactivate the opposite button if it's a toggle button
        if (GTK_IS_TOGGLE_BUTTON(opposite_button))
        {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(opposite_button), FALSE);
            if (flagEnc == 0)
            {
                flagEnc = 1;
            }
            else
            {
                flagEnc = 0;
            }
        }
    }
}

// Main function to create the user interface
void create_ui(GtkWidget *window)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *header_label = create_header_label();
    gtk_box_pack_start(GTK_BOX(vbox), header_label, FALSE, FALSE, 0);

    create_mode_radio_buttons(vbox);

    // Create and pack header label

    GtkWidget *key_entry;
    create_key_widgets(vbox, &key_entry);

    // Create and pack input widgets
    GtkWidget *input_entry;
    create_input_widgets(vbox, &input_entry);

    // Create radio buttons
    create_radio_buttons(vbox);

    // Declare and define the encrypt_button variable
    GtkWidget *encrypt_button = gtk_toggle_button_new_with_label("Encrypt");
    GtkWidget *decrypt_button = gtk_toggle_button_new_with_label("Decrypt");
    g_signal_connect(encrypt_button, "toggled", G_CALLBACK(on_toggle_button_toggled), decrypt_button);
    g_signal_connect(decrypt_button, "toggled", G_CALLBACK(on_toggle_button_toggled), encrypt_button);

    create_result_widgets(vbox);

    // Create and pack submit button
    GtkWidget *submit_button = create_submit_button(input_entry, key_entry, encrypt_button, result_label);
    gtk_box_pack_start(GTK_BOX(vbox), submit_button, FALSE, FALSE, 0);

    // Connect clicked signal of submit button to on_submit_button_clicked function
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_button_clicked), key_entry);

    // Create and pack spacer widget
    GtkWidget *spacer = create_spacer();
    gtk_box_pack_start(GTK_BOX(vbox), spacer, FALSE, FALSE, 0);

    // Create and pack copy button
    GtkWidget *copy_button = create_copy_button();
    gtk_box_pack_start(GTK_BOX(vbox), copy_button, FALSE, FALSE, 0);
    g_signal_connect(copy_button, "clicked", G_CALLBACK(on_copy_button_clicked), NULL);

    // Create and pack result widgets
    // Show all the widgets
    gtk_widget_show_all(window);
}
