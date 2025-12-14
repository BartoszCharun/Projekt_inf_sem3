#include "Napisy.h"

namespace {
const std::vector<std::string> MENU_OPTIONS = {
    "Nowa gra",
    "Wczytaj gre",
    "Tabela wynikow",
    "Wyjscie"
};
}

const char* Napisy::Pliki::font()
{
    return "Arimo-Regular.ttf";
}

const char* Napisy::Pliki::score()
{
    return "scores.txt";
}

const char* Napisy::Pliki::save()
{
    return "savedgame.txt";
}

const char* Napisy::Menu::title()
{
    return "ARKANOID";
}

const std::vector<std::string>& Napisy::Menu::options()
{
    return MENU_OPTIONS;
}

const char* Napisy::Menu::scoresTitle()
{
    return "Tabela wynikow";
}

const char* Napisy::Menu::noScoresLabel()
{
    return "Brak wynikow";
}

const char* Napisy::Gra::windowTitle()
{
    return "Arkanoid";
}

const char* Napisy::Gra::gameOver()
{
    return "Game over! Nacisnij R aby zrestartowac";
}

const char* Napisy::Gra::loadSaveError()
{
    return "Brak zapisu gry lub uszkodzony plik.";
}

std::string Napisy::Gra::hitsLabel(int count)
{
    return "Odbicia: " + std::to_string(count);
}

std::string Napisy::Gra::scoreEntry(int position, int score)
{
    return std::to_string(position) + ". " + std::to_string(score) + " odbic";
}

const char* Napisy::Gra::emptyScorePlaceholder()
{
    return "-";
}
