#ifndef MENUOPTION_H
#define MENUOPTION_H

#include <string>
#include <functional>

class MenuOption {
public:
    MenuOption(const std::string& name, std::function<void()> action = nullptr)
        : name(name), action(action) {}

    void execute() const {
        if (action) {
            action();
        }
    }

    std::string getName() const {
        return name;
    }

private:
    std::string name;
    std::function<void()> action;
};

#endif // MENUOPTION_H
