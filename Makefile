NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBMLX_DIR = mlx
LIBFT_DIR = Libft
LIBFT = Libft/libft.a
LIBMLX = libmlx.dylib
INC_DIR = incs
SRC_DIR = srcs
OBJS =  ${SRCS:.c=.o}
SRCS =  $(SRC_DIR)/main.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/render.c \
		$(SRC_DIR)/DDA.c \
		$(SRC_DIR)/raycasting.c \
		$(SRC_DIR)/screenbuffer.c \
		$(SRC_DIR)/img.c \
		$(SRC_DIR)/texture.c \
		$(SRC_DIR)/convert.c \
		$(SRC_DIR)/config.c \
		$(SRC_DIR)/hook/hook.c \
		$(SRC_DIR)/hook/key_action.c \
		$(SRC_DIR)/parse/parse_file.c \
		$(SRC_DIR)/parse/parse_line.c \
		$(SRC_DIR)/parse/parse_rgb.c \
		$(SRC_DIR)/parse/parse_texture.c \
		$(SRC_DIR)/parse/check_map_leaks.c \
		$(SRC_DIR)/parse/check_worldmap.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/utils/utils2.c \
		$(SRC_DIR)/utils/utils_lst.c \
		$(SRC_DIR)/utils/utils_map.c \
		$(SRC_DIR)/utils/mallocexit.c \
		$(SRC_DIR)/utils/get_next_line.c \
		$(SRC_DIR)/utils/get_next_line_utils.c \


# colors
BG_BLACK   = \033[40m
BG_RED     = \033[41m
BG_GREEN   = \033[42m
BG_YELLOW  = \033[43m
BG_BLUE    = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN    = \033[46m
BG_LGREY   = \033[47m
BG_DGREY   = \033[100m
BG_LRED    = \033[101m
BG_LGREEN  = \033[102m
BG_LYELLOW = \033[103m
BG_LBLUE   = \033[104m
BG_LMAGENTA= \033[105m
BG_LCYAN   = \033[106m
BG_WHITE   = \033[107m

FG_BLACK   = \033[30m
FG_RED     = \033[31m
FG_GREEN   = \033[32m
FG_YELLOW  = \033[33m
FG_BLUE    = \033[34m
FG_MAGENTA = \033[35m
FG_CYAN    = \033[36m
FG_LGREY   = \033[37m
FG_DGREY   = \033[90m
FG_LRED    = \033[91m
FG_LGREEN  = \033[92m
FG_LYELLOW = \033[93m
FG_LBLUE   = \033[94m
FG_LMAGENTA= \033[95m
FG_LCYAN   = \033[96m
FG_WHITE   = \033[97m

CL_BOLD   = \033[1m
CL_DIM    = \033[2m
CL_UDLINE = \033[4m
CL_BLINK  = \033[5m
CL_INVERT = \033[7m
CL_HIDDEN = \033[8m

NO_COLOR = \033[0m

all : $(NAME)

$(NAME) : $(LIBFT) $(LIBMLX) $(OBJS) link
	@$(CC) $(CFLAGS) \
	-L $(LIBMLX_DIR) -lmlx -framework OpenGL -framework Appkit -lz \
	-L $(LIBFT_DIR) -lft \
	$(OBJS) -o $@


$(SRC_DIR)/parse/%.o: $(SRC_DIR)/parse/%.c compile1
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIBMLX_DIR)

$(SRC_DIR)/utils/%.o: $(SRC_DIR)/utils/%.c compile2
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIBMLX_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c compile0
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIBMLX_DIR)


# libft compile
$(LIBFT) :
	@echo "${FG_DGREY}"
	@echo "Compiling Libft . . ."
	@echo "${NO_COLOR}"
	@$(MAKE) -C $(LIBFT_DIR) all

# libmlx compile
$(LIBMLX) :
	@echo "${FG_DGREY}"
	@echo "Compiling minilibX . . ."
	@echo "${NO_COLOR}"
	@$(MAKE) -C $(LIBMLX_DIR) all -s
	@cp $(LIBMLX_DIR)/libmlx.dylib ./

clean : cleanup
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@$(MAKE) -C $(LIBMLX_DIR) clean --silent
	@rm -rf $(OBJS)

fclean : clean fcleanup
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@rm -rf $(LIBMLX_DIR)/libmlx.dylib
	@rm -rf ./libmlx.dylib
	@rm -rf $(NAME)

re : fclean all



compile0 :
	@echo "${FG_LRED}"
	@echo "Compiling default sources . . ."
	@echo "${NO_COLOR}"

compile1 :
	@echo "${FG_LGREEN}"
	@echo "Compiling parse . . ."
	@echo "${NO_COLOR}"

compile2 :
	@echo "${FG_LYELLOW}"
	@echo "Compiling utils . . ."
	@echo "${NO_COLOR}"

compile3 :
	@echo "${FG_CYAN}"
	@echo "Compiling builtin . . ."
	@echo "${NO_COLOR}"

link :
	@echo "${FG_MAGENTA}"
	@echo "${CL_BOLD}Linking object files . . ."
	@echo "${NO_COLOR}"

cleanup :
	@echo "\n🗑  removing all object files . . ."

fcleanup :
	@echo "\n🗑  removing all binary files . . ."

.INTERMEDIATE : compile0 compile1 compile2 compile3 link cleanup fcleanup
