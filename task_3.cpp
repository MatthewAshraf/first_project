#include <iostream>
#include <string>
#include <regex>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Constructor
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
    }

    // Method to add two fractions
    Fraction add(const Fraction& other) const {
        int newNumerator = numerator * other.denominator + denominator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // Method to subtract two fractions
    Fraction subtract(const Fraction& other) const {
        int newNumerator = numerator * other.denominator - denominator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // Method to multiply two fractions
    Fraction multiply(const Fraction& other) const {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    // Method to divide two fractions
    Fraction divide(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero");
        }
        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;
        return Fraction(newNumerator, newDenominator);
    }

    // Method to simplify the fraction
    void simplify() {
        int gcd = greatestCommonDivisor(std::abs(numerator), std::abs(denominator));
        numerator /= gcd;
        denominator /= gcd;
    }

    // Method to get the greatest common divisor
    int greatestCommonDivisor(int a, int b) const {
        return b == 0 ? a : greatestCommonDivisor(b, a % b);
    }

    // Method to convert the fraction to string
    std::string toString() const {
        if (denominator == 1) {
            return std::to_string(numerator);
        }
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
};


int main(){
    string input;
    bool valid_input = false;
    int num1;
    int den1;
    char op;
    int num2;
    int den2;

    do{
        //ask the user for the input
        cout << "Enter a string with a fraction, operation, and fraction: ";
        getline(cin, input);

        // the expression to match the pattern
        regex pattern(R"((-?\d+)(?:/(\d+))?\s*([-+/*])\s(-?\d+)(?:/(\d+))?)");

        smatch matches;
        if (regex_match(input, matches, pattern)) {
            num1 = stoi(matches[1]);
            den1 = matches[2].matched ? stoi(matches[2]) : 1;
            op = matches[3].str()[0];
            num2 = stoi(matches[4]);
            den2 = matches[5].matched ? stoi(matches[5]) : 1;
            valid_input = true;

            //do the calculation
            Fraction fraction1(num1, den1);
            Fraction fraction2(num2, den2);
            Fraction result;
            switch (op) {
                case '+':
                    result = fraction1.add(fraction2);
                    break;
                case '-':
                    result = fraction1.subtract(fraction2);
                    break;
                case '*':
                    result = fraction1.multiply(fraction2);
                    break;
                case '/':
                    result = fraction1.divide(fraction2);
                    break;
            }

            result.simplify();
            std::cout << "Result: " << result.toString() << std::endl;

        } 
        else {
            cout << "Invalid input format, please try again." << '\n';
            valid_input = false;
        }
    } while (!valid_input);
  
  return 0;
}