FROM ubuntu:22.04

# Install build tools and Allegro dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    pkg-config \
    liballegro5-dev \
    liballegro-image5 liballegro-ttf5 liballegro-font5 \
    liballegro-audio5 liballegro-acodec5 \
 && rm -rf /var/lib/apt/lists/*

# Copy source code
WORKDIR /usr/src/app
COPY . .

# Build the game
RUN make

# Set display to host display by default
ENV DISPLAY=:0

# Run the game
CMD ["./invaders"]
