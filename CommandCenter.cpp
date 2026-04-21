#include "CommandCenter.hpp"
#include "Entity.hpp"

CommandCenter::CommandCenter(Entity& e) {
    entity = &e;
}

void CommandCenter::registerCommand(const std::string& name, Command cmd) {
    commands[name] = cmd;
}

void CommandCenter::execute(const std::string& name, const std::list<std::string>& args) {
    auto it = commands.find(name);

    if (it == commands.end()) {
        std::cout << "Comando no existe\n";
        return;
    }

    // estado antes
    int x1 = entity->getX();
    int y1 = entity->getY();
    int h1 = entity->getHealth();

    // ejecutar comando
    it->second(args);

    // estado despues
    int x2 = entity->getX();
    int y2 = entity->getY();
    int h2 = entity->getHealth();

    // guardar historial completo
    std::string record = name + ": (" +
        std::to_string(x1) + "," +
        std::to_string(y1) + "," +
        std::to_string(h1) + ") -> (" +
        std::to_string(x2) + "," +
        std::to_string(y2) + "," +
        std::to_string(h2) + ")";

    history.push_back(record);
}

void CommandCenter::removeCommand(const std::string& name) {
    auto it = commands.find(name);

    if (it != commands.end()) {
        commands.erase(it);
        std::cout << "Comando eliminado\n";
    } else {
        std::cout << "No existe\n";
    }
}

void CommandCenter::registerMacro(
    const std::string& name,
    const std::list<std::pair<std::string, std::list<std::string>>>& steps
) {
    macros[name] = steps;
}

void CommandCenter::executeMacro(const std::string& name) {
    auto it = macros.find(name);

    if (it == macros.end()) {
        std::cout << "Macro no existe\n";
        return;
    }

    for (auto stepIt = it->second.begin(); stepIt != it->second.end(); ++stepIt) {
        const std::string& cmdName = stepIt->first;
        const std::list<std::string>& args = stepIt->second;

        auto cmdIt = commands.find(cmdName);
        if (cmdIt == commands.end()) {
            std::cout << "Error en macro: comando no existe\n";
            return;
        }

        execute(cmdName, args);
    }
}

void CommandCenter::showHistory() const {
    for (auto it = history.begin(); it != history.end(); ++it) {
        std::cout << *it << std::endl;
    }
}