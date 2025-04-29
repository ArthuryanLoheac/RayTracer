##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

# ============= OBJECT ============= #

OBJ_DIR = obj

OBJ = $(SRC_LIB:.$(EXTENSION)=$(OBJ_DIR)/%.o)

OBJ_SRC = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

OBJ_MAIN = $(SRC_MAIN:%.cpp=$(OBJ_DIR)/%.o)

DEPS = $(OBJ_SRC:.o=.d) $(OBJ_MAIN:.o=.d)

# ============= PARAMETERS ============= #

COMPILER = g++

EXTENSION = cpp

# ============= FLAGS ============= #

FLAGS = -I./include -I./src \
	$(shell find include src -type d -exec echo -I{} \;) \
	-MMD -MP $(FLAGS_LIB) -lsfml-graphics -lsfml-window -lsfml-system -ldl \

FLAGS_INCLUDE = -I./include \
			-I./src \
			-I./src/3dDatas \
			-I./src/Primitive \

FLAGS_TEST = $(FLAGS) -lcriterion --coverage \

FLAGS_LIB = -std=c++20 -Wall -Wextra -Werror

FLAGS_LINTER =	\
	--repository=. \
	--quiet \
	--output=vs7	\
	--filter=-legal/copyright,-build/c++17,+build/c++20,-runtime/references\
	--recursive

FLAGS_PRIMITIVE = $(FLAGS_LIB) -lsfml-graphics -lsfml-window -lsfml-system \
            $(FLAGS_INCLUDE)

FLAGS_LIB = -std=c++20 -Wall -Wextra -Werror

# ============= NAMES ============= #

NAME_LIB	= \

NAME	=	raytracer

NAME_SPHERE = libs/primitive_sphere.so

# ============= SOURCES ============= #

SRC_LIB	=	\

SRC_MAIN	=	main.cpp \

SRC	= 	src/3dDatas/Point3D.cpp \
		src/3dDatas/Vector3D.cpp \
		src/3dDatas/Ray.cpp \
		src/3dDatas/Rectangle3D.cpp \
		src/Draw/draw.cpp \
		src/Scene/Camera.cpp \
		src/Primitive/A_Primitive.cpp \
		src/Primitive/Sphere.cpp \

SRC_TESTS	= 	\

COMMON_SRC = src/3dDatas/Point3D.cpp \
			src/3dDatas/Vector3D.cpp \
			src/3dDatas/Ray.cpp \

SRC_PRIMITIVE = $(COMMON_SRC) \
				src/Primitive/A_Primitive.cpp \

# ============= RULES ============= #

all: core primitive

$(NAME): $(OBJ_SRC) $(OBJ_MAIN)
	$(COMPILER) -o $(NAME) $(OBJ_SRC) $(OBJ_MAIN) $(FLAGS)

$(NAME_LIB): $(OBJ)
	ar rc $(NAME_LIB) $(OBJ)

primitive:
	@mkdir -p libs
	$(COMPILER) -o $(NAME_SPHERE) -shared -fPIC $(SRC_PRIMITIVE) \
		src/Primitive/PrimSphere.cpp $(FLAGS_PRIMITIVE)

core: $(NAME) $(NAME_LIB)


# ============= CLEANS ============= #

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.gcda *.gcno

fclean: clean
	rm -rf libs
	rm -f $(NAME) $(NAME_LIB) unit_tests

# ============= COMPILATION ============= #

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) -c $(FLAGS) $< -o $@

-include $(DEPS)

# ============= OTHERS ============= #

re: fclean all

run: all
	./$(NAME)

# ============= TESTS ============= #

unit_tests:
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) -o $(OBJ_DIR)/unit_tests $(SRC_TESTS) $(SRC) $(FLAGS_TEST)
	cp $(OBJ_DIR)/unit_tests unit_tests

tests_run: unit_tests
	./$(OBJ_DIR)/unit_tests --verbose

tests_run_coverage: tests_run
	gcovr -r . -e tests/

tests_clean_run: fclean tests_run

tests_clean_run_coverage: tests_clean_run
	gcovr -r . -e tests/

style_check:
	@cpplint $(FLAGS_LINTER) \
		$(shell find . -type f \( -name '*.cpp' -o -name '*.hpp' \))
