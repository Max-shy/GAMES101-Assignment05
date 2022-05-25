# GAMES101-Assignment05
Ray-Tracing(Moller-Trumbore)

## Assignment 05

Assignment 5 required ray intersection with the triangle mesh. It's not a difficult task. Only need to use Moller-Trumbore Algorithm to calculate the intersection point. 

First of all, I need to create a direction vector from the camera to pixel and convert it from raster space to world space.

```cpp
for (int j = 0; j < scene.height; ++j){
    for (int i = 0; i < scene.width; ++i){
    	// generate primary ray direction
        float x = (2.0f*((i+0.5f)/scene.width)-1)*scale*imageAspectRatio;
        float y = (1-2.0f*((j+0.5f)/scene.height))*scale;

		//normalize this direction
        Vector3f dir = normalize(Vector3f(x, y, -1)); 
            
        //store the color of each pixel
        framebuffer[m++] = castRay(eye_pos, dir, scene, 0);
    }
}
```

Within the function **castRay(eye_pos, dir, scene, 0)**, ray the light from each direction vector and determine if it will intersect with the object.

And then trace each ray in function **trace(Orig, dir, scene.get_objects())**, within this function we have a function **rayTriangleIntersect()** to determine whether the ray intersects the triangle or not.

This function is the key to assignment 5. Inside this function, we implement the Moller-Trumbore Algorithm.

![image](https://user-images.githubusercontent.com/68177870/170151541-30d01a1d-23e0-4895-9e2b-794bf5c60e76.png)

```CPP
bool rayTriangleIntersect(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, const Vector3f& orig, const Vector3f& dir, float& tnear, float& u, float& v)
{
    Vector3f E1 = v1 - v0;
    Vector3f E2 = v2 - v0;
    Vector3f S = orig - v0;
    Vector3f S1 = crossProduct(dir, E2);
    Vector3f S2 = crossProduct(S, E1);

    //compute the Barycentric coordinates
    float t = dotProduct(S2, E2) / dotProduct(S1, E1);
    float b1 = dotProduct(S1, S) / dotProduct(S1, E1);
    float b2 = dotProduct(S2, dir) / dotProduct(S1, E1);

    if (t > 0 && b1 > 0  && b2 > 0 && (1 - b1 - b2 > 0)) {
        tnear = t;
        u = b1;
        v = b2;
        return true;
    }
    return false;
}
```

Let's take a look at the render result.

![image](https://user-images.githubusercontent.com/68177870/170151721-fa3f31e7-2634-4057-a921-3d40b3055bee.png)


I noticed that there was a problem with blue dots in the shadows.

![image](https://user-images.githubusercontent.com/68177870/170151746-39cd9107-c156-43b4-904b-afa7fa54f927.png)

Finally, it was found that there was a precision problem when compared with 0. To solve this problem, compare the parameter with a negative number which a little less than zero.

```CPP
float minDis = -0.00001;
if (t > minDis && b1 > minDis && b2 > minDis && (1 - b1 - b2 > minDis)) {
    tnear = t;
    u = b1;
    v = b2;
    return true;
}
```

Now, let's look at the new render results.

![image](https://user-images.githubusercontent.com/68177870/170151758-6dbdf401-0d4c-4add-b66d-8a5b0316f808.png)

The problem was solved perfectly.

![image](https://user-images.githubusercontent.com/68177870/170151765-01b8fd2f-2f83-4ee6-99a1-476d3590b17b.png)
