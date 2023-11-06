#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class PhoneBookEntry {
private:
    string* fullName;
    string homePhone;
    string workPhone;
    string mobilePhone;
    string additionalInfo;

public:

    PhoneBookEntry()
        : fullName(new string()), homePhone(""), workPhone(""), mobilePhone(""), additionalInfo("") {}

    PhoneBookEntry(const string& name, const string& home, const string& work, const string& mobile, const string& info)
        : fullName(new string(name)), homePhone(home), workPhone(work), mobilePhone(mobile), additionalInfo(info) {}

    ~PhoneBookEntry() {
        delete fullName;
    }

    const string& getFullName() const { return *fullName; }
    const string& getHomePhone() const { return homePhone; }
    const string& getWorkPhone() const { return workPhone; }
    const string& getMobilePhone() const { return mobilePhone; }
    const string& getAdditionalInfo() const { return additionalInfo; }

    void setHomePhone(const string& phone) { homePhone = phone; }
    void setWorkPhone(const string& phone) { workPhone = phone; }
    void setMobilePhone(const string& phone) { mobilePhone = phone; }
    void setAdditionalInfo(const string& info) { additionalInfo = info; }
};

class PhoneBook {
private:
    PhoneBookEntry* entries;
    int size;
    int capacity;

public:
    PhoneBook(int initialCapacity = 10)
        : size(0), capacity(initialCapacity) {
        entries = new PhoneBookEntry[initialCapacity];
    }

    ~PhoneBook() {
        delete[] entries;
    }

    void addEntry(const PhoneBookEntry& entry) {
        if (size >= capacity) {
            // Увеличиваем массив, если не хватает места
            capacity *= 2;
            PhoneBookEntry* newEntries = new PhoneBookEntry[capacity];
            for (int i = 0; i < size; i++) {
                newEntries[i] = entries[i];
            }
            delete[] entries;
            entries = newEntries;
        }

        entries[size] = entry;
        size++;
    }

    void removeEntry(const string& fullName) {
        for (int i = 0; i < size; i++) {
            if (entries[i].getFullName() == fullName) {
                for (int j = i; j < size - 1; j++) {
                    entries[j] = entries[j + 1];
                }
                size--;
                break;
            }
        }
    }

    PhoneBookEntry findEntry(const string& fullName) {
        for (int i = 0; i < size; i++) {
            if (entries[i].getFullName() == fullName) {
                return entries[i];
            }
        }
        return PhoneBookEntry("", "", "", "", "");
    }

    void displayAllEntries() {
        for (int i = 0; i < size; i++) {
            cout << "Name: " << entries[i].getFullName() << endl;
            cout << "Home Phone: " << entries[i].getHomePhone() << endl;
            cout << "Work Phone: " << entries[i].getWorkPhone() << endl;
            cout << "Mobile Phone: " << entries[i].getMobilePhone() << endl;
            cout << "Additional Info: " << entries[i].getAdditionalInfo() << endl;
            cout << "----------------------" << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < size; i++) {
                file << entries[i].getFullName() << "\n";
                file << entries[i].getHomePhone() << "\n";
                file << entries[i].getWorkPhone() << "\n";
                file << entries[i].getMobilePhone() << "\n";
                file << entries[i].getAdditionalInfo() << "\n";
            }
            file.close();
        }
        else {
            cerr << "Error opening file for writing." << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            clearEntries();
            string name, home, work, mobile, info;
            while (getline(file, name) && getline(file, home) && getline(file, work) && getline(file, mobile) && getline(file, info)) {
                addEntry(PhoneBookEntry(name, home, work, mobile, info));
            }
            file.close();
        }
        else {
            cerr << "Error opening file for reading." << endl;
        }
    }

    void clearEntries() {
        size = 0;
    }
};

int main() {
    PhoneBook phoneBook;

    PhoneBookEntry entry1("Shaposhnikov Volodimir", "380968291959", "5555555555", "9999999999", "Friend");
    PhoneBookEntry entry2("Shaposhnikov Volodimir Volodimirovich", "123123", "7777777777", "1111111111", "Family");

    phoneBook.addEntry(entry1);
    phoneBook.addEntry(entry2);

    phoneBook.displayAllEntries();

    phoneBook.saveToFile("phonebook.txt");

    return 0;
}
