NAME = philo
FLAG = -Wall -Werror -Wextra -g -MMD
HEAD = ./includes
OBJ = $(addprefix obj/, $(addsuffix _bonus.o, \
				action \
				dead \
				display \
				fork \
				parsing \
				utils \
				time \
				unsetup_philo \
				routine \
				sem_utils \
				ft_itoa \
				thread_routine \
				thread_routine_fork \
				create_philo \
				handle_crash \
				main))
D_LST = $(OBJ:.o=.d)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAG) $(OBJ) -pthread -o $(NAME)

obj/%.o: src/%.c | object
	$(CC) $(FLAG) -I $(HEAD) -pthread -c $< -o $@

object : 
	@mkdir -p obj

clean :
	rm -f $(NAME)

fclean : clean
	rm -rf obj

re : fclean all

.PHONY: re all fclean clean
-include $(D_LST)
