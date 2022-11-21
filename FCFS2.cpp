// FCFS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <limits>
#include <cstdlib>



std::vector <int> Optimal_procs;
float optimal_time = std::numeric_limits<float>::max();

using namespace std;
int gen() {
    
    int a = rand() % 10 + 1;
    return a;
}

float avg_proc_time(vector<int> Procs) {

    float time = 0;

    for (int i = 0; i < Procs.size(); i++) {
        time += Procs[i];
    }

    time = time / Procs.size();

    return time;
};

float avg_exec_time(vector<int> Procs) {
    float time = 0;
    int k = Procs.size(); // n, (n-1), (n-2), ... 1 
    for (int i = 0; i < Procs.size(); i++) {

        time += Procs[i] * k ;
        k--;
    }
    time = time / Procs.size();
    if (time < optimal_time) {
        optimal_time = time;
        Optimal_procs = Procs;
    }

    return time;
}

void display(vector<int> a, int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << " ";
}

void display_graph(vector<int> a) {
    cout << optimal_time << endl;
    char active = '█';
    char prepare = '░';
    for (int i = 0; i < a.size(); i++) {
        cout << "Proc №" << i << ": " << Optimal_procs[i] << "  " << string(Optimal_procs[i], char(2580)) << endl;
        
    }
}

//░
//█

int main() {
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "Russian");    
    int N = 3; // Количество процессов
    vector <int> Procs(N); // Создаем вектор для хранения длительности процессов
    
    srand(unsigned(std::time(nullptr)));
    generate(Procs.begin(), Procs.end(), gen); // Генерируем длительность процессов и заносим в вектор

    for (int i = 0; i < N; i++) {
        cout <<"Proc №" << i << ": " << Procs[i] << endl;
    }
    cout << "Средняя длительность процесса: " << avg_proc_time(Procs) << endl;
    std::sort(Procs.begin(), Procs.end()); //Сортировка вектора перед next_permutation
    //tgamma(N + 1)
    do {
        
        display(Procs, N) ;
        cout << "| Среднее время выполнения процесса: " << avg_exec_time(Procs) << endl;
    }
    while (std::next_permutation(Procs.begin(), Procs.end()));
    display_graph(Procs);

  
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
