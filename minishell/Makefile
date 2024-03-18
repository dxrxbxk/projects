#
#
#                          M A K E F I L E
################################################################################

.DELETE_ON_ERROR:
.DEFAULT_GOAL			:=	all
SHELL					:=	$(shell which zsh)
.SHELLFLAGS				:=	-eu -o pipefail -c

### A S C I I   A R T ##########################################################

ART_NAME_1				=	█▀▄▀█ █ █▄░█ █ █▀ █░█ █▀▀ █░░ █░░\n
ART_NAME_2				=	█░▀░█ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▄ █▄▄\n

ART_BONUS_1				=   █▄▄ █▀█ █▄░█ █░█ █▀\n
ART_BONUS_2				=   █▄█ █▄█ █░▀█ █▄█ ▄█\n

ART_CLN1				=   █▀▀ █░░ █▀▀ ▄▀█ █▄░█\n
ART_CLN2				=   █▄▄ █▄▄ ██▄ █▀█ █░▀█\n

### D I S P L A Y   F U N C T I O N ############################################

Progress	=	ProgressBar() {												\
	name=$$1 ;																\
	if [ $$name = $(lastword $(FILES)) ] ; then name="[DONE]" ; fi ;		\
	progress=`echo "($(COUNT)*100)/$(words $(FILES))" | bc`;				\
	done=`echo "($$progress*3)/10" | bc` ;									\
	left=`echo "30-$$done" | bc` ;											\
	fill=`printf "%*s" $$done | sed 's/ /█/g'` ;							\
	empty=`printf "%*s" $$left | sed 's/ /█/g'` ;							\
	if [ $(COUNT) = 1 ] ; then line=" $(CC_WHITE)Compiling source files	: \n\n" ; fi ;\
	line+="\r\e[0K $(CC_GREEN)$$fill$(CC_RED)$$empty$(RESET) $(CC_WHITE)$$progress%	\
	 $(CC_GREEN)$$name$(RESET)" ;											\
	echo -n $$line															\
	$(eval COUNT = $(shell echo $$(($(COUNT) + 1)))) }

define PRINT_ASCII_ART
	printf "\n $(1)$(2)$(RESET) $(3)$(4)$(RESET)\n"
endef

### C O L O R S ################################################################

COUNT					=	1
CC_GREEN				=	\e[38;5;46;1m
CC_RED					=	\e[31;1m
CC_WHITE				=	\e[38;5;15;1m
YELLOW					=	\e[38;5;3m
PURPLE1					=	\e[38;2;113;31;149m
PURPLE2					=	\e[38;2;101;25;134m
GREEN1					=	\e[38;5;46m
GREEN2					=	\e[38;2;0;235;0m
RED1					=	\e[38;5;196m
RED2					=	\e[38;5;160m
RESET					=	\e[0m
LINE_CLN				=	\r\e[0K\e[2A

### D I R E C T O R Y ' S ######################################################

NAME					:=	minishell
NAME_BONUS				:=	minishell_bonus

override FILES			:=	$(addsuffix .c,				\
							main						\
							get_input					\
							parsing						\
							lexer						\
							token						\
							parser						\
							states_1					\
							states_2					\
							expand						\
							ft_tokencat					\
							ft_usual_dollar_expand		\
							ft_wildcards_expand			\
							ft_dollar_expand			\
							ft_quotes_expand			\
							ft_dquotes_dollar_expand	\
							ft_squotes_dollar_expand	\
							ast_init					\
							ast_utils_1					\
							ast_utils_2					\
							ast_add_cmd_seq				\
							pwd							\
							export						\
							unset						\
							ft_env						\
							cd							\
                            exit						\
                            echo						\
							execution					\
							ft_find_cmd_path			\
							manage_redirections			\
							redirections_utils			\
							ft_wait_children			\
							manage_child				\
							child_utils					\
							exec_child					\
							ft_interpret_child_status	\
							manage_pipe_fds				\
							exec_pipe_child				\
							manage_pipe_child			\
							pipe_redirections			\
							set_heredoc_files			\
							apply_heredoc				\
							heredoc_child				\
							manage_builtins				\
							exec_builtins				\
							builtins_redirections		\
							exec_utils					\
							env							\
							env_utils_1					\
							env_utils_2					\
							env_utils_3					\
							signals						\
							ft_unlink_tmp_file			\
							ft_free_ast					\
							ft_free_children			\
							ft_free_data				\
							ft_free_ast_child			\
							ft_free_token_lst			\
							ft_free_env					\
							ft_memptr					\
							utils						\
							ft_strrchr					\
							ft_isalnum					\
							ft_strcpy					\
							ft_calloc					\
							free_tab					\
							ft_isdigit					\
							ft_bzero					\
							ft_mega_join				\
							ft_strcat					\
							ft_strchr					\
							ft_putendl_fd				\
							ft_findi					\
							ft_putchar_fd				\
							ft_swap_str					\
							ft_strncmp					\
							ft_strlcpy					\
							ft_strcmp					\
							ft_strndup					\
							ft_lst_to_tab				\
							ft_split					\
							ft_atoi						\
							ft_strdup					\
							ft_strjoin					\
							ft_isalpha					\
							get_next_line				\
							ft_strlen					\
							ft_error					\
							ft_itoa						\
							ft_putstr_fd				\
							ft_putstr_fdr				\
							ft_words_count				\
							ft_strlcat)

SRCDIR					:=	src
INCDIR					:=	inc
OBJDIR					:=	_obj
DEPDIR					:=	_dep
UTLDIR					:=	.utils

### C O M P I L E R   F L A G S ################################################

CC						:=	cc
STD						:=	-std=gnu99
CFLAGS					:=	-Wall -Wextra -Werror -g3
IFLAGS					:=	-I$(INCDIR)
LFLAGS					:=	-lreadline
LDFLAGS					?=	-MMD -MF

override MKDIR			:=	mkdir -pv
override RM				:=	rm -rvf

### P A T T E R N   R U L E S ##################################################

override SUB			:=	$(shell find $(SRCDIR) -type d)
override OBJ			:=	$(FILES:%.c=$(OBJDIR)/%.o)
override OBJ_BONUS		:=	$(FILES:%.c=$(OBJDIR)/bonus_%.o)
override DEP			:=	$(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ))
override DEP_BONUS		:=	$(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ_BONUS))

### U T I L I T Y ##############################################################

.SECONDEXPANSION:
DEL_BONUS_PREFIX = $$(subst bonus_,,%)

### C O M P I L A T I O N   F U N C T I O N ####################################

#$(OBJDIR)/%.o:	$(1)/$$(subst bonus_,,%).c | $(OBJDIR) $(DEPDIR)
define COMPILE_RULE
$(OBJDIR)/%.o:	$(1)/$$(DEL_BONUS_PREFIX).c | $(OBJDIR) $(DEPDIR)
	@$$(CC) $$(STD) $$(IFLAGS) $$(CFLAGS) $$(DFLAGS)	\
	-c $$< -o $$@									\
	-MMD -MF $$(DEPDIR)/$$(*F).d
	@$$(Progress) ; ProgressBar $$(shell basename $$<)
endef

### R E C I P E S ##############################################################

.PHONY:	all bonus clean bclean fclean re

all: $(NAME)

bonus: bonusflag $(NAME_BONUS)

$(NAME): $(OBJ)
	@$(CC) $^ $(LFLAGS) -o $@
	@printf "\n\n $(CC_WHITE)Creating binary	: $(CC_GREEN)%s$(RESET)\n" $(NAME)
	@$(call PRINT_ASCII_ART,$(PURPLE1),$(ART_NAME_1),$(PURPLE2),$(ART_NAME_2))

$(NAME_BONUS): $(OBJ_BONUS)
	@$(CC) $^ $(LFLAGS) -o $@
	@printf "\n\n $(CC_WHITE)Creating bonus binary	: $(CC_GREEN)%s$(RESET)\n" $(NAME)
	@$(call PRINT_ASCII_ART,$(GREEN1),$(ART_BONUS_1),$(GREEN2),$(ART_BONUS_2))

bonusflag:
	$(eval DFLAGS := -D BONUS) 

-include $(DEP) $(DEP_BONUS)
$(foreach DIR, $(SUB), $(eval $(call COMPILE_RULE,$(DIR))))

$(OBJDIR) $(DEPDIR):
	@$(if $(findstring $@,$(OBJDIR)),$(eval MSG=object))
	@$(if $(findstring $@,$(DEPDIR)),$(eval MSG=dependency))
	@printf " $(CC_WHITE)Creating %s directory	: $(RESET)$(YELLOW)" $(MSG)
	@$(MKDIR) $@
	@printf "$(RESET)"

clean:	;
	@printf " $(CC_WHITE)Deleting object files	: $(CC_RED)\e[31;9m*.o *.d\n"	
	@$(RM) $(OBJDIR) $(DEPDIR) rl_leaks.txt
	@printf "$(RESET)"

bclean:
	@printf " $(CC_WHITE)Deleting binary files	: $(CC_RED)\e[31;9m$(NAME) $(NAME_BONUS)\n"
	@$(RM) $(NAME) $(NAME_BONUS)
	@printf "$(RESET)"

fclean:	clean bclean
	@$(call PRINT_ASCII_ART,$(RED1),$(ART_CLN1),$(RED2),$(ART_CLN2))

leaks:
	@echo -e "{\nleak readline\nMemcheck:Leak\n...\nfun:readline\n}\n{\nleak add_history\nMemcheck:Leak\n...\nfun:add_history\n}" > rl_leaks.txt

kamikaze:
	@clear
	@(cd $(UTLDIR) ; ./kamikaze.sh)
	@$(RM) ../$(shell basename `pwd`) ; pkill cat ; clear

re:		fclean all
