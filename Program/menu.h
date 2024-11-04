#ifndef	_MENU_H
#define	_MENU_H	1

#include <vector>
#include <iostream>

        class Menu{
            private:
                std::string name;
                std::vector<std::string> options;
                const int numOptions;
                int selectedOption;

            public:
                template <typename... Args>
                Menu(const std::string& name, Args&&... args)
                    : name(name), options{std::forward<Args>(args)...}, numOptions{options.size()}, selectedOption{0} // Initialize items with variadic arguments
                {
                }
               /*  Menu(std::string name, args... options): name{name}, options{options...}, numOptions{options.size()}, selectedOption{0}
                {
                    // this->numOptions = options.size();
                } */

                std::string getName(){
                    return this->name;
                }

                std::vector<std::string> getOptions(){
                    return this->options;
                }
                
                int getNumOptions(){
                    return this->numOptions; 
                }

                int getSelectedOption(){
                    return this->selectedOption;
                }

                void setSelectedOption(int selectedOption){
                    this->selectedOption = selectedOption;
                }
        };


#endif