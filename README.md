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
docker run --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix avl-invaders
```

You may need to allow Docker to access your X server with
`xhost +local:docker` before running the container.

---

### Running with Docker on Windows (using VcXsrv)

If you are using Windows, you need an X server to display the game window from the Docker container. We recommend using [VcXsrv](https://vcxsrv.com/):

1. **Download and install VcXsrv:**
   - Go to [https://vcxsrv.com/](https://vcxsrv.com/) and download the installer.
   - Run the installer and follow the default installation steps.

2. **Start VcXsrv:**
   - Open the Start menu and search for "XLaunch".
   - Run XLaunch.
   - Select "Multiple windows" and click Next.
   - Select "Start no client" and click Next.
   - Check "Disable access control" (for testing) and click Next.
   - Click Finish to start the X server.

3. **Find your Windows IP address:**
   - Open PowerShell and run:
     ```powershell
     ipconfig
     ```
   - Look for your local IPv4 address (e.g., 192.168.1.100).

4. **Run the Docker container:**
   - In PowerShell, run (replace `<YOUR-IP>` with your actual IP):
     ```powershell
     docker run --rm -e DISPLAY=<YOUR-IP>:0.0 avl-invaders
     ```
     Example:
     ```powershell
     docker run --rm -e DISPLAY=192.168.1.100:0.0 avl-invaders
     ```

**Note:**
- You do NOT need to mount `/tmp/.X11-unix` on Windows.
- Make sure your firewall allows connections to VcXsrv (it may prompt you the first time you run it).

Now, when you run the container, the game window should appear on your Windows desktop.
