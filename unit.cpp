// Юніт
// Юніт має назву, колькість поінтів здоров'я та показник атаки
// Юніт може атакувати ворога
// Юніт якого атакують, завжди контратакує на половину сили
// Мертвих юнітів атакувати неможна
// Показник здоров'я юніта не може бути менший за 0 ;)

#include <iostream>

class UnitIsDeadException {};

class Unit {
    private:
        std::string title;
        int hp;
        int maxHP;
        int damage;

    public:
        Unit(const std::string& title, int maxHP, int damage) {
            this->title = title;
            this->maxHP = maxHP;
            this->damage = damage;
            this->hp = maxHP;
        }
        
        const std::string& getTitle() const {
             return this->title;
         }
        int getHP () const {
            return this->hp;
        }

        int getMaxHp () const {
            return this->maxHP;
        }

        int getDamage () const {
            return this->damage;
        }

        void setTitle(const std::string& newTitle) {
            this->title = newTitle;
        }

        void setHP (int newHP) {
            if ( newHP < 0 ) {
                this->hp = 0;
            } else if ( newHP > this->maxHP ) {
                this->hp = this-> maxHP;
            } else {
                this->hp = newHP;
            }
        }

        void setMaxHp (int newMaxHP) {
            if ( newMaxHP <= 0 ) {
                std::cout << "Max HP must be bigger than 0" << std::endl;
                return;
            }
            this->maxHP = newMaxHP;

            if ( this->hp > this->maxHP ) {
                this->hp = this->maxHP;
            }
        }

        void setDamage ( int newDamage) {
            if ( newDamage < 0 ) {
                std::cout << "Damage can't be negative!" << std::endl;
                return;
            }
            this->damage = newDamage;
        }

        void receiveDamage (int damage) {
            this->hp -= damage;

            if ( this->hp < 0 ) {
                this->hp = 0;
            }
        }

        void attack(Unit& enemy) {
            if ( enemy.hp <= 0 ) {
                throw UnitIsDeadException();
            }

            enemy.receiveDamage(this->damage);

            if ( enemy.hp > 0 ) {
                enemy.counterAttack(*this);

            }
        }

        void counterAttack(Unit& enemy) {
            enemy.receiveDamage(this->damage / 2);
        }
};

std::ostream& operator<<(std::ostream& out, const Unit& unit) {
    return out << unit.getTitle() << ":: hp(" << unit.getHP() << "/" << unit.getMaxHp() << "), dmg(" << unit.getDamage() << ")";
}

int main() {
    Unit knight("Knight", 100, 20);
    Unit barbarian("Barbarian", 80, 30);

    std::cout << knight << std::endl; 
    std::cout << barbarian << std::endl; 

    try {
        knight.attack(barbarian);
        std::cout << knight << std::endl; 
        std::cout << barbarian << std::endl; 
    } catch (UnitIsDeadException& exc) {
        std::cout << "Can't attack because unit is dead" << std::endl;
    }

        try {
        knight.attack(barbarian);
        std::cout << knight << std::endl; 
        std::cout << barbarian << std::endl; 
    } catch (UnitIsDeadException& exc) {
        std::cout << "Can't attack because unit is dead" << std::endl;
    }


    try {
        knight.attack(barbarian);
        std::cout << knight << std::endl; 
        std::cout << barbarian << std::endl; 
    } catch (UnitIsDeadException& exc) {
        std::cout << "Can't attack because unit is dead" << std::endl;
    }


    try {
        knight.attack(barbarian);
        std::cout << knight << std::endl; 
        std::cout << barbarian << std::endl;
    } catch (UnitIsDeadException& exc) {
        std::cout << "Can't attack because unit is dead" << std::endl;
    }


    try {
        knight.attack(barbarian);
        std::cout << knight << std::endl; 
        std::cout << barbarian << std::endl; 
    } catch (UnitIsDeadException& exc) {
        std::cout << "Can't attack because unit is dead" << std::endl;
    }


    try {
        knight.attack(barbarian);
        std::cout << knight << std::endl; 
        std::cout << barbarian << std::endl; 
    } catch (UnitIsDeadException& exc) {
        std::cout << "Can't attack because unit is dead" << std::endl;
    }

    knight.setDamage(-10);
    knight.setMaxHp(0);
    knight.setMaxHp(-10);


    return 0;
}