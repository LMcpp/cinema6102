/**
Кто писал код:
Малинов Леонид
Акимов Никита 
Егор Хоробрых 
Сараев Владимир
Анисимов Максим
Колоколов Александр
Перевертова Анастасия

Кто тестировал + учавствовал в создании схемы приложения
Гридяев Олег
Чебыкина Софья
Касимов Сергей
Колосова Анастасия
Богомолова Кристина
**/



#include <iostream>
#include <string> 
#include <cstdlib>
#include <iomanip>
#include <array> 
#include <map>
#include <random>
#include <ctime>
#include <algorithm>
#include <sstream>


using namespace std;

//Малинов Леонид
//константа по количеству игнорируемых символов
const int SYMBOLS_TO_IGNORE = 100000;
//константы по размеру залов
const int CINEMA_HALLS_COUNTER = 6;
const int HALL_ROWS = 6;
const int HALL_COLS = 6;
//константа по рандомной генерации ключей
const int RANDOM_GENERATION = 9000 + 1000;
//константа по количеству и списков фильмов
const int FILMS_COUNT = 48;
const array<string, FILMS_COUNT> MOVIES = {
        "Мстители: Финал", "Веном", "Игра", "Гарри Поттер 1" , "Матрица", "Иллюзия обмана", "Голодные игры", "Оно", "Круэлла",
        "Главный герой", "Дрянные девчонки", "Сумерки", "Аквамэн", "Титаник", "Отряд самоубийц",
        "Маска", "Люди X", "Люди в чёрном", "Пассажиры", "Миссия невыполнима", "Куб", "Тело Дженнифер", "Поезд в Пусан", "День сурка",
        "Солнцестояние", "Барби", "Пять ночей с Фредди", "Бугимэн", "Бойцовский клуб", "Грань будущего", "Васаби", "Аватар",
        "Капитан Америка : Другая война", "Твое имя", "Гадкий Я", "История игрушек", "Шрэк", "Корпорация монстров", "Мой сосед Тоторо",
        "Золушка", "Трансформеры", "Звездная пыль", "Обратный отсчёт", "Всё везде и сразу", "Жизнь Пи", "Терминатор", "Один дома", "Время"
};

//словарики для хранения купленных и бронированных фильмов
map <int, string> purchasedTickets;
map <int ,string> reservedTickets;
//глобальная переменная которая считает занятые места
int onesCounter;

class CorrectCin {
private:
    //Малинов Леонид
    //Вспомогательная функция для очистки ввода
    void fixInput(const string& message = "") {
        cin.ignore(SYMBOLS_TO_IGNORE, '\n');
        cin.clear();
        cout << message;
    }
public:
    //Малинов Леонид
    //Вспомогательные функции для различных считываний
    string correctMainMenuInput() {
        string tempString;
        while (!(cin >> tempString) || cin.peek() != '\n' || (tempString != "1" && tempString != "2" && tempString != "3" && tempString != "exit"))
            fixInput("Ошибка, введите 1,2,3 (или exit для выхода): ");
        return tempString;
    }
    string correctReservationMenuInput() {
        string tempString;
        while (!(cin >> tempString) || cin.peek() != '\n' || (tempString != "1" && tempString != "2" && tempString != "e"))
            fixInput("Ошибка, введите 1,2 (или e для выхода): ");
        return tempString;
    }
    string correctPurschasedMenuInput() {
        string tempString;
        while (!(cin >> tempString) || cin.peek() != '\n' || (tempString != "1" && tempString != "2" && tempString != "e"))
            fixInput("Ошибка, введите 1,2 (или e для выхода): ");
        return tempString;
    }
    string correctSeveralPlaceInput(){
        string tempString;
        while (!(cin >> tempString) || cin.peek() != '\n' || (tempString != "e" && tempString < "2" && tempString > "6")) 
            fixInput("Ошибка, введите цифру от 2 до 6 (или e для выхода): ");
        return tempString;
    }

    //Малинов Леонид
    //Фунция для корректного считывания сеансов зала
    string correctScheduleInput(const map<string, int**>& dictionary) const {
        bool elementExist = false;
        bool firstCin = true;
        string key = "0";

        while (!elementExist) {
            getline(cin, key);
            if (key == "e") {
                elementExist = true;
            }
            else {
                if (dictionary.find(key) != dictionary.end()) {
                    elementExist = true;
                }
                else {
                    if (!firstCin) {
                        cin.sync();
                        cout << "Неверно, введите сеанс в формате 1 10:00: ";
                    }
                }
                firstCin = false;
            }
        }
        return key;
    }

    //Малинов Леонид
    //Функция для корректного считывания выбора места + проверка не занято ли
    bool checkIfClear(int** matrix, const string& rowCol) {
        string row = rowCol.substr(0, 1);
        string col = rowCol.substr(1, 1);
        int rowInt = stoi(row) - 1;
        int colInt = stoi(col) - 1;
        return (matrix[rowInt][colInt] == 0);
    }
    string correctRowColInput(int** matrix) {
      string tempString;
      while (!(cin >> tempString) && !(tempString != "e") && (cin.peek() != '\n' || !(tempString[0] >= '1' && tempString[0] <= '6' && tempString[1] >= '1' && tempString[1] <= '6') || !checkIfClear(matrix, tempString))) {
              fixInput("Ошибка, введите в формате (ряд)(столбец) от 1 до 6 или вы выбрали место которое занято: ");
          }
      return tempString;
      }

    //Анисимов Максим + Сараев Владимир
    //Функция для корректного считывания ключа в словаре бронирования
    string correctBookingKeyInput(map<int, string>& bookingmap) {
        string userInput;
        while (true) {
            cin >> userInput;
            if (userInput == "e" && cin.peek() == '\n') {
                return userInput;
            }
            try {
                int key = stoi(userInput);

                if (bookingmap.find(key) != bookingmap.end() && cin.peek() == '\n') {
                    string returnString = bookingmap[key] + ';' + userInput;
                    return returnString;
                }
                else {
                    cout << "Ошибка: Некорректный ввод. Пожалуйста, введите четырёхзначный код (или 'e' для выхода): ";
                    cin.ignore(100000000, '\n');
                }
            }
            catch (invalid_argument&) {
                cout << "Ошибка: Некорректный ввод. Пожалуйста, введите четырёхзначный код (или 'e' для выхода): ";
                cin.ignore(100000000, '\n');
            }
            catch (out_of_range&) {
                cout << "Ошибка: Введенное значение слишком большое для преобразования в int: ";
                cin.ignore(100000000, '\n');
            }
        }
    }
};

class OutputHelper {
public:
    //Малинов Леонид
    //Функция для вывода матрицы зала
    static void printMatrix(int** matrix){
        cout << "  ";
        for (int j = 0; j < HALL_COLS; ++j) {
            cout << j + 1 << " ";
        }
        cout << std::endl;

        for (int i = 0; i < HALL_ROWS; ++i) {
            cout << i + 1 << " ";
            for (int j = 0; j < HALL_COLS; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << std::endl;
        }
    }

    //Малинов Леонид
    //Функция для вывода всех дополнительных сеансов
    static void printSchedule(const map<int, string>& movieDictionary){
        for (int i = 1; i <= CINEMA_HALLS_COUNTER; ++i) {
            cout << i << " зал. " << movieDictionary.at(i) << "\nДоступные сеансы:\n10:00 13:00 16:00 19:00 22:00\n\n";
        }
    }

    //Малинов Леонид 
    //Функция для пропуска N строк
    static void skipLines(int n) {
        for (int i = 0; i < n; ++i) {
            cout << endl;
        }
    }
    
    //Малинов Леонид 
    //ASCII вспомогательные арты 
    static void cinemaASCII(){
      cout << R"(
    ____ _____ _   _ ______ __  __              __ __  ___ ___  
  / ____|_   _| \ | |  ____|  \/  |   /\       / //_ |/ _ \__ \ 
 | |      | | |  \| | |__  | \  / |  /  \     / /_ | | | | | ) |
 | |      | | | . ` |  __| | |\/| | / /\ \   | '_ \| | | | |/ / 
 | |____ _| |_| |\  | |____| |  | |/ ____ \  | (_) | | |_| / /_ 
  \_____|_____|_| \_|______|_|  |_/_/    \_\  \___/|_|\___/____|
      

)";
    }

    static void purchasedASCII(){
        cout << R"(
  _____  _    _ _____   _____ _    _           _____ ______ 
 |  __ \| |  | |  __ \ / ____| |  | |   /\    / ____|  ____|
 | |__) | |  | | |__) | |    | |__| |  /  \  | (___ | |__   
 |  ___/| |  | |  _  /| |    |  __  | / /\ \  \___ \|  __|  
 | |    | |__| | | \ \| |____| |  | |/ ____ \ ____) | |____ 
 |_|     \____/|_|  \_\\_____|_|  |_/_/    \_\_____/|______|


)";
    }

    static void bookingASCII(){
        cout << R"(
  ____   ____   ____  _  _______ _   _  _____ 
 |  _ \ / __ \ / __ \| |/ /_   _| \ | |/ ____|
 | |_) | |  | | |  | | ' /  | | |  \| | |  __ 
 |  _ <| |  | | |  | |  <   | | | . ` | | |_ |
 | |_) | |__| | |__| | . \ _| |_| |\  | |__| |
 |____/ \____/ \____/|_|\_\_____|_| \_|\_____|


)";
    }

    static void infoASCII(){
        cout << R"(
  _____ _   _ ______ ____  
 |_   _| \ | |  ____/ __ \ 
   | | |  \| | |__ | |  | |
   | | | . ` |  __|| |  | |
  _| |_| |\  | |   | |__| |
 |_____|_| \_|_|    \____/ 


)";
    }


};

class CinemaSystem {
private:
    //список всех возможных фильмов
    array<string, FILMS_COUNT> movies;
    
    //для удобства инциализируем глобальными константами
    int rows = HALL_ROWS;
    int cols = HALL_COLS;

    //создаем массив словарей (размером в нашем случае 6)
    map<string, int**> dictionaries[CINEMA_HALLS_COUNTER];
public: 

    CinemaSystem() : movies(MOVIES){};

    //Малинов Леонид
    //Функция которая создает словарь в формате {1 : "Название фильма"}
    //Фильмы берет случайным образом из словарика всех фильмов
    map<int, string> createMovieDictionary() const {
        map<int, string> movieDictionary;
        vector<int> indices(movies.size());
        for (int i = 0; i < movies.size(); ++i) {
            indices[i] = i;
        }
        default_random_engine randomEngine(static_cast<unsigned>(time(0)));
        shuffle(indices.begin(), indices.end(), randomEngine);
        for (int i = 0; i < min(CINEMA_HALLS_COUNTER, static_cast<int>(movies.size())); ++i) {
            movieDictionary[i + 1] = movies[indices[i]];
        }
        return movieDictionary;
    }
    
    //Малинов Леонид
    //функция которая генерирует каждый зал и заполняет его 0 и 1 с небольшой вероятностью
    int** createCinemaHallMatrix() {
        int** matrix = new int* [rows];
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                matrix[i][j] = (dis(gen) < 0.2) ? 1 : 0;
                onesCounter += matrix[i][j];
            }
        }
        return matrix;
    }

    //Малинов Леонид 
    //Функция которая создает словарь, где ключами являются строки в формате {1 + время : матрица n x m} 
    map<string, int**> createCinemaDictionary() {
        map<string, int**> dictionary;
        for (int i = 0; i < CINEMA_HALLS_COUNTER; ++i) {
            for (int j = 10; j <= 22; j += 3) {
                string key = to_string(i + 1) + " " + to_string(j) + ":00";
                dictionary[key] = createCinemaHallMatrix();
            }
        }
        return dictionary;
    }

    //Малинов Леонид
    //Функция по подчистке памяти матрицы 
    void deleteCinemaHallMatrix(int** matrix) const {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    //Малинов Леонид
    //Функция по подчистке всего словаря, где ключами являются матрицы
    void deleteCinemaHallDictionary(const map<string, int**>& dictionary) {
        for (auto& entry : dictionary) {
            deleteCinemaHallMatrix(entry.second);
        }
    }

    //Сараев Владимир + Анисимов Максим
    //Функция по созданию ключа для бронирования +  бронированя определенного места (заменяет на 1)
    string booking(int** arr, map<int, string>& bookingMap, const string& hallAndTime, const string& row, const string& place) {
        int  rowint, placeint;
        rowint = stoi(row) - 1;
        placeint = stoi(place) - 1;
        if (arr[rowint][placeint] != 1) {
            int key = rand() % RANDOM_GENERATION;
            size_t spacePos = hallAndTime.find(" ");
            string hall = hallAndTime.substr(0, spacePos);
            string time = hallAndTime.substr(spacePos + 1);
            bookingMap[key] = hall + ';' + time + ';' + row + ';' + place;
            arr[rowint][placeint] = 1;
            return hall + ';' + time + ';' + row + ';' + place + ';' + to_string(key);
        }
        return "1";
    }
    
    //Сараев Владимир + Анисимов Максим
    //Функция которая очищает словарь брони
    void bookingClear(int** arr, map<int, string>& bookingMap, const string& row, const string& place, int key) {
        int rowint = stoi(row), placeint = stoi(place);
        if (bookingMap.find(key) != bookingMap.end()) {
            arr[rowint-1][placeint-1] = 0;
            bookingMap.erase(key);
        }
    }
    
    //Акимов Никита + Егор Хопробрых
    //Функция по покупке сразу несколько билетов стоящих в ряд 
    bool buySeveralTickets(int** cinema_hall, int rows, int cols, int numTickets, const string& hallTime, map<int,string>& movieDictionary){
        for (int row = 0; row < rows; ++row) {
            int consecutiveEmptySeats = 0; // Количество свободных в ряд мест, которое мы нашли
            int startSeat; // Место, с которого будем отсчитывать количество свободных
            // Проходимся по ряду для поиска подходящих мест.
            for (int seat = 0; seat < cols; ++seat) {
                if (cinema_hall[row][seat] == 0) { // Если место не занято
                    if (consecutiveEmptySeats == 0) { // Если мы ещё не начали отсчёт свободных мест, начинаем его здесь
                        startSeat = seat; // В startSeat записываем начало потенциальной группы соседних мест
                    }
                    consecutiveEmptySeats++;
                    if (consecutiveEmptySeats == numTickets) { // Нашли нужное количество соседних мест
                        for (int i = startSeat; i < startSeat + numTickets; ++i) { // Проходимся с первого свободного места до последнего свободного
                            cinema_hall[row][i] = 1; // Покупаем место
                            string infoAboutTickets = "Зал, вермя: " + hallTime + ". Название фильма: " + movieDictionary[rows] + ". Ряд: " + to_string(row+1) + ". Место: " + to_string(i+1);
                            purchasedTickets[rand() % RANDOM_GENERATION] = infoAboutTickets;
                            onesCounter += 1;
                        }
                        cout << "Успешно куплены билеты на " << numTickets << " мест в ряду " << row + 1 << ", места с " << startSeat + 1 << " по " << startSeat + numTickets << endl;
                        return true;
                    }
                }
                else {
                    consecutiveEmptySeats = 0; // Сбрасываем счетчик свободных в ряд мест при обнаружении занятого места
                }
            }
        }
        return false;
    }

    //Акимов Никита + Егор Хоробрых 
    //Функция по покупке билетов
    void ticketBuy(int** cinema_hall, int rows, int cols) {
        cinema_hall[rows][cols] = 1;
    }

};


//main - Малинов Леонид
int main() {
    srand(static_cast<unsigned>(time(0)));
    setlocale(LC_ALL, "ru");
    
    //Класс с основной логикой по работе кинотеатра
    CinemaSystem cinemaSystem; 
    //Класс для различного форматирования вывода (пропуск N строк и.т.д.)
    OutputHelper out; 
    //Класс для корректного считывания всех input'ов с клавиатуры
    CorrectCin input; 

    //создаем словарик в формате {1 : "название фильма"}
    map<int, string> movieDictionary = cinemaSystem.createMovieDictionary();     
     //создаем словарик с 36 кинозалами, то есть для каждого зала для каждого сеанса будет отдельная матрица
    map<string, int**> cinemaScheduleDictionary = cinemaSystem.createCinemaDictionary();
     //словарик в котором будут храниться забронированные значения
    map<int, string> bookingDictionary = {}; 

    //флаг выхода из главного меню
    bool exitFlag = false; 
    while (!exitFlag) {
        //строки для input'ов в различных меню
        string mainMenuInput;
        string buyTicketsMenuInput;
        string reservationMenuInput;
        string infoMenu;

        //очищаем экран
        system("cls"); 

        //Выводим ASCII каритнку главного меню
        out.cinemaASCII();
        // Вывод меню
        cout << "Что вы хотите сделать?" << endl;
        cout << "[1]: Купить билет" << endl;
        cout << "[2]: Забронировать место" << endl;
        cout << "[3]: Информация о кинотеатре" << endl << endl;

        cout << "Купленные билеты: " << endl; 
        if (purchasedTickets.empty()) {
          cout << "У вас пока нет купленных билетов." << endl;
        } else {
          for (const auto& pair : purchasedTickets) {
              cout << pair.second << endl;
          }
        }
        // Проверяем, пуст ли второй словарь
        cout << endl << "Забронированные билеты: " << endl;
        if (reservedTickets.empty()) {
          cerr << "У вас пока нет забронированных билетов" << endl;
        } else {
          // Выводим значения второго словаря
          for (const auto& pair : reservedTickets) {
              cout << pair.second << endl;
          }
        }
        cout << endl << endl;
        cout << "Выберите пункт из меню 1,2,3 или 'exit' для выхода" << endl;
        cout << "Input > ";
        //считываем переменную для ввода
        mainMenuInput = input.correctMainMenuInput();
        
        //тут начинается основная логика меню. 1 - покупка билетов
        if (mainMenuInput == "1") {
            string buyTicketsSecondLvl;

            while (buyTicketsMenuInput != "e") {
              
                system("cls");

                //выводим меню для данного экрана
                out.purchasedASCII();
                cout << "Что вы хотите сделать?: " << endl;
                cout << "[1]: Купить 1 билет" << endl;
                cout << "[2]: Купить несколько билетов";
                out.skipLines(5);


                cout << "Выберите пункт из меню 1,2 или 'e' для выхода" << endl;
                cout << "Input > ";

                buyTicketsMenuInput = input.correctPurschasedMenuInput();

                if (buyTicketsMenuInput == "1"){
                    system("cls");
                    cout << "Доступные сеансы для покупки мест: " << endl;
                    out.printSchedule(movieDictionary);

                    cout << endl << "Введите зал и время сеанса для выбора в формате 1 10:00" << endl;
                    cout << "Где 1 - номер зала, 10:00 - время сеанса" << endl << endl;

                    cout << "Input > ";
                    buyTicketsSecondLvl = input.correctScheduleInput(cinemaScheduleDictionary);

                    bool hasPurchased = false;
                    string buyTicketsThirdLvl;

                    while (!hasPurchased && buyTicketsSecondLvl != "e" && buyTicketsThirdLvl != "e") {
                      system("cls");
                      cout << "Выберите место в формате (ряд (пробел) место) для покупки." << endl;
                      cout << endl << "1: место уже куплено/забронированно." << endl << "0: место свободно" << endl << endl;
                      cout << "Зал для сеанса " << buyTicketsSecondLvl << ":" << endl;
                      out.printMatrix(cinemaScheduleDictionary[buyTicketsSecondLvl]);

                      cout << endl << "Введите ряд и место которое хотите забронировать в формате (ряд)(место) или e для выхода: " << endl;
                      cout << "Input > ";

                      buyTicketsThirdLvl = input.correctRowColInput(cinemaScheduleDictionary[buyTicketsSecondLvl]);
                      if (buyTicketsThirdLvl != "e") {
                          system("cls");
                          string row = buyTicketsThirdLvl.substr(0, 1);
                          string col = buyTicketsThirdLvl.substr(1, 1);

                          int rowInt = stoi(row) - 1;
                          int colInt = stoi(col) - 1;

                          cinemaSystem.ticketBuy(cinemaScheduleDictionary[buyTicketsSecondLvl], rowInt, colInt);
                          hasPurchased = true;

                          string infoAboutTickets = "Зал, вермя: " + buyTicketsSecondLvl + ". Название фильма: " + movieDictionary[stoi(row)] + ". Ряд: " + row + ". Место: " + col;
                          purchasedTickets[rand() % RANDOM_GENERATION] = infoAboutTickets;

                          onesCounter += 1;
                      }
                    }
                }
                else if (buyTicketsMenuInput == "2"){
                    system("cls");
                    cout << "Доступные сеансы для покупки мест: " << endl;
                    out.printSchedule(movieDictionary);

                    cout << endl << "Введите зал и время сеанса для выбора в формате 1 10:00" << endl;
                    cout << "Где 1 - номер зала, 10:00 - время сеанса" << endl << endl;

                    cout << "Input > ";
                    buyTicketsSecondLvl = input.correctScheduleInput(cinemaScheduleDictionary);

                    bool hasPurchased = false;
                    string buyTicketsThirdLvl;
                    while (!hasPurchased && buyTicketsSecondLvl != "e" && buyTicketsThirdLvl != "e") {
                      system("cls");
                      cout << "Выберите количество мест для покупки: " << endl;
                      cout << endl << "1: место уже куплено/забронированно." << endl << "0: место свободно" << endl << endl;
                      cout << "Зал для сеанса " << buyTicketsSecondLvl << ":" << endl;
                      out.printMatrix(cinemaScheduleDictionary[buyTicketsSecondLvl]);

                      cout << endl << "Введите количество мест которое хотите забронировать (от 2 до 6) " << endl;
                      cout << "Input > ";
                        
                      buyTicketsThirdLvl = input.correctSeveralPlaceInput();
                      if (buyTicketsThirdLvl != "e" && buyTicketsThirdLvl >= "2" && buyTicketsThirdLvl <= "6"){
                          hasPurchased = cinemaSystem.buySeveralTickets(cinemaScheduleDictionary[buyTicketsSecondLvl], HALL_ROWS, HALL_COLS, stoi(buyTicketsThirdLvl), buyTicketsSecondLvl, movieDictionary);
                          while (buyTicketsThirdLvl != "e" && !hasPurchased){
                              cout << "К сожалению, нет такого количества свободных мест находящимся в одном ряду." << endl; 
                              cout << "Введите другое количество мест, или 'e' для выхода: ";
                              buyTicketsThirdLvl = input.correctSeveralPlaceInput();
                              if (buyTicketsThirdLvl != "e" && buyTicketsThirdLvl >= "2" && buyTicketsThirdLvl <= "6"){
                                hasPurchased = cinemaSystem.buySeveralTickets(cinemaScheduleDictionary[buyTicketsSecondLvl], HALL_ROWS, HALL_COLS, stoi(buyTicketsThirdLvl), buyTicketsSecondLvl, movieDictionary);
                              }
                          } 
                      }
                      buyTicketsMenuInput = "e";
                    }
                }
                buyTicketsMenuInput = "e";
            }
        }
        //2 - бронирование билетов
        else if (mainMenuInput == "2") {
            while (reservationMenuInput != "e") {
                system("cls");

                //выводим меню для данного экрана
                out.bookingASCII();
                cout << "Что вы хотите сделать?: " << endl;
                cout << "[1]: Забронировать билет" << endl;
                cout << "[2]: Отменить бронь";
                out.skipLines(5);


                cout << "Выберите пункт из меню 1,2 или 'e' для выхода" << endl;
                cout << "Input > ";

                //считываем input
                reservationMenuInput = input.correctReservationMenuInput();

                //если пользовать выбрал бронь билетов
                if (reservationMenuInput == "1") {

                    system("cls");
                    string reservationSecondLvl;

                    while (reservationSecondLvl != "e") {
                        cout << "Доступные сеансы для бронирования мест: " << endl;
                        out.printSchedule(movieDictionary);

                        cout << endl << "Введите зал и время сеанса для выбора в формате 1 10:00" << endl;
                        cout << "Где 1 - номер зала, 10:00 - время сеанса" << endl << endl;

                        cout << "Input > ";
                        reservationSecondLvl = input.correctScheduleInput(cinemaScheduleDictionary);

                        bool hasBooked = false;
                        string reservationThirdLvl;
                        while (!hasBooked && reservationThirdLvl != "e" && reservationSecondLvl != "e") {
                            system("cls");
                            cout << "Выберите место в формате (ряд (пробел) место) для бронирования." << endl;
                            cout << endl << "1: место уже куплено/забронированно." << endl << "0: место свободно" << endl << endl;
                            cout << "Зал для сеанса " << reservationSecondLvl << ":" << endl;
                            out.printMatrix(cinemaScheduleDictionary[reservationSecondLvl]);

                            cout << endl << "Введите ряд и место которое хотите забронировать в формате (ряд)(место) или e для выхода: " << endl;
                            cout << "Input > ";
                            reservationThirdLvl = input.correctRowColInput(cinemaScheduleDictionary[reservationSecondLvl]);
                            if (reservationThirdLvl != "e") {
                                string row = reservationThirdLvl.substr(0, 1);
                                string col = reservationThirdLvl.substr(1, 1);
                                //тут мы одновременно и бронируем, и сохраняем основную инфу в красивом виде
                                string mainInfo = cinemaSystem.booking(cinemaScheduleDictionary[reservationSecondLvl], bookingDictionary, reservationSecondLvl, row, col);
                                hasBooked = true;


                                onesCounter += 1;

                                stringstream split(mainInfo);
                                string token;
                                getline(split, token, ';');
                                int hallNumber = stoi(token);
                                string hallNumberS = token;
                                getline(split, token, ';');
                                string time = token;
                                getline(split, token, ';');
                                int rows = stoi(token);
                                string rowsH = token;
                                getline(split, token, ';');
                                int cols = stoi(token);
                                string colsH = token;
                                getline(split, token, ';');
                                string keyH = token;
                                int key = stoi(token);


                                string cinemaName = movieDictionary[hallNumber];
                                string reservationsInfo = "Зал, время: " + hallNumberS + " " + time + ". Название фильма: " + cinemaName + ". Ряд: " + rowsH + ". Место: " + colsH + ". Ключ брони: " + keyH;
                                reservedTickets[key] = reservationsInfo;

                            }
                            reservationSecondLvl = "e";
                        }
                    }
                    reservationMenuInput = "e";

                }
                else if (reservationMenuInput == "2") {
                    system("cls");
                    string reservationSecondLvl;
                    bool hasCancel = false;
                    while (reservationSecondLvl != "e" && !hasCancel) {

                        if (!bookingDictionary.empty()) {
                            cout << "Ваши забронированные места: ";
                            if (reservedTickets.empty()) {
                              cerr << "У вас пока нет забронированных билетов" << endl;
                            } else {
                              // Выводим значения второго словаря
                              for (const auto& pair : reservedTickets) {
                                  cout << pair.second << endl;
                              }
                            }

                            cout << endl << endl;
                            cout << "Введите ключ (4х значное число) для отмены брони, или 'e' для выхода" << endl;
                            cout << "Input > ";
                            //тут мы будем считывать ключ 
                            reservationSecondLvl = input.correctBookingKeyInput(bookingDictionary);

                            string mainInfo = reservationSecondLvl;
                            string token;
                            stringstream split(mainInfo);

                            getline(split, token, ';');
                            string hallNumber = token;
                            getline(split, token, ';');
                            string time = token;
                            getline(split, token, ';');
                            string rows = token;
                            getline(split, token, ';');
                            string cols = token;
                            getline(split, token, ';');
                            int key = stoi(token);

                            string getHall = hallNumber + " " + time;

                            cinemaSystem.bookingClear(cinemaScheduleDictionary[getHall], bookingDictionary, rows, cols, key);

                            hasCancel = true;
                            reservedTickets.erase(key);
                            onesCounter -= 1;
                            

                            reservationSecondLvl = "e";

                        }
                        else {
                            system("cls");
                            cout << "У вас пока нет забронированных сеансов" << endl << endl;
                            cout << "Введите что угодно для выхода в главное меню: ";
                            string temp;
                            cin >> temp;
                            reservationSecondLvl = "e";
                        }
                    }
                    reservationMenuInput = "e";
                }
            }
        }
        //3 - информация о кинотеатре
        else if (mainMenuInput == "3") {
            system("cls");
            out.infoASCII();
            cout << "Мест куплено: " << onesCounter << endl;
            cout << "Прибыль кинотеатра с продажи мест: " << onesCounter * 350 << " рублей";
            out.skipLines(5);

            cout << "Введите что-нибудь, чтобы выйти: " << endl;
            cout << "Input > ";
            string temp;
            cin >> temp;
        }
        //выход из главного меню
        else if (mainMenuInput == "exit") {
            exitFlag = true;
        }
    }
    
    //очистка памяти в словарях
    cinemaSystem.deleteCinemaHallDictionary(cinemaScheduleDictionary);
}
