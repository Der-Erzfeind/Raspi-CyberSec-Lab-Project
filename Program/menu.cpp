#include "menu.h"


    template <typename... Options>
    Menu::Menu(const std::string& title, Options&&... options, Menu& previousMenu) : 
        title(title), 
        options{std::forward<Options>(options)...}, 
        numOptions{options.size()}, 
        selectedOption{0},
        previousMenu{previousMenu}
    {}


    std::string Menu::getTitle(){
        return this->title;
    }

    std::vector<std::string> Menu::getOptions(){
        return this->options;
    }

    int Menu::getNumOptions(){
        return this->numOptions; 
    }

    int Menu::getSelectedOption(){
        return this->selectedOption;
    }

    void Menu::setSelectedOption(int selectedOption){
        this->selectedOption = selectedOption;
    }

    void Menu::exit(){
        currentMenu = this->previousMenu;
    }