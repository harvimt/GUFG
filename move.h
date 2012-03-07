#include "SDL.h"

struct activeWindow{
	int start;
	int end;
	int damage;
	int stun;
};

class move{
public:
	move();
	move(char*);
	move(char*, char*, bool);
	~move();
	void execute();	//Do the move. The char arg is just for testing.
	int check(int[], int[]);	//Check to see if the move is possible right now.
	int input;
private:
	int frames;	//Number of frames.
//	SDL_Surface *sprite, *hit, *hittable, *collision;
	char * name;
	bool special;
	int cost;
	int button[5];
};

class moveTrie{
public:
	moveTrie();
	moveTrie(move*);
	moveTrie(move*, int);
	moveTrie(move*, char*);
	~moveTrie();
	move * moveHook(int[40], int, void * l, int[5], int[5]);
	moveTrie * child[10];
	move * fish; 		//Because it's what a hook catches! Okay, this name probably needs to change.
	moveTrie * insert(int);
	moveTrie * insert(int, move*);
	moveTrie * insert(int, move*, int);
	void insert(move *);
private:
	int occupants;
	int * button;
	int tolerance;
};
