CC=g++
#LDLIBS=-lSOIL -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
CPPFLAGS=-c -Wall -g -I ~/Mooc/computer_graphics/raytracer/proj1 -O
OBJ= Core/Bitmap.o Core/Color.o Main.o Core/Matrix34.o Object/MeshObject.o Core/Vector3.o Object/InstanceObject.o Camera.o Triangle.o Scene.o
TARGET= raytracer
	
all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

.c.o:
	$(CC) $(CPPFLAGS) $< -g


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
