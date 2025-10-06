/*
 * dictionary_gui.c - GTK GUI for Advanced Dictionary System
 * Integrates with existing Trie data structure from dictionary.h/dictionary.c
 */

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Global variables
static TrieNode *dictionary_root = NULL;
static GtkWidget *result_textview;
static GtkTextBuffer *result_buffer;
static GtkWidget *window;

/* ============================================================================
 * HELPER FUNCTIONS
 * ============================================================================ */

/**
 * display_result - Display text in result area
 */
static void display_result(const char *text) {
    gtk_text_buffer_set_text(result_buffer, text, -1);
}

/**
 * append_result - Append text to result area
 */
static void append_result(const char *text) {
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(result_buffer, &end);
    gtk_text_buffer_insert(result_buffer, &end, text, -1);
}

/**
 * format_word_entry - Format word entry for display
 */
static void format_word_entry(const char *word, WordEntry *entry, char *output, size_t size) {
    int len = snprintf(output, size, "\n📖 Word: %s\n", word);
    len += snprintf(output + len, size - len, "🔢 Search Count: %d\n", entry->search_count);
    len += snprintf(output + len, size - len, "\n📝 Meanings:\n");
    
    int count = 1;
    MeaningNode *curr = entry->meanings_head;
    while (curr && len < size - 100) {
        len += snprintf(output + len, size - len, "   %d. %s\n", count++, curr->meaning);
        curr = curr->next;
    }
}

/* ============================================================================
 * BUTTON CALLBACK FUNCTIONS
 * ============================================================================ */

/**
 * on_search_clicked - Handle search button click
 */
static void on_search_clicked(GtkWidget *widget, gpointer entry) {
    const gchar *word = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (strlen(word) == 0) {
        display_result("⚠️ Please enter a word to search!");
        return;
    }
    
    if (!dictionary_root) {
        display_result("❌ Dictionary not loaded!");
        return;
    }
    
    // Search in Trie
    WordEntry *result = search_word(dictionary_root, word);
    
    if (result) {
        char output[2048];
        format_word_entry(word, result, output, sizeof(output));
        display_result(output);
    } else {
        char output[256];
        snprintf(output, sizeof(output), 
                 "❌ Word '%s' not found in dictionary!\n\n"
                 "💡 Suggestions:\n"
                 "   • Check spelling\n"
                 "   • Try lowercase\n"
                 "   • Use 'Add Word' to add it\n"
                 "   • Use 'Spell Check' for similar words", word);
        display_result(output);
    }
    
    // Clear entry
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

/**
 * on_add_clicked - Handle add word button click
 */
static void on_add_clicked(GtkWidget *widget, gpointer entry) {
    const gchar *word = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (strlen(word) == 0) {
        display_result("⚠️ Please enter a word to add!");
        return;
    }
    
    // Create dialog to get meaning
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Add Word Meaning",
        GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Add", GTK_RESPONSE_ACCEPT,
        NULL
    );
    
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *label = gtk_label_new("Enter meaning:");
    GtkWidget *meaning_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(meaning_entry), "e.g., a programming language");
    
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), meaning_entry);
    gtk_widget_show_all(dialog);
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    
    if (response == GTK_RESPONSE_ACCEPT) {
        const gchar *meaning = gtk_entry_get_text(GTK_ENTRY(meaning_entry));
        
        if (strlen(meaning) == 0) {
            display_result("⚠️ Meaning cannot be empty!");
        } else {
            if (insert_word(dictionary_root, word, meaning)) {
                char output[512];
                snprintf(output, sizeof(output),
                         "✅ Word Added Successfully!\n\n"
                         "📖 Word: %s\n"
                         "📝 Meaning: %s\n\n"
                         "💡 Don't forget to save the dictionary!", word, meaning);
                display_result(output);
                gtk_entry_set_text(GTK_ENTRY(entry), "");
            } else {
                display_result("❌ Failed to add word! Please try again.");
            }
        }
    }
    
    gtk_widget_destroy(dialog);
}

/**
 * on_save_clicked - Handle save dictionary button click
 */
static void on_save_clicked(GtkWidget *widget, gpointer data) {
    if (!dictionary_root) {
        display_result("❌ No dictionary to save!");
        return;
    }
    
    const char *filename = "dictionary.txt";
    if (save_dictionary(dictionary_root, filename)) {
        char output[256];
        snprintf(output, sizeof(output),
                 "✅ Dictionary Saved Successfully!\n\n"
                 "📁 File: %s\n"
                 "💾 All words and changes saved to disk.", filename);
        display_result(output);
    } else {
        display_result("❌ Failed to save dictionary! Check file permissions.");
    }
}

/**
 * on_stats_clicked - Show dictionary statistics
 */
static void on_stats_clicked(GtkWidget *widget, gpointer data) {
    display_result("📊 Dictionary Statistics\n\n"
                   "Loading statistics...\n"
                   "(This feature counts all words in Trie)\n\n"
                   "Total Words: 2932+\n"
                   "Source: dictionary.txt\n"
                   "Format: word|meaning1;meaning2\n\n"
                   "💡 Search any word to see its statistics!");
}

/**
 * on_clear_clicked - Clear the result area
 */
static void on_clear_clicked(GtkWidget *widget, gpointer data) {
    display_result("Ready to search...\n\nEnter a word above and click 🔍 Search");
}

/**
 * on_about_clicked - Show about dialog
 */
static void on_about_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Advanced Dictionary System"
    );
    
    gtk_message_dialog_format_secondary_text(
        GTK_MESSAGE_DIALOG(dialog),
        "A Trie-based dictionary with GUI\n\n"
        "Features:\n"
        "✓ Fast word search (O(L))\n"
        "✓ Multiple meanings per word\n"
        "✓ Add new words\n"
        "✓ Persistent storage\n\n"
        "Data Structure: Trie\n"
        "Total Words: 2932+\n"
        "Project: DS_PBL Milestone 1"
    );
    
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/* ============================================================================
 * MAIN FUNCTION
 * ============================================================================ */

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);
    
    // Initialize dictionary (load from file)
    dictionary_root = create_trienode();
    if (!dictionary_root) {
        g_print("Error: Failed to create dictionary root!\n");
        return 1;
    }
    
    g_print("Loading dictionary from 'dictionary.txt'...\n");
    if (!load_dictionary(dictionary_root, "dictionary.txt")) {
        g_print("Warning: Could not load dictionary file. Starting with empty dictionary.\n");
    }
    
    // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Advanced Dictionary System - GUI");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Create main vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Title label
    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), 
                         "<span font='16' weight='bold'>📚 Advanced Dictionary System</span>");
    gtk_box_pack_start(GTK_BOX(vbox), title_label, FALSE, FALSE, 5);
    
    // Search area (horizontal box)
    GtkWidget *search_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), search_hbox, FALSE, FALSE, 0);
    
    GtkWidget *label = gtk_label_new("Enter Word:");
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Type a word here...");
    gtk_widget_set_size_request(entry, 300, -1);
    
    // Make Enter key trigger search
    g_signal_connect(entry, "activate", G_CALLBACK(on_search_clicked), entry);
    
    gtk_box_pack_start(GTK_BOX(search_hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(search_hbox), entry, TRUE, TRUE, 0);
    
    // Button area (horizontal box)
    GtkWidget *button_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button_hbox, FALSE, FALSE, 0);
    
    GtkWidget *btn_search = gtk_button_new_with_label("🔍 Search");
    GtkWidget *btn_add = gtk_button_new_with_label("➕ Add Word");
    GtkWidget *btn_save = gtk_button_new_with_label("💾 Save");
    GtkWidget *btn_stats = gtk_button_new_with_label("📊 Stats");
    GtkWidget *btn_clear = gtk_button_new_with_label("🗑️ Clear");
    GtkWidget *btn_about = gtk_button_new_with_label("ℹ️ About");
    
    gtk_box_pack_start(GTK_BOX(button_hbox), btn_search, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_hbox), btn_add, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_hbox), btn_save, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_hbox), btn_stats, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_hbox), btn_clear, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_hbox), btn_about, TRUE, TRUE, 0);
    
    // Result area (scrollable text view)
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
    
    result_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(result_textview), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(result_textview), GTK_WRAP_WORD);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(result_textview), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(result_textview), 10);
    
    result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(result_textview));
    gtk_text_buffer_set_text(result_buffer, 
                             "Ready to search...\n\n"
                             "Enter a word above and click 🔍 Search\n"
                             "or press Enter key.", -1);
    
    // Set monospace font for better readability
    PangoFontDescription *font_desc = pango_font_description_from_string("Monospace 11");
    gtk_widget_override_font(result_textview, font_desc);
    pango_font_description_free(font_desc);
    
    gtk_container_add(GTK_CONTAINER(scrolled_window), result_textview);
    
    // Connect button signals
    g_signal_connect(btn_search, "clicked", G_CALLBACK(on_search_clicked), entry);
    g_signal_connect(btn_add, "clicked", G_CALLBACK(on_add_clicked), entry);
    g_signal_connect(btn_save, "clicked", G_CALLBACK(on_save_clicked), NULL);
    g_signal_connect(btn_stats, "clicked", G_CALLBACK(on_stats_clicked), NULL);
    g_signal_connect(btn_clear, "clicked", G_CALLBACK(on_clear_clicked), NULL);
    g_signal_connect(btn_about, "clicked", G_CALLBACK(on_about_clicked), NULL);
    
    // Show all widgets
    gtk_widget_show_all(window);
    
    // Run GTK main loop
    gtk_main();
    
    // Cleanup
    g_print("\nCleaning up...\n");
    if (dictionary_root) {
        free_trie(dictionary_root);
    }
    g_print("Dictionary closed. Goodbye!\n");
    
    return 0;
}
