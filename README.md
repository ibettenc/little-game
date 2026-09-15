*This project has been created as part of the 42 curriculum by **ibettenc**, **raantoin**.*
<div align="center">

#   CUB3D
> *A minimalist program to run a video game using basic 3D methods*

</div>

---

##  Description

The goal of this project is to create a minimalist version of a Wolfenstein3D game. We will read a file which contains all the information we need to
create our map and give the textures as well, we will render a 3D visual from it using minilibx and give the ability to move the player or the camera.
The program is built around **6 core components**:

### 1.  File_reading
This part here is all about opening and reading the file, finding out if it respects the assignment rules, and if it does gathering all the information for further usage by our program.

### 2.  The Map
This part here is where after getting the map from the file, we check if its valid then we store all map information inside a structure

### 3.  The Render and raycasting
This is where we use raycasting techniques to make 3D visuals that works on a 2D screen.
And where we make sure that it is correctly displayed on the screen.

### 4.  The Textures
The textures are what give the game it's colours for the floor and ceiling and the walls graphics

### 5.  The Commands
By using the directionnal arrows and keyboard, we can make it so that the camera/player moves.
You can also exit the window.


##  Instructions

You have to download minilibx put it inside the folder srcs/includes.
Make inside the terminal and give the program a file.cub as argument

### Run

Make

### Clean

make clean    # Remove object files
make fclean   # Remove object files + binary
make re       # Full rebuild

---

##  Resources

Here are the key references used during the development of this project:

Raycasting :
- https://lodev.org/cgtutor/raycasting.html
- https://youtu.be/gYRrGTC7GtA?si=3Z-UvM0beglPsvET

- MAN

- This guide on Minilibx is where we found answers to most our questions on graphics, (https://harm-smits.github.io/42docs/libs/minilibx)
- We used AI such as Claude mainly to understand the rendering process, help with debugging

---


<div align="center">

Made with fun and pain at **42** — *ibettenc* & *raantoin*

</div>%     