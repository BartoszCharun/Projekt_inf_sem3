#pragma once
#include <string>
#include <vector>

namespace sf {
class Font;
class Text;
class RectangleShape;
}

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
        static void initLayout(const sf::Font& font, sf::RectangleShape& panel, sf::Text& title,
                               float width, float height);
        static std::vector<sf::Text> createMenuItems(const sf::Font& font, float width, float height);
        static std::vector<sf::Text> createScoreTexts(const sf::Font& font, const std::vector<int>& scores,
                                                      float viewWidth, float viewHeight, sf::Text& scoreTitle);
        static float titleScale(float animTimer);
    };

    struct Gra {
        static const char* windowTitle();
        static const char* gameOver();
        static const char* loadSaveError();
        static std::string hitsLabel(int count);
        static std::string scoreEntry(int position, int score);
        static const char* emptyScorePlaceholder();
        static void initTexts(const sf::Font& font, sf::Text& tekstPrzegrana, sf::Text& tekstOdbicia,
                              sf::Text& tekstTabela, float gameWidth, float gameHeight);
    };
};
