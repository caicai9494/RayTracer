CC=g++
CPPFLAGS=-c -Wall -g -I .  -std=c++11 -O
OBJ= Core/Bitmap.o Core/Color.o Core/Vector3.o Core/Matrix34.o \
     \
     Main.o \
     Scene/Scene.o \
     \
     Object/MeshObject.o Object/InstanceObject.o Object/Triangle.o \
     Object/PlaneObject.o  Object/SphereObject.o \
     Object/BoxTreeObject.o  Object/BoxTreeNode.o \
     \
     Camera/Camera.o Camera/RayTrace.o
#     Material/LambertMaterial.o Material/AshikhminMaterial.o
    


TARGET= raytracer
	
all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

.c.o:
	$(CC) $(CPPFLAGS) $< -g


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
