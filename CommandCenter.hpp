#ifndef COMMANDCENTER_HPP
#define COMMANDCENTER_HPP

#include <map>
#include <list>
#include <functional>
#include <string>
#include <iostream>

class Entity;

using Command = std::function<void(const std::list<std::string>&)>;

class CommandCenter {
private:
    std::map<std::string, Command> commands;
    std::list<std::string> history;

    std::map<std::string, std::list<
        std::pair<std::string, std::list<std::string>>
    >> macros;

    Entity* entity; // para capturar estado antes/despues

public:
    CommandCenter(Entity& e);

    void registerCommand(const std::string& name, Command cmd);
    void execute(const std::string& name, const std::list<std::string>& args);
    void removeCommand(const std::string& name);

    void registerMacro(
        const std::string& name,
        const std::list<std::pair<std::string, std::list<std::string>>>& steps
    );

    void executeMacro(const std::string& name);

    void showHistory() const;
};

#endif