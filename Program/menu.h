#ifndef	_MENU_H
#define	_MENU_H	1

#include <vector>
#include <iostream>
#include <stdbool.h>

        class Menu{
            private:
                const std::string title;
                const std::vector<std::string> options;
                const int numOptions;
                int selectedOption;
                Menu& previousMenu;

            public:
                template <typename... Options>
                Menu(const std::string& title, Options&&... options, Menu& previousMenu);

                std::string getTitle();

                std::vector<std::string> getOptions();
                
                int getNumOptions();

                int getSelectedOption();

                void setSelectedOption(int selectedOption);

                virtual void exit();

        };


        class mainMenu : Menu{
            public: 
                void exit() override;
                void navigate(Menu&);
        };


#endif