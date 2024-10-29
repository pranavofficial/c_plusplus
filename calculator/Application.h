#ifndef APPLICATION_H
#define APPLICATION_H

#include <FL/Enumerations.H>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/textbox.h>
#include <bobcat_ui/window.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


namespace bobcat {

class Application: public Application_ {
    Window* window;
    TextBox* message;
    TextBox* answer;
    std::vector<Button*> keyboard;

    void handleClick(Widget* sender){
        std::string current = message->label();

        current = current + sender->label();

        message->label(current);
    }
    void backSpace(Widget* sender){
        std::string current = message->label();
        std::string deleted = current.erase(current.length() - 1, 1);
        message->label(deleted);
    }
    void clearCalc(Widget* sender){
        message->label("");
        answer->label("");
    }
    void switchSign(Widget* sender){
        std::string current = message->label();\

        if (current.find("-") != std::string::npos){
            size_t finder = current.find("-");
            std::string removeOG = current.erase(finder , 1);
            message->label(removeOG);
        }
        else{
            std::string switchedSign = "-" + current;
            message->label(switchedSign);
        }
    }
    void solve(Widget* sender){
        std::string current = message->label();
        std::string variable1 = message->label();
        current = current + sender->label();
        message->label(current);
        size_t add = current.find("+");
        size_t minus = current.find("-");
        size_t divide = current.find("/");
        size_t multiply = current.find("*");
        size_t modulo = current.find("%");
        if (current.find("+") != std::string::npos){
            std::string intTWO = current.substr(add + 1);
            std::string intONE = current.substr(0, add);
            float float1 = stof(intONE);
            float float2 = stof(intTWO);
            float THEanswer = float1 + float2;
            answer->label("Answer: " + roundFloat(THEanswer));
        }
        else if (current.find("-") != std::string::npos){
            std::string intTWO = current.substr(minus + 1);
            std::string intONE = current.substr(0, minus);
            float float1 = stof(intONE);
            float float2 = stof(intTWO);
            float THEanswer = float1 - float2;
            answer->label("Answer: " + roundFloat(THEanswer));
        }
        else if (current.find("/") != std::string::npos){
            std::string intTWO = current.substr(divide + 1);
            std::string intONE = current.substr(0, divide);
            float float1 = stof(intONE);
            float float2 = stof(intTWO);
            if (float2 != 0) { // Check for division by zero
                float THEanswer = float1 / float2;
                answer->label("Answer: " + roundFloat(THEanswer));
            } 
            else {
                answer->label("Undefined");
            }
        }
        else if (current.find("*") != std::string::npos){
            std::string intTWO = current.substr(multiply + 1);
            std::string intONE = current.substr(0, multiply);
            float float1 = stof(intONE);
            float float2 = stof(intTWO);
            float THEanswer = float1 * float2;
            answer->label("Answer: " + roundFloat(THEanswer));
        }
        else if (current.find("%") != std::string::npos){
            std::string intTWO = current.substr(modulo + 1);
            std::string intONE = current.substr(0, modulo);
            int int1 = stoi(intONE);
            int int2 = stoi(intTWO);
            int THEanswer = int1 % int2;
            std::string finalSolution = std::to_string(THEanswer);
            answer->label("Answer: " + finalSolution);
        }
        else{
            message->label("");
            answer->label(current);
        }
        
        
        
    }





    void setupRow(std::vector<std::string> keys, int y){
        int start = (window->w() - ((keys.size() * 30) - 5 )) / 2;
        for (int i = 0; i < keys.size(); i++){
            keyboard.push_back(new Button(start + (i*30), y, 25, 25, keys[i]));
        }
    }


    void setupKeyboard(int y){
        std::vector<std::string> row1 = {"1","2","3","4","5"};
        std::vector<std::string> row2 = {"6","7","8","9","0", "."};
        std::vector<std::string> row3 = {"+", "-", "/", "*", "%"};

        setupRow(row1, y);
        setupRow(row2, y + 30);
        setupRow(row3, y + 60);
        
        keyboard.push_back(new Button(130, y + 90, 50, 25, "Delete"));
        keyboard.push_back(new Button(187, y + 90, 25, 25, "+/-"));
        keyboard.push_back(new Button(220, y + 90, 50, 25, "Clear"));
        keyboard.push_back(new Button((window->w() - (100)) / 2, y + 120, 100, 25, " = "));

        
        for (int i = 0; i < keyboard.size(); i++){
            ON_CLICK(keyboard[i],  handleClick);
            ON_CLICK(keyboard[16], backSpace);
            ON_CLICK(keyboard[17], switchSign);
            ON_CLICK(keyboard[18], clearCalc);
            ON_CLICK(keyboard[19], solve);
        }
    }

public:
    Application() {
        // Build up interface
        theme();
        window = new Window(100, 100, 400, 400, "Calculator");

        message = new TextBox(10, 50, 380, 25, "");
        answer = new TextBox(10, 90, 380, 25, "");
        message->labelsize(25);
        message->align(FL_ALIGN_CENTER);
        answer->labelsize(25);
        answer->align(FL_ALIGN_CENTER);

        setupKeyboard(250);

        // Show the window
        window->show();
    }

    friend struct AppTest;
};

}
#endif