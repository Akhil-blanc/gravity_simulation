# Gravity Simulation

```
cd src
```

```
g++  main.cpp sphere.cpp mouseHandler.cpp -lGL -lGLU -lglut -lSOIL
```
-----------------
## Stuff to be implemented
- [X] Sphere class to render as many planets as possible
- [ ] Load texture for planets (either add in sphere class or separately)
- [ ] Texture for space (create a sphere that is very large, covers the scene i.e, all planets and camera are inside the bigger sphere),(now add texture to internal surface)
- [X] Lighting with attenuation 
- [ ] Test lighting with different object textures
- [ ] Arcball camera with mouse and keyboard traversal
- [ ] ImgGUI sliders for planet distance, size, density
- [ ] Velocity based on gravity



### Extras
- [ ] Algorithm to render planets with less stacks and slices if far away from camera