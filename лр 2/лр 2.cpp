#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Stack {
    int info;
    Stack* next;
} *Begin, * t;

Stack* InStack(Stack*, int);
void View(Stack*);
void Del_All(Stack**);
void FindMinMax(Stack*, int&, int&);
void DeleteBetween(Stack**, int&, int, int);
bool Exception(Stack* p, int min, int max);



Stack* InStack(Stack* p, int in) {
    Stack* t = new Stack;
    t->info = in;
    t->next = p;
    return t;
}

void View(Stack* p) {  
    Stack* t = p;
    while (t != NULL) {
        cout << " " << t->info << endl;
        t = t->next;
    }
}

void FindMinMax(Stack* p, int& min, int& max) {
    if (p == NULL) {
        cout << "Список пуст." << endl;
        return;
    }

    Stack* t = p;
    min = t->info;
    max = t->info;
    while (t != NULL) {
        if (t->info < min) min = t->info;
        if (t->info > max) max = t->info;
        t = t->next;
    }
    cout << "\nМинимальное значение: " << min << "\nМаксимальное значение: " << max << endl;
}

bool Exception(Stack* p, int min, int max) {
    Stack* t = p;
    while (t->next != NULL) {
        if (max == min) {
            cout << "\nМаксимальное и минимальное значения совпадают" << endl;
            return true;
        }
        else if ((t->info == min && t->next->info == max) || (t->info == max && t->next->info == min)) {
            cout << "\nНечего удалять! Максимальное и минимальное значения стоят рядом" << endl;
            return true;
        }
        t = t->next;
    }
    return false;
}



void DeleteBetween(Stack** p, int &k, int min, int max) {
    Stack* t = *p;
    Stack* d = t;
    bool l=true;

    while (t->next != NULL) {
        if (t->info == min) {
            l = true;
            break;
        }
        else if (t->info == max) {
            l = false;
            break;
        }
        t = t->next;
    }

    if (l == false) {
        int e = min;
        min = max;
        max = e;
    }
   
    if ( t->info != min )
        t = t->next;
    else {
        while ( t->next->info != max ) {
            d = t->next;
            t->next = d->next;
            delete d;
            k++;
        }
    }   
}

void Sort_info(Stack* p) {
    Stack* kr = new Stack;
    kr->next = Begin;
    Begin = kr;
    Stack* t = NULL, * t1;
    int r; 
    do {
        for (t1 = p; t1->next != t; t1 = t1->next)
            if (t1->info > t1->next->info) {
                
                    r = t1->info;
                t1->info = t1->next->info;
                t1->next->info = r;
            }
        t = t1;
    } while (p->next != t);
    Begin = Begin->next;
    delete kr;
}

void Sort_p(Stack** p) {
    Stack* kr = new Stack;
    kr->next = Begin;
    Begin = kr;
    Stack* t = NULL, * t1, * r;
    if ((*p)->next->next == NULL) return;
    do {
        for (t1 = *p; t1->next->next != t; t1 = t1->next)
            if (t1->next->info > t1->next->next->info) {
                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        t = t1->next;
    } while ((*p)->next->next != t);
    Begin = Begin->next;
    delete kr;
}

void Del_All(Stack** p) {
    while (*p != NULL) {
        Stack* t = *p;
        *p = (*p)->next;
        delete t;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(static_cast<unsigned>(time(0)));

    Begin = nullptr; // Инициализация стека
    int i, in, n, min, max, choose;
    int k = 0;

    cout << "Введите количество чисел в стеке : ";
    cin >> n;
    for (i = 1; i <= n; i++) {
        in = (rand() % 41)-20;
        Begin = InStack(Begin, in);
    }

    cout << "Исходный Stack:\n";
    View(Begin);
    cout << "\nЧто делаем со стеком ?\n 1 - выполняем индивидуальное задание\
             \n 2 - сортируем по адресу\n 3 - сортируем по значению\n\n";
    cin >> choose;
    

    switch (choose) {
    case 1 :

        if (Begin != NULL) {
        FindMinMax(Begin, min, max);

        if (Exception(Begin, min, max) == true) {
            return 0;
        }
        else {
            DeleteBetween(&Begin, k, min, max);
            cout << "\nStack после удаления:\n";
            View(Begin);
            cout << "\nКоличество удалённых элементов : " << k;
        }
        }
        break;

    case 2: 
        cout << "\nУпорядоченный стек (по адресу) \n";
        Sort_p(&Begin);
        View(Begin);
        break;

    case 3: 
        cout << "\nУпорядоченный стек (по значению) \n";
        Sort_info(Begin);
        View(Begin);
        break;
    default:
        cout << "Такой цифры нет в меню. Попробуйте снова\n";
    }
        
    Del_All(&Begin);
    return 0;
}
