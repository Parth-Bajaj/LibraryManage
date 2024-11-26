#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a Book
typedef struct Book {
    int bookID;
    char title[100];
    char author[100];
    struct Book* prev; // Pointer to the previous book
    struct Book* next; // Pointer to the next book
} Book;

// Function prototypes
void addBook(Book** head, int bookID, const char* title, const char* author);
void removeBook(Book** head, int bookID);
void displayBooks(Book* head);
Book* searchBookByTitle(Book* head, const char* title);
Book* searchBookByAuthor(Book* head, const char* author);
void freeLibrary(Book* head);
void trimNewline(char* str);

// Main function
int main() {
    Book* library = NULL; // Pointer to the head of the library list
    int choice, bookID;
    char title[100], author[100];
    Book* bookByTitle = NULL;  // Declare variables outside switch
    Book* bookByAuthor = NULL; 

    while (1) {
        printf("\n========== Book Library Management System ==========\n");
        printf("1. Add a new book\n");
        printf("2. Remove a book\n");
        printf("3. Display all books\n");
        printf("4. Search for a book by title\n");
        printf("5. Search for a book by author\n");
        printf("6. Exit\n");
        printf("====================================================\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character left by scanf

        switch (choice) {
            case 1:
                // Add a new book
                printf("Enter Book ID: ");
                scanf("%d", &bookID);
                getchar(); // consume newline
                printf("Enter Book Title: ");
                fgets(title, sizeof(title), stdin);
                trimNewline(title); // Remove the trailing newline
                printf("Enter Author Name: ");
                fgets(author, sizeof(author), stdin);
                trimNewline(author); // Remove the trailing newline
                addBook(&library, bookID, title, author);
                break;

            case 2:
                // Remove a book
                printf("Enter Book ID to remove: ");
                scanf("%d", &bookID);
                removeBook(&library, bookID);
                break;

            case 3:
                // Display all books
                displayBooks(library);
                break;

            case 4:
                // Search for a book by title
                printf("Enter Book Title to search: ");
                fgets(title, sizeof(title), stdin);
                trimNewline(title); // Remove the trailing newline
                bookByTitle = searchBookByTitle(library, title);
                if (bookByTitle) {
                    printf("Found Book: ID: %d, Title: %s, Author: %s\n",
                           bookByTitle->bookID, bookByTitle->title, bookByTitle->author);
                } else {
                    printf("Book not found.\n");
                }
                break;

            case 5:
                // Search for a book by author
                printf("Enter Author Name to search: ");
                fgets(author, sizeof(author), stdin);
                trimNewline(author); // Remove the trailing newline
                bookByAuthor = searchBookByAuthor(library, author);
                if (bookByAuthor) {
                    printf("Found Book: ID: %d, Title: %s, Author: %s\n",
                           bookByAuthor->bookID, bookByAuthor->title, bookByAuthor->author);
                } else {
                    printf("Book not found.\n");
                }
                break;

            case 6:
                // Exit the program
                freeLibrary(library);
                printf("Exiting the library management system.\n");
                return 0;

            default:
                printf("Invalid choice! Please choose again.\n");
        }
    }

    return 0;
}

// Function to add a book to the library (doubly linked list)
void addBook(Book** head, int bookID, const char* title, const char* author) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newBook->bookID = bookID;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->prev = NULL;
    newBook->next = *head;

    if (*head != NULL) {
        (*head)->prev = newBook; // set previous head's prev pointer to new book
    }

    *head = newBook; // update head to new book
    printf("Book added successfully!\n");
}

// Function to remove a book by ID
void removeBook(Book** head, int bookID) {
    Book* current = *head;
    while (current != NULL) {
        if (current->bookID == bookID) {
            if (current->prev != NULL) {
                current->prev->next = current->next; // set prev node's next to current's next
            } else {
                *head = current->next; // update head if removing the first book
            }
            if (current->next != NULL) {
                current->next->prev = current->prev; // set next node's prev to current's prev
            }
            free(current);
            printf("Book with ID %d removed successfully!\n", bookID);
            return;
        }
        current = current->next;
    }
    printf("Book with ID %d not found.\n", bookID);
}

// Function to display all books
void displayBooks(Book* head) {
    if (head == NULL) {
        printf("No books in the library.\n");
        return;
    }
    Book* current = head;
    while (current != NULL) {
        printf("ID: %d, Title: %s, Author: %s\n", current->bookID, current->title, current->author);
        current = current->next;
    }
}

// Function to search for a book by title
Book* searchBookByTitle(Book* head, const char* title) {
    Book* current = head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            return current; // found the book
        }
        current = current->next;
    }
    return NULL; // book not found
}

// Function to search for a book by author
Book* searchBookByAuthor(Book* head, const char* author) {
    Book* current = head;
    while (current != NULL) {
        if (strcmp(current->author, author) == 0) {
            return current; // found the book
        }
        current = current->next;
    }
    return NULL; // book not found
}

// Function to free the entire library (free all books)
void freeLibrary(Book* head) {
    Book* current = head;
    while (current != NULL) {
        Book* next = current->next;
        free(current);
        current = next;
    }
}

// Helper function to trim newline character from input strings
void trimNewline(char* str) {
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}
