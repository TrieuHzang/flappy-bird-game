CFLAGS		+= -I./sources/app/screens
CPPFLAGS	+= -I./sources/app/screens

VPATH += sources/app/screens

# CPP source files
SOURCES_CPP += sources/app/screens/screens_bitmap.cpp
SOURCES_CPP += sources/app/screens/scr_idle.cpp
SOURCES_CPP += sources/app/screens/scr_qrcode.cpp
SOURCES_CPP += sources/app/screens/scr_startup.cpp
SOURCES_CPP += sources/app/screens/scr_welcome.cpp
SOURCES_CPP += sources/app/screens/scr_flappy_start.cpp
SOURCES_CPP += sources/app/screens/scr_flappy_mode.cpp
SOURCES_CPP += sources/app/screens/scr_flappy_menu.cpp
SOURCES_CPP += sources/app/screens/scr_flappy_game.cpp
SOURCES_CPP += sources/app/screens/scr_about.cpp
SOURCES_CPP += sources/app/screens/scr_high_score.cpp 
SOURCES_CPP += sources/app/screens/high_score.cpp 
SOURCES_CPP += sources/app/screens/sound.cpp 
SOURCES_CPP += sources/app/screens/scr_settings.cpp 