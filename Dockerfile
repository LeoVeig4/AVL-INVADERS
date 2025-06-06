FROM ubuntu:22.04

# Install build tools and Allegro dependencies (install each Allegro part separately for easier debugging)
RUN apt-get update && apt-get install -y build-essential pkg-config && rm -rf /var/lib/apt/lists/*
RUN apt-get update && apt-get install -y liballegro5-dev && rm -rf /var/lib/apt/lists/*
RUN apt-get update && apt-get install -y liballegro-image5-dev && rm -rf /var/lib/apt/lists/*
RUN apt-get update && apt-get install -y liballegro-ttf5-dev && rm -rf /var/lib/apt/lists/*
RUN apt-get update && apt-get install -y liballegro-audio5-dev && rm -rf /var/lib/apt/lists/*
RUN apt-get update && apt-get install -y liballegro-acodec5-dev && rm -rf /var/lib/apt/lists/*

# Copy source code
WORKDIR /usr/src/app
COPY . .

# Build the game
RUN make

# Set display to host display by default
ENV DISPLAY=:0

# Run the game
CMD ["./invaders"]
