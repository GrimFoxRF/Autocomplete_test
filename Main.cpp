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
    //��������, ����������� �� ���� �������
    if (!fin.is_open()) {
        cout << "������: �� ������� ������� ���� �������" << endl;
        return 1;
    }
    string word;
    while (fin >> word) {
        dict.push_back(word);
        insert(root, word);
    }
    fin.close();

    string prefix;
    cout << "������� ����� ����� �� ���������� ����� ��� ��������������" << endl; 
    cout<<"��� ����� ����� ��� ������: ";
    cin >> prefix;
    
    while (!isdigit(prefix[0])) {
        for (char c : prefix) {
            if (!isalpha(c) || !isupper(c) && !islower(c)) {
                cout << "������������ ����! ���������� ��� ���." << endl;            
            }
            else {
                vector<string> res = search(root, prefix); // ������� ��� �����, ������������ � ��������� ��������
                if (res.empty()) {
                    cout << "��� ����, ������������ � ������� ��������." << endl;
                }
                //����� ���������� ��������� �� �������
                else {
                    cout << "\n�������� (";
                    for (auto word : res) {
                        cout << word << " ";
                    }
                    cout << ")\n" << endl;
                    cout << "�� ������ �������� �����? (y/n): ";
                    char choice;
                    cin >> choice;

                    if (tolower(choice) == 'y') {
                        // �������� ����� �� ��������
                        string wordToReplace = res[0]; // ������ ����� �� ���������
                        // ���������� ������ �����
                        vector<string> res = search(root, prefix);
                        if (!res.empty()) {
                            prefix = res[0];
                            cout << "\n�������� ��: " << prefix << endl;
                        }
                        cout << "����� ������� ��������!" << endl;
                    }
                }
            }
        }
        cout << "������� ����� ����� �� ���������� ����� ��� ��������������" << endl;
        cout << "��� ����� ����� ��� ������: ";
        cin >> prefix;
        
    }
    cout << "\n��� ������ �� ��������� ������� ����� �������.";
    system("pause>NULL");
    return 0;
}