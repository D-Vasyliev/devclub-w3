#include <iostream>

class OutOfInk {};

class Pen {
private:
    int inkAmount;
    int inkCapacity;

    int stringLength(const char* string) const {
        int length = 0;
        while (string[length] != '\0') {
            length++;
        }
        return length;
    }

public:
    Pen(int capacity = 4096) {
        inkCapacity = capacity;
        inkAmount = inkCapacity;
    }

    ~Pen(){};

    int getInkAmount() const { return inkAmount; }

    int getInkCapacity() const { return inkCapacity; }

    int write(const char* message) {
        if (inkAmount <= 0) {
            throw OutOfInk();
        }

        int messageLength = stringLength(message);

        int charsWritten;
        if (messageLength <= inkAmount) {
            charsWritten = messageLength;
        } else {
            charsWritten = inkAmount;
        }

        inkAmount -= charsWritten;

        return charsWritten;
    }

    void refill() {
        inkAmount = inkCapacity;
    }
};

std::ostream& operator<<(std::ostream& out, const Pen& pen) {
    out << "Чорнила: " << pen.getInkAmount() << " / " << pen.getInkCapacity();
    return out;
}

int main() {
    try {
        Pen pen;
        int symbols = pen.write("Hello, Santa!");

        std::cout << symbols << std::endl; // Виведе: 13
        std::cout << pen << std::endl;      // Виведе: Чорнила: 4083 / 4096

        Pen lowInkPen(5);
        symbols = lowInkPen.write("Привіт, світ!");
        std::cout << symbols << std::endl;
        std::cout << lowInkPen << std::endl;

        symbols = lowInkPen.write("Додатковий текст");
    }
    catch (const OutOfInk& e) {
        std::cerr << "Чорнила закінчилися!" << std::endl;
    }

    return 0;
}
