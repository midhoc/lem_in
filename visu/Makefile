NAME = visu

SRC =	main.c \


OBJ = $(patsubst %.c, obj/%.o, $(SRC))

HEADER = ./includes/visu.h \
		 		./../libft/includes/libft.h

INCLUDE_PATH = -I ./includes -I ./../libft/includes

LIBFT =	../libft/libft.a


CC = gcc

FLAGS = -g `sdl2-config --cflags --libs`

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	$(CC) -o $(NAME)  $(INCLUDE_PATH) $(OBJ) $(LIBFT) $(FLAGS)

# $(SDL2):
# 	@if [ ! -d ./SDL2.framework ]; \
# 	then curl https://www.libsdl.org/release/SDL2-2.0.10.dmg \
# 	-o SDL2-2.0.10.dmg ; hdiutil attach SDL2-2.0.10.dmg ; \
# 	cp -r /Volumes/SDL2/SDL2.framework . ; \
# 	hdiutil detach /Volumes/SDL2 ; fi; \


obj:
	mkdir -p obj

obj/%.o: src/%.c $(LIBFT) $(HEADER)| obj
	 $(CC) $(FLAGS)  -c $< -o $@


$(LIBFT):
	make -C ../libft/

clean:
	rm -rf obj
	make clean -C ../libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C ../libft/

re: fclean all

.PHONY : all, re, clean, flcean
