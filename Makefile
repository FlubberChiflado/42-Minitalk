# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcespede <fcespede@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 12:56:54 by fcespede          #+#    #+#              #
#    Updated: 2023/03/04 13:33:54 by fcespede         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER		= minitalk.h ./libft/libft.a
NAME		= minitalk.a
BON			= .bonus
FILES		= client.c server.c
B_FILES		= client_bonus.c server_bonus.c

CFLAGS		= -Wall -Werror -Wextra
DFLAGS		= -MT $@ -MMD -MP

INCLUDE		= -I./
OBJ_DIR		= .obj/
LIB_DIR		= -C libft/

RM			= rm -rf
LIB			= libft/libft.a

OBJ			= $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
B_OBJ		= $(addprefix $(OBJ_DIR)/, $(B_FILES:.c=.o))
	
DEP			= $(addsuffix .d, $(basename $(OBJ)))
B_DEP		= $(addsuffix .d, $(basename $(B_OBJ)))

$(OBJ_DIR)/%.o: %.c $(HEADER) Makefile 
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@
	@$(CC) $(CFLAGS) -o $(basename $<) $< $(LIB)
	@echo "\033[0;35m$< has been compiled!"

all: $(LIB)
	@$(MAKE) $(NAME)

$(LIB)::
	@$(MAKE) bonus $(LIB_DIR)

$(NAME):: $(OBJ) #client server
	@ar -rcs $(NAME) $(OBJ)

$(NAME)::
	@echo "\033[0;35mNothing more to be done (Minitalk)"

bonus: $(LIB)
	@$(MAKE) $(BON)

$(BON): $(OBJ) $(B_OBJ)
	@ar -rcs $(NAME) $^

-include $(DEP)

clean:
	@$(RM) client
	@$(RM) server
	@$(RM) client_bonus
	@$(RM) server_bonus
	@$(RM) $(OBJ_DIR)
	@$(MAKE) clean $(LIB_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean $(LIB_DIR)

re:
	@$(MAKE) fclean
	@$(MAKE)

.PHONY: all clean fclean re
