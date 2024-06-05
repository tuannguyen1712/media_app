CC = g++
CFLAGS = -Wall
# HFLAGS = -I./Driver/ADC/Inc/ -I./Driver/GPIO/Inc/
SRC_DIR = ./
LIB_DIR = ./MVC
OBJ_DIR = ./Output
TAG_LIB = -ltag
SDL2 = -lSDL2
SDL2_MIXER = -lSDL2_mixer

# include file
DRV_MODULE_INC := $(wildcard $(LIB_DIR)/*)
DRV_MODULE_SRC := $(wildcard $(LIB_DIR)/*)

# with foreach, name of value in parameter 3 is parameter 1
HFLAGS = $(foreach DRV_MODULE_INC, $(DRV_MODULE_INC), -I$(DRV_MODULE_INC))

SRC_DIRS := $(DRV_MODULE_SRC) $(SRC_DIR)
SRC_FILES := $(foreach DRV_MODULE_SRC, $(DRV_MODULE_SRC), $(wildcard $(DRV_MODULE_SRC)/*.cpp)) \
				$(wildcard $(SRC_DIR)/*.cpp)

SRC_FILES_NAME := $(notdir $(SRC_FILES))
OBJ_FILE := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES_NAME))

# print: 
# 	@echo $(OBJ_FILE)
vpath %.cpp $(SRC_DIRS)

TARGET = ./my_app

$(OBJ_DIR)/%.o:%.cpp
	$(CC) -c $(CFLAGS) $(HFLAGS) $< -o $@ 

$(TARGET):$(OBJ_FILE)
	$(CC) $(OBJ_FILE) -o $(TARGET) $(TAG_LIB) $(SDL2) $(SDL2_MIXER)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)