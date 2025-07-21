# Antspace

Antspace is a multithreaded, SDL-based simulation of an artificial ant colony. Each ant acts as an autonomous agent in a 2D grid world, guided by local perception and pheromone fields. The simulation explores decentralized behavior, swarm intelligence, and parallel execution — all visualized in real time using SDL.

Built in modern C++, Antspace is a sandbox for experimenting with low-level concurrency, agent-based modeling, and emergent collective behavior.

## Features

- Multithreaded agent simulation using `std::thread`
- Real-time visualization via SDL2
- Decentralized ant behavior based on local rules
- Pheromone fields with evaporation and diffusion
- Dynamic 2D grid world with configurable terrain and food
- Fine-grained concurrency with cell-level synchronization
- Optional debug overlays (pheromone maps, agent state, FPS)

## Build Instructions

### Dependencies

- SDL2 development libraries
- C++17 or newer
- CMake (recommended)

### Build (Linux/macOS)

```bash
git clone https://github.com/yourusername/antspace.git
cd antspace
mkdir build && cd build
cmake ..
make
./antspace
```

## Command-Line Options 
--ants <N>: Number of ants

--threads <N>: Number of simulation threads

--scale <N>: Visual cell scaling factor

--fps <N>: Frame rate cap

--map <file>: Load a custom world map

--headless: Disable rendering (benchmark mode)

## Architecture Overview

```
/src
  main.cpp            → Entry point and main loop
  Ant.cpp/.hpp        → Ant agent logic and behavior
  Grid.cpp/.hpp       → Grid structure and pheromone data
  Simulation.cpp/.hpp → Multithreaded coordination and update logic
  Renderer.cpp/.hpp   → SDL2 rendering and display
  Config.hpp          → Tunable parameters

/assets
  maps/               → World layouts
  textures/           → (Optional) visual assets

/include
  ...
```

## Concept
Antspace models collective intelligence using individual agents with no global knowledge. Each ant follows simple rules: explore the world, deposit pheromones, and respond to local signals. Together, their actions result in path optimization and adaptive foraging, without any central control.

The project emphasizes:

    Low-level control over threading and memory layout

    Performance through parallelization and cache-aware design

    Visualization of emergent behavior in real time
    
## License
MIT
