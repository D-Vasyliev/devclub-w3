#include <iostream>
#include <cmath>

class NotEnoughTankCapacityException {};
class NotEnoughFuelException {};


class Location {
    private:
        int x;
        int y;

    public:
        Location(int x = 0, int y = 0) {
            this -> x = x;
            this -> y = y;
        }

        int getX() const {
            return this -> x;
        }

        int getY() const {
            return this -> y;
        }

        double distance(const Location& location) const {
            int new_x = location.x - this -> x;
            int new_y = location.y - this -> y;

            return hypot(new_x, new_y);
        }

        friend std::ostream& operator<<(std::ostream& out, const Location& location);
};

class Car {
    private:
        std::string model;
        double tankCapacity;
        double fuelAmount;
        double mileage;
        double fuelConsumption;
        Location location;

    public:
        Car(const std::string& model, double tankCapacity, double fuelConsumption) {
            this->model = model;
            this->tankCapacity = tankCapacity;
            this->fuelAmount = 0.0;
            this->mileage = 0.0;
            this->fuelConsumption = fuelConsumption;
            this->location = Location();
        }

        const std::string& getModel() const {
            return this->model;
        }

        double getTankCapacity() const {
            return this->tankCapacity;
        }

        double getFuelAmount() const {
            return this->fuelAmount;
        }

        double getMileage() const {
            return this->mileage;
        }

        const Location& getLocation() const {
            return this->location;
        }

        void refuel(double fuel) {
            if ( this->fuelAmount + fuel > this->tankCapacity ) {
                throw NotEnoughTankCapacityException();
            }
            this->fuelAmount += fuel;
        }

        void refuelUntilFull() {
            this->fuelAmount = this -> tankCapacity;
        }

        void move(const Location& newLocation) {
            double ToMove = this->location.distance(newLocation);
            double NeedFuel = ToMove * this->fuelConsumption;

            if (NeedFuel > this->fuelAmount) {
                throw NotEnoughFuelException();
            }

            this->fuelAmount -= NeedFuel;
            this->mileage += ToMove;
            this->location = newLocation;
        }

        friend std::ostream& operator<<(std::ostream& out, const Car& car);
};

std::ostream& operator<<(std::ostream& out, const Location& location) {
    out << '(' << location.x << ',' << location.y << ')';
    return out;
}

std::ostream& operator<<(std::ostream& out, const Car& car) {
    out << car.model << ": " << std::endl;
    out << "  - fuel: " << car.fuelAmount << "/" << car.tankCapacity << std::endl;
    out << "  - mileage: " << car.mileage << std::endl;
    out << "  - location: " << car.location << std::endl;
    return out;
}

int main() {
    Car toyota("Toyota", 60.0, 1.3);

    std::cout << toyota << std::endl;

// Toyota:
//   - fuel: 0/60
//   - mileage: 0
//   - location: (0, 0)

    toyota.refuel(30.0);
    std::cout << toyota << std::endl;

// Toyota:
//   - fuel: 30/60
//   - mileage: 0
//   - location: (0, 0)

    toyota.move(Location(10, 4));
    std::cout << toyota << std::endl;

// Toyota:
//   - fuel: 15.9986/60
//   - mileage: 10.7703
//   - location: (10, 4)

    toyota.move(Location());
    std::cout << toyota << std::endl;

// Toyota:
//   - fuel: 1.99714/60
//   - mileage: 21.5407
//   - location: (0, 0)

    try {
        toyota.move(Location(10, 8));
    } catch ( NotEnoughFuelException exc ) {
        std::cout << "Not enough fuel..." << std::endl;
    }

    try {
        toyota.refuel(100.0);
    } catch ( NotEnoughTankCapacityException exc ) {
        std::cout << "Not enough tank capacity..." << std::endl;
    }
    
    toyota.refuelUntilFull();
    std::cout << toyota << std::endl;

// Toyota:
//   - fuel: 60/60
//   - mileage: 21.5407
//   - location: (0, 0)

    return 0;
}