#pragma once
#include "Lunacy/Lunacy.hpp"
// Original functions. Call them to perform the vanilla game behavior. You can add to the vanilla behavior or overwrite it completely.
namespace Original
{
	// The original plant update function. Call to update the plant normally.
	void __stdcall PlantUpdate(Plant*);
	// The original shooting function. Call to make the plant shoot normally.
	void __stdcall PlantShoot(Plant*, Zombie* Target, int Lane, bool IsSecondaryWeapon);
	// The original plant drawing function. Call to draw the plant normally.
	void __stdcall PlantDraw(Plant*, Sexy::Graphics*);

	// The original zombie update function. Call to update the zombie normally.
	void __stdcall ZombieUpdate(Zombie*);
	// The original plant biting function. Call to make the zombie bite the plant normally.
	void __stdcall BitePlant(Zombie*, Plant*);
	// The original zombie draw function. Call to draw the zombie normally.
	void __stdcall ZombieDraw(Zombie*, Sexy::Graphics*);

	// The original projectile update function. Call to update the projectile normally.
	void __stdcall ProjectileUpdate(Projectile*);
	// The original projectile collision function. Call to make the projectile collide with a zombie normally.
	void __stdcall ProjectileCollide(Projectile*, Zombie*);
	// The original projectile draw function. Call to draw the projectile normally.
	void __stdcall ProjectileDraw(Projectile*, Sexy::Graphics*);
}