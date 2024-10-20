#include "pch.h" // ���� ������������� Visual Studio, ��� ���� �������� ���������� �����������
#include "CppUnitTest.h"
#include "../Lab_07.3 rec.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
    TEST_CLASS(CalculateRowCharacteristicTests)
    {
    public:

        TEST_METHOD(TestCalculateRowCharacteristic)
        {
            // �������� �����
            int row1[] = { -2, -4, 3, 1 }; // ���������� ���������: -6 (sum of -2 and -4)
            int row2[] = { 2, 4, -6, 1 };  // ���������� ���������: -6 (sum of -6)
            int row3[] = { -1, 1, 3, -5 };  // ���������� ���������: 0 (no negative even numbers)
            int row4[] = { 0, -2, -8, 4 };  // ���������� ���������: -10 (sum of -2 and -8)

            Assert::AreEqual(-6, CalculateRowCharacteristicRecursive(row1, 4, 0));
            Assert::AreEqual(-6, CalculateRowCharacteristicRecursive(row2, 4, 0));
            Assert::AreEqual(0, CalculateRowCharacteristicRecursive(row3, 4, 0));
            Assert::AreEqual(-10, CalculateRowCharacteristicRecursive(row4, 4, 0));
        }
    };
}
