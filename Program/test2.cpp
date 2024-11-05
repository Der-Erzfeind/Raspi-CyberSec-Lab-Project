#include <iostream>
#include <stdlib.h>
#include <vector>

class Menu{
    private: 
        const std::string name;
        const std::vector<Menu> submenues;
        
        std::vector<bool&> functionPointers;
        const int numOptions;
        int selectedOption;

    public:
        template <typename... Options, typename... FunctionPointers>
        Menu(const std::string& name, Options&&... options, FunctionPointers&&... functionPointers);

        std::string getName();

        std::vector<std::string> getOptions();
        
        int getNumOptions();

        int getSelectedOption();

        void setSelectedOption(int selectedOption);

        std::vector<bool&> getFunctionPointers();

        void setFunctionPointers(std::vector<bool&> functionPointers);

};

int main() {
    system("touch test.sh");
    system("echo test.sh");
}

