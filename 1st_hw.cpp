#include <iostream> 
#include <climits>
#include "deque.h" 

using namespace std;

int main(){
    srand(time(nullptr)); 
    unsigned n = 15;
    deque <int> numbers; 
    if (n % 10 != 1 || n % 100 == 11)
        cout << "Создание дека, состоящего из " << n << " случайных элементов целого типа" << endl; 
    else
        cout << "Создание дека, состоящего из " << n << " случайного элемента целого типа" << endl; 
    for (unsigned i = 0; i < n; ++i) 
        numbers.push_back(rand() % 201 - 100); 
    print_deque(numbers); 
    cout << endl;
    char c; 
    int val; 
    unsigned* elems; 

    while(true){ 
        cout << "Выберете одно из действий:" << endl; 
        cout << "\t1) Включение нового элемента в начало дека" << endl; 
        cout << "\t2) Вывод элемента из начала дека" << endl;
        cout << "\t3) Вывод элемента дека по его индексу (не первого и не последнего)" << endl;
        cout << "\t4) Удаление элемента из начала дека" << endl;
        cout << "\t5) Удаление элемента из конца дека" << endl;
        cout << "\t6) Выход из программы с последующим удалением дека" << endl; 
        c = cin.get();
        while (cin.get() != '\n');
        switch (c) {
            case '1':
                if (numbers.size() == n) { 
                    cout << "Включение невозможно, дек переполнен" << endl << endl; 
                    continue;
                }
                cout << "Введите число целого типа (новый элемент)" << endl; 
                cin >> val;
                if (!cin)
                    break; 
                numbers.push_front(val); 
                break; 
            case '2':
                if (!numbers.size()) { 
                    cout << "Вывод первого элемента невозможен, дек пуст" << endl << endl; 
                    continue; 
                }
                cout << "Первый элемент в деке равен " << numbers.front() << endl << endl; 
                break; 
            case '3':
                if (!numbers.size()) { 
                    cout << "Вывод элемента по индексу невозможен, дек пуст" << endl << endl; 
                    continue; 
                }
                cout << "Введите число целого типа (индекс элемента в деке)" << endl; 
                cin >> val; 
                if (!cin)
                    break;
                if (val < numbers.size() && 1 < val)
                    cout << "Элемент под номером " << val << " равен " << numbers[val - 1] << endl;
                else {
                    cout << "Индекс элемента некорректен: он должен быть меньше размера дека и больше 1" << endl; 
                }
                break;
            case '4':
                if (!numbers.size()) { 
                    cout << "Удаление невозможно, дек пуст" << endl << endl; 
                    continue; 
                }
                numbers.pop_front();
                break;
            case '5':
                if (!numbers.size()) {
                    cout << "Удаление невозможно, дек пуст" << endl << endl; 
                    continue;
                }
                numbers.pop_back();
                break;
            case '6':
                break;
            default:
                cout << "Ваш выбор непонятен, вызов меню" << endl; 
                break; 
        } 
        if (c == '6')
            break;
        if (c == '1' || c == '3') { 
            if (!cin) { 
                cin.clear(); 
                while (cin.get() != '\n'); 
                cout << "То что введено не является числом входящим в диапазон [ " << INT_MIN << " : " << INT_MAX <<" ], вызов меню" << endl << endl; 
                continue;
            }
            while (cin.get() != '\n'); 
        } 
        if (c != '3' && c != '2' && c <= '5' && c >= '1') 
            print_deque(numbers); 
        cout << endl; 
    }
    cout << "Удаление дека" << endl; 
    while (numbers.size())
        numbers.pop_back();
    return 0; 
}