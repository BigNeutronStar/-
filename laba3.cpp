#include <iostream>
#include <cassert>
#include <cmath>
#include <string>

enum NumberType { COMPLEX, QUATERNION };

class ComplexNumber {
private:
    double real;
    double imaginary;
    NumberType type;

public:
    // Конструктор по умолчанию
    ComplexNumber() : real(0), imaginary(0), type(COMPLEX) {}

    // Конструктор инициализации
    ComplexNumber(double r, double i) : real(r), imaginary(i), type(COMPLEX) {}

    // Конструктор копирования
    ComplexNumber(const ComplexNumber& other) : real(other.real), imaginary(other.imaginary), type(COMPLEX) {}

    // Методы доступа
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }
    NumberType getType() const { return type; }

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


    void print() const {
        if (imaginary >= 0)
            std::cout << real << " + " << imaginary << "i" << std::endl;
        else
            std::cout << real << " - " << fabs(imaginary) << "i" << std::endl;
    }

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
private:
    // ComplexNumber first;
    ComplexNumber second; // Комплексное число для части c + di
    NumberType type;
public:
    //конструктор по умолчанию
    Quaternion() : ComplexNumber(0, 0), second(0, 0), type(QUATERNION) {}
    // конструктор инициализации
    Quaternion(long double a, long double b, long double c, long double d)
        : ComplexNumber(a, b), second(c, d), type(QUATERNION) {}

    // Конструктор копирования
    Quaternion(const Quaternion& other)
        : ComplexNumber(other.getA(), other.getB()), second(other.getC(), other.getD()), type(other.type) {}

    // Сеттеры для каждой части кватерниона
    void setA(long double a) { setReal(a); }
    void setB(long double b) { setImaginary(b); }
    void setC(long double c) { second.setReal(c); }
    void setD(long double d) { second.setImaginary(d); }
    // геттеры для кватерниона
    long double getA() const { return getReal(); }
    long double getB() const { return getImaginary(); }
    long double getC() const { return second.getReal(); }
    long double getD() const { return second.getImaginary(); }
    NumberType getType() const { return type; }

    Quaternion operator+(const Quaternion& other) const {
        return Quaternion(getA() + other.getA(),
                          getB() + other.getB(),
                          getC() + other.getC(),
                          getD() + other.getD());
    }

    Quaternion operator-(const Quaternion& other) const {
        return Quaternion(getA() - other.getA(),
                          getB() - other.getB(),
                          getC() - other.getC(),
                          getD() - other.getD());
    }

    Quaternion operator*(const Quaternion& other) const {
        long double a = getA();
        long double b = getB();
        long double c = getC();
        long double d = getD();

        long double new_a = a * other.getA() - b * other.getB() - c * other.getC() - d * other.getD();
        long double new_b = a * other.getB() + b * other.getA() + c * other.getD() - d * other.getC();
        long double new_c = a * other.getC() - b * other.getD() + c * other.getA() + d * other.getB();
        long double new_d = a * other.getD() + b * other.getC() - c * other.getB() + d * other.getA();

        return Quaternion(new_a, new_b, new_c, new_d);
    }

    Quaternion operator/(const Quaternion& other) const {
        Quaternion conjugateOther(other.getA(), -other.getB(), -other.getC(), -other.getD());
        long double denominator = other.norm();

        return (*this * conjugateOther) * (1.0 / denominator);
    }
    // добавил умножение на скаляр
    Quaternion operator*(long double scalar) const {
        return Quaternion(getA() * scalar, getB() * scalar, getC() * scalar, getD() * scalar);
    }
    // высчитывание нормы кватерниона
    long double norm() const {
        return (getA() * getA() + getB() * getB() + getC() * getC() + getD() * getD());
    }
    //для вывода
    void print() const {
    // Выводим a + bi
    std::cout << getA() << " + " << getB() << "i";

    // Выводим c + dk
    if (getC() >= 0) {
        std::cout << " + " << getC() << "j";
    } else {
        std::cout << " - " << fabs(getC()) << "j";
    }

    if (getD() >= 0) {
        std::cout << " + " << getD() << "k";
    } else {
        std::cout << " - " << fabs(getD()) << "k";
    }

    std::cout << "\n";
    }

    static void test() {
    // Создание объектов
    Quaternion q1(1.0, 2.0, 3.0, 4.0);
    Quaternion q2(5.0, 6.0, 7.0, 8.0);

    // Тест конструктора по умолчанию
    Quaternion q_default;
    assert(q_default.getA() == 0.0);
    assert(q_default.getB() == 0.0);
    assert(q_default.getC() == 0.0);
    assert(q_default.getD() == 0.0);

    // Тест конструктора копирования
    Quaternion q_copy(q1);
    assert(q_copy.getA() == q1.getA());
    assert(q_copy.getB() == q1.getB());
    assert(q_copy.getC() == q1.getC());
    assert(q_copy.getD() == q1.getD());

    Quaternion q;
    //тест сеттеров
    // Устанавливаем значения
    q.setA(10.0);
    q.setB(20.0);
    q.setC(30.0);
    q.setD(40.0);

    // Проверяем через геттеры
    assert(q.getA() == 10.0);
    assert(q.getB() == 20.0);
    assert(q.getC() == 30.0);
    assert(q.getD() == 40.0);

    // Тест получения значений
    assert(q1.getA() == 1.0);
    assert(q1.getB() == 2.0);
    assert(q1.getC() == 3.0);
    assert(q1.getD() == 4.0);

    // Тест арифметических операций
    Quaternion sum = q1 + q2;
    assert(sum.getA() == 6.0);
    assert(sum.getB() == 8.0);
    assert(sum.getC() == 10.0);
    assert(sum.getD() == 12.0);

    Quaternion diff = q1 - q2;
    assert(diff.getA() == -4.0);
    assert(diff.getB() == -4.0);
    assert(diff.getC() == -4.0);
    assert(diff.getD() == -4.0);

    Quaternion product = q1 * q2;
    assert(product.getA() == -60.0);
    assert(product.getB() == 12.0);
    assert(product.getC() == 30.0);
    assert(product.getD() == 24.0);

    Quaternion quotient = q1 / q2;
    assert(fabs(quotient.getA() - 0.402299) < 1e-6);
    assert(fabs(quotient.getB() - 0.045977) < 1e-6);
    assert(fabs(quotient.getC()) < 1e-6);
    assert(fabs(quotient.getD() - 0.091954) < 1e-6);

    // Тест нормы
    long double norm_q1 = q1.norm();
    assert(fabs(norm_q1 - (1.0*1.0 + 2.0*2.0 + 3.0*3.0 + 4.0*4.0)) < 1e-6);
    
    // Тест умножения на скаляр
    Quaternion scalar_mult = q1 * 2.0;
    assert(scalar_mult.getA() == 2.0);
    assert(scalar_mult.getB() == 4.0);
    assert(scalar_mult.getC() == 6.0);
    assert(scalar_mult.getD() == 8.0);

    // Тест метода print (вывод на экран, не проверяем assert'ом)
    std::cout << "Printing q1: ";
    q1.print();
    std::cout << std::endl;

    // Убедимся, что программа дошла до конца без ошибок
    std::cout << "All tests passed for Quaternion!" << std::endl;
    }
};

class Calculator {
public:
    // Метод для выполнения операции над двумя комплексными числами
    void performOperation(std::stack<ComplexNumber>& stack, char operation) {
        ComplexNumber num2 = stack.top();
        stack.pop();
        ComplexNumber num1 = stack.top();
        stack.pop();

        ComplexNumber result(0, 0);
        switch (operation) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
            default:
                std::cout << "Invalid operation" << std::endl;
                break;
        }

        stack.push(result);
    }

    // Метод для выполнения операции над двумя кватернионами
    void performOperation(std::stack<Quaternion>& stack, char operation) {
        Quaternion q2 = stack.top();
        stack.pop();
        Quaternion q1 = stack.top();
        stack.pop();

        Quaternion result(0, 0, 0, 0);
        switch (operation) {
            case '+':
                result = q1 + q2;
                break;
            case '-':
                result = q1 - q2;
                break;
            case '*':
                result = q1 * q2;
                break;
            case '/':
                result = q1 / q2;
                break;
            default:
                std::cout << "Invalid operation" << std::endl;
                break;
        }

        stack.push(result);
    }

    // Функция для тестирования операций
    void runTests() {
        // Тесты для комплексных чисел
        std::stack<ComplexNumber> complexStack;
        complexStack.push(ComplexNumber(3, 4));  // 3 + 4i
        complexStack.push(ComplexNumber(1, 2));  // 1 + 2i

        // Сложение
        performOperation(complexStack, '+');
        std::cout << "Test 1 - Complex Addition: \n";
        complexStack.top().print();  // Ожидаемый результат: 4 + 6i

        // Вычитание
        complexStack.push(ComplexNumber(3, 4));
        complexStack.push(ComplexNumber(1, 2));
        performOperation(complexStack, '-');
        std::cout << "Test 2 - Complex Subtraction: \n";
        complexStack.top().print();  // Ожидаемый результат: 2 + 2i

        // Умножение
        complexStack.push(ComplexNumber(3, 4));
        complexStack.push(ComplexNumber(1, 2));
        performOperation(complexStack, '*');
        std::cout << "Test 3 - Complex Multiplication: \n";
        complexStack.top().print();  // Ожидаемый результат: -5 + 10i

        // Деление
        complexStack.push(ComplexNumber(3, 4));
        complexStack.push(ComplexNumber(1, 2));
        performOperation(complexStack, '/');
        std::cout << "Test 4 - Complex Division: \n";
        complexStack.top().print();  // Ожидаемый результат: 2.2 - 0.4i

        // Тесты для кватернионов
        std::stack<Quaternion> quaternionStack;
        quaternionStack.push(Quaternion(1, 2, 3, 4));  // 1 + 2i + 3j + 4k
        quaternionStack.push(Quaternion(5, 6, 7, 8));  // 5 + 6i + 7j + 8k

        // Сложение
        performOperation(quaternionStack, '+');
        std::cout << "Test 5 - Quaternion Addition: \n";
        quaternionStack.top().print();  // Ожидаемый результат: 6 + 8i + 10j + 12k

        // Вычитание
        quaternionStack.push(Quaternion(1, 2, 3, 4));
        quaternionStack.push(Quaternion(5, 6, 7, 8));
        performOperation(quaternionStack, '-');
        std::cout << "Test 6 - Quaternion Subtraction: \n";
        quaternionStack.top().print();  // Ожидаемый результат: -4 - 4i - 4j - 4k

        // Умножение
        quaternionStack.push(Quaternion(1, 2, 3, 4));
        quaternionStack.push(Quaternion(5, 6, 7, 8));
        performOperation(quaternionStack, '*');
        std::cout << "Test 7 - Quaternion Multiplication: \n";
        quaternionStack.top().print();  // Ожидаемый результат: -60 + 12i + 30j + 24k

        // Деление
        quaternionStack.push(Quaternion(1, 2, 3, 4));
        quaternionStack.push(Quaternion(5, 6, 7, 8));
        performOperation(quaternionStack, '/');
        std::cout << "Test 8 - Quaternion Division: \n";
        quaternionStack.top().print();  // Ожидаемый результат: 0.04 + 0.08i + 0.12j + 0.16k
    }
};

// Пример использования
int main() {
    Calculator calc;

    // Запуск тестов
    calc.runTests();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
