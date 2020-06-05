/*
 * LIBRARY MANAGEMENT SYSTEM
 *
*/

#include <bits/stdc++.h>

using namespace std;

char ADMIN[] = "admin";
char USER[] = "user";

class User {
    char username[10], passwd[15], addr[50], role[6];
    long int contact;

    public:
    User *next;

    User() {
        strcpy(role, "user");
    }

    // Getters (char* getters can act as setters too)
    char* getRole() { return role; }
    char* getPasswd() { return passwd; }
    char* getUsername() { return username; }
    char* getAddr() { return addr; }
    int getContact() { return contact; }

    // Setters
    void setContact(long int contact) { this->contact = contact; }
} *user_head, *curr_user;

void INITIALIZE_WITH_DUMMY_DATA() {
    user_head = new User();
    strcpy(user_head->getRole(), ADMIN);
    strcpy(user_head->getUsername(), "admin");
    strcpy(user_head->getPasswd(), "password");
    strcpy(user_head->getAddr(), "Fake Address, don't go there!!!\0");
    user_head->setContact(9999999999);
}

class Book {
    char title[20], author[20], category[20], status[10];
    int publ_year, code;


    public:
    Book *next;
    User *issued_by;

    // Initialize the Object
    Book(Book *books_head) {
        strcpy(status, "available");
        code = books_head == NULL ? 1 : books_head->code + 1;
        next = NULL;
        issued_by = NULL;
    }

    // Getters (char* getters can act as setters too)
    int getPublYear() {return publ_year;}
    int getCode() {return code;}
    char* getTitlePtr() {return title;}
    char* getAuthorPtr() {return author;}
    char* getCategoryPtr() {return category;}
    char* getStatusPtr() {return status;}

    // Setters
    void setPublYear(int publ_year) {this->publ_year = publ_year;}
} *books_head;

void createAndAddBook() {
    // Allocate memory for new Node
    Book *new_book = new Book(books_head);
    int publ_year;

    // Get the Input
    getchar();
    cout << "Enter the Book Title: ";
    fgets(new_book->getTitlePtr(), 20, stdin);
    new_book->getTitlePtr()[strlen(new_book->getTitlePtr()) - 1] = '\0'; // To remove the newline character at the end
    cout << "Enter the Book Author: ";
    fgets(new_book->getAuthorPtr(), 20, stdin);
    new_book->getAuthorPtr()[strlen(new_book->getAuthorPtr()) - 1] = '\0'; // To remove the newline character at the end
    cout << "Enter the Book Category: ";
    fgets(new_book->getCategoryPtr(), 20, stdin);
    new_book->getCategoryPtr()[strlen(new_book->getCategoryPtr()) - 1] = '\0'; // To remove the newline character at the end
    cout << "Enter the Book's Publishing Year: ";
    cin >> publ_year;
    new_book->setPublYear(publ_year);

    // Add the node to the Linked List
    new_book->next = books_head;
    books_head = new_book;
}

void deleteBookRecord() {
    Book *tmp = books_head, *prev;
    int book_id;

    cout << "Enter the id of the Book Record to be Deleted: ";
    cin >> book_id;

    // If the Head node is the node to be deleted
    if (tmp != NULL && tmp->getCode() == book_id) {
        books_head = tmp->next;
        delete tmp;
        return;
    }

    while (tmp != NULL && tmp->getCode() != book_id) {
        prev = tmp;
        tmp = tmp->next;
    }

    // If the while loop stopped before reaching the end of the list
    // This would imply that we have found the node to be deleted
    if (tmp != NULL) {
        cout << "Book Found!" << endl;
        prev->next = tmp->next;
        delete tmp;
        cout << "Book Record Deleted" << endl;
        return;
    }

    cout << "Book Record not Found!!" << endl;
}

void listAllBooks() {
    Book *tmp = books_head;
    int count = 0;

    while(tmp != NULL) {
        cout << "Book Code: " << tmp->getCode() << endl;
        cout << "Title: " << tmp->getTitlePtr() << endl;
        cout << "Author: " << tmp->getAuthorPtr() << endl;
        cout << "Category: " << tmp->getCategoryPtr() << endl;
        cout << "Year Published in: " << tmp->getPublYear() << endl;
        cout << "Status: " << tmp->getStatusPtr() << endl;

        // Show the Username of the user who issued the book to an admin only
        if (strcmp(curr_user->getRole(), ADMIN) == 0 && strcmp(tmp->getStatusPtr(), "issued") == 0)
            cout << "Issued By: " << (tmp->issued_by)->getUsername() << endl;

        cout << endl;
        count++;
        tmp = tmp->next;
    }

    cout << "Found " << count << " Books.";
}

void searchByCode() {
    Book *tmp = books_head;
    int code;
    cout << "Enter the code of the Book you're looking for: ";
    cin >> code;
    while(tmp != NULL) {
        if(tmp->getCode() == code) {
            cout << "Book Found!!" << endl;
            cout << "Title: " << tmp->getTitlePtr() << endl;
            cout << "Author: " << tmp->getAuthorPtr() << endl;
            cout << "Category: " << tmp->getCategoryPtr() << endl;
            cout << "Year Published in: " << tmp->getPublYear() << endl;
            cout << "Status: " << tmp->getStatusPtr() << endl << endl;
            return;
        }
        tmp = tmp->next;
    }
    // The control will reach this line only when no record is found
    cout << "Book Record not found!!" << endl;
}

void searchByCategory() {
    Book *tmp = books_head;
    char category[20];
    int flag, count;
    cout << "Enter the category of the Book you're looking for: ";
    getchar();
    fgets(category, 20, stdin);
    category[strlen(category) - 1] = '\0';
    while(tmp != NULL) {
        if(!strcmp(category, tmp->getCategoryPtr())) {
            cout << "Book Code: " << tmp->getCode() << endl;
            cout << "Title: " << tmp->getTitlePtr() << endl;
            cout << "Author: " << tmp->getAuthorPtr() << endl;
            cout << "Category: " << tmp->getCategoryPtr() << endl;
            cout << "Year Published in: " << tmp->getPublYear() << endl;
            cout << "Status: " << tmp->getStatusPtr() << endl << endl;
            count++;
        }
        tmp = tmp->next;
    }

    if(!count)
        cout << "No Books not found!!" << endl;
    else
        cout << "Found " << count << " Books";
}

void issueBook() {
    Book *tmp = books_head;
    int code;
    cout << "Enter the code of the book to be issued: ";
    cin >> code;
    while(tmp != NULL) {
        if(tmp->getCode() == code) {
            cout << "Book Found!!" << endl;

            if(!strcmp(tmp->getStatusPtr(), "available")) {
                strcpy(tmp->getStatusPtr(), "issued");
                tmp->issued_by = curr_user;
            } else
                cout << "Sorry, but the book has already been issued by someone." << endl;

            return;
        }
        tmp = tmp->next;
    }
    // The control will reach this line only when no record is found
    cout << "Book Record not found!!" << endl;
}

void returnBook() {
    Book *tmp = books_head;
    int code;
    cout << "Enter the code of the book to be returned: ";
    cin >> code;
    while(tmp != NULL) {
        if(tmp->getCode() == code) {
            cout << "Book Found!!" << endl;
            if(!strcmp(tmp->getStatusPtr(), "issued")) {
                if(tmp->issued_by == curr_user) {
                    strcpy(tmp->getStatusPtr(), "available");
                    tmp->issued_by = NULL;
                } else
                    cout << "The Book wasn't issued by this account!" << endl;
            } else
                cout << "The book hasn't been issued yet!!." << endl;
            return;
        }
        tmp = tmp->next;
    }
    // The control will reach this line only when no record is found
    cout << "Book Record not found!!" << endl;
}

void userPanel() {
    int ch;

    while (ch != 6) {
        cout << "\n\nWelcome to the User Panel!" << endl;
        cout << "What action would you like to perform?" << endl;
        cout << "1. List all Books" << endl;
        cout << "2. Search Books by book code" << endl;
        cout << "3. Search Books by Category" << endl;
        cout << "4. Issue a Book" << endl;
        cout << "5. Return a Book" << endl;
        cout << "6. Logout" << endl;
        cin >> ch;

        switch (ch){
            case 1: listAllBooks();
                break;
            case 2: searchByCode();
                break;
            case 3: searchByCategory();
                break;
            case 4: issueBook();
                break;
            case 5: returnBook();
                break;
            case 6:
                break;
            default: cout << "Please enter a valid option!!" << endl;
                break;
        }
    }
}

void adminPanel() {
    int ch;
    while (ch != 4) {
        cout << "\n\nWelcome to the Admin Panel!" << endl;
        cout << "What action would you like to perform?" << endl;
        cout << "1. List all Books" << endl;
        cout << "2. Add a Book" << endl;
        cout << "3. Delete a Book" << endl;
        cout << "4. Logout" << endl;
        cin >> ch;

        switch (ch){
            case 1: listAllBooks();
                break;
            case 2: createAndAddBook();
                break;
            case 3: deleteBookRecord();
                break;
            case 4:
                break;
            default: cout << "Please enter a valid option!!" << endl;
                break;
        }
    }
}

int authenticate(char username[], char passwd[]) {
    User *tmp = user_head;
    while(tmp != NULL) {
        if(!strcmp(tmp->getUsername(), username) && !strcmp(tmp->getPasswd(), passwd)) {
            curr_user = tmp;
            return 1;
        }
        tmp = tmp->next;
    }
    cout << "Incorrect Username or Password!!" << endl;
    return 0;
}

void adminLogin() {
    char passwd[10];
    cout << "Enter the admin password: ";
    cin >> passwd;
    if(authenticate(ADMIN, passwd))
        adminPanel();
}

void userLogin() {
    char username[10], passwd[10];
    cout << "Enter your Username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> passwd;
    if(authenticate(username, passwd))
        userPanel();
}

void userRegistration() {
    User *new_user = new User();
    long contact;
    cout << "Enter Username: ";
    cin >> new_user->getUsername();
    cout << "Enter Pssword: ";
    cin >> new_user->getPasswd();
    cout << "Enter your Address: ";
    getchar();
    fgets(new_user->getAddr(), 50, stdin);
    new_user->getAddr()[strlen(new_user->getAddr()) - 1] = '\0';
    cout << "Enter your Contact No.: ";
    cin >> contact;
    new_user->setContact(contact);

    new_user->next = user_head;
    user_head = new_user;
}

int main() {
    INITIALIZE_WITH_DUMMY_DATA();
    int ch;
    while(ch != 4) {
        cout << "Welcome to the Library Management System\nPlease choose an Option:\n";
        cout << "1. Admin Login" << endl;
        cout << "2. User Login" << endl;
        cout << "3. Register as a new user" << endl;
        cout << "4. Exit" << endl;
        cin >> ch;
        switch(ch) {
            case 1: adminLogin();
                    break;
            case 2: userLogin();
                    break;
            case 3: userRegistration();
                    break;
            case 4: break;
            default: cout << "Please Enter a valid choice!!" << endl;
                    break;
        }
    }
    return 0;
}
