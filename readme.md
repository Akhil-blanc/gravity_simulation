# Gravity Simulation

```
sudo apt-get install libglm-dev
```

```
cd src
```

```
g++  main.cpp sphere.cpp mouseHandler.cpp keyboardHandler.cpp -lGL -lGLU -lglut -lSOIL
```

-----------------
## Stuff to be implemented
- [X] Sphere class to render as many planets as possible
- [X] Load texture for planets Texture loading is done in main.cpp)
- [ ] Texture for space (create a sphere that is very large, covers the scene i.e, all planets and camera are inside the bigger sphere),(now add texture to internal surface)
- [X] Lighting with attenuation 
- [ ] Test lighting with different object textures
- [ ] Arcball camera with mouse and keyboard traversal
- [ ] ImgGUI sliders for planet distance, size, density
- [ ] Velocity based on gravity



### Extras
- [ ] Algorithm to render planets with less stacks and slices if far away from camera

___________________

## Camera Instructions
#### Movements
 - Arrow Key `a`: Pan left
 - Arrow Key `w`: Move forward in view direction (towards)
 - Arrow Key `s`: Move backward in view direction (away)
 - Arrow Key `d`: Pan right
 
 #### Camera Angles
 - Arrow Key `q`: Angle down
 - Arrow Key `e`: Angle up 
 - Arrow Key `s`: Angle left
 - Arrow Key `d`: Angle right

#### Mouse
 - Left mouse button for arcball movement

