#pragma once
#include "Lunacy/Lunacy.hpp"

// Load resources in this function. Called only once when the game is started.
void __stdcall GameLoaded(LawnApp*);

// Plants \\
// Called when a new plant is added to the game.
void __stdcall PlantAdded(Plant*);
// Called when a plant is updating (once per frame per plant, iterating through all the plants on the board).
void __stdcall PlantUpdating(Plant*);
// Called when a plant is shooting and should create its projectiles.
void __stdcall PlantShooting(Plant* aPlant, Zombie* Target, int Lane, bool IsSecondary);
// Called when a plant is being drawn on the screen.
void __stdcall PlantDrawing(Plant*, Sexy::Graphics*);

// Zombies \\
// Called when a zombie spawns.
void __stdcall ZombieAdded(Zombie*);
// Called when a zombie is updating.
void __stdcall ZombieUpdating(Zombie*);
// Called when a zombie bites a plant.
void __stdcall ZombieEating(Zombie*, Plant*);
// Called whena  zombie is being drawn.
void __stdcall ZombieDrawing(Zombie*, Sexy::Graphics*);

// Projectiles \\
// Called when a new projectile is created.
void __stdcall ProjectileAdded(Projectile*);
// Called when a projectile is updating
void __stdcall ProjectileUpdating(Projectile*);
// Called when a projectile is colliding with a zombie. Zombie could be NULL if it hit the roof.
void __stdcall ProjectileColliding(Projectile*, Zombie*);
// Called when a projectile is being drawn.
void __stdcall ProjectileDrawing(Projectile*, Sexy::Graphics*);