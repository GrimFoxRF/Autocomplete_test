#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Trie.h"

using namespace std;

int main() 
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    
    TrieNode* root = new TrieNode('\0');
    vector<string> dict;
    ifstream fin("dict.txt");
    //проверка, открывается ли файл словаря
    if (!fin.is_open()) {
        cout << "ОШИБКА: Не удалось открыть файл словаря" << endl;
        return 1;
    }
    string word;
    while (fin >> word) {
        dict.push_back(word);
        insert(root, word);
    }
    fin.close();

    string prefix;
    cout << "Введите часть слова на английском языке для автодополнения" << endl; 
    cout<<"или любую цифру для выхода: ";
    cin >> prefix;
    
    while (!isdigit(prefix[0])) {
        for (char c : prefix) {
            if (!isalpha(c) || !isupper(c) && !islower(c)) {
                cout << "Некорректный ввод! Попробуйте еще раз." << endl;            
            }
            else {
                vector<string> res = search(root, prefix); // находим все слова, начинающиеся с заданного префикса
                if (res.empty()) {
                    cout << "Нет слов, начинающихся с данного префикса." << endl;
                }
                //вывод подходящих вариантов из словаря
                else {
                    cout << "\nВарианты (";
                    for (auto word : res) {
                        cout << word << " ";
                    }
                    cout << ")\n" << endl;
                    cout << "Вы хотите заменить слово? (y/n): ";
                    char choice;
                    cin >> choice;

                    if (tolower(choice) == 'y') {
                        // Заменяем слово по префиксу
                        string wordToReplace = res[0]; // Первое слово из найденных
                        // Реализация замены слова
                        vector<string> res = search(root, prefix);
                        if (!res.empty()) {
                            prefix = res[0];
                            cout << "\nЗаменено на: " << prefix << endl;
                        }
                        cout << "Слово успешно заменено!" << endl;
                    }
                }
            }
        }
        cout << "Введите часть слова на английском языке для автодополнения" << endl;
        cout << "или любую цифру для выхода: ";
        cin >> prefix;
        
    }
    cout << "\nДля выхода из программы нажмите любую клавишу.";
    system("pause>NULL");
    return 0;
}