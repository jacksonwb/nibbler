# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/03 12:06:08 by jbeall            #+#    #+#              #
#    Updated: 2019/06/04 10:39:37 by jbeall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==================================== GENERAL =================================#

NAME = nibbler

CPPFLAGS = -Wall -Wextra -Werror -std=c++11 #-Ofast #-fsanitize=address

SRC_DIR = ./src/

LIB_DIR = ./lib/

#=================================== SOURCES ==================================#

LIST = main \
Game \
Snake

SRC = $(addsuffix .cpp, $(addprefix $(SRC_DIR), $(LIST)))

#=================================== OBJECTS ==================================#

OBJ_DIR = .obj/
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(LIST)))
DEP = $(OBJ:%.o=%.d)

#=================================== HEADERS ==================================#

#INC_DIR = ./src/

#INC = -I $(INC_DIR)

#==================================== COLORS ==================================#

#COLORS
COM_COLOR   = \033[92m
NO_COLOR    = \033[m

#TEXT
COM_STRING  = "$(NAME) compilation successful"
CLEAN_OBJ	= "cleaned $(NAME) objects"
CLEAN_NAME	= "cleaned $(NAME) binary"
CLEAN_LIB	= "cleaned $(name) libraries"

#===================================== RULES ==================================#

all: obj $(NAME)

$(NAME): $(OBJ)
	@echo "linking..."
	@clang++ $(CPPFLAGS) $^ -o $@
	@echo "$(COM_COLOR) $(COM_STRING) $(NO_COLOR)"

-include $(DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@printf "compiling: %s\n" $<
	@clang++ $(CPPFLAGS) $(INC) -MMD -g -c $< -o $@

dylib:
	@mkdir -p $(LIB_DIR)
	@clang++ -std=c++11 -g -shared -fPIC -l ncurses -o $(LIB_DIR)lib1.dylib $(SRC_DIR)Render1.cpp
	@echo "lib1 successfully built!"
	@clang++ -std=c++11 -g -shared -fPIC `pkg-config --cflags --libs sdl2` -l SDL2_ttf -o $(LIB_DIR)lib2.dylib $(SRC_DIR)Render2.cpp
	@echo "lib2 successfully built!"
	@clang++ -std=c++11 -g -shared -fPIC `pkg-config --cflags --libs sdl2` -l SDL2_ttf -l SDL2_image -o $(LIB_DIR)lib3.dylib $(SRC_DIR)Render3.cpp
	@echo "lib3 successfully built!"
obj:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(COM_COLOR)$(CLEAN_OBJ)$(NO_COLOR)"
	@rm -rf $(LIB_DIR)
	@echo "$(COM_COLOR)$(CLEAN_LIB)$(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COM_COLOR)$(CLEAN_NAME)$(NO_COLOR)"

re: fclean all
