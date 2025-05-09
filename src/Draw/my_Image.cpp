#include "Draw/my_Image.hpp"
#include "my_Image.hpp"

my_Image::my_Image() {
}

my_Image::my_Image(float x, float y, sf::Color fill) {
    image.create(x, y, fill);
}

void my_Image::setPixel(float x, float y, sf::Color c)
{
    std::lock_guard<std::mutex> lock(imageMutex);
    image.setPixel(x, y, c);
}

sf::Color my_Image::getPixel(float x, float y) {
    std::lock_guard<std::mutex> lock(imageMutex);
    return image.getPixel(x, y);
}

float my_Image::getSizeX() {
    return image.getSize().x;
}

float my_Image::getSizeY() {
    return image.getSize().y;
}
