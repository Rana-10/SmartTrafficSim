# Smart Traffic Management System Simulator

**SmartTrafficSim**

A console-based Smart Traffic Management System Simulator (C++).  
This project simulates vehicle movement, traffic signals, road closures and emergency vehicle behavior on a grid-based road network. It was developed as a data-structures / systems project and includes sample datasets (CSV/Excel), a GUI-less terminal simulation screen, and utilities to experiment with traffic control logic.

---

## 🔎 Overview

SmartTrafficSim models an urban traffic grid where:
- Vehicles follow routes across a grid/road network.
- Traffic signals control flow at intersections.
- Emergency vehicles (e.g., ambulances) get priority and can override signals or change routing.
- Road closures and dynamic events can be fed via data files.
- The simulation demonstrates scheduling, priority handling and routing logic—useful for prototyping traffic control policies.

The project uses plain C++ (single/multiple source files) and basic file I/O to load scenario data.

---

## ⚙️ Key Features

- Grid-based road network representation
- Traffic signal scheduling and state changes
- Vehicle classes including emergency vehicles with priority rules
- Road closure handling and dynamic rerouting
- Loadable sample datasets (vehicles, traffic_signals, roads, closures)
- Console visualization of the grid (ASCII)
- Configurable simulation parameters (speed, ticks, etc.)
- Save / load functionality for scenarios (where implemented)

---

## 📂 File structure (example)
/ (repo root)
├─ dataproject.cpp # main simulation source (name may differ)
├─ sample.cpp # helper / test harness
├─ traffic_signals.xlsx # sample data for signal timings
├─ vehicles.xlsx # sample vehicle dataset
├─ road.xlsx # road topology
├─ road_closures.xlsx # closures/events data
├─ Smart Traffic Management System Simulator.pdf # project report
├─ README.md
└─ .vscode/ # optional editor settings
