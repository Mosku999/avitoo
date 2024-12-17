#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Item {
    string name;
    string description;
    int price;
};

class User {
    int balance; 
    vector<Item> inventory;

public:
    User() : balance(5000) {}

    void AddItemToInventory(const Item& item) {
        inventory.push_back(item);
        balance -= item.price;
    } 

    void SellItem(int index, int SellPrice) {
        if (index >= 0 && index < inventory.size()) {
            balance += SellPrice;
            inventory.erase(inventory.begin() + index);
        }
    }

    void ShowInventory() { 
        cout << "Инвентарь:\n";
        for (int i = 0; i < inventory.size(); i++) {
            cout << i + 1 << ". " << inventory[i].name << " - " << inventory[i].price << " \n";
        }
        cout << "Баланс: " << balance << " \n";
    }

    int GetBalance() const {
        return balance;
    }

    bool CanAfford(int price) const {
        return balance >= price;
    }
};

class Ad {
private:
    string title;
    string description;
    double price;
    string author;

public:
    Ad(string t, string d, double p, string a) : title(t), description(d), price(p), author(a) {}
    string getTitle() const { return title; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }
    string getAuthor() const { return author; }
    void display() const {
        cout << "Название: " << title << endl;
        cout << "Описание: " << description << endl; 
        cout << "Цена: " << price << " " << endl;    
        cout << "Автор: " << author << endl;
    }
};

void addAd(vector<Ad>& ads) {
    string title, description, author;
    double price;

    cout << "Введите название товара: ";
    cin.ignore();
    getline(cin, title);
    cout << "Введите описание товара: ";
    getline(cin, description);
    cout << "Введите цену товара: ";
    cin >> price;
    cout << "Введите имя автора: ";
    cin.ignore();
    getline(cin, author);

    ads.push_back(Ad(title, description, price, author));
    cout << "Объявление добавлено!\n";
}

void viewAds(const vector<Ad>& ads, User& user) {
    for (int i = 0; i < ads.size(); i++) {
        cout << i + 1 << ". " << ads[i].getTitle() << " - " << ads[i].getPrice() << " \n";
    }
    cout << "Выберите товар для просмотра (0 для выхода): ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= ads.size()) {
        const Ad& selectedAd = ads[choice - 1];
        selectedAd.display();

        if (user.CanAfford(selectedAd.getPrice())) {
            cout << "Хотите купить этот товар? (1 - Да, 0 - Нет): ";
            int buyChoice;
            cin >> buyChoice;
            if (buyChoice == 1) {
                user.AddItemToInventory(Item{selectedAd.getTitle(), selectedAd.getDescription(), static_cast<int>(selectedAd.getPrice())});
                cout << "Товар куплен!\n";
            }
        } else {
            cout << "Недостаточно средств для покупки.\n";
        }
    }
}

void viewProfile(User& user) {
    cout << "Ваш профиль:\n";
    user.ShowInventory();
}

void search(const vector<Ad>& ads) {
    string query;
    cout << "|------------------------------------------------------------|" << endl;
    cout << "|  Введите ваш запрос...                                     |" << endl;
    cout << "|------------------------------------------------------------|" << endl;
    getline(cin, query);
    cout << "Результаты поиска:" << endl;
    for (const auto& ad : ads) {
        if (ad.getTitle().find(query) != string::npos || ad.getDescription().find(query) != string::npos) {
            ad.display();
            cout << "---------------------" << endl;
        }
    }
}
void run() {
    int choice;
    vector<Ad> ads = {
        Ad("PS4 Slim 500GB", "PS4 Slim 500GB", 17990, "Кирилл"),
        Ad("Диск GTA5 Ps4", "Диск GTA5 Ps4", 1200, "Максим"),
        Ad("IPhone SE 2020", "IPhone SE 2020", 10990, "Даниил"),
        Ad("PS5 Pro 2TB", "PS5 Pro 2TB", 56990, "Никита")
    };

    User user;

        do {
            cout << " Главное меню:" << endl;
            cout << "                                                              " << endl;
            cout << "|------------------------------------------------------------|" << endl;
            cout << "|                1. Поиск обьявлений на авито                |" << endl;
            cout << "|------------------------------------------------------------|" << endl;
            cout << "                                                                 " << endl;
            cout << "|-----------------------------|" "|-----------------------------|" << endl;
            cout << "|                             |" "|                             |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  PS4 Slim 500GB             |" "|  Диск GTA5 Ps4              |" << endl;
            cout << "|  17990                      |" "|  1200                       |" << endl;
            cout << "|  - Кирилл                   |" "|  - Максим                   |" << endl;
            cout << "|          5.Открыть          |" "|                             |" << endl;
            cout << "|-----------------------------|" "|-----------------------------|" << endl;
            cout << "                                                                 " << endl;
            cout << "|-----------------------------|" "|-----------------------------|" << endl;
            cout << "|                             |" "|                             |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  Resident Evil 4            |" "|  PSP White 8GB              |" << endl;
            cout << "|  2100                       |" "|  6500                       |" << endl;
            cout << "|  - Кирилл                   |" "|  - Евгений                  |" << endl;
            cout << "|          5.Открыть          |" "|                             |" << endl;
            cout << "|-----------------------------|" "|-----------------------------|" << endl;
            cout << "                                                                 " << endl;
            cout << "|-----------------------------|" "|-----------------------------|" << endl;
            cout << "|                             |" "|                             |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  *************************  |" "|  *************************  |" << endl;
            cout << "|  IPhone SE 2020             |" "|  PS5 Pro 2TB                |" << endl;
            cout << "|  10990                      |" "|  56990                      |" << endl;
            cout << "|  - Даниил                   |" "|  - Никита                   |" << endl;
            cout << "|                             |" "|                             |" << endl;
            cout << "|-----------------------------|" "|-----------------------------|" << endl;
            cout << "                                                                 " << endl;
            cout << "|---------------|""|--------------|""|-------------|""|------------|" << endl;
            cout << "|  2.Обьявления |""|  3.Добавить  |""|  4.Профиль  |""|   0.Выход  |" << endl;
            cout << "|---------------|""|--------------|""|-------------|""|------------|" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            break;
        case 2:
            viewAds(ads, user);
            break;
        case 3:
            addAd(ads);
            break;
        case 4:
            viewProfile(user);
            break;
        case 0:
            cout << "Вы вышли из авито.. эх" << endl;
            break;
        default:
            cout << "Неверный выбор" << endl;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "RUS");
    run();
    return 0;
}
