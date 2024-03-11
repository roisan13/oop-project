#include <iostream>
#include <utility>
#include <vector>
#include <string>

class Voievod;


class Spell{
private:
    std::string name;
    int baseDamage;
    int critChance;  // critchance/100

public:
    Spell(std::string name, int baseDamage, int critChance) : name(std::move(name)), baseDamage(baseDamage),
                                                                     critChance(critChance) {}


    virtual ~Spell() {
        std::cout << "Spell destr\n";
    }

    [[nodiscard]] int evalDamage() const{                 //TODO implement random library
        if (rand() % 101 > critChance)
            return baseDamage;
        else return 2 * baseDamage;
    }


    friend std::ostream &operator<<(std::ostream &os, const Spell &spell) {
        os << spell.name;

        // Default os
        // os << "name: " << spell.name << " baseDamage: " << spell.baseDamage << " critChance: " << spell.critChance << '\n';
        return os;
    }

};

/// class VoievodAttack : public Spell{};

class Voievod {
private:
    std::string name;
    int strength;
    int healthPoints;
    std::vector<Spell> spells;

public:
    Voievod(std::string name_, int strength_, int healthPoints_, const std::vector<Spell> &spells_) : name(std::move(name_)),
                                                                                                         strength(
                                                                                                                 strength_),
                                                                                                         healthPoints(
                                                                                                                 healthPoints_),
                                                                                                         spells(spells_) {}

    virtual ~Voievod() {
        std::cout << "Voievod destr\n";
    }


    Voievod& operator=(const Voievod&) = default;



    friend std::ostream &operator<<(std::ostream &os, const Voievod &voievod) {
        os << "name: " << voievod.name << " strength: " << voievod.strength << " healthPoints: "
           << voievod.healthPoints << '\n';
        return os;
    };

    void printSpells(){
        for (unsigned int i = 0; i < spells.size(); ++i)
            std::cout << i + 1 << ". " << spells[i] << '\n';
    }

    void useSpell(int spellIndex, Voievod& enemy){     //TODO implement spell use
        enemy.healthPoints -= spells[spellIndex].evalDamage();
    }
};

class Game{
private:
    Voievod voievod1, voievod2;


public:
    void play(){
        std::cout << "The game has started!\n";
        std::cout << voievod1 << "\n" << voievod2 << "\n";

    };

    Game(const Voievod &voievod1, const Voievod &voievod2) : voievod1(voievod1), voievod2(voievod2) {}

    virtual ~Game() {
        std::cout << "Game destr\n";
    }
};



int main() {

    Spell basicAttack = Spell("Basic Attack", 5, 20);
    Spell powerfulAttack = Spell("Powerful Attack", 10, 10);

    std::vector<Spell> basicSpells = {basicAttack, powerfulAttack};

    Voievod v1 = Voievod("Michael The Brave", 89, 30, basicSpells);
    Voievod v2 = Voievod("Vlad The Impaler", 93, 30, basicSpells);

    Game game = Game(v1, v2);

    game.play();

    v1.printSpells();
    v1.useSpell(1, v2);
    std::cout << v2;

    return 0;
}
