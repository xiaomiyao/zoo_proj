#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>

class Keeper {
public:
    static const int MAX_KEEPERS = 10;
    static int keeperCount;
    std::string name;
    std::string dateOfBirth;

    Keeper(const std::string& name, const std::string& dob) : name(name), dateOfBirth(dob) {
        keeperCount++;
    }

    ~Keeper() {
        keeperCount--;
    }
};

class Veterinarian {
public:
    static const int MAX_VETERINARIANS = 3;
    static int veterinarianCount;
    std::string name;
    std::string dateOfBirth;

    Veterinarian(const std::string& name, const std::string& dob) : name(name), dateOfBirth(dob) {
        veterinarianCount++;
    }

    ~Veterinarian() {
        veterinarianCount--;
    }
};

class Guide {
public:
    static const int MAX_GUIDES = 5;
    static int guideCount;
    std::string name;
    std::string dateOfBirth;

    Guide(const std::string& name, const std::string& dob) : name(name), dateOfBirth(dob) {
        guideCount++;
    }

    ~Guide() {
        guideCount--;
    }
};

// Инициализация статических переменных
int Keeper::keeperCount = 0;
int Veterinarian::veterinarianCount = 0;
int Guide::guideCount = 0;

// Объявление функций
void addPersonnel();
void removePersonnel();
void displayAllPersonnel();
void displayPersonnelByCategory();
void searchPersonnelByName();
void keeperSubMenu();
void veterinarianSubMenu();
void guideSubMenu();
void addMessage();
void viewWorkSchedule();
void viewFeedingSchedule();
void displayFAQ();

int main() {
    char choice;

    do {
        std::cout << "\nMain Menu (Главное Меню):" << std::endl;
        std::cout << "1. Add personnel (Добавить персонал)" << std::endl;
        std::cout << "2. Remove personnel (Удалить персонал)" << std::endl;
        std::cout << "3. Display all personnel (Показать весь персонал)" << std::endl;
        std::cout << "4. Display personnel by category (Показать персонал по категориям)" << std::endl;
        std::cout << "5. Search personnel by name (Поиск персонала по имени)" << std::endl;
        std::cout << "6. FAQ (Часто задаваемые вопросы)" << std::endl;
        std::cout << "7. Exit (Выход)" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case '1':
                addPersonnel();
                break;
            case '2':
                removePersonnel();
                break;
            case '3':
                displayAllPersonnel();
                break;
            case '4':
                displayPersonnelByCategory();
                break;
            case '5':
                searchPersonnelByName();
                break;
            case '6':
                displayFAQ();
                break;
            case '7':
                std::cout << "Exiting program. (Выход из программы)" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again. (Неверный выбор. Пожалуйста, введите снова.)" << std::endl;
                break;
        }
    } while (choice != '7');

    return 0;
}

void addPersonnel() {
    char categoryChoice;

    std::cout << "\nAdd Personnel Menu (Меню добавления персонала):" << std::endl;
    std::cout << "Select category of personnel to add (Выберите категорию персонала для добавления):" << std::endl;
    std::cout << "1. Keeper (Смотритель)" << std::endl;
    std::cout << "2. Veterinarian (Ветеринар)" << std::endl;
    std::cout << "3. Guide (Гид)" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> categoryChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name, dateOfBirth;

    std::cout << "Enter personnel's full name (Введите ФИО сотрудника): ";
    std::getline(std::cin, name);

    std::cout << "Enter personnel's date of birth (Введите дату рождения сотрудника): ";
    std::getline(std::cin, dateOfBirth);

    switch (categoryChoice) {
        case '1': {
            // Добавление сотрудника в категорию смотрителей
            Keeper newKeeper(name, dateOfBirth);
            std::ofstream outFile("personnel.txt", std::ios_base::app);
            if (outFile.is_open()) {
                outFile << "Keeper: " << newKeeper.name << ", Date of Birth: " << newKeeper.dateOfBirth << std::endl;
                outFile.close();
                std::cout << "Keeper added successfully. (Смотритель успешно добавлен)" << std::endl;
                keeperSubMenu();
            } else {
                std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
            }
            break;
        }
        case '2': {
            // Добавление сотрудника в категорию ветеринаров
            Veterinarian newVet(name, dateOfBirth);
            std::ofstream outFile("personnel.txt", std::ios_base::app);
            if (outFile.is_open()) {
                outFile << "Veterinarian: " << newVet.name << ", Date of Birth: " << newVet.dateOfBirth << std::endl;
                outFile.close();
                std::cout << "Veterinarian added successfully. (Ветеринар успешно добавлен)" << std::endl;
                veterinarianSubMenu();
            } else {
                std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
            }
            break;
        }
        case '3': {
            // Добавление сотрудника в категорию гидов
            Guide newGuide(name, dateOfBirth);
            std::ofstream outFile("personnel.txt", std::ios_base::app);
            if (outFile.is_open()) {
                outFile << "Guide: " << newGuide.name << ", Date of Birth: " << newGuide.dateOfBirth << std::endl;
                outFile.close();
                std::cout << "Guide added successfully. (Гид успешно добавлен)" << std::endl;
                guideSubMenu();
            } else {
                std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Please enter again. (Неверный выбор. Пожалуйста, введите снова.)" << std::endl;
            break;
    }
}

void removePersonnel() {
    std::ifstream inFile("personnel.txt");

    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open personnel.txt for reading!" << std::endl;
        return;
    }

    std::vector<std::string> personnelList;

    // Прочитать список персонала из файла
    std::string line;
    while (std::getline(inFile, line)) {
        personnelList.push_back(line);
    }

    inFile.close(); // Закрыть файл

    std::string searchName;
    bool found = false;

    std::cout << "\nEnter the name of the personnel to remove: ";
    std::getline(std::cin >> std::ws, searchName);

    // Поиск и удаление сотрудника с заданным именем
    for (auto it = personnelList.begin(); it != personnelList.end(); ++it) {
        if ((*it).find(searchName) != std::string::npos) {
            personnelList.erase(it);
            found = true;
            std::cout << "Personnel '" << searchName << "' removed successfully. (Персонал '" << searchName << "' успешно удален)" << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "No personnel found with the name: " << searchName << std::endl;
    }

    // Записать обновленный список персонала в файл
    std::ofstream outFile("personnel.txt");

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
        return;
    }

    for (const auto& person : personnelList) {
        outFile << person << '\n';
    }

    outFile.close(); // Закрыть файл
}

void keeperSubMenu() {
    char choice;

    do {
        std::cout << "\nKeeper Submenu (Подменю смотрителя):" << std::endl;
        std::cout << "1. View work schedule (Посмотреть график работы)" << std::endl;
        std::cout << "2. View feeding schedule (Посмотреть график кормления)" << std::endl;
        std::cout << "3. Add message (Добавить сообщение)" << std::endl;
        std::cout << "4. Return to main menu (Вернуться в главное меню)" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case '1':
                viewWorkSchedule();
                break;
            case '2':
                viewFeedingSchedule();
                break;
            case '3':
                addMessage();
                break;
            case '4':
                std::cout << "Returning to main menu. (Возвращение в главное меню)" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again. (Неверный выбор. Пожалуйста, введите снова.)" << std::endl;
                break;
        }
    } while (choice != '4');
}

void veterinarianSubMenu() {
    char choice;

    do {
        std::cout << "\nVeterinarian Submenu:" << std::endl;
        std::cout << "1. View work schedule" << std::endl;
        std::cout << "2. View feeding schedule" << std::endl;
        std::cout << "3. Add message" << std::endl;
        std::cout << "4. Return to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case '1':
                viewWorkSchedule();
                break;
            case '2':
                viewFeedingSchedule();
                break;
            case '3':
                addMessage();
                break;
            case '4':
                std::cout << "Returning to main menu." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
                break;
        }
    } while (choice != '4');
}

void guideSubMenu() {
    char choice;

    do {
        std::cout << "\nGuide Submenu:" << std::endl;
        std::cout << "1. View work schedule" << std::endl;
        std::cout << "2. View available programs" << std::endl;
        std::cout << "3. Add message" << std::endl;
        std::cout << "4. Return to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case '1':
                viewWorkSchedule();
                break;
            case '2':
                // Здесь реализуйте просмотр доступных программ от гида
                break;
            case '3':
                addMessage();
                break;
            case '4':
                std::cout << "Returning to main menu." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
                break;
        }
    } while (choice != '4');
}

void addMessage() {
    std::string message;
    std::cout << "Enter the message: ";
    std::getline(std::cin >> std::ws, message);

    std::ofstream outFile("messages.txt", std::ios_base::app);
    if (outFile.is_open()) {
        outFile << message << std::endl;
        std::cout << "Message added successfully." << std::endl;
        outFile.close();
    } else {
        std::cerr << "Error: Unable to open messages.txt for writing!" << std::endl;
    }
}

void viewWorkSchedule() {
    std::ifstream inFile("work_schedule.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open work_schedule.txt for reading!" << std::endl;
        return;
    }

    std::cout << "\nWork Schedule:" << std::endl;
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    inFile.close();
}

void viewFeedingSchedule() {
    std::ifstream inFile("feeding_schedule.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open feeding_schedule.txt for reading!" << std::endl;
        return;
    }

    std::cout << "\nFeeding Schedule:" << std::endl;
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    inFile.close();
}

void displayAllPersonnel() {
    std::ifstream inFile("personnel.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open personnel.txt for reading!" << std::endl;
        return;
    }

    std::cout << "\nAll Personnel:" << std::endl;
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    inFile.close();
}

void displayPersonnelByCategory() {
    std::ifstream inFile("personnel.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open personnel.txt for reading!" << std::endl;
        return;
    }

    std::string categoryChoice;
    std::cout << "\nSelect category of personnel to display:" << std::endl;
    std::cout << "1. Keepers" << std::endl;
    std::cout << "2. Veterinarians" << std::endl;
    std::cout << "3. Guides" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> categoryChoice;

    switch (categoryChoice[0]) {
        case '1': {
            std::cout << "\nKeepers:" << std::endl;
            std::string line;
            while (std::getline(inFile, line)) {
                if (line.find("Keeper:") != std::string::npos) {
                    std::cout << line << std::endl;
                }
            }
            break;
        }
        case '2': {
            std::cout << "\nVeterinarians:" << std::endl;
            std::string line;
            while (std::getline(inFile, line)) {
                if (line.find("Veterinarian:") != std::string::npos) {
                    std::cout << line << std::endl;
                }
            }
            break;
        }
        case '3': {
            std::cout << "\nGuides:" << std::endl;
            std::string line;
            while (std::getline(inFile, line)) {
                if (line.find("Guide:") != std::string::npos) {
                    std::cout << line << std::endl;
                }
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Please enter again." << std::endl;
            break;
    }

    inFile.close();
}

void searchPersonnelByName() {
    std::ifstream inFile("personnel.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open personnel.txt for reading!" << std::endl;
        return;
    }

    std::string searchName;
    std::cout << "Enter the name to search: ";
    std::getline(std::cin, searchName);

    bool found = false;
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.find(searchName) != std::string::npos) {
            std::cout << line << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No personnel found with the name: " << searchName << std::endl;
    }

    inFile.close();
}

void displayFAQ() {
    std::ifstream inFile("FAQ.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open FAQ.txt for reading!" << std::endl;
        return;
    }

    std::cout << "\nFAQ (Часто задаваемые вопросы):" << std::endl;
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    inFile.close();
}
