#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <fstream>
#include <string>

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

static std::string randomString(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;

    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return ("renders/screenshot" + tmp_s + ".ppm");
}

void renderAtClosing(sf::RenderWindow &window) {
    sf::Texture texture;
    sf::Image screenshot;

    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    screenshot  = texture.copyToImage();
    createPPMFile(screenshot, "renders/render.ppm");
}

void screenshot(sf::RenderWindow &window) {
    sf::Texture texture;
    sf::Image screenshot;

    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    screenshot  = texture.copyToImage();
    createPPMFile(screenshot, randomString(5));
}
