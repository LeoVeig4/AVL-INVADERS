# AVL-INVADERS

This is a game made in Programming Laboratory classes

##
The algorith uses trees in C++ to represent the "invaders".

the tree follows the balancement rules of AVL, so the tree is always balanced.

this is a game made with **ALLEGRO 5**

- If you are using linux, use **make** to compile

- If you are using windows, use **g++  principal.cpp tela.cpp  -o Invaders  -lallegro -lallegro_main  -lallegro_color -lallegro_font -lallegro_primitives -lallegro_image**

**Have fun**

### Running with Docker

You can also build and run the game in a container. The container
requires access to your X server so the game window can be displayed.

Build the image:

```bash
docker build -t avl-invaders .
```

Run the game (Linux):

```bash
docker run --rm \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    avl-invaders
```

You may need to allow Docker to access your X server with
`xhost +local:docker` before running the container.
