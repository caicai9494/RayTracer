CC=g++
CPPFLAGS=-c -Wall -g -I ~/Mooc/computer_graphics/raytracer/proj1 
OBJ= Core/Bitmap.o Core/Color.o Core/Vector3.o Core/Matrix34.o \
     \
     Main.o Camera.o Scene.o RayTrace.o\
     \
     Object/MeshObject.o Object/InstanceObject.o Object/Triangle.o \
     Object/PlaneObject.o  Object/SphereObject.o \
     Object/BoxTreeObject.o  Object/BoxTreeNode.o \
     \
     Material/LambertMaterial.o


TARGET= raytracer
	
all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

.c.o:
	$(CC) $(CPPFLAGS) $< -g


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
