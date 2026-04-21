#include "Entity.hpp"
#include "CommandCenter.hpp"
#include <string>

void freeHeal(Entity& e, const std::list<std::string>& args) {
    if (args.size() != 1) {
        std::cout << "Error: heal necesita 1 argumento\n";
        return;
    }

    try {
        int val = std::stoi(args.front());
        e.heal(val);
    } catch (...) {
        std::cout << "Error: argumento invalido\n";
    }
}

class DamageFunctor {
private:
    Entity& entity;
    int counter;

public:
    DamageFunctor(Entity& e) : entity(e), counter(0) {}

    void operator()(const std::list<std::string>& args) {
        if (args.size() != 1) {
            std::cout << "Error: damage necesita 1 argumento\n";
            return;
        }

        try {
            int val = std::stoi(args.front());
            entity.damage(val);
            counter++;
            std::cout << "Damage usado " << counter << " veces\n";
        } catch (...) {
            std::cout << "Error: argumento invalido\n";
        }
    }
};

int main() {
    Entity entity;
    CommandCenter center(entity);

    center.registerCommand("heal", [&](const std::list<std::string>& args) {
        freeHeal(entity, args);
    });

    center.registerCommand("move", [&](const std::list<std::string>& args) {
        if (args.size() != 2) {
            std::cout << "Error: move necesita 2 argumentos\n";
            return;
        }

        try {
            auto it = args.begin();
            int x = std::stoi(*it++);
            int y = std::stoi(*it);
            entity.move(x, y);
        } catch (...) {
            std::cout << "Error: argumento invalido\n";
        }
    });

    DamageFunctor dmg(entity);
    center.registerCommand("damage", dmg);

    center.registerCommand("status", [&](const std::list<std::string>&) {
        entity.status();
    });

    center.registerCommand("reset", [&](const std::list<std::string>&) {
        entity.reset();
    });

    // validos
    center.execute("move", {"10", "5"});
    center.execute("heal", {"20"});
    center.execute("damage", {"15"});
    center.execute("status", {});

    // invalidos
    center.execute("move", {"10"});
    center.execute("fake", {});

    // macros
    center.registerMacro("combo", {
        {"heal", {"10"}},
        {"damage", {"5"}},
        {"status", {}}
    });

    center.registerMacro("fullheal", {
        {"heal", {"50"}},
        {"status", {}}
    });

    center.registerMacro("panic", {
        {"damage", {"30"}},
        {"move", {"-5", "-5"}},
        {"status", {}}
    });

    center.registerMacro("bad", {
        {"noExiste", {}}
    });

    center.executeMacro("combo");
    center.executeMacro("fullheal");
    center.executeMacro("panic");
    center.executeMacro("bad");

    center.showHistory();

    return 0;
}