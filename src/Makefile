#/**********************************************************
# * Author        : Aiken.zhao
# * Email         : Aiken.zhao@goertek.com
# * Last modified : 2018-03-06 09:12
# * Filename      : Makefile
# * Description   : 
# * *******************************************************/

TARGET = list

DIR_LIB = ../lib 
DIR_INC = ../include
DIR_BIN = ../bin
DIR_TEM = ../tmp

LIBS := -L$(DIR_LIB) #库文件
INC := -I$(DIR_INC) #头文件

#配置编译器
CXX = g++

CC = gcc
#依赖库
LIBS +=

#中间临时文件
OBJECTS = my_list.o list_main.o

all : $(TARGET) 

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(INC) -o $(TARGET) $(LIBS)

%.o : %.cpp
	$(CXX) -c $(INC) $< -o $@

.PHONY : clean install

install:
	mv $(TARGET) ../bin
	-mv *.o ../tmp

clean:
	-rm *.o $(TARGET) ../bin/$(TARGET) ../tmp/*.o

