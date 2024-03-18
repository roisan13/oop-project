#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "random.hpp"

class Voievod;


class Spell{
private:
    std::string name;
    int baseDamage;
    int critChance;  // critchance/100

public:
    Spell(std::string name, int baseDamage, int critChance) : name(std::move(name)), baseDamage(baseDamage),
                                                                     critChance(critChance) {}


    virtual ~Spell() = default;

    [[nodiscard]] int evalDamage() const{
        if ( effolkronium::random_static::get(1, 100) > critChance)
            return baseDamage;
        else {
            std::cout << "Critical strike! \n";
            return 2 * baseDamage;
        }
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

    virtual ~Voievod() = default;


    Voievod& operator=(const Voievod&) = default;



    friend std::ostream &operator<<(std::ostream &os, const Voievod &voievod) {
        os << voievod.name << " strength: " << voievod.strength << " healthPoints: " << voievod.healthPoints << '\n';
        return os;
    };

    void printSpells(){
        for (unsigned int i = 0; i < spells.size(); ++i)
            std::cout << i + 1 << ". " << spells[i] << '\n';
    }

    [[nodiscard]] bool isAlive() const{
        return (healthPoints > 0);
    }

    void useSpell(unsigned int spellIndex, Voievod& enemy){
        if ( spellIndex < spells.size() )
            enemy.healthPoints -= spells[spellIndex].evalDamage();
        else std::cout << "It didn't work: Wrong spellIndex provided!\n";
    }
};

class Game{
private:
    Voievod voievod1, voievod2;


public:
    void play(){
        std::cout << "The game has started! \n";
        std::cout << "Voievod 1: " << voievod1 << "\n" << "Voievod 2: " <<  voievod2 << "\n";

        while(voievod1.isAlive() && voievod2.isAlive()){

            std::cout << "Voievod1, choose your spell:\n";
            voievod1.printSpells();
            int *spellIndex_ = new int;
            std::cin >> *spellIndex_;
            // aici ar trebui un if in care sa se citeasca frumos spellIndex, fara erori
            voievod1.useSpell(*spellIndex_-1, voievod2);
            std::cout << "It worked! " << voievod2;

            std::cout << "Voievod2, choose your spell:\n";
            voievod2.printSpells();
            std::cin >> *spellIndex_;
            // alt if frumos, posibil o functie
            voievod2.useSpell(*spellIndex_-1, voievod1);
            std::cout << "It worked! " << voievod1;

            delete spellIndex_;

        }

    };

    Game(const Voievod &voievod1, const Voievod &voievod2) : voievod1(voievod1), voievod2(voievod2) {}

    virtual ~Game() {
        std::cout << "\nGame over! \n";
    }
};



int main() {

    Spell basicAttack = Spell("Basic Attack", 5, 20);
    Spell powerfulAttack = Spell("Powerful Attack", 10, 10);
    Spell voievod1specificAttack = Spell("Battle of Calugareni Attack", 15, 40);
    Spell voievod2specificAttack = Spell("Night Attack at Targoviste", 15, 40);

    /// std::vector<Spell> basicSpells = {basicAttack, powerfulAttack};

    Voievod v1 = Voievod("Michael The Brave", 89, 30, {basicAttack, powerfulAttack, voievod1specificAttack});
    Voievod v2 = Voievod("Vlad The Impaler", 93, 30, {basicAttack, powerfulAttack, voievod2specificAttack});

    Game game = Game(v1, v2);

    game.play();

    return 0;
}
