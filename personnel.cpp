#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <map>

class Keeper {
public:
    static const int MAX_KEEPERS = 10;
    static int keeperCount;

    std::string name;
    std::string dateOfBirth;

    Keeper(const std::string& name, const std::string& dateOfBirth)
        : name(name), dateOfBirth(dateOfBirth) {
            keeperCount++;
    }
};

class Veterinarian {
public:
    static const int MAX_VETERINARIANS = 3;
    static int veterinarianCount;

    std::string name;
    std::string dateOfBirth;

    Veterinarian(const std::string& name, const std::string& dateOfBirth)
        : name(name), dateOfBirth(dateOfBirth) {
            veterinarianCount++;
    }
};

class Guide {
public:
    static const int MAX_GUIDES = 6;
    static int guideCount;

    std::string name;
    std::string dateOfBirth;
    std::string languages;

    Guide(const std::string& name, const std::string& dateOfBirth, const std::string& languages)
        : name(name), dateOfBirth(dateOfBirth), languages(languages) {
            guideCount++;
    }
};

int Keeper::keeperCount = 0;
int Veterinarian::veterinarianCount = 0;
int Guide::guideCount = 0;


// Объявление функций
void mainMenu();
void personnelSubMenu();
void viewAdminPanel();
void excursionBreakdown();
void totalRevenue();
void visitorsPerDay();
void displayExcursionTours();
void writeTicketInfoToFile();
void buyTickets();
void addPersonnel();
int getKeeperCount();
int getVeterinarianCount();
int getGuideCount();
void addKeeper(const std::string& name, const std::string& dateOfBirth);
void addVeterinarian(const std::string& name, const std::string& dateOfBirth);
void addGuide(const std::string& name, const std::string& dateOfBirth, const std::string& languages);
void displayVacancies();
void removePersonnel();
void displayAllPersonnel();
void displayPersonnelByCategory();
void searchPersonnelByName();
void keeperSubMenu();
void veterinarianSubMenu();
void viewAvailablePrograms();
void guideSubMenu();
void addMessage();
void viewWorkSchedule();
void viewFeedingSchedule();
int readCounter(const std::string& counterName);
void writeCounter(const std::string& counterName, int counterValue);
int generateId();
bool checkPersonnelLimit(const std::string& category);
int getCurrentPersonID();
void displayFAQ();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    char choice;

    do {
        std::cout << "\nMain Menu (Главное Меню):" << std::endl;
        std::cout << "1. Personnel (Персонал)" << std::endl;
        std::cout << "2. Excursion Tours (Экскурсионные туры)" << std::endl;
        std::cout << "3. FAQ (Часто задаваемые вопросы)" << std::endl;
        std::cout << "4. Exit (Выход)" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case '1':
                personnelSubMenu();
                break;
            case '2':
                displayExcursionTours();
                break;
            case '3':
                displayFAQ();
                break;
            case '4':
                std::cout << "Exiting program. (Выход из программы)" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again. (Неверный выбор. Пожалуйста, введите снова.)" << std::endl;
                break;
        }
    } while (choice != '4');
}

void personnelSubMenu() {
    char choice;

    do {
        std::cout << "\nPersonnel Submenu (Подменю персонала):" << std::endl;
        std::cout << "1. Add personnel (Добавить персонал)" << std::endl;
        std::cout << "2. Remove personnel (Удалить персонал)" << std::endl;
        std::cout << "3. Display all personnel (Показать весь персонал)" << std::endl;
        std::cout << "4. Display personnel by category (Показать персонал по категориям)" << std::endl;
        std::cout << "5. Search personnel by name (Поиск персонала по имени)" << std::endl;
        std::cout << "6. View work schedule (Посмотреть график работы)" << std::endl;
        std::cout << "7. Admin panel (Панель администратора)" << std::endl;
        std::cout << "8. Return to main menu (Вернуться в главное меню)" << std::endl;
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
                viewWorkSchedule();
                break;
            case '7':
                viewAdminPanel();
                break;
            case '8':
                std::cout << "Returning to main menu. (Возвращение в главное меню)" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again. (Неверный выбор. Пожалуйста, введите снова.)" << std::endl;
                break;
        }
    } while (choice != '8');
}

void viewAdminPanel() {
    std::cout << "\nAdmin panel (Панель администратора)" << std::endl;
    std::cout << "1. Excursion breakdown (Разрез экскурсий)" << std::endl;
    std::cout << "2. Total revenue (Общий доход)" << std::endl;
    std::cout << "3. Number of visitors per day (Количество посетителей за день)" << std::endl;
    std::cout << "4. Back to main menu (Выход в главное меню)" << std::endl;

    int adminChoice;
    std::cout << "Enter your choice: ";
    std::cin >> adminChoice;

    switch (adminChoice) {
        case 1:
            excursionBreakdown();
            break;
        case 2:
            totalRevenue();
            break;
        case 3:
            visitorsPerDay();
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid choice. Please enter again." << std::endl;
            break;
    }
}

void excursionBreakdown() {
    std::ifstream inFile("tickets.txt");
    if (!inFile) {
        std::cerr << "Error: Unable to open tickets.txt for reading!" << std::endl;
        return;
    }

    // Используем карту для хранения информации о каждом типе экскурсии
    std::map<std::string, std::pair<int, int>> excursionInfo; // Пара: общая сумма, общее количество посетителей

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string token;
        std::string excursionName;
        int totalAmount = 0, numVisitors = 0;
        while (std::getline(iss, token, ',')) {
            if (token.find("Tour: ") != std::string::npos) {
                excursionName = token.substr(6); // Удаляем "Tour: "
            } else if (token.find("Total Amount: $") != std::string::npos) {
                totalAmount = std::stoi(token.substr(16)); // Удаляем "Total Amount: $"
            } else if (token.find("Number of Visitors: ") != std::string::npos) {
                numVisitors = std::stoi(token.substr(21)); // Удаляем "Number of Visitors: "
            }
        }

        // Обновляем информацию о типе экскурсии в карте
        excursionInfo[excursionName].first += totalAmount;
        excursionInfo[excursionName].second += numVisitors;
    }

    inFile.close();

    // Выводим информацию о каждом типе экскурсии
    std::cout << "\nExcursion breakdown (Разрез экскурсий):" << std::endl;
    for (const auto& pair : excursionInfo) {
        std::cout << "Excursion: " << pair.first << ", Visitors: " << pair.second.second << ", Total Amount: $" << pair.second.first << std::endl;
    }
}

void totalRevenue() {
    std::ifstream inFile("tickets.txt");
    if (!inFile) {
        std::cerr << "Error: Unable to open tickets.txt for reading!" << std::endl;
        return;
    }

    int totalRevenue = 0;
    std::string line;
    while (std::getline(inFile, line)) {
        size_t amountPos = line.find("Total Amount: $");
        if (amountPos != std::string::npos) {
            size_t commaPos = line.find(",", amountPos); 
            if (commaPos != std::string::npos) {
                std::string amountStr = line.substr(amountPos + 15, commaPos - amountPos - 15);
                totalRevenue += std::stoi(amountStr);
            }
        }
    }

    inFile.close();

    std::cout << "\nTotal revenue (Общий доход): $" << totalRevenue << std::endl;
}

void visitorsPerDay() {
    std::ifstream inFile("tickets.txt");
    if (!inFile) {
        std::cerr << "Error: Unable to open tickets.txt for reading!" << std::endl;
        return;
    }

    int totalVisitors = 0;
    std::string line;
    while (std::getline(inFile, line)) {
        size_t visitorsPos = line.find("Number of Visitors: ");
        if (visitorsPos != std::string::npos) {
            std::string visitorsStr = line.substr(visitorsPos + 20); 
            totalVisitors += std::stoi(visitorsStr);
        }
    }

    inFile.close();

    std::cout << "\nNumber of visitors per day (Количество посетителей за день): " << totalVisitors << std::endl;
}

void buyTickets(int tourChoice);

void displayExcursionTours() {
    std::cout << "\nExcursion Tours Information:" << std::endl;
    std::cout << "1. Audio guide - $10" << std::endl;
    std::cout << "   - Available at any time during zoo operating hours, which are daily from 9:00 to 21:00" << std::endl;
    std::cout << "2. Group tour - $20" << std::endl;
    std::cout << "   - Group tours are conducted every 60 minutes." << std::endl;
    std::cout << "3. Individual tour - $50" << std::endl;
    std::cout << "   - Individual tours must be booked at times that are divisible by 30 minutes, and the duration of the tour will be 60 minutes." << std::endl;
    std::cout << "   - Booking is available between 9:00 and 20:00." << std::endl;
    std::cout << "4. Extreme tour - $150" << std::endl;
    std::cout << "   - The extreme tour has a duration of 2 hours and can be booked at any convenient time between 9:00 and 19:00." << std::endl;
    
    int tourChoice;
    std::cout << "Enter your choice: ";
    std::cin >> tourChoice;
    buyTickets(tourChoice); // передаем выбор тура в функцию для покупки билетов
}

// Функция для записи информации о проданных билетах в файл
void writeTicketInfoToFile(const std::string& tourName, int totalAmount, int numVisitors) {
    std::ofstream file("tickets.txt", std::ios::app);
    if (file.is_open()) {
        file << "Tour: " << tourName << ", Total Amount: $" << totalAmount << ", Number of Visitors: " << numVisitors << std::endl;
        file.close();
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }
}

// Функция для получения ФИО гида из файла personnel.txt
std::string getGuideNameFromFile() {
    std::ifstream inFile("personnel.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.find("Job Title: Guide") != std::string::npos) {
            // Найдена строка с должностью "Guide", извлекаем имя гида
            size_t nameStart = line.find("Name: ") + 6; // Длина "Name: "
            std::string guideName = line.substr(nameStart, line.find(",") - nameStart); // Получаем имя до первой запятой
            return guideName;
        }
    }
    return "Unknown"; // Если гид не найден, возвращаем "Unknown"
}

// Функция для обработки покупки билетов
void buyTickets(int tourChoice) {
    int tourPrice = 0; 
    std::string tourName;
    int numVisitors = 0;

    // Определение цены и имени тура
    switch (tourChoice) {
        case 1:
            tourPrice = 10; 
            tourName = "Audio guide";
            break;
        case 2:
            tourPrice = 20; 
            tourName = "Group tour";
            break;
        case 3:
            tourPrice = 50; 
            tourName = "Individual tour";
            break;
        case 4:
            tourPrice = 150; 
            tourName = "Extreme tour";
            break;
        default:
            std::cerr << "Invalid choice!" << std::endl;
            return;
    }

    // Запрос количества посетителей для каждой категории
    int numBabies, numChildren, numTeenagers, numAdults, numSeniors;
    std::cout << "\nEnter the number of visitors for each category:" << std::endl;
    std::cout << "Babies (0-3 years old): ";
    std::cin >> numBabies;
    numVisitors += numBabies;

    std::cout << "Children (3-10 years old): ";
    std::cin >> numChildren;
    numVisitors += numChildren;

    std::cout << "Teenagers (10-18 years old): ";
    std::cin >> numTeenagers;
    numVisitors += numTeenagers;

    std::cout << "Adults (18-65 years old): ";
    std::cin >> numAdults;
    numVisitors += numAdults;

    std::cout << "Seniors (65+ years old): ";
    std::cin >> numSeniors;
    numVisitors += numSeniors;

    /* Расчет суммы заказа в зависимости от выбранной экскурсии и возрастных категорий
       Рассмотрим скидки для различных возрастных категорий
       Babies: 100%, Children: 25%, Teenagers: 50%, Seniors: 75%*/
    double totalAmount = (numBabies * 0 + numChildren * 0.75 + numTeenagers * 0.5 + numAdults + numSeniors * 0.25) * tourPrice;

    // Запись информации о проданных билетах в файл
    writeTicketInfoToFile(tourName, totalAmount, numVisitors);

    // Выбор случайного ФИО гида
    std::string guideName = getGuideNameFromFile();

    // Вывод информации о скидках и общей сумме заказа
    std::cout << "\nTOTAL AMOUNT: $" << totalAmount << ", Number of Visitors: " << numVisitors << ", Tour: " << tourName << ", Guide: " << guideName << std::endl;
}

void addPersonnel() {
char choice;

    do {
        std::cout << "Choose job title:" << std::endl;
        std::cout << "1. Keeper" << std::endl;
        std::cout << "2. Veterinarian" << std::endl;
        std::cout << "3. Guide" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string name, dateOfBirth, languages;
        switch (choice) {
            case '1':
                std::cout << "Enter keeper's full name: ";
                std::getline(std::cin, name);
                std::cout << "Enter keeper's date of birth: ";
                std::getline(std::cin, dateOfBirth);
                addKeeper(name, dateOfBirth);
                break;
            case '2':
                std::cout << "Enter veterinarian's full name: ";
                std::getline(std::cin, name);
                std::cout << "Enter veterinarian's date of birth: ";
                std::getline(std::cin, dateOfBirth);
                addVeterinarian(name, dateOfBirth);
                break;
            case '3':
                std::cout << "Enter guide's full name: ";
                std::getline(std::cin, name);
                std::cout << "Enter guide's date of birth: ";
                std::getline(std::cin, dateOfBirth);
                std::cout << "Enter guide's languages: ";
                std::getline(std::cin, languages);
                addGuide(name, dateOfBirth, languages);
                break;
            default:
                std::cerr << "Invalid choice." << std::endl;
                break;
        }

        std::cout << "Do you want to add another personnel? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (choice == 'y' || choice == 'Y');
}

// Функция для подсчета количества сотрудников-смотрителей в файле
int getKeeperCount() {
    std::ifstream file("personnel.txt");
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Job Title: Keeper") != std::string::npos) {
            count++;
        }
    }
    file.close();
    return count;
}

// Функция для подсчета количества ветеринаров в файле
int getVeterinarianCount() {
    std::ifstream file("personnel.txt");
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Job Title: Veterinarian") != std::string::npos) {
            count++;
        }
    }
    file.close();
    return count;
}

// Функция для подсчета количества гидов в файле
int getGuideCount() {
    std::ifstream file("personnel.txt");
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Job Title: Guide") != std::string::npos) {
            count++;
        }
    }
    file.close();
    return count;
}

void addKeeper(const std::string& name, const std::string& dateOfBirth) {
    // Получаем следующий доступный ID
    int newId = generateId();
    if (newId == -1) {
        std::cerr << "Error: Unable to generate new person ID." << std::endl;
        return;
    }

    // Открываем файл для записи в конец
    std::ofstream outFile("personnel.txt", std::ios_base::app);
    if (outFile.is_open()) {
        // Записываем данные о новом сотруднике в файл
        outFile << "ID: " << newId << ", Job Title: Keeper, Name: " << name << ", Date of Birth: " << dateOfBirth << std::endl;
        outFile.close();
        std::cout << "Keeper added successfully. (Смотритель успешно добавлен)" << std::endl;
    } else {
        std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
    }
}

void addVeterinarian(const std::string& name, const std::string& dateOfBirth) {
    // Получаем следующий доступный ID
    int newId = generateId();
    if (newId == -1) {
        std::cerr << "Error: Unable to generate new person ID." << std::endl;
        return;
    }

    // Открываем файл для записи в конец
    std::ofstream outFile("personnel.txt", std::ios_base::app);
    if (outFile.is_open()) {
        // Записываем данные о новом сотруднике в файл
        outFile << "ID: " << newId << ", Job Title: Veterinarian, Name: " << name << ", Date of Birth: " << dateOfBirth << std::endl;
        outFile.close();
        std::cout << "Veterinarian added successfully. (Ветеринар успешно добавлен)" << std::endl;
    } else {
        std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
    }
}

void addGuide(const std::string& name, const std::string& dateOfBirth, const std::string& languages) {
    // Получаем следующий доступный ID
    int newId = generateId();
    if (newId == -1) {
        std::cerr << "Error: Unable to generate new person ID." << std::endl;
        return;
    }

    // Открываем файл для записи в конец
    std::ofstream outFile("personnel.txt", std::ios_base::app);
    if (outFile.is_open()) {
        // Записываем данные о новом сотруднике в файл
        outFile << "ID: " << newId << ", Job Title: Guide, Name: " << name << ", Date of Birth: " << dateOfBirth 
                << ", Languages: " << languages << std::endl;
        outFile.close();
        std::cout << "Guide added successfully. (Гид успешно добавлен)" << std::endl;
    } else {
        std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
    }
}

void displayVacancies() {
    std::cout << "\nVacancies (Вакансии):" << std::endl;
    std::cout << "1. Keeper (Смотритель): " << Keeper::MAX_KEEPERS - Keeper::keeperCount << " vacancies available." << std::endl;
    std::cout << "2. Veterinarian (Ветеринар): " << Veterinarian::MAX_VETERINARIANS - Veterinarian::veterinarianCount << " vacancies available." << std::endl;
    std::cout << "3. Guide (Гид): " << Guide::MAX_GUIDES - Guide::guideCount << " vacancies available." << std::endl;
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

    inFile.close();

    std::string searchName;
    bool found = false;

    std::cout << "\nEnter the name of the personnel to remove: ";
    std::getline(std::cin >> std::ws, searchName);

    // Поиск и удаление сотрудника с заданным именем
    for (auto it = personnelList.begin(); it != personnelList.end(); ++it) {
        if ((*it).find(searchName) != std::string::npos) {
            // Найден сотрудник, перемещаем его данные в файл dissmissed.txt
            std::ofstream dissmissedFile("dissmissed.txt", std::ios::app);
            if (dissmissedFile.is_open()) {
                dissmissedFile << *it << '\n';
                dissmissedFile.close();
            } else {
                std::cerr << "Error: Unable to open dissmissed.txt for writing!" << std::endl;
            }

            // Удаляем сотрудника из списка
            personnelList.erase(it);
            found = true;
            std::cout << "Personnel '" << searchName << "' removed successfully. (Персонал '" << searchName << "' успешно удален)" << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "No personnel found with the name: " << searchName << std::endl;
    }

    // Записать обновленный список персонала в файл personnel.txt
    std::ofstream outFile("personnel.txt");

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
        return;
    }

    for (const auto& person : personnelList) {
        outFile << person << '\n';
    }

    outFile.close();
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
        std::cout << "2. View feeding vitamin's schedule" << std::endl;
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

void viewAvailablePrograms() {
    std::cout << "\nAvailable Programs:" << std::endl;
    std::cout << "1. Audio guide - $10" << std::endl;
    std::cout << "2. Group tour - $20" << std::endl;
    std::cout << "3. Individual tour - $50" << std::endl;
    std::cout << "4. Extreme tour - $150" << std::endl;
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
                viewAvailablePrograms();
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
            if (line.find("Job Title: Keeper") != std::string::npos) {
                std::cout << line << std::endl;
            }
        }
        break;
    }
    case '2': {
        std::cout << "\nVeterinarians:" << std::endl;
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find("Job Title: Veterinarian") != std::string::npos) {
                std::cout << line << std::endl;
            }
        }
        break;
    }
    case '3': {
        std::cout << "\nGuides:" << std::endl;
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find("Job Title: Guide") != std::string::npos) {
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

int readCounter(const std::string& counterName) {
    int counterValue = 0;
    std::ifstream counterFile("count.txt");
    if (counterFile.is_open()) {
        std::string name;
        while (counterFile >> name >> counterValue) {
            if (name == counterName) {
                break;
            }
        }
        counterFile.close();
    }
    return counterValue;
}

void writeCounter(const std::string& counterName, int value) {
    std::ifstream inFile("count.txt"); // Открываем файл для чтения
    std::ofstream outFile("temp.txt"); // Открываем временный файл для записи

    if (inFile.is_open() && outFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) { // Читаем файл построчно
            if (line.find(counterName) != std::string::npos) { // Находим строку с нужным счетчиком
                outFile << counterName << "" << value << std::endl; // Записываем новое значение
            } else {
                outFile << line << std::endl; // Переписываем остальные строки без изменений
            }
        }
        inFile.close(); // Закрываем исходный файл
        outFile.close(); // Закрываем временный файл
        std::remove("count.txt"); // Удаляем исходный файл
        std::rename("temp.txt", "count.txt"); // Переименовываем временный файл
    } else {
        std::cerr << "Error: Unable to open files for writing!" << std::endl;
    }
}

int generateId() {
    int idCounter = getCurrentPersonID(); // Получаем текущее значение ID
    if (idCounter == -1) {
        std::cerr << "Error: Unable to get current person ID." << std::endl;
        return -1; // Обработать ошибку или принять другое решение
    }
    idCounter++; // Увеличиваем значение счетчика на единицу
    writeCounter("Person ID: ", idCounter); // Записываем обновленное значение счетчика в файл
    return idCounter; // Возвращаем новое значение счетчика
}


bool checkPersonnelLimit(const std::string& category) {
    if (category == "Keeper") {
        return getKeeperCount() < 10;
    } else if (category == "Veterinarian") {
        return getVeterinarianCount() < 3;
    } else if (category == "Guide") {
        return getGuideCount() < 6;
    }
    return false;
}

void addPersonnel(const std::string& jobTitle, const std::string& name, const std::string& dateOfBirth) {
    // Получаем следующее доступное значение ID
    int newId = generateId();
    if (newId == -1) {
        std::cerr << "Error: Unable to generate new person ID." << std::endl;
        return;
    }

    // Проверяем лимиты для данной категории
    if (!checkPersonnelLimit(jobTitle)) {
        std::cerr << "Error: Personnel limit exceeded for category: " << jobTitle << std::endl;
        return;
    }

    // Открываем файл для записи в конец
    std::ofstream outFile("personnel.txt", std::ios_base::app);
    if (outFile.is_open()) {
        // Записываем данные о новом сотруднике в файл
        outFile << "ID: " << newId << ", Job Title: " << jobTitle << ", Name: " << name 
                << ", Date of Birth: " << dateOfBirth << std::endl;
        outFile.close();
        std::cout << "Personnel added successfully." << std::endl;
    } else {
        std::cerr << "Error: Unable to open personnel.txt for writing!" << std::endl;
    }
}

int getCurrentPersonID() {
    std::ifstream inFile("count.txt");
    if (!inFile) {
        std::cerr << "Error: Unable to open count.txt for reading!" << std::endl;
        return -1; // Вернуть ошибку или другое значение по умолчанию
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.find("Person ID: ") != std::string::npos) {
            // Найдена строка с ID, извлекаем его значение
            int id = std::stoi(line.substr(11)); // 11 - это длина "Person ID: "
            return id;
        }
    }

    // Если строка с ID не найдена
    return -1; // Вернуть ошибку или другое значение по умолчанию
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