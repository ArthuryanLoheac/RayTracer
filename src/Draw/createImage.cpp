#include <fstream>
#include <string>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


static void createPPMFile(const sf::Image& image,
    const std::string& filename) {
    unsigned int width;
    unsigned int height;
    std::ofstream out(filename);

    width = image.getSize().x;
    height = image.getSize().y;
    out << "P3\n" << width << " " << height << "\n255\n";
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            sf::Color color = image.getPixel(x, y);
            out << static_cast<int>(color.r) << " "
                << static_cast<int>(color.g) << " "
                << static_cast<int>(color.b) << "  ";
        }
        out << "\n";
    }
    out.close();
}

std::string getTimestampAsString() {
    std::time_t now = std::time(nullptr);
    std::tm *tm = std::localtime(&now);
    std::string ret =
        std::to_string(tm->tm_mday) + "-" +
        std::to_string(tm->tm_mon + 1) + "-" +
        std::to_string(tm->tm_year + 1900) + "_" +
        std::to_string(tm->tm_hour) + "-" +
        std::to_string(tm->tm_min) + "-" +
        std::to_string(tm->tm_sec);
    return ret;
}

void renderAtClosing(sf::RenderWindow &window) {
    sf::Texture texture;
    sf::Image screenshot;

    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    screenshot  = texture.copyToImage();
    createPPMFile(screenshot, "renders/render-" +
        getTimestampAsString() + ".ppm");
}

void screenshot(sf::RenderWindow &window) {
    sf::Texture texture;
    sf::Image screenshot;

    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    screenshot  = texture.copyToImage();
    createPPMFile(screenshot, "renders/screenshot-" +
        getTimestampAsString() + ".ppm");
}
