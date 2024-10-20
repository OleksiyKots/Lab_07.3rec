#include <iostream>
#include <iomanip>
using namespace std;

// ќголошенн€ функц≥й дл€ роботи з масивами
void InputRows(int** a, const int rowCount, const int colCount, int rowNo); // ¬веденн€ елемент≥в матриц≥
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo); // ¬иведенн€ елемент≥в матриц≥
int FindZeroColRecursive(int** a, const int rowCount, const int colCount, int colNo, int rowNo); // ѕошук першого стовпц€ з нульовим елементом
int CalculateRowCharacteristicRecursive(int* row, const int colCount, int colNo); // ќбчисленн€ характеристики р€дка
void SortRowsRecursive(int** a, const int rowCount, const int colCount, int rowNo); // —ортуванн€ р€дк≥в за характеристикою

int main() {
    int rowCount, colCount;
    // ¬веденн€ к≥лькост≥ р€дк≥в ≥ стовпц≥в
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    // —творенн€ двовим≥рного масиву
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    // ¬веденн€ елемент≥в матриц≥
    InputRows(a, rowCount, colCount, 0);

    // ¬иведенн€ матриц≥
    PrintRows(a, rowCount, colCount, 0);

    // ѕошук першого стовпц€, що м≥стить нульовий елемент
    int zeroCol = FindZeroColRecursive(a, rowCount, colCount, 0, 0);
    if (zeroCol != -1)
        cout << "First column with zero element: " << zeroCol << endl;
    else
        cout << "No zero elements in any column." << endl;

    // —ортуванн€ р€дк≥в за характеристикою (в пор€дку спаданн€)
    SortRowsRecursive(a, rowCount, colCount, 0);
    cout << "Matrix after sorting rows by characteristic (descending):" << endl;

    // ¬иведенн€ в≥дсортованоњ матриц≥
    PrintRows(a, rowCount, colCount, 0);

    // ¬идаленн€ динам≥чно вид≥леноњ пам'€т≥
    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// –екурсивне введенн€ елемент≥в матриц≥
void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo >= rowCount) return; // Ѕазовий випадок: дос€гнуто к≥нц€ р€дк≥в
    for (int j = 0; j < colCount; j++) {
        cout << "a[" << rowNo << "][" << j << "] = ";
        cin >> a[rowNo][j]; // ¬веденн€ елемент≥в дл€ р€дка
    }
    InputRows(a, rowCount, colCount, rowNo + 1); // ѕерех≥д до наступного р€дка
}

// –екурсивне виведенн€ елемент≥в матриц≥
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo >= rowCount) return; // Ѕазовий випадок: дос€гнуто к≥нц€ р€дк≥в
    for (int j = 0; j < colCount; j++) {
        cout << setw(4) << a[rowNo][j]; // ¬иведенн€ елемент≥в дл€ поточного р€дка
    }
    cout << endl;
    PrintRows(a, rowCount, colCount, rowNo + 1); // ѕерех≥д до наступного р€дка
}

// –екурсивний пошук першого стовпц€ з нульовим елементом
int FindZeroColRecursive(int** a, const int rowCount, const int colCount, int colNo, int rowNo) {
    if (colNo >= colCount) return -1; // якщо стовпц≥ зак≥нчились, повертаЇмо -1 (немаЇ нул≥в)
    if (rowNo >= rowCount) return FindZeroColRecursive(a, rowCount, colCount, colNo + 1, 0); // ѕерев≥рка наступного стовпц€
    if (a[rowNo][colNo] == 0) return colNo; // якщо знайдено нуль, повертаЇмо номер стовпц€
    return FindZeroColRecursive(a, rowCount, colCount, colNo, rowNo + 1); // ѕерев≥рка наступного р€дка
}

// –екурсивне обчисленн€ характеристики р€дка
int CalculateRowCharacteristicRecursive(int* row, const int colCount, int colNo) {
    if (colNo >= colCount) return 0; // Ѕазовий випадок: стовпц≥ зак≥нчились
    int sum = 0;
    // ƒодаЇмо до суми значенн€ елемент≥в, €к≥ Ї парними та в≥д'Їмними
    if (row[colNo] < 0 && row[colNo] % 2 == 0) {
        sum += row[colNo];
    }
    return sum + CalculateRowCharacteristicRecursive(row, colCount, colNo + 1); // –екурсивно додаЇмо характеристику
}

// ‘ункц≥€ дл€ обм≥ну р€дк≥в м≥сц€ми
void SwapRows(int** a, int row1, int row2) {
    int* temp = a[row1];
    a[row1] = a[row2];
    a[row2] = temp;
}

// –екурсивне сортуванн€ р€дк≥в матриц≥ за характеристикою (в пор€дку спаданн€)
void SortRowsRecursive(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo >= rowCount - 1) return; // Ѕазовий випадок: дос€гнуто останнього р€дка
    for (int i = rowNo + 1; i < rowCount; i++) {
        // якщо характеристика поточного р€дка менша, н≥ж у наступного, м≥н€Їмо њх м≥сц€ми
        if (CalculateRowCharacteristicRecursive(a[rowNo], colCount, 0) <
            CalculateRowCharacteristicRecursive(a[i], colCount, 0)) {
            SwapRows(a, rowNo, i);
        }
    }
    SortRowsRecursive(a, rowCount, colCount, rowNo + 1); // –екурсивно переходимо до наступного р€дка
}
