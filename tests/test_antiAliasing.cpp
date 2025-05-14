#include <criterion/criterion.h>

#include <vector>
#include <memory>

#include "Draw/my_Image.hpp"
#include "Generation/tools.hpp"

Test(createListImages, creates_correct_number_of_images) {
    my_Image baseImage(10, 10, sf::Color::Black);
    std::vector<std::unique_ptr<my_Image>> images;

    createListImages(images, baseImage, 9);

    cr_assert_eq(images.size(), 9, "Expected 9 images, but got %lu", images.size());
    for (const auto &img : images) {
        cr_assert_not_null(img.get(), "Expected image");
        cr_assert_eq(img->getSizeX(), baseImage.getSizeX(), "bad image width");
        cr_assert_eq(img->getSizeY(), baseImage.getSizeY(), "bad image height");
    }
}

Test(averageAllImages, averages_pixel_values_correctly) {
    my_Image baseImage(10, 10, sf::Color::Black);
    std::vector<std::unique_ptr<my_Image>> images;

    createListImages(images, baseImage, 9);

    for (size_t k = 0; k < images.size(); ++k) {
        for (float i = 0; i < baseImage.getSizeX(); ++i) {
            for (float j = 0; j < baseImage.getSizeY(); ++j) {
                images[k]->setPixel(i, j, sf::Color(i + k, j + k, 100, 255));
            }
        }
    }

    my_Image resultImage(10, 10, sf::Color::Black);
    averageAllImages(5, 5, resultImage, images);

    sf::Color result = resultImage.getPixel(5, 5);
    cr_assert_eq(result.r, 5 + 4, "Expected red to be %d, but got %d", 5 + 4, result.r);
    cr_assert_eq(result.g, 5 + 4, "Expected green to be %d, but got %d", 5 + 4, result.g);
    cr_assert_eq(result.b, 100, "Expected blue to be 100, but got %d", result.b);
    cr_assert_eq(result.a, 255, "Expected alpha to be 255, but got %d", result.a);
}
