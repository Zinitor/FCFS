#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <limits>
#include <cstdlib>

std::vector <int> Optimal_procs;
float optimal_time = std::numeric_limits<float>::max();
float optimal_wait_time = std::numeric_limits<float>::max();



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
        time += Procs[i] * k;
        k--;
    }
    time = time / Procs.size();
    if (time < optimal_time) {
        optimal_time = time;
    }
    return time;
}

float avg_wait_time(vector <int> a) {
    float time = 0;
    int k = a.size(); // n, (n-1), (n-2), ... 1 
    for (int i = 1; i < a.size(); i++) {

        time += a[i - 1];
        k--;
    }
    time = time / a.size();
    if (time < optimal_wait_time) {
        optimal_wait_time = time;
        Optimal_procs = a;
    }
    else if (time == optimal_wait_time) {
        for (int i = 0; i < a.size(); i++) {
            Optimal_procs.push_back(a[i]);
        }
    }
    return time;
}

void display(vector<int> a, int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << " ";
    cout << endl << "| Среднее время выполнения процесса: " << avg_exec_time(a) << endl;
    cout << "| Среднее время ожидания процесса: " << avg_wait_time(a) << endl;
}

void display_graph(vector<int> a) {
    char active = 'И';
    char prepare = 'Г';
    int swch = 0;
    int count = 0;
    for (int i = 0; i < a.size(); i++) {
        if (swch == 0) {
            cout << "Proc №" << i << ": " << a[i] << "\t" << string(a[i], active) << endl;
            swch = 1;
            count += a[i];
        }
        else if (swch == 1) {
            cout << "Proc №" << i << ": " << a[i] << "\t" << string(count, prepare) << string(a[i], active) << endl;
            count += a[i];
        }
    }
}

void display_optimal_graph(vector<int> a, int N) {
    char active = 'И';
    char prepare = 'Г';
    int swch = 0;
    int count = 0;
    char yn;
    for (int i = 0; i < N; i++) {
        if (swch == 0) {
            cout << "Proc №" << i << ": " << a[i] << "\t" << string(a[i], active) << endl;
            swch = 1;
            count += a[i];
        }
        else if (swch == 1) {
            cout << "Proc №" << i << ": " << a[i] << "\t" << string(count, prepare) << string(a[i], active) << endl;
            count += a[i];
        }
    }
    cout << "Оптимальное время выполнения: " << optimal_time << endl;
    cout << "Оптимальное время ожидания: " << optimal_wait_time << endl;
    cout << "Найдено всего " << Optimal_procs.size() / N << " путей с таким же оптимальным временем ожидания" << endl;
    cout << "Показать? Y/N" << endl;

    cin >> yn;
    yn = tolower(yn);
    switch (yn) {
    case 'y':
        swch = 0;
        count = 0;
        for (int i = 0; i < Optimal_procs.size(); i++){
            if (i % (N) == 0 && i != 0) {
                cout << endl;
                swch = 0;
                count = 0;
            }
            if (swch == 0) {
                cout << "Proc №" << i%N << ": " << Optimal_procs[i] << "\t" << string(a[i], active) << endl;
                swch = 1;
                count += a[i];
            }
            else if (swch == 1) {
                cout << "Proc №" << i%N << ": " << Optimal_procs[i] << "\t" << string(count, prepare) << string(a[i], active) << endl;
                count += a[i];
            }
        }
        break;
    case 'n':
        cout << "Выходим" << endl;
        break;
    default:
        cout << "Неправильный символ, введите Y/N" << endl;
        break;
    }

}

void display_next_permutation(vector <int> Procs){
    
}

int main() {
    setlocale(LC_ALL, "Russian");

    int N; // Количество процессов 
    cout << "Введите количество процессов: ";
    cin >> N;
    vector <int> Procs(N); // Создаем вектор для хранения длительности процессов

    srand(unsigned(std::time(nullptr)));
    generate(Procs.begin(), Procs.end(), gen); // Генерируем длительность процессов и заносим в вектор

    for (int i = 0; i < N; i++) {
        cout << "Proc №" << i << ": " << Procs[i] << endl;
    }
    cout << "Средняя длительность процесса: " << avg_proc_time(Procs) << endl;
    std::sort(Procs.begin(), Procs.end()); //Сортировка вектора перед next_permutation

    do {
        display(Procs, N);
        display_graph(Procs);
        cout << endl;
    } while (std::next_permutation(Procs.begin(), Procs.end()));
    cout << endl << "Оптимальный граф: " << endl;
    display_optimal_graph(Optimal_procs, N);
    

    return 0;
}