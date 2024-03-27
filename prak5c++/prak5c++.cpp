#include <iostream>
#include <stdexcept> 

using namespace std;

class BankAccount {
private:
    int accountNumber; // Номер банковского счета
    double balance; // Баланс
    double interestRate; // Процентная ставка

public:
    BankAccount(int accountNumber, double initialBalance, double initialInterestRate) {
        this->accountNumber = accountNumber;
        this->balance = initialBalance;
        this->interestRate = initialInterestRate;
    }

    // Функция для внесения средств на счет
    void deposit(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма не может быть отрицательной"); // Проверка на отрицательную сумму
        }
        balance += amount; // Увеличение баланса
    }

    // Функция для снятия средств со счета
    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма не может быть отрицательной"); // Проверка на отрицательную сумму
        }
        if (amount > balance) {
            throw invalid_argument("Недостаточно средств на счете"); // Проверка на наличие достаточных средств для снятия
        }
        balance -= amount; // Уменьшение баланса
    }

    // Функция для получения текущего баланса
    double getBalance() const {
        return balance;
    }

    // Функция для расчета и возврата суммы процентов
    double getInterest() const {
        return balance * interestRate * (1.0 / 12.0); 
    }

    // Функция для обновления процентной ставки
    void setInterestRate(double newInterestRate) {
        interestRate = newInterestRate;
    }

    // Функция для получения номера банковского счета
    int getAccountNumber() const {
        return accountNumber;
    }
};

// Функция для перевода денег между счетами
bool transfer(BankAccount& from, BankAccount& to, double amount) {
    try {
        from.withdraw(amount); // Списание средств со счета отправителя
        to.deposit(amount); // Зачисление средств на счет получателя
        return true; // Перевод успешно завершен
    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка при переводе: " << e.what() << endl; // Вывод сообщения об ошибке
        return false; // Перевод не удался
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    // Создание банковских счетов
    BankAccount account1(123456, 1000.0, 0.05); // Создаем счет 1
    BankAccount account2(654321, 500.0, 0.03); // Создаем счет 2

    int choice;
    double amount;
    bool exit = false;

    while (!exit) {
        // Выводим меню для пользователя
        cout << "\nВыберите действие:\n";
        cout << "1. Внести средства на счет\n";
        cout << "2. Вывести текущий баланс\n";
        cout << "3. Перевести средства между счетами\n";
        cout << "4. Выйти\n";

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите сумму для внесения на счет: ";
            cin >> amount;
            try {
                account1.deposit(amount);
                cout << "Баланс счета 1 после внесения: " << account1.getBalance() << endl;
            }
            catch (const invalid_argument& e) {
                cerr << e.what() << endl;
            }
            break;
        case 2:
            cout << "Текущий баланс счета 1: " << account1.getBalance() << endl;
            break;
        case 3:
            cout << "Введите сумму для перевода: ";
            cin >> amount;
            if (transfer(account1, account2, amount)) {
                cout << "Перевод успешно выполнен\n";
            }
            else {
                cout << "Перевод не выполнен\n";
            }
            break;
        case 4:
            exit = true;
            break;
        default:
            cout << "Неверный выбор\n";
            break;
        }
    }

    return 0;
}
        