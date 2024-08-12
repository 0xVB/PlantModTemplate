#include "Functions.h"
#include "Original.h"
#include <iostream>

// Load resources in this function. Called only once when the game loads.
void __stdcall GameLoaded(LawnApp* App)
{

}

// Called when a new plant is added to the game.
void __stdcall PlantAdded(Plant* aPlant)
{
	auto Lawn = aPlant->mLawn;
	auto App = aPlant->mApp;
}

// Called when a plant is updating (once per frame per plant, iterating through all the plants on the board).
void __stdcall PlantUpdating(Plant* aPlant)
{
	auto Lawn = aPlant->mLawn;
	auto App = aPlant->mApp;
	Original::PlantUpdate(aPlant);
}

// Called when a plant is being drawn on the screen.
void __stdcall PlantDrawing(Plant* aPlant, Sexy::Graphics* G)
{
	auto Lawn = aPlant->mLawn;
	auto App = aPlant->mApp;
	Original::PlantDraw(aPlant, G);
}

// Called when a plant is shooting and should create its projectiles.
void __stdcall PlantShooting(Plant* aPlant, Zombie* Target, int Lane, bool IsSecondary)
{
	auto Lawn = aPlant->mLawn;
	auto App = aPlant->mApp;
	Original::PlantShoot(aPlant, Target, Lane, IsSecondary);
}

// Called when a zombie spawns.
void __stdcall ZombieAdded(Zombie* aZombie)
{
	auto Lawn = aZombie->mLawn;
	auto App = aZombie->mApp;
}

// Called when a zombie is updating.
void __stdcall ZombieUpdating(Zombie* aZombie)
{
	auto Lawn = aZombie->mLawn;
	auto App = aZombie->mApp;
	Original::ZombieUpdate(aZombie);
}

// Called whena  zombie is being drawn.
void __stdcall ZombieDrawing(Zombie* aZombie, Sexy::Graphics* G)
{
	auto App = aZombie->mApp;
	Original::ZombieDraw(aZombie, G);
}

// Called when a zombie bites a plant.
void __stdcall ZombieEating(Zombie* aZombie, Plant* BittenPlant)
{
	auto Lawn = aZombie->mLawn;
	auto App = aZombie->mApp;
	Original::BitePlant(aZombie, BittenPlant);
}

// Called when a new projectile is created.
void __stdcall ProjectileAdded(Projectile* aProj)
{
	auto Lawn = aProj->mLawn;
	auto App = aProj->mApp;
}

// Called when a projectile is updating
void __stdcall ProjectileUpdating(Projectile* aProj)
{
	auto Lawn = aProj->mLawn;
	auto App = aProj->mApp;
	Original::ProjectileUpdate(aProj);
}

// Called when a projectile is colliding with a zombie. Zombie could be NULL if it hit the roof.
void __stdcall ProjectileColliding(Projectile* aProj, Zombie* aZombie)
{
	auto Lawn = aProj->mLawn;
	auto App = aProj->mApp;
	Original::ProjectileCollide(aProj, aZombie);
}

// Called when a projectile is being drawn.
void __stdcall ProjectileDrawing(Projectile* aProj, Sexy::Graphics* G)
{
	auto Lawn = aProj->mLawn;
	auto App = aProj->mApp;
	Original::ProjectileDraw(aProj, G);
}