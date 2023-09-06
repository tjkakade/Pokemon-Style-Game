//=================================================================
// The map class file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "map.h"
#include "globals.h"
#include "graphics.h"
#include "hash_table.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items; // Hashtables for all items of the map
    int w, h;         // Map dimensions
    int index;        // Index of map (tells if its the first map or second map)
};

///////////////////////
//Important Definitions
///////////////////////

#define MHF_NBUCKETS 97     //  Hashing value
#define NUM_MAPS 2          //  You may add more maps here
static Map maps[NUM_MAPS];  //  Array of maps
static int active_map;      //  Current active map on screen


//To erase a MapItem, we can simply replace it 
//with a clear type item called clear sentinel
static const MapItem CLEAR_SENTINEL = { 
    .type = CLEAR,
    .draw = draw_nothing
};


/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {

    //****************
    // TODO: Implement
    //****************

    // 1. Return the 1-D XY key
    // Hint: Think about how you accessed location previous projects/hw

    int key = X + (get_active_map() -> w) * Y; // X * width * Y
    return key;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    //****************
    // TODO: Implement
    //****************

    // Hint: what math operator can be used as an easy way to hash a key?
    // 1. Use MHF_NBUCKETS defined at the top as the value to hash for your hash function
    // 2. Return the hashed key

    int hash = key % MHF_NBUCKETS; // already mod in hash table implmentation
    //int hash = key;
    return hash;
}

/**
 * Initializes the map, using a hash_table, setting the width and height.
 */
void maps_init()
{
    //****************
    // TODO: Implement
    //****************

    // 1. Loop through all possible maps, where for each map's items, create a hashtable 
    // 2. Set width & height for any maps 
    // 3. Set the first map to be active

    for (int i = 0; i < NUM_MAPS; i++) {
        maps[i].items = createHashTable(map_hash, MHF_NBUCKETS); // hash table creation
        if (i == 0) { // original map
            maps[i].h = 50;
            maps[i].w = 50;
        } else if (i == 1) { // secondary map
            maps[i].h = 16; // smaller map
            maps[i].w = 16;
        }
    }
    set_active_map(0); // map1 = 0, map2 = 1
}


Map* get_active_map()
{
    //****************
    // TODO: Implement
    //****************

    // 1. Return a pointer to the current map based on which map is active (active_map)
    //    Hint: What operator do we use for returning addresses?
    //    Note: active_map is set as a Global Variable 

    return &maps[active_map];
}

int get_active_map_index()
{
    //****************
    // TODO: Implement
    //****************
    
    // 1. Return the index to the current map based on which map is active (active_map)

    return active_map; 
}

Map* set_active_map(int m)
{
    //****************
    // TODO: Implement
    //****************

    // 1. Set the Global Variable for active map to the map index passed in
    // 2. Return a pointer to the current map based on which map is active (active_map)

    active_map = m; // 0 for map1, 1 for map2
    return &maps[active_map];
}

/**
 *  Prints out the map for debugging on the terminal
 */

void print_map()
{
    // NOTE: As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'D', 'P', 'A', 'K', 'C', 'N',' ','S'};
    Map* map = get_active_map();
    for(int j = 0; j < map->h; j++)
    {
        for (int i = 0; i < map->w; i++)
        {
            MapItem* item = (MapItem*)getItem(map->items, XY_KEY(i, j));
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}


/**
 * Returns width of active map
 */
int map_width()
{
    //****************
    // TODO: Implement 
    //****************
    // Hint 1 for this and below functions: use another function to GET the current active map
    // Hint 2: check the struct of a map item

    int width = get_active_map() -> w;
    return width;
}

/**
 * Returns height of active map
 */
int map_height()
{
    //****************
    // TODO: Implement  
    //****************

    int height = get_active_map() -> h;
    return height;
}

/**
 * Returns the area of the active map
 */
int map_area()
{
    //****************
    // TODO: Implement  
    //****************
    // HINT: You have the width and height to compute area
    int area = map_width() * map_height();
    return area;
}

/**
 * Returns the MapItem immediately above the given location.
 */
MapItem* get_north(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 

    int north = XY_KEY(x, y - 1); // y-1 up one
    HashTable *temp = get_active_map() -> items; // get HT
    MapItem *item = (MapItem*) getItem(temp, north); // get item north
    if (item -> type == CLEAR) {
        removeItem(temp, north);
    }
    return item;
}

/**
 * Returns the MapItem immediately below the given location.
 */
MapItem* get_south(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 

    int south = XY_KEY(x, y + 1); // y+1 down one
    HashTable *temp = get_active_map() -> items;
    MapItem *item = (MapItem*) getItem(temp, south);
    if (item -> type == CLEAR) {
        removeItem(temp, south);
    }
    return item;
}

/**
 * Returns the MapItem immediately right the given location.
 */
MapItem* get_east(int x, int y)
{
   //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 

    int east = XY_KEY(x + 1, y); // x+1 right one
    HashTable *temp = get_active_map() -> items;
    MapItem *item = (MapItem*) getItem(temp, east);
    if (item -> type == CLEAR) {
        removeItem(temp, east);
    }
    return item;
}

/**
 * Returns the MapItem immediately left the given location.
 */
MapItem* get_west(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 

    int west = XY_KEY(x - 1, y); // x-1 left one
    HashTable *temp = get_active_map() -> items;
    MapItem *item = (MapItem*) getItem(temp, west);
    if (item -> type == CLEAR) {
        removeItem(temp, west);
    }
    return item;
}

/**
 * Returns the MapItem at current coordinate location
 */
 MapItem* get_here(int x, int y)
 {
    //****************
    // TODO: Implement
    //****************
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 

    int here = XY_KEY(x, y); // x,y current location
    HashTable *temp = get_active_map() -> items;
    MapItem *item = (MapItem*) getItem(temp, here);
    if (item -> type == CLEAR) {
        removeItem(temp, here);
    }
    return item;
 }

 

/**
 * Erases item on a location by replacing it with a clear sentinel
 */
void map_erase(int x, int y)
{
    MapItem* item = (MapItem*)insertItem(get_active_map()->items, XY_KEY(x, y), (void*)&CLEAR_SENTINEL);
    if(item) free(item);
}


////////////////////////////////////
// Adding specific items to the map
////////////////////////////////////

void add_basket(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = BASKET;
    w1->draw = draw_basket;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_npc(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant
    //     *Make the NPC NOT walkable

    MapItem* npc = (MapItem*) malloc(sizeof(MapItem));
    npc->type = NPC;
    npc->draw = draw_npc;
    npc->walkable = false;
    npc->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), npc);
    if (val) free(val); // If something is already there, free it
}


void add_water(int x, int y)
{

   //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant

    MapItem* water = (MapItem*) malloc(sizeof(MapItem));
    water->type = WATER;
    water->draw = draw_water;
    water->walkable = true;
    water->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), water);
    if (val) free(val); // If something is already there, free it
}

void add_fire(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant

    MapItem* fire = (MapItem*) malloc(sizeof(MapItem));
    fire->type = FIRE;
    fire->draw = draw_fire;
    fire->walkable = true;
    fire->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), fire);
    if (val) free(val); // If something is already there, free it
}

void add_earth(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant

    MapItem* earth = (MapItem*) malloc(sizeof(MapItem)); 
    earth->type = EARTH;
    earth->draw = draw_earth;
    earth->walkable = true;
    earth->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), earth);
    if (val) free(val); // If something is already there, free it
}


void add_buzz(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant

    MapItem* buzz = (MapItem*) malloc(sizeof(MapItem));
    buzz->type = BUZZ;
    buzz->draw = draw_buzz;
    buzz->walkable = true;
    buzz->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), buzz);
    if (val) free(val); // If something is already there, free it
}

void add_slain_buzz(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Implement the same way as how we add plant
    // Note: This function is to ovewrite Buzz when he is defeated
    //      You can do the following:
    //      -   Overwrite buzz with any other item (say plant, mud)
    //      -   Make a new drawing for a defeated buzz
    //      -   Erase buzz instead 

    MapItem* slain = (MapItem*) malloc(sizeof(MapItem));
    slain->type = SLAIN_BUZZ;
    slain->draw = draw_mud;
    slain->walkable = true;
    slain->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), slain);
    if (val) free(val); // If something is already there, free it
}



////////////////////////////////////
// Adding environment to the map
////////////////////////////////////


void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_door(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = DOOR;
        w1->draw = draw_door;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}


void add_stairs(int x, int y, int tm, int tx, int ty)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = STAIRS;
    w1->draw = draw_stairs;
    w1->walkable = true;
    StairsData* data = (StairsData*) malloc(sizeof(StairsData));
    data->tm = tm;
    data->tx = tx;
    data->ty = ty;
    w1->data = data;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it    
}


void add_cave(int x, int y, int n, int tm, int tx, int ty)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CAVE;
    if (n==1){
        w1->draw = draw_cave1;
    }
    if (n==2){
        w1->draw = draw_cave2;
    }
    if (n==3){
        w1->draw = draw_cave3;
    }
    if (n==4){
        w1->draw = draw_cave4;
    }
    w1->walkable = true;
    StairsData* data = (StairsData*) malloc(sizeof(StairsData));
    data->tm = tm;
    data->tx = tx;
    data->ty = ty;
    w1->data = data;
    
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it    
}


void add_mud(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = MUD;
        w1->draw = draw_mud;
        w1->walkable = true;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}