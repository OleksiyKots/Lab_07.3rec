#include <iostream>
#include <iomanip>
using namespace std;

// ���������� ������� ��� ������ � ��������
void InputRows(int** a, const int rowCount, const int colCount, int rowNo); // �������� �������� �������
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo); // ��������� �������� �������
int FindZeroColRecursive(int** a, const int rowCount, const int colCount, int colNo, int rowNo); // ����� ������� ������� � �������� ���������
int CalculateRowCharacteristicRecursive(int* row, const int colCount, int colNo); // ���������� �������������� �����
void SortRowsRecursive(int** a, const int rowCount, const int colCount, int rowNo); // ���������� ����� �� ���������������

int main() {
    int rowCount, colCount;
    // �������� ������� ����� � ��������
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    // ��������� ����������� ������
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    // �������� �������� �������
    InputRows(a, rowCount, colCount, 0);

    // ��������� �������
    PrintRows(a, rowCount, colCount, 0);

    // ����� ������� �������, �� ������ �������� �������
    int zeroCol = FindZeroColRecursive(a, rowCount, colCount, 0, 0);
    if (zeroCol != -1)
        cout << "First column with zero element: " << zeroCol << endl;
    else
        cout << "No zero elements in any column." << endl;

    // ���������� ����� �� ��������������� (� ������� ��������)
    SortRowsRecursive(a, rowCount, colCount, 0);
    cout << "Matrix after sorting rows by characteristic (descending):" << endl;

    // ��������� ����������� �������
    PrintRows(a, rowCount, colCount, 0);

    // ��������� �������� ������� ���'��
    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// ���������� �������� �������� �������
void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo >= rowCount) return; // ������� �������: ��������� ���� �����
    for (int j = 0; j < colCount; j++) {
        cout << "a[" << rowNo << "][" << j << "] = ";
        cin >> a[rowNo][j]; // �������� �������� ��� �����
    }
    InputRows(a, rowCount, colCount, rowNo + 1); // ������� �� ���������� �����
}

// ���������� ��������� �������� �������
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo >= rowCount) return; // ������� �������: ��������� ���� �����
    for (int j = 0; j < colCount; j++) {
        cout << setw(4) << a[rowNo][j]; // ��������� �������� ��� ��������� �����
    }
    cout << endl;
    PrintRows(a, rowCount, colCount, rowNo + 1); // ������� �� ���������� �����
}

// ����������� ����� ������� ������� � �������� ���������
int FindZeroColRecursive(int** a, const int rowCount, const int colCount, int colNo, int rowNo) {
    if (colNo >= colCount) return -1; // ���� ������� ����������, ��������� -1 (���� ����)
    if (rowNo >= rowCount) return FindZeroColRecursive(a, rowCount, colCount, colNo + 1, 0); // �������� ���������� �������
    if (a[rowNo][colNo] == 0) return colNo; // ���� �������� ����, ��������� ����� �������
    return FindZeroColRecursive(a, rowCount, colCount, colNo, rowNo + 1); // �������� ���������� �����
}

// ���������� ���������� �������������� �����
int CalculateRowCharacteristicRecursive(int* row, const int colCount, int colNo) {
    if (colNo >= colCount) return 0; // ������� �������: ������� ����������
    int sum = 0;
    // ������ �� ���� �������� ��������, �� � ������� �� ��'������
    if (row[colNo] < 0 && row[colNo] % 2 == 0) {
        sum += row[colNo];
    }
    return sum + CalculateRowCharacteristicRecursive(row, colCount, colNo + 1); // ���������� ������ ��������������
}

// ������� ��� ����� ����� ������
void SwapRows(int** a, int row1, int row2) {
    int* temp = a[row1];
    a[row1] = a[row2];
    a[row2] = temp;
}

// ���������� ���������� ����� ������� �� ��������������� (� ������� ��������)
void SortRowsRecursive(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo >= rowCount - 1) return; // ������� �������: ��������� ���������� �����
    for (int i = rowNo + 1; i < rowCount; i++) {
        // ���� �������������� ��������� ����� �����, �� � ����������, ������ �� ������
        if (CalculateRowCharacteristicRecursive(a[rowNo], colCount, 0) <
            CalculateRowCharacteristicRecursive(a[i], colCount, 0)) {
            SwapRows(a, rowNo, i);
        }
    }
    SortRowsRecursive(a, rowCount, colCount, rowNo + 1); // ���������� ���������� �� ���������� �����
}
