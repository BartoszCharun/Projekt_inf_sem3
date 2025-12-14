#pragma once
#include <string>
#include <vector>

class Napisy {
public:
    struct Pliki {
        static const char* font();
        static const char* score();
        static const char* save();
    };

    struct Menu {
        static const char* title();
        static const std::vector<std::string>& options();
        static const char* scoresTitle();
        static const char* noScoresLabel();
    };

    struct Gra {
        static const char* windowTitle();
        static const char* gameOver();
        static const char* loadSaveError();
        static std::string hitsLabel(int count);
        static std::string scoreEntry(int position, int score);
        static const char* emptyScorePlaceholder();
    };
};
