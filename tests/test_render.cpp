#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <memory>
#include <fstream>
#include <filesystem>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Generation/tools.hpp"

void redirect_all_stdout() {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Render, render_at_closing, .init = redirect_all_stdout) {
    sf::RenderWindow window(sf::VideoMode(10, 10), "Test Render");
    std::string filename = "renders/render-" + getTimestampAsString() + ".ppm";

    renderAtClosing(window);

    cr_assert(std::filesystem::exists(filename),
        "Render file was not created.");
    std::filesystem::remove(filename);  // Clean up
}

Test(Render, screenshot, .init = redirect_all_stdout) {
    sf::RenderWindow window(sf::VideoMode(10, 10), "Test Screenshot");
    std::string filename = "renders/screenshot-" + getTimestampAsString()
        + ".ppm";

    screenshot(window);

    cr_assert(std::filesystem::exists(filename),
        "Screenshot file was not created.");
    std::filesystem::remove(filename);  // Clean up
}
