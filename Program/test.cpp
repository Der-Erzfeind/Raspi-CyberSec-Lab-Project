#include <iostream>
#include <filesystem>
#include <string>

std::string scriptPath(std::string script){
    std::string path = std::filesystem::absolute(__FILE__).parent_path().parent_path();
    std::string scriptpath = path + "/Skripte/" + script + ".sh";
    return scriptpath;
}
int main(){

std::cout << scriptPath("test") << std::endl;

return 0; 
}
