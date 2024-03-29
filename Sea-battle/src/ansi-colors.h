#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_PURPLE "\033[35m"
#define COLOR_LIGHT_BLUE "\033[36m"

#define BACKGROUND_COLOR_RED "\033[41m"
#define BACKGROUND_COLOR_GREEN "\033[48;5;22m"
#define BACKGROUND_COLOR_BLUE "\033[44m"
#define BACKGROUND_COLOR_PURPLE "\033[45m"

#define COLOR_BOLD "\033[1m"
#define COLOR_RESET "\033[0m"

#define TEXT_RED(str) COLOR_RED COLOR_BOLD str COLOR_RESET
#define TEXT_GREEN(str) COLOR_GREEN COLOR_BOLD str COLOR_RESET
#define TEXT_YELLOW(str) COLOR_YELLOW COLOR_BOLD str COLOR_RESET
#define TEXT_BLUE(str) COLOR_BLUE COLOR_BOLD str COLOR_RESET
#define TEXT_PUROLE(str) COLOR_PURPLE COLOR_BOLD str COLOR_RESET
#define TEXT_LIGHT_BLUE(str) COLOR_LIGHT_BLUE COLOR_BOLD str COLOR_RESET

#define TEXT_BACKGROUND_RED(str) BACKGROUND_COLOR_RED COLOR_BOLD str COLOR_RESET
#define TEXT_BACKGROUND_GREEN(str) BACKGROUND_COLOR_GREEN COLOR_BOLD str COLOR_RESET
#define TEXT_BACKGROUND_BLUE(str) BACKGROUND_COLOR_BLUE COLOR_BOLD str COLOR_RESET
#define TEXT_BACKGROUND_PURPLE(str) BACKGROUND_COLOR_PURPLE COLOR_BOLD str COLOR_RESET