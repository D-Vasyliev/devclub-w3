#include <iostream>

class OutOfSpace {};

class Paper {
private:
    static const int maxSymbols = 4096;
    int symbols;
    char content[maxSymbols + 1];

public:
    Paper() {
        symbols = 0;
        content[0] = '\0';
    }

    int getMaxSymbols() const { return maxSymbols; }
    int getSymbols() const { return symbols; }

    int addContent(const char *message) {
        int messageLength = 0;

        for (int i = 0; message[i] != '\0'; i++) {
            messageLength++;
        }

        int spaceAvailable = maxSymbols - symbols;
        if (spaceAvailable <= 0) {
            throw OutOfSpace();
        }

        int toAdd;
        if (messageLength < spaceAvailable) {
            toAdd = messageLength;
        } else {
            toAdd = spaceAvailable;
        }

        for (int i = 0; i < toAdd; i++) {
            content[symbols + i] = message[i];
        }
        symbols += toAdd;
        content[symbols] = '\0';

    std::cout << "Message Length: " << messageLength << ", Space Available: " << spaceAvailable << ", To Add: " << toAdd << std::endl;

        return toAdd;

    }

    void show() const {
        std::cout << content;
    }

    friend std::ostream& operator<<(std::ostream& out, const Paper& paper);

};

    std::ostream& operator<<(std::ostream& out, const Paper& paper) {
        out << paper.content;
        return out;
    }

int main() {
    Paper paper;
    try {
        int symbols = paper.addContent("Hello, Santa!");
        std::cout << "Added " << symbols << " characters. Current symbols: " << paper.getSymbols() << std::endl;
        std::cout << paper << std::endl;
        symbols = paper.addContent(" Putin Huilooooo!!!!!!");
        std::cout << "Added " << symbols << " characters. Current symbols: " << paper.getSymbols() << std::endl;
        std::cout << paper << std::endl;
        symbols = paper.addContent(" This is a test of the paper.");
        std::cout << "Added " << symbols << " characters. Current symbols: " << paper.getSymbols() << std::endl;
        std::cout << paper << std::endl;
        } catch (OutOfSpace&) {
            std::cout << "Error: Not enough space to add more content!" << std::endl;
        }

    return 0;
}