####################################### BEG ####

NAME        := philo

INCS        := \
			include \

SRC_DIR     := src
SRCS        := \
			main.c \
			philo.c \
			status.c \
			utils/utils.c

SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
INCFLAGS    := $(addprefix -I,$(INCS))

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory #-j #remove to see relink + flags silence 
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
	$(info CREATED $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	for f in $(dir ); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir ); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

.PHONY: clean fclean re
.SILENT: #remove to see relink + flags silence 

####################################### END ####
