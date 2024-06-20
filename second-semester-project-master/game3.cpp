#include <graphics.h>
//#include <iostream>
//#include <string>
//#include <chrono>
//#include <vector>
//#include <ctime>
//#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

const vector<string> sentences = {
    "The quick brown fox jumps over the lazy dog.",
    "A journey of a thousand miles begins with a single step.",
    "To be or not to be, that is the question.",
    "All that glitters is not gold.",
    "A picture is worth a thousand words."
};

string getRandomSentence() {
    srand(static_cast<unsigned int>(time(0)));
    int index = rand() % sentences.size();
    return sentences[index];
}

void displayText(const string& text, int x, int y, int color) {
    setcolor(color);
    outtextxy(x, y, const_cast<char*>(text.c_str()));
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    cleardevice();

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(BLACK);

    displayText("Typing Speed Test", 200, 50, BLUE);
    displayText("You have 60 seconds to type the following sentence as accurately as possible.", 50, 100, BLACK);

    string sentence = getRandomSentence();
    displayText("Sentence:", 50, 150, BLACK);
    outtextxy(50, 200, const_cast<char*>(sentence.c_str()));

    displayText("Press any key to start typing...", 50, 250, RED);
    getch();

    cleardevice();
    displayText("Start typing:", 50, 100, BLACK);
    outtextxy(50, 150, const_cast<char*>(sentence.c_str()));

    auto start = high_resolution_clock::now();
    string userInput;
    char ch;
    int x = 50, y = 200;
    while ((ch = getch()) != 13) { // Enter key
        if (ch == 8) { // Backspace
            if (!userInput.empty()) {
                userInput.pop_back();
                setcolor(WHITE);
                outtextxy(x, y, "_"); // Erase character
                setcolor(BLACK);
                x -= textwidth("_");
            }
        } else {
            userInput.push_back(ch);
            char temp[2] = {ch, '\0'};
            outtextxy(x, y, temp);
            x += textwidth(temp);
        }
    }

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    double seconds = elapsed.count();

    int correctChars = 0;
    for (size_t i = 0; i < min(sentence.size(), userInput.size()); ++i) {
        if (sentence[i] == userInput[i]) {
            correctChars++;
        }
    }

    int wpm = (userInput.size() / 5) / (seconds / 60);
    double accuracy = (static_cast<double>(correctChars) / sentence.size()) * 100;

    cleardevice();
    displayText("Results:", 50, 100, BLUE);
    string timeStr = "Time taken: " + to_string(seconds) + " seconds";
    displayText(timeStr, 50, 150, BLACK);
    string wpmStr = "Words per minute: " + to_string(wpm);
    displayText(wpmStr, 50, 200, BLACK);
    string accuracyStr = "Accuracy: " + to_string(accuracy) + "%";
    displayText(accuracyStr, 50, 250, BLACK);

    getch();
    closegraph();

    return 0;
}
