SRC = additional_functions.c additional_functions_two.c apply_scene.c\
	  bmp_file_save.c color.c cylindre.c error_manage.c keys_events.c\
	  plan.c ray.c read_camera.c read_objects.c read_scene.c\
	  sphere.c square.c translate.c triangle.c vector.c vector_cont.c\
	  libft/ft_atof.c libft/ft_split.c libft/ft_memcpy.c\
	  libft/ft_strcmp.c libft/ft_strdup.c\
	  libft/ft_strlen.c libft/ft_substr.c\
	  get_next_line/get_next_line.c

OBJSRC=  additional_functions.o additional_functions_two.o apply_scene.o\
		 bmp_file_save.o color.o cylindre.o error_manage.o keys_events.o\
		 plan.o ray.o read_camera.o read_objects.o read_scene.o\
		 sphere.o square.o translate.o triangle.o vector.o vector_cont.o\
		 ft_atof.o ft_split.o ft_strcmp.o ft_strdup.o ft_strlen.o ft_memcpy.o\
		 ft_substr.o get_next_line.o

NAME = libRT.a

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c $(SRC)
	ar rc $(NAME) $(OBJSRC)
	ranlib $(NAME)

clean:
	rm -rf $(NAME)
fclean:
	/bin/rm -f $(OBJSRC)
re: fclean all
