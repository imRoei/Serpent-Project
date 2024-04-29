#include "../headers/serpent_functions.h"
#include "../headers/graphs.h"
#include <gtk/gtk.h>
int main(int argc, const char *argv[])
{

    GtkWidget *window;

    gtk_init(&argc, &argv);

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "My GTK App");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Display all widgets contained in the window
    gtk_widget_show_all(window);

    // Run the main GTK event loop
    gtk_main();

    // Regular text input
    const char *test_string = "Hello World!";
    const char *key_string = "MySecretKey12345"; // Key must still be 128 bits

    unsigned char *encrypted_string = (unsigned char *)malloc(16 * sizeof(unsigned char) /*bytes*/);
    unsigned char *decrypted_string = (unsigned char *)malloc(16 * sizeof(unsigned char) /*bytes*/);

    // Assuming serpent_encrypt_standard and serpent_decrypt_standard now handle text
    serpent_encrypt_standard(test_string, key_string, encrypted_string, 16);
    printHex(encrypted_string, 16, "Encrypted Cipher:");
    printf("\n");

    serpent_decrypt_standard(encrypted_string, key_string, decrypted_string, 16);
    printf("Decrypted Text: %s\n", decrypted_string);

    free(encrypted_string);
    free(decrypted_string);

    srand(time(NULL)); // Seed initialization
    int a, b;
    double key[][keyMatSize] = {{1, 1, 2, 5, 3},
                                {4, 8, 9, 12, 6},
                                {5, 18, 21, 10, 3},
                                {63, 38, 7, 29, 24},
                                {0, 25, 75, 4, 33}};

    char *plaintext = "DECEMBERFIRST";
    Graph **WorkSet;
    if (determinant(key, keyMatSize) == 0)
    {
        printf("Key is not secure enough");
    }
    else
    {
        int len = strlen(plaintext);
        if (len % block_size != 0)
        {
            len = len + block_size - len % block_size;
        }

        printf("Enter two numbers between 0 and 26\n");
        scanf("%d%d", &a, &b);
        while (a < 0 || a > 26 || b < 0 || b >= 26 || !isGcdOne(a, b))
        {
            printf("Invalid input - ");
            printf("Enter two numbers between 0 and 26 that their gcd equals 1");
            scanf("%d%d", &a, &b);
        }
        WorkSet = Encryption(key, plaintext, a, b);
        Decreyption(key, WorkSet, len / block_size, a, b);
    }

    return 0;
}
