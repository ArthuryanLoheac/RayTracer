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

FLAGS = $(FLAGS_INCLUDE) \
	$(shell find include src -type d -exec echo -I{} \;) \
	-MMD -MP $(FLAGS_LIB) -lsfml-graphics -lsfml-window -lsfml-system -ldl \
	-lconfig++ -g \

FLAGS_INCLUDE = -I./include -I./src -I./src/dlLoader \

FLAGS_TEST = $(FLAGS) -lcriterion --coverage \

FLAGS_LIB = -std=c++20 -Wall -Wextra -Werror

FLAGS_LINTER =	\
	--repository=. \
	--quiet \
	--output=vs7	\
	--filter=-legal/copyright,-build/c++17,+build/c++20,-runtime/references \
	--recursive \
	--exclude=tests/ \

FLAGS_SO = $(FLAGS_LIB) -lsfml-graphics -lsfml-window -lsfml-system \
            $(FLAGS_INCLUDE) -ldl -g \

FLAGS_LIB = -std=c++20 -Wall -Wextra -Werror

# ============= NAMES ============= #

NAME_LIB	= \

NAME	=	raytracer

# ============= SOURCES ============= #

SRC_LIB	=	\

SRC_MAIN	=	main.cpp \

SRC	= 	$(shell find src -type f -name "*.cpp" ! -name "main.cpp" \
		! -path "src/Primitive/**" ! -path "src/Material/**" \
		! -path "src/Lights/**") \

SRC_TESTS	= 	\
	tests/test_Vector3D.cpp \
	tests/test_Rectangle3D.cpp \
	tests/test_Ray.cpp \
	tests/test_Point3D.cpp \
	tests/test_PrimNone.cpp \
	tests/test_computeTreeValues.cpp \
	tests/test_LoadSo.cpp \
	tests/test_A_Primitive.cpp \

COMMON_SRC = src/3dDatas/Point3D.cpp \
			src/3dDatas/Vector3D.cpp \
			src/3dDatas/Ray.cpp \
			src/3dDatas/Rectangle3D.hpp \
			src/Scene/Camera.cpp \

SRC_PRIMITIVE = $(COMMON_SRC) \
				src/Interfaces/Primitive/A_Primitive.cpp \

SRC_LIGHT = $(COMMON_SRC) \
			src/Interfaces/Light/A_Light.cpp \

SRC_MATERIAL = $(COMMON_SRC)

# ============= RULES ============= #

all: core primitive material light

$(NAME): $(OBJ_SRC) $(OBJ_MAIN)
	$(COMPILER) -o $(NAME) $(OBJ_SRC) $(OBJ_MAIN) $(FLAGS)

$(NAME_LIB): $(OBJ)
	ar rc $(NAME_LIB) $(OBJ)

sphere:
	@mkdir -p plugins
	$(COMPILER) -o plugins/primitive_sphere.so -shared -fPIC $(SRC_PRIMITIVE) \
		src/Primitive/PrimSphere.cpp $(FLAGS_SO)

cone:
	@mkdir -p plugins
	$(COMPILER) -o plugins/primitive_cone.so -shared -fPIC $(SRC_PRIMITIVE) \
		src/Primitive/PrimCone.cpp $(FLAGS_SO)

limcone:
	@mkdir -p plugins
	$(COMPILER) -o plugins/primitive_limcone.so \
		-shared -fPIC $(SRC_PRIMITIVE) \
		src/Primitive/PrimLimCone.cpp $(FLAGS_SO)

cylinder:
	@mkdir -p plugins
	$(COMPILER) -o plugins/primitive_cylinder.so -shared -fPIC \
		$(SRC_PRIMITIVE) src/Primitive/PrimCylinder.cpp $(FLAGS_SO)

limcylinder:
	@mkdir -p plugins
	$(COMPILER) -o plugins/primitive_limcylinder.so -shared -fPIC \
		$(SRC_PRIMITIVE) src/Primitive/PrimLimCylinder.cpp $(FLAGS_SO)

plane:
	@mkdir -p plugins
	$(COMPILER) -o plugins/primitive_plane.so -shared -fPIC $(SRC_PRIMITIVE) \
		src/Primitive/PrimPlane.cpp $(FLAGS_SO)

obj_prim:
	@mkdir -p libs
	$(COMPILER) -o plugins/primitive_obj.so -shared -fPIC $(SRC_PRIMITIVE) \
		src/Primitive/PrimObj.cpp $(FLAGS_SO)

none:
	@mkdir -p libs
	$(COMPILER) -o plugins/primitive_none.so -shared -fPIC $(SRC_PRIMITIVE) \
		src/Primitive/PrimNone.cpp $(FLAGS_SO)

primitive: sphere plane none cylinder cone limcylinder obj_prim limcone

flat_mat:
	@mkdir -p plugins
	$(COMPILER) -o plugins/mat_flat.so -shared -fPIC $(SRC_MATERIAL) \
		src/Material/FlatMat.cpp $(FLAGS_SO)

chess_mat:
	@mkdir -p plugins
	$(COMPILER) -o plugins/mat_chess.so -shared -fPIC $(SRC_MATERIAL) \
		src/Material/ChessboardMat.cpp $(FLAGS_SO)

trans_mat:
	@mkdir -p libs
	$(COMPILER) -o plugins/mat_trans.so -shared -fPIC $(SRC_MATERIAL) \
		src/Material/TransMat.cpp $(FLAGS_SO)

perlin_mat:
	@mkdir -p plugins
	$(COMPILER) -o plugins/mat_perlin.so -shared -fPIC $(SRC_MATERIAL) \
		src/Material/PerlinMat.cpp $(FLAGS_SO)

image_mat:
	@mkdir -p plugins
	$(COMPILER) -o plugins/mat_image.so -shared -fPIC $(SRC_MATERIAL) \
		src/Material/ImageMat.cpp $(FLAGS_SO)

reflect_mat:
	@mkdir -p plugins
	$(COMPILER) -o plugins/mat_reflect.so -shared -fPIC $(SRC_MATERIAL) \
		src/Material/ReflectMat.cpp $(FLAGS_SO)

material: flat_mat chess_mat perlin_mat image_mat trans_mat reflect_mat

ambient_light:
	@mkdir -p plugins
	$(COMPILER) -o plugins/light_ambient.so -shared -fPIC $(SRC_LIGHT) \
		src/Lights/Ambient.cpp $(FLAGS_SO)

spot_light:
	@mkdir -p plugins
	$(COMPILER) -o plugins/light_spot.so -shared -fPIC $(SRC_LIGHT) \
		src/Lights/Spot.cpp $(FLAGS_SO)

light: ambient_light spot_light

core: $(NAME) $(NAME_LIB)


# ============= CLEANS ============= #

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.gcda *.gcno

fclean: clean
	rm -rf plugins
	rm -f $(NAME) $(NAME_LIB) unit_tests

screenshot:
	rm -rf renders/*.ppm

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

unit_tests: fclean primitive light material
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
