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
	-MMD -MP $(FLAGS_LIB) -lsfml-graphics -lsfml-window -lsfml-system \

FLAGS_TEST = $(FLAGS) -lcriterion --coverage \

FLAGS_LIB = -std=c++20 -Wall -Wextra -Werror

FLAGS_LINTER =	\
	--repository=. \
	--quiet \
	--output=vs7	\
	--filter=-legal/copyright,-build/c++17,+build/c++20,-runtime/references\
	--recursive

# ============= NAMES ============= #

NAME_LIB	= \

NAME	=	raytracer

# ============= SOURCES ============= #

SRC_LIB	=	\

SRC_MAIN	=	main.cpp \

SRC	= 	$(shell find src -type f -name "*.cpp" ! -name "main.cpp") \

SRC_TESTS	= 	\

# ============= RULES ============= #

all: $(NAME) $(NAME_LIB)

$(NAME): $(OBJ_SRC) $(OBJ_MAIN)
	$(COMPILER) -o $(NAME) $(OBJ_SRC) $(OBJ_MAIN) $(FLAGS)

$(NAME_LIB): $(OBJ)
	ar rc $(NAME_LIB) $(OBJ)

# ============= CLEANS ============= #

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.gcda *.gcno

fclean: clean
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
