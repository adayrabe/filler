NAME := adayrabe.filler

OBJ_DIR := ./obj/
SRC_DIR := ./src/
INC_DIR := ./inc/
LIB_DIR := ./libftprintf/

RM = /bin/rm -rf

SRC :=  play.c filler.c cut_token.c
OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIBFT := $(LIB_DIR)libft.a
LIBFT_INC := $(LIB_DIR)inc
LIBFT_FLAGS := -lftprintf -L $(LIB_DIR)

FLAGS := -Wall -Wextra -Werror
HEADER_FLAGS := -I inc/ -I $(LIB_DIR)inc/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(LIBFT_FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o:%.c
	@ mkdir -p obj
	@gcc $(FLAGS) $(HEADER_FLAGS) -c $< -o $@ 
$(LIBFT):
	@make -C $(LIB_DIR)

clean: 
	@$(RM) $(OBJ_DIR)
	@ make clean -C$(LIB_DIR)

fclean: clean
	@$(RM) $(NAME)
	@ make fclean -C $(LIB_DIR)
re: fclean all

vpath %.c $(SRC_DIR)