#include <iostream>
#include <cassert>
#include <cmath> // для функции fabs()

class ComplexNumber {
private:
    double real;
    double imaginary;

public:
    // Конструктор по умолчанию
    ComplexNumber() : real(0), imaginary(0) {}

    // Конструктор инициализации
    ComplexNumber(double r, double i) : real(r), imaginary(i) {}

    // Конструктор копирования
    ComplexNumber(const ComplexNumber& other) : real(other.real), imaginary(other.imaginary) {}

    // Методы доступа
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    void setReal(double r) { real = r; }
    void setImaginary(double i) { imaginary = i; }

    // Операции сложения
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imaginary + other.imaginary);
    }

    // Операция вычитания
    ComplexNumber operator-(const ComplexNumber& other) const {
        return ComplexNumber(real - other.real, imaginary - other.imaginary);
    }

    // Операция умножения
    // ac - bd + (ad + bc)i
    ComplexNumber operator*(const ComplexNumber& other) const {
        return ComplexNumber(real * other.real - imaginary * other.imaginary,
                             real * other.imaginary + imaginary * other.real);
    }

    // Операция деления
    // домножаем на сопряженное, получаем в знаменателе c^2 + d^2
    // в числителе получаем (a + bi)*(c - di)
    ComplexNumber operator/(const ComplexNumber& other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        return ComplexNumber((real * other.real + imaginary * other.imaginary) / denominator,
                             (imaginary * other.real - real * other.imaginary) / denominator);
    }


    // void print() const {
    //     if (imaginary >= 0)
    //         std::cout << real << " + " << imaginary << "i" << std::endl;
    //     else
    //         std::cout << real << " - " << fabs(imaginary) << "i" << std::endl;
    // }

    // Тестирование
    static void test() {
        ComplexNumber c1(3, 4);
        ComplexNumber c2(1, 2);

        // Тест конструктора по умолчанию
        ComplexNumber c3;
        assert(c3.getReal() == 0 && c3.getImaginary() == 0);

        // Тест конструктора инициализации
        assert(c1.getReal() == 3 && c1.getImaginary() == 4);

        // Тест конструктора копирования
        ComplexNumber c4 = c1;
        assert(c4.getReal() == c1.getReal() && c4.getImaginary() == c1.getImaginary());

        // Тест арифметических операций
        ComplexNumber sum = c1 + c2;
        assert(sum.getReal() == 4 && sum.getImaginary() == 6);

        ComplexNumber difference = c1 - c2;
        assert(difference.getReal() == 2 && difference.getImaginary() == 2);

        ComplexNumber product = c1 * c2;
        assert(product.getReal() == -5 && product.getImaginary() == 10);

        ComplexNumber quotient = c1 / c2;

        // Добавляем допуск для сравнения с плавающей точкой
        double epsilon = 1e-6;
        assert(fabs(quotient.getReal() - 2.2) < epsilon);
        assert(fabs(quotient.getImaginary() + 0.4) < epsilon); // Ожидаем -0.4

        // Тест геттеров и сеттеров
        ComplexNumber c5;
        c5.setReal(5.5);
        c5.setImaginary(-2.5);
        assert(c5.getReal() == 5.5);
        assert(c5.getImaginary() == -2.5);

        // Изменяем значения через сеттеры
        c5.setReal(10.0);
        c5.setImaginary(5.0);
        assert(c5.getReal() == 10.0);
        assert(c5.getImaginary() == 5.0);

        std::cout << "All tests passed for ComplexNumber!" << std::endl;
    }
};

class Quaternion : public ComplexNumber {
    
};

int main() {
    ComplexNumber::test();
    return 0;
    
}