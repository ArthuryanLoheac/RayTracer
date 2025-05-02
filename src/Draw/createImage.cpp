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

std::string randomString(int max_length) {
    std::string characters =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<> dist(0, characters.size()-1);
    std::string ret = "";
    for (int i = 0; i < max_length; i++) {
        int random_index = dist(engine);
        ret += characters[random_index];
    }
    return ("renders/screenshot" + ret + ".ppm");
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
