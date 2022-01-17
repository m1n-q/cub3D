#ifndef MAP_H
# define MAP_H


# include <fcntl.h>

#define RET_CLEAR 1
#define RET_ERROR 0
#define RET_EOF	  -1


# define NO				0	// north wall texture
# define SO				1	// 			"
# define WE				2	// 			"
# define EA				3	// 			"
// RGB
# define FLOOR			4	// floor rgb
# define CEILI			5	// ceilling rgb
// 
# define UN_DEF			6  // undefine

//# define P_SKY		"\x1b[1;34m"
# define P_RED		"\x1b[31m"
# define P_RESET	"\x1b[0m"





#endif