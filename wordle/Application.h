#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/bobcat_ui.h>
#include <FL/Enumerations.H>
#include <bobcat_ui/window.h>
#include <bobcat_ui/list_box.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/input.h>
#include <bobcat_ui/textbox.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Light_Button.H>
#include <cmath>
#include <FL/fl_draw.H>
#include <cctype>
#include <functional>

#include "hexagon_button.h"

using namespace bobcat;
using namespace std;

class Application: public Application_ {
    bobcat::Window* mainMenu;
    bobcat::Window* instructions;
    bobcat::Window* gamePlay;
    bobcat::Window* stats;
    bobcat::Window* endGameScreen;
    Button* playGame;
    Button* delBut;
    Button* play;
    Button* viewInstructions;
    Button* viewStats;
    Button* returnMainfromInstruct;
    Button* returnMainfromStats;
    Button* returnMainfromEnd;
    Button* clearStats;
    Button* enterBut;
    TextBox* message;
    TextBox* try1;
    TextBox* try2;
    TextBox* try3;
    TextBox* try4;
    TextBox* try5;
    TextBox* try6;
    std::vector<Button*> keyboard;
    std::vector<TextBox*> guessKeyboard;
    TextBox* mainTitle;
    TextBox* WinStreak;
    TextBox* og1;
    TextBox* og2;
    TextBox* og3;
    TextBox* og4;
    TextBox* og5;
    TextBox* w1g1;
    TextBox* w1g2;
    TextBox* w1g3;
    TextBox* w1g4;
    TextBox* w1g5;
    TextBox* w2g1;
    TextBox* w2g2;
    TextBox* w2g3;
    TextBox* w2g4;
    TextBox* w2g5;
    TextBox* w3g1;
    TextBox* w3g2;
    TextBox* w3g3;
    TextBox* w3g4;
    TextBox* w3g5;
    TextBox* w4g1;
    TextBox* w4g2;
    TextBox* w4g3;
    TextBox* w4g4;
    TextBox* w4g5;
    TextBox* w5g1;
    TextBox* w5g2;
    TextBox* w5g3;
    TextBox* w5g4;
    TextBox* w5g5;
    TextBox* w6g1;
    TextBox* w6g2;
    TextBox* w6g3;
    TextBox* w6g4;
    TextBox* w6g5;
    TextBox* instruct1;
    TextBox* instruct2;
    TextBox* instruct3;
    TextBox* instruct5;
    TextBox* instruct4;
    TextBox* instruct6;
    TextBox* instruct7;
    TextBox* instruct8;
    TextBox* instruct9;
    TextBox* instruct0;
    TextBox* gameResult;
    TextBox* gameResult1;
    ListBox* Statistics;
    int attemptCount = 0;
    int winCond = 1;
    int messageStart = 25;
    std::string randWord = "";
    int winStreak = 0;

    void closeEnd(Widget* sender){
        endGameScreen->hide();
    }
    bool string_in_file(const std::string& filename, const std::string& search_string) {
    std::ifstream file(filename);  // Open the file
    std::string line;
    while (std::getline(file, line)) {  // Read the file line by line
        if (line.find(search_string) != std::string::npos) {  // Check if search_string is found in the line
            return true;  // String found
        }
    }

    return false;  // String not found
}
    
    void handleClick(Widget* sender){
        std::string lengthCheck = message->label();
       if (lengthCheck.length() < 5){
            std::string current = message->label();

            current = current + sender->label();

            message->label(current);
        }
    }
    void backSpace(Widget* sender){
        std::string lengthCheck = message->label();
        if (lengthCheck.length() > 0){
            std::string current = message->label();
            std::string deleted = current.erase(current.length() - 1, 1);
            message->label(deleted);
        }
    }
    void setupRow(std::vector<std::string> keys, int y){
        int start = (gamePlay->w() - ((keys.size() * 30) - 5 )) / 2;
        for (int i = 0; i < keys.size(); i++){
            keyboard.push_back(new Button(start + (i*30), y, 25, 25, keys[i]));
        }
    }
    void closeInstruct(Widget* sender){
        instructions->hide();
    }
    void closeStats(Widget* sender){
        stats->hide();
    }
    void clearStatistics(Widget* sender){
        std::ofstream file("stats.txt", std::ofstream::trunc);
        Statistics->clear();
        winStreak = 0;
        WinStreak->redraw();
    }
    void closeGame(Widget* sender){
        gamePlay->hide();
    }
    void populateListboxFromFile(std::string filename, ListBox*Statistics){
        Statistics->clear();
        std::fstream file("/home/me/workspace/assignments/programming-project/exercise-1/stats.txt");

        if(file.is_open()){
            std::string line;
            while(getline(file,line)){
                Statistics->add(line);
            }
            file.close();
        }
    }
    void numAttempts(){
        attemptCount++;
    }
    void statsTofile(std::string filename, int winCond){
        std::fstream file("/home/me/workspace/assignments/programming-project/exercise-1/stats.txt", std::ios::app);
        numAttempts();
        std::string newAttemptNum = std::to_string(attemptCount);
        std::string WINS = std::to_string(winCond);
        std::string line = "";
        if (winCond == 1){
            line = "Trial " + newAttemptNum + ": " + "First Try!";
        }
        if (winCond > 1 && winCond < 7){
            line = "Trial " + newAttemptNum + ": " + WINS + " Attempts.";
        }
        if (winCond >= 7){
            line = "Trial " + newAttemptNum + ": " + "You lost.";
        }
        
        file << line << std::endl;
        file.close();

        winCond = 1;
    }
    void endGame(std::string endGameTitle, std::string randWord, int winCond){
        gamePlay->hide();
        endGameScreen = new bobcat::Window(100, 100, 400, 400, endGameTitle);
        gameResult = new TextBox(50,25,300,50, endGameTitle);
        std::string stringWinCond = std::to_string(winCond);
        if (winCond == 1){
            gameResult1 = new TextBox(50,100,300,50, "You took 1 try");
        }
        if (winCond > 1 && winCond < 7){
            gameResult1 = new TextBox(50,100,300,50, "You took " + stringWinCond + " tries");
        }
        if (winCond >= 7){
            gameResult1 = new TextBox(50,100,300,50,"The word was "+ randWord);
        }
        statsTofile("stats.txt", winCond);
        returnMainfromEnd = new Button(50, 300,300,50, "Main Menu");
        endGameScreen->show();
        std::cout << "Game End" << std::endl;
    
        ON_CLICK(returnMainfromEnd, closeEnd)
    }
    void winCheck(Widget* sender){
        std::string guess = message->label();
        if (guess.size() == 5){
            std::string filename = "words.txt";
            std::string search_string = guess;
            if (string_in_file(filename, search_string)) {
                if (guess == randWord){
                    winStreak++;
                    endGame("You Win!", randWord, winCond);
                    
                }
                else{
                    int start = 150;
                    char l1 = guess[0];
                    char l2 = guess[1];
                    char l3 = guess[2];
                    char l4 = guess[3];
                    char l5 = guess[4];

                    char r1 = randWord[0];
                    char r2 = randWord[1];
                    char r3 = randWord[2];
                    char r4 = randWord[3];
                    char r5 = randWord[4];

                    std::string let1(1, l1);
                    std::string let2(1, l2);
                    std::string let3(1, l3);
                    std::string let4(1, l4);
                    std::string let5(1, l5);

                    std::string guess = message->label();
                    std::string right = " correct and in right pos";
                    std::string rightWrong = " correct but in wrong pos";
                    std::string wrong = " wrong letter";

                    og1->resize(150, messageStart + 2, 22, 26);
                    og2->resize(173, messageStart + 2, 22, 26);
                    og3->resize(196, messageStart + 2, 22, 26);
                    og4->resize(219, messageStart + 2, 22, 26);
                    og5->resize(242, messageStart + 2, 22, 26);

                    og1->label(let1);
                    og2->label(let2);
                    og3->label(let3);
                    og4->label(let4);
                    og5->label(let5);
                    
                    og1->labelcolor(FL_WHITE);
                    og2->labelcolor(FL_WHITE);
                    og3->labelcolor(FL_WHITE);
                    og4->labelcolor(FL_WHITE);
                    og5->labelcolor(FL_WHITE);

                    og1->labelsize(25);
                    og2->labelsize(25);
                    og3->labelsize(25);
                    og4->labelsize(25);
                    og5->labelsize(25);

                    og1->box(FL_FLAT_BOX);
                    og2->box(FL_FLAT_BOX);
                    og3->box(FL_FLAT_BOX);
                    og4->box(FL_FLAT_BOX);
                    og5->box(FL_FLAT_BOX);

                    og1->color(fl_rgb_color(130, 130, 130));
                    og2->color(fl_rgb_color(130, 130, 130));
                    og3->color(fl_rgb_color(130, 130, 130));
                    og4->color(fl_rgb_color(130, 130, 130));
                    og5->color(fl_rgb_color(130, 130, 130));

                    if (l1 == r2){
                        og1->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l1 == r3){
                        og1->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l1 == r4){
                        og1->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l1 == r5){
                        og1->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l2 == r1){
                        og2->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l2 == r3){
                        og2->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l2 == r4){
                        og2->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l2 == r5){
                        og2->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l3 == r1){
                        og3->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l3 == r2){
                        og3->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l3 == r4){
                        og3->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l3 == r5){
                        og3->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l4 == r1){
                        og4->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l4 == r2){
                        og4->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l4 == r3){
                        og4->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l4 == r5){
                        og4->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l5 == r1){
                        og5->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l5 == r2){
                        og5->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l5 == r3){
                        og5->color(fl_rgb_color(200, 165, 0));
                    }
                    if (l5 == r4){
                        og5->color(fl_rgb_color(200, 165, 0));
                    }



                    if (l1 == r1){
                        og1->color(fl_rgb_color(85, 175, 85));
                    }
                    if (l2 == r2){
                        og2->color(fl_rgb_color(85, 175, 85));
                    }
                    if (l3 == r3){
                        og3->color(fl_rgb_color(85, 175, 85));
                    }
                    if (l4 == r4){
                        og4->color(fl_rgb_color(85, 175, 85));
                    }
                    if (l5 == r5){
                        og5->color(fl_rgb_color(85, 175, 85));
                    }

                    og1->redraw();
                    og2->redraw();
                    og3->redraw();
                    og4->redraw();
                    og5->redraw();

                    message->label("");
                    messageStart = messageStart + 35;
                    message->resize(150, messageStart, 115, 27);

                    winCond++;
                
                } 
            }
            else {
                showMessage("Make sure that your word exists.");
            }
            
        }
        else{
            showMessage("Make sure that your word is 5 letters long.");
        }
        if (winCond > 6){
            winStreak = 0;
            endGame("You Lose.", randWord, winCond);
            
        }
    }
    void openGame(Widget* sender){
        winCond = 1;
        gamePlay = new bobcat::Window(100, 100, 400, 400, "Wordle");
        // Open the file "words.txt"
        std::ifstream file("words.txt");
        std::vector<std::string> words;
        std::string word;
        while (file >> word) {
            words.push_back(word);
        }
    
        // Close the file
        file.close();

        // Seed the random number generator
        std::srand(std::time(0)); 
    
        // Generate a random index to select a word
        int randomIndex = std::rand() % words.size();
    
        // Output the randomly selected word
        std::cout << "Random word: " << words[randomIndex] << std::endl;
        randWord = words[randomIndex];
        std::vector<std::string> row1 = {"A","B","C","D","E","F","G","H","I"};
        std::vector<std::string> row2 = {"J","K","L","M","N","O","P","Q","R"};
        std::vector<std::string> row3 = {"S", "T", "U", "V", "W","X","Y","Z"};
        delBut = new Button(175, 340, 50, 25, "Delete");
        enterBut = new Button(175, 370, 50, 25, "Enter");
        messageStart = 25;      
        
        int start = 150;
        int wordAdd = 35;

        w1g1 = new TextBox(150, messageStart + 2, 22, 25, " ");
        w1g2 = new TextBox(173, messageStart + 2, 22, 25, " ");
        w1g3 = new TextBox(196, messageStart + 2, 22, 25, " ");
        w1g4 = new TextBox(219, messageStart + 2, 22, 25, " ");
        w1g5 = new TextBox(242, messageStart + 2, 22, 25, " ");

        w2g1 = new TextBox(150, messageStart + 2+ wordAdd, 22, 25, " ");
        w2g2 = new TextBox(173, messageStart + 2+ wordAdd, 22, 25, " ");
        w2g3 = new TextBox(196, messageStart + 2+ wordAdd, 22, 25, " ");
        w2g4 = new TextBox(219, messageStart + 2+ wordAdd, 22, 25, " ");
        w2g5 = new TextBox(242, messageStart + 2+ wordAdd, 22, 25, " ");

        w3g1 = new TextBox(150, messageStart + 2+ wordAdd+ wordAdd, 22, 25, " ");
        w3g2 = new TextBox(173, messageStart + 2+ wordAdd+ wordAdd, 22, 25, " ");
        w3g3 = new TextBox(196, messageStart + 2+ wordAdd+ wordAdd, 22, 25, " ");
        w3g4 = new TextBox(219, messageStart + 2+ wordAdd+ wordAdd, 22, 25, " ");
        w3g5 = new TextBox(242, messageStart + 2+ wordAdd+ wordAdd, 22, 25, " ");

        w4g1 = new TextBox(150, messageStart + 2+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w4g2 = new TextBox(173, messageStart + 2+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w4g3 = new TextBox(196, messageStart + 2+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w4g4 = new TextBox(219, messageStart + 2+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w4g5 = new TextBox(242, messageStart + 2+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");

        w5g1 = new TextBox(150, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w5g2 = new TextBox(173, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w5g3 = new TextBox(196, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w5g4 = new TextBox(219, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w5g5 = new TextBox(242, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");

        w6g1 = new TextBox(150, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w6g2 = new TextBox(173, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w6g3 = new TextBox(196, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w6g4 = new TextBox(219, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");
        w6g5 = new TextBox(242, messageStart + 2+ wordAdd+ wordAdd+ wordAdd+ wordAdd+ wordAdd, 22, 25, " ");


        w1g1->box(FL_ENGRAVED_BOX);
        w1g2->box(FL_ENGRAVED_BOX);
        w1g3->box(FL_ENGRAVED_BOX);
        w1g4->box(FL_ENGRAVED_BOX);
        w1g5->box(FL_ENGRAVED_BOX);
        w2g1->box(FL_ENGRAVED_BOX);
        w2g2->box(FL_ENGRAVED_BOX);
        w2g3->box(FL_ENGRAVED_BOX);
        w2g4->box(FL_ENGRAVED_BOX);
        w2g5->box(FL_ENGRAVED_BOX);
        w3g1->box(FL_ENGRAVED_BOX);
        w3g2->box(FL_ENGRAVED_BOX);
        w3g3->box(FL_ENGRAVED_BOX);
        w3g4->box(FL_ENGRAVED_BOX);
        w3g5->box(FL_ENGRAVED_BOX);
        w4g1->box(FL_ENGRAVED_BOX);
        w4g2->box(FL_ENGRAVED_BOX);
        w4g3->box(FL_ENGRAVED_BOX);
        w4g4->box(FL_ENGRAVED_BOX);
        w4g5->box(FL_ENGRAVED_BOX);
        w5g1->box(FL_ENGRAVED_BOX);
        w5g2->box(FL_ENGRAVED_BOX);
        w5g3->box(FL_ENGRAVED_BOX);
        w5g4->box(FL_ENGRAVED_BOX);
        w5g5->box(FL_ENGRAVED_BOX);
        w6g1->box(FL_ENGRAVED_BOX);
        w6g2->box(FL_ENGRAVED_BOX);
        w6g3->box(FL_ENGRAVED_BOX);
        w6g4->box(FL_ENGRAVED_BOX);
        w6g5->box(FL_ENGRAVED_BOX);

        message = new TextBox(150, messageStart, 115, 27, "");
        message->labelsize(25);
        message->box(FL_ENGRAVED_BOX);
        setupRow(row1, 250);
        setupRow(row2, 250 + 30);
        setupRow(row3, 250 + 60);
        for (int i = 0; i < keyboard.size(); i++){
            ON_CLICK(keyboard[i],  handleClick);
        }
        ON_CLICK(delBut, backSpace);
        ON_CLICK(enterBut, winCheck);


        og1 = new TextBox(150, messageStart, 25, 25, "");
        og2 = new TextBox(167, messageStart, 25, 25, "");
        og3 = new TextBox(184, messageStart, 25, 25, "");
        og4 = new TextBox(201, messageStart, 25, 25, "");
        og5 = new TextBox(218, messageStart, 25, 25, "");

        gamePlay->show();
    }
    
    void openStats(Widget* sender){
        stats = new bobcat::Window(100, 100, 400, 400, "Statistics");
        Statistics = new ListBox(20,20,360,250);
        std::string strWinStreak = to_string(winStreak);
        WinStreak = new TextBox(175,280,50,20,"Winstreak: " + strWinStreak);
        returnMainfromStats= new Button(50, 310,300,30, "Main Menu");
        clearStats= new Button(50, 350,300,30, "Clear Statistics");
        WinStreak->align(FL_ALIGN_CENTER);
        ON_CLICK(returnMainfromStats, closeStats)
        ON_CLICK(clearStats, clearStatistics)
    
        populateListboxFromFile("stats.txt", Statistics);
        stats->show();
    }

    

    void openInstruct(Widget* sender){
        instructions = new bobcat::Window(100,100,400,400,"Instructions");
        instruct1 = new TextBox(10,25,300,50,"Objective: Guess the hidden 5-letter word within");
        instruct2 = new TextBox(10,40,300,50,"6 guesses. After each guess, you'll receive");
        instruct3 = new TextBox(10,55,300,50,"feedback that helps guide your next guess.");
        instruct4 = new TextBox(10,105,300,50,"Steps:");
        instruct5 = new TextBox(10,120,300,50,"Make Your First Guess");
        instruct6 = new TextBox(10,135,300,50,"Interpret the Feedback:");
        instruct7 = new TextBox(10,150,300,50,"Green: The letter is correct and in the right position");
        instruct8 = new TextBox(10,165,300,50,"Yellow: The letter is correct but in the wrong position");
        instruct9 = new TextBox(10,180,300,50,"Grey: The letter is not in the word at all.");
        instruct0 = new TextBox(10,230,300,50,"Strategically guess, you have 6 guesses total.");
        returnMainfromInstruct = new Button(50, 300,300,50, "Main Menu");

        ON_CLICK(returnMainfromInstruct, closeInstruct)

        instructions->show();
    }

public:
    Application() {
        theme();
        //main menu window
        mainMenu = new bobcat::Window(100, 100, 400, 400, "Main Menu");
        mainTitle = new TextBox(170,25,300,50,"Wordle");
        playGame = new Button(50, 150,300,50, "Play Game");
        viewInstructions = new Button(50, 225,300,50, "View Instructions");
        viewStats = new Button(50, 300,300,50, "View Statistics");
        mainMenu->show();

      


        ON_CLICK(playGame, openGame)
        ON_CLICK(viewStats, openStats)
        ON_CLICK(viewInstructions, openInstruct)


;
    }

    friend struct ::AppTest;
};

#endif