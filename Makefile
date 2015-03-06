CC=g++
#LDLIBS=-lSOIL -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
CFLAGs=-c -Wall -g -O
OBJ= Bitmap.o Color.o Main.o Matrix34.o MeshObject.o Vector3.o 
TARGET= raytracer

	
all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $< -g


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
