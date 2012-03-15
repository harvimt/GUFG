#include "character.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <cstring>

character::character() 
//Character constructor. This loads the whole character into memory so that that we don't have disk reads during gameplay
{
	name = "White";
	moveTrie * curr;

	/*Currently I'm using this as a test case for my move hooks*/
	
	head = new moveTrie(new move("White/A", "A", 0, 11));
	head->fish[0].debugStateInit(3, 16, 30);
	head->fish[0].debugRectsInit();
	head->fish[0].debugDamageInit(10);
	head->fish[0].debugHitboxInit(55, 45, 30, 30);
	head->fish[0].debugHittableInit(0, 0, 100, 150);
	head->fish[0].xLock = 1;
	head->fish[0].yLock = 1;


	head->insert(new move("B", "B", 0));
	head->fish[1].debugStateInit(1, 16, 30);
	head->fish[1].debugRectsInit();
	
	head->insert(new move("C", "C", 0));
	head->fish[2].debugStateInit(1, 16, 30);
	head->fish[2].debugRectsInit();
	
	head->insert(new move("White/D", "D", 0, 1));
	head->fish[3].debugStateInit(3, 16, 30);
	head->fish[3].debugRectsInit();
	
	head->insert(new move("E", "E", 0));
	head->fish[4].debugStateInit(1, 16, 30);
	head->fish[4].debugRectsInit();
	
	curr = head->insert(6);
	curr = curr->insert(3);
	curr = curr->insert(2, new move("236B", "B", 1));
	curr->fish[0].debugStateInit(8, 16, 16);
	curr->fish[0].debugRectsInit();

	neutral = new move("White/N", 1);
	neutral->debugRectsInit();
	neutral->debugStateInit(1, 31, 31);
	neutral->debugHittableInit(0, 0, 100, 150);

	cMove = neutral;
	health = 300;
	meter = 0;
}

character::~character()
//Character destructor. Might not need this if we aren't working with any dynamic memory, but it might be worthwhile to have.
{
	delete head;
	//Empty for now
}

/*Here begin move functions. Actually contemplating making this a class instead, but this might be simpler for now*/

int * character::takeHit(move * attack)
{
	/*All the important logic like blocking and stuff will go here later.*/

	/*Damage scaling logic will factor into this later*/
	if(cMove->block & attack->blockMask){
		/*Do blocking stuff. Specifically, we need to put the player in
		block stun, a state in which they're frozen in the last block animation until blockstun ends.
		During blockstun, generally the option available to everyone is to switch blocks, so as not
		to allow mixup to be guaranteed. Some games have options like Alpha Counters (Any attack out of blockstun) 
		or Rolls (Invulnerable movement option) that cost meter but can break out of blockstun state. These can
		be universal or character-specific. Notably, characters are throw-invulnerable during blockstun,
		for what should be obvious reasons. In MOST games, characters remain throw-invuln for a few frames after
		coming out of blockstun.
		*/		
	}
	else{
		/*Do hitstun stuff. Specifically, the player needs to be put in a "hitstun" state for a number
		of frames defined by the stun of the attacking move. Blockstun may be separate, or a function of the same
		number. The hitstun state while standing generally has a "reeling" animation that can affect what hits them,
		but unless we have a "burst-like" option, no actions can be taken by a player during hitstun. There will probably
		also be a "launch" property, which knocks a grounded player into the air if hit by certain moves.
		In the air, hitstun is slightly different. There is a "falling" animation the character is in, and they are launched
		a little bit by any further move that hits them. Generally, there's some option to get out of aerial hitstun, most
		easily referred to as a "Tech." Therefore, while falling state persists until they hit the ground, there's an amount of
		"untechable" time associated with any move that hits them. This is not functionally different from hitstun in any other way.
		*/
		health -= attack->damage;
		if(health < 0){
			health = 0; 	//Healthbar can't go below 0;
			//Reckon other KO stuff;
		}
	}
	attack->connect(); 	//Tell the attack it's connected.

	return NULL; 		
	/*Eventually the plan is to have this return a combo count. This not only allows us to display a counter and do whatever scaling/combo 
	mitigation we want to, but also allows us to do things like pushback ramping during blockstrings*/
}
