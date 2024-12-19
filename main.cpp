#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Item {
    string name;
    string description;
    int price;
};

class User {
int balance; 


vector<Item> inventory;
string username;
string password;

public:
    User() : balance(5000) {}

void vhod(const string& user, const string& pass) {
    username = user;
    password = pass;
}
string getUsername() const {
    return username;
}
bool checkPassword(const string& pass) const {
    return password == pass;
}
void AddItemToInventory(const Item& item) {
    inventory.push_back(item);
    balance -= item.price;
}
void SellItem(int index) {
    if (index >= 0 && index < inventory.size()) {
        string itemName = inventory[index].name;
        int sellingPrice = 0;
        
        if (itemName == "Диск GTA5 Ps4") {
            sellingPrice = 1800;
        } else if (itemName == "Джойстик PS4") {
            sellingPrice = 1500;
        } else if (itemName == "FIFA 24 диск ps4") {
            sellingPrice = 2100;
        } else if (itemName == "The Witcher 3 Диск PS4") {
            sellingPrice = 1800;
        } else if (itemName == "IPhone SE 2020") {
            sellingPrice = 11250;
        }
        else if (itemName == "PSP e1008 64gb прошитая") {
            sellingPrice = 5500;
        }
        else if (itemName == "PS5 Pro 2TB") {
            sellingPrice = 41500;
        }
        else if (itemName == "PS4 1Tb в идеале") {
            sellingPrice = 19000;
        }  
        if (sellingPrice > 0) {
            cout << "Вы хотите продать " << itemName << " за " << sellingPrice << "? (1 - Да, 0 - Нет): ";
            int choice;
            cin >> choice;
            if (choice == 1) {
                balance += sellingPrice;
                inventory.erase(inventory.begin() + index);
                cout << itemName << " продан за " << sellingPrice << ".\n";
    } else {
        cout << "Ошибка \n";
    }
}
    }}
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

    bool give(int price) const {
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
        cout << "Продавец: " << author << endl;
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
    cout << "Введите имя продавца: ";
    cin.ignore();
    getline(cin, author);

    ads.push_back(Ad(title, description, price, author));
    cout << "Объявление добавлено!\n";
}

void viewAds(const vector<Ad>& ads, User& user) {
    for (int i = 0; i < ads.size(); i++) {
        cout << i + 1 << ". " << ads[i].getTitle() << " - " << ads[i].getPrice() << " \n";
    }
    cout << "Выберитк товар или 0 для выхода: ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= ads.size()) {
        const Ad& selectedAd = ads[choice - 1];
        selectedAd.display();

        if (user.give(selectedAd.getPrice())) {
            cout << "Хотите купить этот товар? 1 - Да, 0 - Нет ";
            int buyChoice;
            cin >> buyChoice;
            if (buyChoice == 1) {
                user.AddItemToInventory(Item{selectedAd.getTitle(), selectedAd.getDescription(), static_cast<int>(selectedAd.getPrice())});
                cout << "Товар куплен\n";
            }
        } else {
            cout << "Недостаточно денех для покупки\n";
        }
    }
}

void viewProfile(User& user) {
    cout << "Ваш профиль:\n";
    user.ShowInventory();

    cout << "Хотите продать предмет? (1 - Да, 0 - Нет): ";
    int sellChoice;
    cin >> sellChoice;

    if (sellChoice == 1) {
        cout << "Введите номер предмета для продажи: ";
        int itemIndex;
        cin >> itemIndex;
        itemIndex--;
        user.SellItem(itemIndex);
}
}

void registerUser (const string& username, const string& password) {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
    }
    else
    {
        cout << "Ошибка";
    }
}
bool loginUser (User& user) {
    string username, password;
    cout << "Введите логин: ";
    cin >> username;
    cout << "Введите пароль: ";
    cin >> password;

    ifstream file("users.txt");
    if (file.is_open()) {
        string fileUsername, filePassword;
        while (file >> fileUsername >> filePassword) {
            if (fileUsername == username && filePassword == password) {
                user.vhod(username, password);
                return true;
            }
        }
        file.close();
    } 
    else
    {
         cout << "Ошибка";
    }
    return false;
}

void run() {
    int choice;
    vector<Ad> ads = {
        Ad("PS4 Slim 500GB", "PS4 Slim 500GB в отличном состоянии, пломба на месте. В комплекте есть джойстик, зарядка, коробка, HDMI", 18990, "Кирилл"),
        Ad("Диск GTA5 Ps4", "Диск GTA5 Ps4", 1200, "Максим"),
        Ad("IPhone SE 2020", "IPhone SE 2020", 9900, "Даниил"),
        Ad("PS5 Pro 2TB", "PS5 2TB в отличном состоянии, пломба на месте. В комплекте есть джойстик, зарядка, коробка, HDMI", 36990, "Никита"),
        Ad("PSP e1008 64gb прошитая", "psp", 3500, "Артем"),
        Ad("The Witcher 3 Диск PS4", "PS5 Pro 2TB", 1300, "Наталья"),
        Ad("PS4 1Tb в идеале", "PS4 Slim 500GB в отличном состоянии, пломба на месте. В комплекте есть джойстик, зарядка, коробка, HDMI", 16000, "Михаил"),
        Ad("FIFA 24 диск ps4", "PS5 Pro 2TB", 2800, "Владислав"),
        Ad("Джойстик PS4 ", "PS5 Pro 2TB", 2000, "Егор"),
    
    };

    User user;

    cout << "|------------------------------------------------------------|" << endl;
    cout << "|       Добро пожаловать на Авито! Выберите действие:        |" << endl;
    cout << "|------------------------------------------------------------|" << endl;
     cout << "                                                                 " << endl;
    cout << "|------------------------------|""|----------------------------|" << endl;
    cout << "|         1.Регистрация        |""|     2. Войти в аккаунт     |" << endl;
    cout << "|------------------------------|""|----------------------------|" << endl;
    int action;
    cin >> action;
    if (action == 1) {
        string username, password;
        cout << "Введите логин: ";
        cin >> username;
        cout << "Введите пароль: ";
        cin >> password;
        registerUser (username, password);
        cout << "Вы зарегистрированы";
    } 
    else if (action == 2) {
        while (!loginUser (user)) {
            cout << "Неверное имя пользователя или пароль. Попробуйте снова.\n";
        }
        cout << "Вы успешно вошли";
    }
    
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
            cout << "|  18990                      |" "|  1200                       |" << endl;
            cout << "|  - Кирилл                   |" "|  - Максим                   |" << endl;
            cout << "|                             |" "|                             |" << endl;
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
            cout << "|                             |" "|                             |" << endl;
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
            cout << "Нажмите любую клавишу для возврата в главное меню.\n";
            cin.ignore();
            cin.get();
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
