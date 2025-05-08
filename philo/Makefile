NAME			= philo

INC_DIR			= ./includes/
SRC_DIR			= ./src/
OBJ_DIR			= ./obj/
SRCS			= $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS			= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRCS:.c=.o))

RM				= rm -rf
CC				= cc
CFLAGS			= -O3 -Wall -Wextra -Werror
CDEBUG			= -g3 -O0 -Wall -Wextra -Werror -D DEBUG=true
IFLAGS			= -I$(INC_DIR)
VOPTIONS		= --track-origins=yes --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-fds=yes --trace-children=yes --errors-for-leak-kinds=all

GR				= \e[92m
B				= \e[94m
G				= \e[90m
C				= \e[96m
IT				= \e[3m
NC				= \e[0m
BSIZE			= 50
TFILES			= $(words $(SRCS))
CFILES			= 0

ifeq ($(origin ARG), undefined)
ARG				:= "5 180 60 60 10"
endif
ARG_LIST		= $(shell echo $(ARG))


all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)
				@$(eval CFILES := $(shell echo $$(($(CFILES)+1))))
				@echo -n "⚙️ ["
				@for i in `seq 1 $(shell echo "$$(($(CFILES)*$(BSIZE)/$(TFILES)))")`; do \
					echo -n "$(GR)▆$(NC)" ; \
				done
				@for i in `seq 1 $(shell echo "$$(($(BSIZE)-$(CFILES)*$(BSIZE)/$(TFILES)))")`; do \
					echo -n "$(G)▆$(NC)" ; \
				done
				@echo -n "] $(shell echo "scale=2; $(CFILES)/$(TFILES) * 100" | bc)% [$(CFILES)/$(TFILES)] ➜ $(notdir $<)"
				@echo -n "\e[0K\r"

$(NAME):		title $(OBJS)
				@MSG=$$( \
					if [ -f "$(NAME)" ]; then \
						NEWER=$$(find . -name '*.c' -newer $(NAME) -o -name '*.h' -newer $(NAME)); \
						if [ -z "$$NEWER" ]; then \
							echo "⚠️ No changes detected, no need for compilation."; \
						else \
							echo "✅ Compilation completed."; \
						fi; \
					else \
						echo "✅ Compilation completed."; \
					fi \
				); \
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS); \
				echo -n "\e[0K\r"; \
				echo "$$MSG"

clean:
				@$(RM) $(OBJ_DIR) $(OBJ_BONUS_DIR)
				@clear
				@echo "🆑 Clean completed."

fclean:			clean
				@$(RM) $(NAME) $(NAME_BONUS)
				@clear
				@echo "✴️ Full clean completed."

re:				fclean all
				@echo -n "\e[1A\e[0K\r"
				@echo "🔄 Recompilation completed."

run:			all
				@echo "🚀 Running $(NAME).."
				@./$(NAME) $(ARG_LIST)

cdebug:			CFLAGS = $(CDEBUG)
cdebug:			fclean title $(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
				@echo -n "\e[0K\r"
				@echo "✅ Compilation completed."

debug:			cdebug
				@echo "🚧 Running $(NAME) in debug mode.."
				@valgrind $(VOPTIONS) ./$(NAME) $(ARG_LIST)

forbidden:		all
				@nm $(NAME) | grep U

norminette:
				@norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR) > norminette.log 2>&1 || true
				@if grep -qE "Error|Warning" norminette.log; then \
					grep -E "Error|Warning" norminette.log; \
				else \
					echo "Norme: $(GR)OK!$(NC)"; \
				fi
				@$(RM) norminette.log

title:
				@clear
				@echo ""
				@echo "$(B)██████$(G)╗ $(B)██$(G)╗  $(B)██$(G)╗$(B)██$(G)╗$(B)██$(G)╗      $(B)██████$(G)╗ $(B)███████$(G)╗ $(B)██████$(G)╗ $(B)██████$(G)╗ $(B)██$(G)╗  $(B)██$(G)╗$(B)███████$(G)╗$(B)██████$(G)╗ $(B)███████$(G)╗"
				@echo "$(B)██$(G)╔══$(B)██$(G)╗$(B)██$(G)║  $(B)██$(G)║$(B)██$(G)║$(B)██$(G)║     $(B)██$(G)╔═══$(B)██$(G)╗$(B)██$(G)╔════╝$(B)██$(G)╔═══$(B)██$(G)╗$(B)██$(G)╔══$(B)██$(G)╗$(B)██$(G)║  $(B)██$(G)║$(B)██$(G)╔════╝$(B)██$(G)╔══$(B)██$(G)╗$(B)██$(G)╔════╝"
				@echo "$(B)██████$(G)╔╝$(B)███████$(G)║$(B)██$(G)║$(B)██$(G)║     $(B)██$(G)║   $(B)██$(G)║$(B)███████$(G)╗$(B)██$(G)║   $(B)██$(G)║$(B)██████$(G)╔╝$(B)███████$(G)║$(B)█████$(G)╗  $(B)██████$(G)╔╝$(B)███████$(G)╗"
				@echo "$(B)██$(G)╔═══╝ $(B)██$(G)╔══$(B)██$(G)║$(B)██$(G)║$(B)██$(G)║     $(B)██$(G)║   $(B)██$(G)║╚════$(B)██$(G)║$(B)██$(G)║   $(B)██$(G)║$(B)██$(G)╔═══╝ $(B)██$(G)╔══$(B)██$(G)║$(B)██$(G)╔══╝  $(B)██$(G)╔══$(B)██$(G)╗╚════$(B)██$(G)║"
				@echo "$(B)██$(G)║     $(B)██$(G)║  $(B)██$(G)║$(B)██$(G)║$(B)███████$(G)╗╚$(B)██████$(G)╔╝$(B)███████$(G)║╚$(B)██████$(G)╔╝$(B)██$(G)║     $(B)██$(G)║  $(B)██$(G)║$(B)███████$(G)╗$(B)██$(G)║  $(B)██$(G)║$(B)███████$(G)║"
				@echo "$(G)╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ $(NC)"
				@echo "$(G)$(IT)Part:	 $(C)Bonus$(NC)"
				@echo "$(G)$(IT)Authors: $(C)FonWasH $(G)($(C)juperez$(G))$(NC)"
				@echo ""

-include 		$(OBJS:.o=.d)
.PHONY: 		all clean fclean re run debug forbidden norminette title