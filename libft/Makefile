# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: machouba <machouba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 15:02:54 by machouba          #+#    #+#              #
#    Updated: 2024/09/04 14:42:45 by machouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME			= libft.a

# Directories
INC				= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/

# Compielr and Flags
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I
RM				= rm -f
AR				= ar rcs

# Source Files
FTIS_DIR		=	$(SRC_DIR)/ft_isalnum.c \
					$(SRC_DIR)/ft_isalpha.c \
					$(SRC_DIR)/ft_isascii.c \
					$(SRC_DIR)/ft_isdigit.c \
					$(SRC_DIR)/ft_isprint.c 

FTMEM_DIR		=	$(SRC_DIR)/ft_bzero.c \
					$(SRC_DIR)/ft_calloc.c \
					$(SRC_DIR)/ft_memchr.c \
					$(SRC_DIR)/ft_memcmp.c \
					$(SRC_DIR)/ft_memmove.c \
					$(SRC_DIR)/ft_memset.c 

FTPUT_DIR		=	$(SRC_DIR)/ft_putchar_fd.c \
					$(SRC_DIR)/ft_putendl_fd.c \
					$(SRC_DIR)/ft_putnbr_fd.c \
					$(SRC_DIR)/ft_putstr_fd.c 

FTTO_DIR		=	$(SRC_DIR)/ft_atoi.c \
					$(SRC_DIR)/ft_itoa.c \
					$(SRC_DIR)/ft_tolower.c \
					$(SRC_DIR)/ft_toupper.c

FTSTR_DIR		=	$(SRC_DIR)/ft_split.c \
					$(SRC_DIR)/ft_strchr.c \
					$(SRC_DIR)/ft_strdup.c \
					$(SRC_DIR)/ft_striteri.c \
					$(SRC_DIR)/ft_strjoin.c \
					$(SRC_DIR)/ft_strlcat.c \
					$(SRC_DIR)/ft_strlcpy.c \
					$(SRC_DIR)/ft_strlen.c \
					$(SRC_DIR)/ft_strmapi.c \
					$(SRC_DIR)/ft_strnstr.c \
					$(SRC_DIR)/ft_strrchr.c \
					$(SRC_DIR)/ft_strtrim.c \
					$(SRC_DIR)/ft_strcmp.c \
					$(SRC_DIR)/ft_strncmp.c \
					$(SRC_DIR)/ft_strstr.c \
					$(SRC_DIR)/ft_substr.c \
					$(SRC_DIR)/ft_strbrk.c \
					$(SRC_DIR)/ft_free_tab.c \

FTLST_DIR		=	$(SRC_DIR)/ft_lstadd_back.c \
					$(SRC_DIR)/ft_lstadd_front.c \
					$(SRC_DIR)/ft_lstclear.c \
					$(SRC_DIR)/ft_lstdelone.c \
					$(SRC_DIR)/ft_lstiter.c \
					$(SRC_DIR)/ft_lstlast.c \
					$(SRC_DIR)/ft_lstmap.c \
					$(SRC_DIR)/ft_lstnew.c \
					$(SRC_DIR)/ft_lstsize.c 

FTPRINTF_DIR	=	$(SRC_DIR)/ft_printf.c \
					$(SRC_DIR)/ft_putchar.c \
					$(SRC_DIR)/ft_puthexa.c \
					$(SRC_DIR)/ft_putnbr.c \
					$(SRC_DIR)/ft_putptr.c \
					$(SRC_DIR)/ft_putstr.c	\
					$(SRC_DIR)/ft_putunbr.c \

GNL_DIR			=	$(SRC_DIR)/get_next_line.c \
# Concatenate all source files
SRC 			= $(FTIS_DIR) $(FTMEM_DIR) $(FTPUT_DIR) $(FTTO_DIR) $(FTTO_DIR) $(FTSTR_DIR) $(FTLST_DIR) $(FTPRINTF_DIR) $(GNL_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Build rules
all: 			$(NAME)

$(NAME): 		$(OBJ)
				@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)
				@$(RM) .cache_exists

fclean: 		clean
				@$(RM) $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re