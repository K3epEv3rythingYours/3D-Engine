CC = cc
FLAGS = -Wall -Werror -Wextra
LFLAGS = -lmlx -lX11 -lXext -lm
HEADER = -I./
SRC = line.c put_pixel.c mouse.c handle.c functions.c objects.c cube.c UI.c reset.c sphere.c donut.c project.c main.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
NAME = a.out

all: $(NAME)
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(HEADER) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(FLAGS) $(LFLAGS)

$(OBJ_DIR)/put_pixel.o: put_pixel.c rainbow.h
$(OBJ_DIR)/line.o: line.c rainbow.h
$(OBJ_DIR)/main.o: main.c rainbow.h
$(OBJ_DIR)/mouse.o: mouse.c rainbow.h
$(OBJ_DIR)/handle.o: handle.c rainbow.h

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
