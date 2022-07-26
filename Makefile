NAME = philo
FLAG = -Werror -Wextra -Wall -g -MMD
HEAD = ./includes
OBJ = obj/main.o $(addprefix obj/ph_, $(addsuffix .o, create_thread parsing routine time utils))
D_LST = obj/main.d $(addprefix obj/ph_, $(addsuffix .d,create_thread parsing routine time utils))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAG) $(OBJ) -o $(NAME)

obj/%.o: src/%.c | object
	$(CC) $(FLAG) -I $(HEAD) -c $< -o $@

object : 
	@mkdir -p obj

clean :
	rm -f $(NAME)

fclean : clean
	rm -rf obj

re : fclean all

.PHONY: re all fclean clean
-include $(D_LST)
