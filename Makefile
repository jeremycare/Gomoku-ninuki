NAME		= gomoku_ninuki

SRC		= src/main.cpp	\
		  src/Goban.cpp \
		  src/Tree.cpp	\
		  src/AI.cpp	\
		  src/Controller.cpp	\
		  src/Print.cpp \
		  src/Rave.cpp \
		  src/SFMLGUI/SFMLGUI.cpp \
		  src/SFMLGUI/SFMLGUIBackGround.cpp \
		  src/SFMLGUI/SFMLGUIClickableSprite.cpp \
		  src/SFMLGUI/SFMLGUIClickableText.cpp \
		  src/SFMLGUI/SFMLGUIComposition.cpp \
		  src/SFMLGUI/SFMLGUIDynamicSprite.cpp \
		  src/SFMLGUI/SFMLGUIDynamicText.cpp \
		  src/SFMLGUI/SFMLGUIGameBoard.cpp \
		  src/SFMLGUI/SFMLGUISettingsMenu.cpp \
		  src/SFMLGUI/SFMLGUIMessageLayout.cpp \
		  src/SFMLGUI/SFMLGUIStaticText.cpp \
		  src/SFMLGUI/SFMLGUIStaticSprite.cpp \
		  src/SFMLGUI/SFMLGUIGameHUI.cpp \
		  src/GameInfos.cpp \
		  src/GameSettings.cpp \
		  src/thread.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	= -g3 -W -Wall -Wextra -std=c++11 -Iinclude -Ilib/ctpl -Iinclude/SFMLGUI -lsfml-graphics -lsfml-window -lsfml-system -pthread -lprofiler
CXX		= g++

RM		= rm -f

all		: $(NAME)

$(NAME)		: $(OBJ)
		$(CXX) $(OBJ) $(CXXFLAGS) -o $(NAME)

clean	:
		$(RM) $(OBJ)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all