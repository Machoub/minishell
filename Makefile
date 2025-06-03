# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gino <gino@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 18:34:39 by machouba          #+#    #+#              #
#    Updated: 2024/08/08 18:30:04 by gino             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	minishell
CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -g3


VAL_FLAGS	:=	--leak-check=full --show-leak-kinds=all --track-origins=yes \
				--suppressions=readline.supp


BIN_DIR 	:=	./bin
INC_DIR 	:=	./inc
LIBFT_DIR	:=	./libft

SRC_DIR		:=	./srcs
INIT_DIR	:=	$(SRC_DIR)/init
TOKEN_DIR	:=	$(SRC_DIR)/tokenizer
PARSING_DIR	:=	$(SRC_DIR)/parsing
EXEC_DIR	:=	$(SRC_DIR)/exec
UTILS_DIR	:=	$(SRC_DIR)/utils
BUILTINS_DIR:=	$(SRC_DIR)/builtins


LIBFT		:=	$(LIBFT_DIR)/libft.a


INITS		:=	$(INIT_DIR)/init.c \

TOKEN		:=	$(TOKEN_DIR)/expansion_utils2.c \
				$(TOKEN_DIR)/expansion_utils.c \
				$(TOKEN_DIR)/expand.c \
				$(TOKEN_DIR)/lexing.c \
				$(TOKEN_DIR)/token_utils.c \
				$(TOKEN_DIR)/token_check.c \
				$(TOKEN_DIR)/token.c

PARSERS		:=	$(PARSING_DIR)/parse_args.c \
				$(PARSING_DIR)/envs_utils.c \
				$(PARSING_DIR)/parse_utils.c \
				$(PARSING_DIR)/parse_infile.c \
				$(PARSING_DIR)/parse_outfile.c \
				$(PARSING_DIR)/parse_envs.c \
				$(PARSING_DIR)/parse_cmd.c

EXECS		:=	$(EXEC_DIR)/exec.c \
				$(EXEC_DIR)/exec_utils.c \
				$(EXEC_DIR)/exec_utils2.c \
				$(EXEC_DIR)/hd.c \
				$(EXEC_DIR)/hd_utils.c \
				$(EXEC_DIR)/hd_utils2.c \
				$(EXEC_DIR)/hd_utils3.c \
				$(EXEC_DIR)/pipe.c \
				$(EXEC_DIR)/redir.c \
				$(EXEC_DIR)/singel_cmd.c \
				$(EXEC_DIR)/x_cmds.c \
				$(EXEC_DIR)/x_cmds_utils.c \

BUILTINS	:=	$(BUILTINS_DIR)/ft_echo.c \
				$(BUILTINS_DIR)/ft_env.c \
				$(BUILTINS_DIR)/ft_exit.c \
				$(BUILTINS_DIR)/ft_export.c \
				$(BUILTINS_DIR)/ft_pwd.c \
				$(BUILTINS_DIR)/ft_unset.c \
				$(BUILTINS_DIR)/ft_cd.c \
				$(BUILTINS_DIR)/builtins_utils.c \
				$(BUILTINS_DIR)/export_utils.c \
				$(BUILTINS_DIR)/export_utils2.c \
				$(BUILTINS_DIR)/export_utils3.c \
				
UTILS	:=		$(UTILS_DIR)/free_next.c \
				$(UTILS_DIR)/free.c \
				$(UTILS_DIR)/ft_errors.c \
				$(UTILS_DIR)/utils.c \
				$(UTILS_DIR)/utils2.c \
				$(UTILS_DIR)/utils3.c				

SRC			:=	$(SRC_DIR)/main.c $(INITS) $(TOKEN) \
				$(PARSERS) $(EXECS) $(UTILS) $(BUILTINS)
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

READLINE_INC = -I/usr/local/opt/readline/include
READLINE_LIB = -L/usr/local/opt/readline/lib -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) -I $(INC_DIR) $(OBJ) $(LIBFT) $(READLINE_LIB) $(READLINE_INC) -o $(NAME)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INC_DIR) $(READLINE_INC) -c $< -o $@


# libft
$(LIBFT):
	@make -C ./libft

# Clean Objects
clean:
	@make -C ./libft clean
	rm -rf $(BIN_DIR)
	@echo "binary files cleaned !"

# Full Clean, Objects and Binaries
fclean: clean
	@make -C ./libft fclean
	rm -f $(NAME)
	@echo "exec files cleaned !"

# Remake
re: fclean $(NAME)
	@echo "Cleaned and rebuilt everything !"

# Norminette
norm:
	@norminette $(SRC) $(INC_DIR)/*.h

# Valgrind
val: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)

# Non-File Targets
.PHONY:	all clean fclean re norm val