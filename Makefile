SRC = additional_functions.c additional_functions_two.c apply_scene.c\
	  bmp_file_save.c color.c cylindre.c error_manage.c keys_events.c\
	  plan.c ray.c read_camera.c read_objects.c read_scene.c check_file.c\
	  sphere.c square.c translate.c triangle.c vector.c vector_cont.c\
	  libft/ft_atof.c libft/ft_split.c libft/ft_memcpy.c\
	  libft/ft_strcmp.c libft/ft_strdup.c\
	  libft/ft_strlen.c libft/ft_substr.c\
	  get_next_line/get_next_line.c

NAME = miniRT

all: $(NAME)

$(NAME):
	cc -Wall -Wextra -Werror -framework OpenGL\
		-framework Appkit -lmlx main.c $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)
fclean:
	rm -rf $(NAME)
re: fclean all
