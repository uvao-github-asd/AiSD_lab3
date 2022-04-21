#include <stdio.h>
#include <iostream>
#include <locale.h>
#include <windows.h>

struct Node
{
    int x;
    int key;
    Node* Next;
};
struct set
{
    Node* data;
};
struct set* y;
struct set* array;



class hash
{
    Node* First;

public:
    //~hash();
    int T = 0;
    int N = 8;
    int size = 0;
    int hashFunction(int key); // берем ключ и возврасчаем хеш как остаток от деления на N=8
    void insert(int key, int data);
    void init();
    void del(int key);// удаляем элемент по ключу
    void print();//выводим всю табилцу
    void copy();// увеличиваем её
    void printkey(int key); // печатаем элементы по ключу
};
/*hash::~hash()
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (array[i].data->x != 0)
        {

            Node* tmp = array[i].data;
            Node* tmpNext = tmp;
            if (tmp != NULL) {
                while (tmp->Next != NULL)
                {
                    tmpNext = tmp->Next;
                    free(tmp);
                    tmp = tmpNext;
                }
            }
            else
            {
                free(array[i].data);
            }


        }
        else
        {
            free(array[i].data);
        }
    }
    delete array;
}*/

int hash::hashFunction(int key)
{   // Хеш считаем как остаток от деления ключа на 8
    return (key % N);
}

void hash::init()
{
    /*1.	Инициализации, создаем массив, для каждой ячейки массива создаем 
    узел связанного списка со значением NULL и помещаем указатель в ячейку массива */

    array = new set[N];
    for (int i = 0; i < N; i++)
    {
        Node* temp = new Node;
        temp->Next = NULL;
        temp->key = 0;
        temp->x = 0;
        array[i].data = temp;


    }
}

void hash::insert(int key, int data)
{   /*2.	Вставка элемента, считываем ключ и значение,
    проверяем ключ, если отрицательный умножаем на -1.
    Высчитываем адрес ячейки -  делим с остатком ключ на размер таблицы,
    остаток берем за адрес, проверяем первый узел в ячейке, 
    если свободен записываем в него значение,
    если узел уже занят что б избежать коллизии создаем следящий узел списка в этой ячейке и записываем значение в него.  */


    // на случай ввода отрицательного ключа
    if (key < 0) key = key * -1;
    // узнаем куда вставлять от 0 до 7 применяя хеш функцию 
    int index = hashFunction(key);

    // создаем новый элемент и кидаем туда введенный ключ
    Node* temp = new Node;
    temp->key = key;

    if (array[index].data->x == 0)
    {

        temp->Next = NULL;
        temp->x = data;

        array[index].data = temp;

        size++;
        printf("\n Ключ (%d) вставлен \n", key);
    }

    else {
        Node* tmp = array[index].data;
        while (tmp->Next != NULL)  tmp = tmp->Next;
        temp->Next = NULL;
        temp->x = data;

        tmp->Next = temp;
    }
    if (N == size * 2) copy();


}

void hash::copy()
{   
    T = N;
    N = N * 2;
    y = new set[T];


    for (int i = 0; i < T; i++) y[i].data = array[i].data;
    delete[] array;
    init();
    for (int i = 0; i < T; i++) array[i].data = y[i].data;
    delete[] y;
    printf("Новый размер хеш-таблицы %d\n", N);
};

void hash::del(int key)
{
    /*4.	Удаление элемента по ключу,
    вычисляем адрес ячейки, если узел по адресу не пуст, 
    освобождаем память последнего узла списка в ячейки, 
    и обнуляем ссылку в предпоследнем узле на следующий элемент. */


    int index = hashFunction(key);
    Node* temp = array[index].data;

    if (array[index].data->x == 0)
    {
        printf("\n Данного ключа не существует \n");
    }

    else if (temp->Next == NULL)
    {
        temp->key = 0;
        temp->x = 0;

        size--;
        printf("\n Ключ (%d) удален \n", key);
    }

    else
    {
        while (temp->Next != NULL)

            if (temp->Next->Next == NULL) {

                free(temp->Next->Next);
                temp->Next = NULL;
            }

        temp = temp->Next;

    }


}

void hash::printkey(int key)
{
    /*3.	Получение значение по ключу, вычисляем адрес ячейки,
    если узел по адресу не пуст, выводим содержимое, если узлов больше одного выводим все.  */

    int index = hashFunction(key);
    Node* temp = array[index].data;

    if (array[index].data->x == 0)
    {
        printf("\n Данного ключа не существует \n");
    }

    else if (temp->Next == NULL)
    {
        // если такой элемент один

        printf(" key: %d value[%d] \t", temp->key, temp->x);
    }

    else
    {
        printf("\n");
        if (temp != NULL) {
            //если таких элементов несколько
            while (temp->Next != NULL)
            {
                printf(" key: %d value[%d] ", temp->key, temp->x);
                temp = temp->Next; 
            }
        }

    }


}

void hash::print()
{
    int i;
    for (i = 0; i < N; i++) // проходим по таблице от 0 до 7
    {
        if (array[i].data->x == 0)
        { // печатаем пустую ячейку, если пусто
            printf("\n value[%d]: / ", i);
        }
        else
        {
            Node* tmp = array[i].data;
            printf("\n");
            if (tmp != NULL) {

                while (tmp->Next != NULL)
                {      
                    printf(" key: %d value[%d]: %d ", array[i].data->key, i, tmp->x);
                    tmp = tmp->Next; // переход к следующему элементу с этим же ключем
                }
            }
            //печать последнего элемента в хештаблице с этим ключем
            printf(" key: %d value[%d]: %d \t", array[i].data->key, i, array[i].data->x);
        }
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    hash hash;
    
    int choice, key, data;
    int c = 0; // флаг выхода
    hash.init(); //инициализация 

    do
    {
        printf("\n1.Вставить элемент в хэш-таблицу"
            "\n2.Удалить элемент из хэш-таблицы"
            "\n3.Вывести хэш-таблицу"
            "\n4.Получить значение по ключу"
            "\n5.Завершить"
            "\n\n Пожалуйста, выберите нужный вариант: ");

        scanf_s("%d", &choice);


        switch (choice)
        {
        case 1:

            printf("Введите ключ -:\t");
            scanf_s("%d", &key);
            printf("Введите данные-:\t");
            scanf_s("%d", &data);
            hash.insert(key, data); //Вставить элемент в хэш-таблицу

            break;

        case 2:

            printf("Введите ключ, который хотите удалить-:");
            scanf_s("%d", &key);
            hash.del(key); //Удалить элемент из хэш-таблицы

            break;



        case 3:

            hash.print(); //Вывести хэш-таблицу

            break;
        case 4:

            printf("Введите ключ:");
            scanf_s("%d", &key);
            hash.printkey(key); //Получить значение по ключу

            break;
        case 5:

            c = 1; // Флаг выхода из бесконечного цикла

            break;

        default:

            printf("Недействительный ввод\n");
        }


    } while (c != 1); //бесконечный цикл
}