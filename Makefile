all:
	g++ -o simpleray main.cpp Camera.cpp GameObject.cpp LightSource.cpp Quaternion.cpp RayTracer.cpp Scene.cpp Sphere.cpp Vector3.cpp -lglfw -lOpenGL -lm -ldl -lpthread
