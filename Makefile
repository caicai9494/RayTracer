CC=g++
CPPFLAGS=-c -Wall -g -I ~/Mooc/computer_graphics/raytracer/proj1 
OBJ= Core/Bitmap.o Core/Color.o Main.o Core/Matrix34.o Object/MeshObject.o Core/Vector3.o Object/InstanceObject.o Camera.o Object/Triangle.o Object/PlaneObject.o Scene.o Object/SphereObject.o
TARGET= raytracer
	
all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

.c.o:
	$(CC) $(CPPFLAGS) $< -g


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
