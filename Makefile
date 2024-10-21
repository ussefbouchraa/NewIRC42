NAME			= ircserv

SRC				= main.cpp					\
				utils/tools.cpp				\
				classes/Server.cpp			\
				classes/Client.cpp			\
				classes/Message.cpp			\
				classes/Channel.cpp			\
				classes/Commands.cpp		\
					
DIR_SRC		= src/
DIR_OBJ		= obj/
DIR_INC		= inc/
OBJ			= ${SRC:%.cpp=${DIR_OBJ}%.o}
CXX			= c++ 
DEP			= ${OBJ:%.o=%.d}
CPPFLAGS	=  -c -I ${DIR_INC} 
RM 			= rm -f
RMDIR		= rm -rf

all: ${NAME}

${NAME} : ${OBJ}
	${CXX} -Wall -Wextra -Werror  $^ -o $@

${OBJ} : ${DIR_OBJ}%.o: ${DIR_SRC}%.cpp
	mkdir -p ${@D}
	${CXX} ${CPPFLAGS} $< -o $@

-include ${DEP}

clean:
	${RMDIR} ${DIR_OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re