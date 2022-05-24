#include "Scene.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Light.hpp"
#include "Renderer.hpp"

// In the main function of the program, we create the scene (create objects and lights)
// as well as set the options for the render (image width and height, maximum recursion
// depth, field-of-view, etc.). We then call the render function().
int main()
{
    Scene scene(1280, 960);//create scene

    auto sph1 = std::make_unique<Sphere>(Vector3f(-1, 0, -12), 2);//create the sphere(center,r)
    sph1->materialType = DIFFUSE_AND_GLOSSY;//Set sphere's Material(glossy)
    sph1->diffuseColor = Vector3f(0.6, 0.7, 0.8); // Set diffuse color

    auto sph2 = std::make_unique<Sphere>(Vector3f(0.5, -0.5, -8), 1.5);//create the sphere(center,r)
    sph2->ior = 1.5;// ior is the material refractive index
    sph2->materialType = REFLECTION_AND_REFRACTION;//Set sphere's Material(reflection)

    scene.Add(std::move(sph1));//add a sphere object in scene
    scene.Add(std::move(sph2));//add a sphere object in scene

    Vector3f verts[4] = {{-5,-3,-6}, {5,-3,-6}, {5,-3,-16}, {-5,-3,-16}};//vertex
    uint32_t vertIndex[6] = {0, 1, 3, 1, 2, 3};// index
    Vector2f st[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}}; //?
   
    auto mesh = std::make_unique<MeshTriangle>(verts, vertIndex, 2, st);
    mesh->materialType = DIFFUSE_AND_GLOSSY;

    scene.Add(std::move(mesh));
    scene.Add(std::make_unique<Light>(Vector3f(-20, 70, 20), 0.5));//add a light source(position,I)
    scene.Add(std::make_unique<Light>(Vector3f(30, 50, -12), 0.5));//add a light source(position,I)   

    //äÖÈ¾Æ÷
    Renderer r;
    r.Render(scene);

    return 0;
}