# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by ysabik            #+#    #+#              #
#    Updated: 2024/10/07 11:14:48 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= gcc
CFLAGS				= -Werror -Wall -Wextra -g
NAME				= ft_ls
INCLUDES			= ./includes
SRC_FILES			= \
						srcs/main.c \
						srcs/flags.c \
						srcs/exec/analyse_dir.c \
						srcs/exec/analysis_utils.c \
						srcs/exec/exec.c \
						srcs/exec/normalise_entries.c \
						srcs/exec/print_entries.c \
						srcs/exec/print_entries_lines.c \
						srcs/exec/set_dir_formats.c \
						srcs/exec/sort_entries.c \
						srcs/parsing/parse_long_option.c \
						srcs/parsing/parse_short_options.c \
						srcs/parsing/parsing.c \
						srcs/utils/dir.c \
						srcs/utils/entry.c \
						srcs/utils/error.c \
						srcs/utils/ft_isalnum.c \
						srcs/utils/ft_itoa.c \
						srcs/utils/ft_malloc.c \
						srcs/utils/ft_strcmp.c \
						srcs/utils/ft_strdup.c \
						srcs/utils/ft_strjoin.c \
						srcs/utils/ft_strlen.c \
						srcs/utils/ft_toupper.c \
						srcs/utils/get_time.c \
						srcs/utils/join_path.c \
						srcs/utils/remove_diacritics.c \
						srcs/utils/strlst.c \
						srcs/utils/ulina.c \
						srcs/utils/undiacritics.c \

BUILD_FOLDER		= ./build

FTPRINTF_FOLDER		= ./42-ft_printf
FTPRINTF_A			= $(FTPRINTF_FOLDER)/libftprintf.a
FTPRINTF_FLAGS		= -L $(FTPRINTF_FOLDER) -lftprintf -I $(FTPRINTF_FOLDER)

C_RESET				= \033[0m
C_BOLD				= \033[1m
C_DIM				= \033[2m
C_UNDERLINE			= \033[4m
C_BLINK				= \033[5m
C_BLACK				= \033[30m
C_RED				= \033[31m
C_GREEN				= \033[32m
C_YELLOW			= \033[33m
C_BLUE				= \033[34m
C_MAGENTA			= \033[35m
C_CYAN				= \033[36m
C_WHITE				= \033[37m

OBJ_FILES			= $(SRC_FILES:.c=.o)
BUILD_FILES			= $(addprefix $(BUILD_FOLDER)/, $(OBJ_FILES))

TO_COMPILE			= 0

all : $(NAME)

$(NAME) : $(BUILD_FILES)
	@echo ""
	@echo -n "  > $(C_YELLOW)$(C_BOLD)./$(NAME)$(C_RESET):  $(C_DIM)"
	$(CC) $(CFLAGS) -o $(NAME) $(BUILD_FILES) -I $(INCLUDES) $(FTPRINTF_FLAGS)
	@echo "$(C_RESET)"
	@echo ""
	@echo -n "$(C_BOLD)$(C_MAGENTA)>$(C_BLUE)>$(C_CYAN)>$(C_GREEN)"
	@echo -n " Compilation success ! "
	@echo "$(C_CYAN)<$(C_BLUE)<$(C_MAGENTA)<$(C_RESET)"
	@echo ""

m_line_break :
	@echo ""

b_flags :
	@$(eval CFLAGS += -D BONUS=1)

bonus : b_flags all

$(FTPRINTF_A) :
	@echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Compiling $(C_YELLOW)$(FTPRINTF_A)$(C_CYAN)... :$(C_RESET)"
	@echo ""
	@make -C $(FTPRINTF_FOLDER)
	@echo "$(C_RESET)"
	@echo ""

$(BUILD_FOLDER)/%.o : %.c | $(FTPRINTF_A)
	@if [ $(TO_COMPILE) -eq 0 ] ; then \
		echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)" ; \
		echo "Compiling $(C_YELLOW)./$(NAME)$(C_CYAN)... :$(C_RESET)" ; \
		echo "" ; \
	fi
	@$(eval TO_COMPILE := 1)
	@echo -n "  - $(C_GREEN)$<$(C_RESET):  $(C_DIM)"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES) $(FTPRINTF_FLAGS)
	@echo -n "$(C_RESET)"

define del =
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Deleting files... :$(C_RESET)$(C_RED)"
	@\
	l=-1 ; \
	for file in $(1) ; do \
		if [ $${#file} -gt $$l ] ; then \
			l=$${#file} ; \
		fi ; \
	done ; \
	cols=$$((64 / $$l)) ; \
	i=0 ; \
	for file in $(1) ; do \
		if [ $$i -eq 0 ] ; then \
			echo -n "    " ; \
		fi ; \
		if [ "$$file" = "./$(NAME)" ] ; then \
			printf "$(C_YELLOW)%-$$((l))s  $(C_RED)" "$$file" ; \
		else \
			printf "%-$$((l))s  " "$$file" ; \
		fi ; \
		if [ $$i -gt $$cols ] ; then \
			echo "" ; \
			i=-1; \
		fi ; \
		i=$$(($$i + 1)); \
	done ; \
	if [ $$i -ne -1 ] ; then \
		echo "" ; \
	fi
	@echo "$(C_RESET)"
endef

clean :
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Cleaning $(FTPRINTF_FOLDER)... :$(C_RESET)$(C_DIM)"
	@make -C $(FTPRINTF_FOLDER) clean
	@echo "$(C_RESET)"
	$(call del, "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(BUILD_FILES) $(BUILD_FOLDER)

fclean :
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "FCleaning $(FTPRINTF_FOLDER)... :$(C_RESET)$(C_DIM)"
	@make -C $(FTPRINTF_FOLDER) fclean
	@echo "$(C_RESET)"
	$(call del, "./$(NAME)" "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(NAME) $(BUILD_FILES) $(BUILD_FOLDER)

re : fclean m_line_break all

re_bonus : fclean m_line_break bonus

soft_clean :
	$(call del, "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(BUILD_FILES) $(BUILD_FOLDER)

soft_fclean :
	$(call del, "./$(NAME)" "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(NAME) $(BUILD_FILES) $(BUILD_FOLDER)

soft_re : soft_fclean m_line_break all

soft_re_bonus : soft_fclean m_line_break bonus

.PHONY : all bonus clean fclean re re_bonus \
			soft_clean soft_fclean soft_re soft_re_bonus \
			m_line_break b_flags
