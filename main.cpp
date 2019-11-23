#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>//Для работы с файлами
#include <sstream>//Для работы со строками
using namespace std;
int main()
{
    ostringstream oss;//Объект для вывода строк
    ifstream in;//Файл для чтения
    setlocale(LC_ALL, "rus");//Подключение кодировки с русскими буквами
    char str[100];//Служебная строка для ввода данных в консоль
    char ch;//Текущий символ при считывании из файла
    char *sentences[3];//Указатели на строки, куда будут заноситься предложения из файла
    int sizes[3]={0, 0, 0};//Размеры предложений, считываемых из файла
    int i=0;//Индекс для строк, куда помещаются данные из файла
    int count=0;//Индекс массива-строки str и для строк, куда помещаются данные из файла
    int choise;//Переменные для номера команды в меню и выбора нужного элемента массива типа Aeroflot
    bool flag=false;//Переменная для поверки правильности команд и т.д.
    while(1)//Основной цикл работы программы
    {
        while(1)//Цикл для проверки правильности введенной команды в меню
        {
            cout << "1 - Read 3 sentences and display it in reverse order\n2 - Exit\n\n";//Информация для пользователя
            cout << "Enter the number of your choise:\n";
            gets(str);
            count=0;
            while(str[count])//Цикл проверки на то, является ли введенная заявка числом
            {
               if(isdigit(str[count]))
               {
                  flag=true;
                  count++;
               }
               else
               {
                  count=0;
                  flag=false;
                  break;
               }
            }
            if(!flag)
            {
               cout << "Incorrect! Press any button...\n";
               _getch();
               system("cls");
               continue;
            }
            else
               choise=atoi(str);//Сообщение - число, теперь идет преобразование из строки в число
            if(choise>2||choise<1)//Такой команды в меню нет, ошибка
            {
               cout << "Incorrect! Press any button...\n";
               _getch();
               system("cls");
               continue;
            }
            else
                break;
        }
        switch(choise)//Коммутатор, определяющий необходимые операции по заданному пункту в меню
        {
        case 1: system("cls");//Считывание 3 предложений из файла, их вывод в обратном порядке
        sizes[0]=0;//
        sizes[1]=0;//Обнуление размеров предложений
        sizes[2]=0;//
        in.open("Source.txt");//Открытие файла
        if(!in)//Ошибка открытия файла
           cout << "File can't be open!\n";
        count=0;
        i=0;
        sentences[0]=NULL;//
        sentences[1]=NULL;//Обнуление указателей
        sentences[2]=NULL;//
        flag=false;
        while(((ch = in.get()) != EOF))//Считывание символов из файла для определения размеров предложений
        {
           if(flag==true&&(ch!='\n'&&ch!='\0'&&ch!='.'&&ch!='!'&&ch!='?'))//Текущий символ - не разделитель, чего нельзя сказать о предыдущем
           {
              count++;//Переход к новому предложению
              if(count>2)//Выход из цикла, т.к. уже считаны данные для размеров трех предложений
                 break;
              sizes[count]++;//Если нет, то наращивание счетчика букв для нового предложения
              flag=false;
              continue;//Ход по циклу далее
           }
           if(ch!='\n'&&ch!='\0')//Пока не переход на новую строку или конец строки, инкремент счетчика символов
              sizes[count]++;
           if(ch=='.'||ch=='!'||ch=='?'||ch=='\0')//Запоминание знака препинания
              flag=true;
        }
        sentences[0]=new char[sizes[0]+1];//
        sentences[1]=new char[sizes[1]+1];//Выделение памяти как раз под размеры предложений и под байты-терминаторы
        sentences[2]=new char[sizes[2]+1];//
        count=0;//
        i=0;//Обнуление служебных переменных
        in.close();//
        in.open("Source.txt");//Переоткрытие файла для заноса символов в строки
        flag=false;
        while(((ch = in.get()) != EOF))
        {
           if(flag==true&&(ch!='\n'&&ch!='\0'&&ch!='.'&&ch!='!'&&ch!='?'))
           {
              sentences[count][i]='\0';//Вставка байта-терминатора в строку
              count++;//Переход на новое предложение
              if(count>2)
                 break;
              i=0;
              sentences[count][i]=ch;//Занесение текущего символа в новом предложении
              i++;
              flag=false;
              continue;
           }
           if(ch!='\n'&&ch!='\0')
           {
              sentences[count][i]=ch;//Занесение текущего символа в текущем предложении
              i++;
           }
           if(ch=='.'||ch=='!'||ch=='?'||ch=='\0')//Запоминание знака препинания
              flag=true;
        }
        in.close();//Закрытие файла
        i=0;
        /*----------Вывод предложений в обратном порядке---------*/
        while(sizes[2]>0)
        {
            cout << sentences[2][i];
            i++;
            sizes[2]--;
        }
        cout << "\n";
        oss.str(sentences[1]);
        cout << oss.str() << "\n";
        oss.str(sentences[0]);
        cout << oss.str() << "\n";
        /*----------Вывод предложений в обратном порядке---------*/
        delete [] sentences[0];//
        delete [] sentences[1];//Удаление памяти для последующих предложений, если файл будет обновлен в течение работы программы
        delete [] sentences[2];//
        cout << "\nPress any button...\n";
        _getch();
        system("cls");
            break;
        case 2://Выход из программы
        cout << "Goodbye!\n";
        return 0;
            break;
        }
    }
}
