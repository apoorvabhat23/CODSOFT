#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string isbn;
    bool available = true;
};

struct Borrower {
    int id;
    string name;
};

struct Transaction {
    int bookId;
    int borrowerId;
    time_t checkoutDate;
    time_t returnDate = 0;
    double fine = 0;
};

vector<Book> books;
vector<Borrower> borrowers;
vector<Transaction> transactions;

int generateBookId() {
    static int bookId = 1;
    return bookId++;
}

int generateBorrowerId() {
    static int borrowerId = 1;
    return borrowerId++;
}

void addBook() {
    Book b;
    b.id = generateBookId();
    cout << "Enter title: ";
    getline(cin >> ws, b.title);
    cout << "Enter author: ";
    getline(cin >> ws, b.author);
    cout << "Enter ISBN: ";
    getline(cin >> ws, b.isbn);
    books.push_back(b);
    cout << "Book added.\n";
}

void searchBook() {
    string keyword;
    cout << "Enter title, author, or ISBN to search: ";
    getline(cin >> ws, keyword);

    bool found = false;
    for (auto &b : books) {
        if (b.title.find(keyword) != string::npos ||
            b.author.find(keyword) != string::npos ||
            b.isbn.find(keyword) != string::npos) {
            cout << "ID: " << b.id << " | " << b.title << " by " << b.author
                 << " | ISBN: " << b.isbn
                 << " | " << (b.available ? "Available" : "Checked Out") << endl;
            found = true;
        }
    }
    if (!found) cout << "No books found.\n";
}

void addBorrower() {
    Borrower b;
    b.id = generateBorrowerId();
    cout << "Enter borrower name: ";
    getline(cin >> ws, b.name);
    borrowers.push_back(b);
    cout << "Borrower added.\n";
}

void checkoutBook() {
    int bookId, borrowerId;
    cout << "Enter Book ID: ";
    cin >> bookId;
    cout << "Enter Borrower ID: ";
    cin >> borrowerId;

    for (auto &b : books) {
        if (b.id == bookId && b.available) {
            b.available = false;
            Transaction t;
            t.bookId = bookId;
            t.borrowerId = borrowerId;
            t.checkoutDate = time(0);
            transactions.push_back(t);
            cout << "Book checked out.\n";
            return;
        }
    }
    cout << "Book not available or not found.\n";
}

void returnBook() {
    int bookId;
    cout << "Enter Book ID to return: ";
    cin >> bookId;

    for (auto &t : transactions) {
        if (t.bookId == bookId && t.returnDate == 0) {
            t.returnDate = time(0);
            double seconds = difftime(t.returnDate, t.checkoutDate);
            int days = static_cast<int>(seconds / (60 * 60 * 24));
            if (days > 14) {
                t.fine = (days - 14) * 1.0;
            }
            for (auto &b : books) {
                if (b.id == bookId) {
                    b.available = true;
                    break;
                }
            }
            cout << "Book returned. Fine: $" << fixed << setprecision(2) << t.fine << endl;
            return;
        }
    }
    cout << "No active checkout found for this book.\n";
}

void listBooks() {
    for (auto &b : books) {
        cout << "ID: " << b.id << " | " << b.title << " by " << b.author
             << " | ISBN: " << b.isbn
             << " | " << (b.available ? "Available" : "Checked Out") << endl;
    }
}

void listBorrowers() {
    for (auto &b : borrowers) {
        cout << "ID: " << b.id << " | Name: " << b.name << endl;
    }
}

int main() {
    while (true) {
        cout << "\nLibrary Menu\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Add Borrower\n";
        cout << "4. Checkout Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. List Borrowers\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: addBorrower(); break;
            case 4: checkoutBook(); break;
            case 5: returnBook(); break;
            case 6: listBooks(); break;
            case 7: listBorrowers(); break;
            case 8: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
