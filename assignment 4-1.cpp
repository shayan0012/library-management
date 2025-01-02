#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Book
{
    int id;
    std::string title;
    std::string author;
    int quantity;
};

class Library
{
private:
    std::vector<Book> inventory;
    const std::string filename = "library_inventory.txt";

public:
    Library()
    {
        loadInventory();
    }

    void addBook()
    {
        Book newBook;
        std::cout << "Enter Book ID: ";
        std::cin >> newBook.id;
        std::cin.ignore();
        std::cout << "Enter Title: ";
        std::getline(std::cin, newBook.title);
        std::cout << "Enter Author: ";
        std::getline(std::cin, newBook.author);
        std::cout << "Enter Quantity: ";
        std::cin >> newBook.quantity;
        inventory.push_back(newBook);
        saveInventory();
        std::cout << "Book added successfully!\n";
    }

    void searchBook()
    {
        std::string searchTerm;
        std::cout << "Enter Book ID or Title to search: ";
        std::cin.ignore();
        std::getline(std::cin, searchTerm);
        for (const auto& book : inventory)
        {
            if (std::to_string(book.id) == searchTerm || book.title == searchTerm)
            {
                std::cout << "Found Book - ID: " << book.id << ", Title: " << book.title
                          << ", Author: " << book.author << ", Quantity: " << book.quantity << "\n";
                return;
            }
        }
        std::cout << "Book not found.\n";
    }

    void displayBooks()
    {
        std::cout << "Available Books:\n";
        for (const auto& book : inventory)
        {
            std::cout << "ID: " << book.id << ", Title: " << book.title
                      << ", Author: " << book.author << ", Quantity: " << book.quantity << "\n";
        }
    }

    void saveInventory()
    {
        std::ofstream outFile(filename);
        for (const auto& book : inventory)
        {
            outFile << book.id << "\n" << book.title << "\n" << book.author << "\n" << book.quantity << "\n";
        }
        outFile.close();
    }

    void loadInventory()
    {
        std::ifstream inFile(filename);
        if (!inFile) return;
        Book book;
        while (inFile >> book.id)
        {
            inFile.ignore();
            std::getline(inFile, book.title);
            std::getline(inFile, book.author);
            inFile >> book.quantity;
            inventory.push_back(book);
        }
        inFile.close();
    }
};

int main()
{
    Library library;
    int choice;
    do {
        std::cout << "Library Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Search Book\n";
        std::cout << "3. Display All Books\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                library.addBook();
                break;
            case 2:
                library.searchBook();
                break;
            case 3:
                library.displayBooks();
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
