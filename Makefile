CC = clang++
CFLAGS = -Werror -Wall -Wextra -std=c++11 -g

NAME = expertSystem

SRC_PATH = ./srcs
INCLUDES = -I ./headers


SRC =   $(SRC_PATH)/main.cpp\
        $(SRC_PATH)/Node.class.cpp\
        $(SRC_PATH)/Parser.class.cpp\
        $(SRC_PATH)/Lexer.class.cpp\
        $(SRC_PATH)/ParsedNode.class.cpp\
        $(SRC_PATH)/Fact.class.cpp\
        $(SRC_PATH)/FactBase.class.cpp\
        $(SRC_PATH)/Rule.class.cpp\
        $(SRC_PATH)/RuleBase.class.cpp\
        $(SRC_PATH)/Motor.class.cpp\
        $(SRC_PATH)/Operand.class.cpp\

OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re