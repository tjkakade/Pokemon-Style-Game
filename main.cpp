//=================================================================
// The main program file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


// Projet includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
#include <math.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

// Helper function declarations
void playSound(char* wav);


/////////////////////////
// Struct of Player 
/////////////////////////

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;            // Current locations
    int px, py;         // Previous locations
    bool has_key;       // flag when obtained the key
    bool game_solved;   // flag when game is complete
    bool talked_to_npc; // flag when you've talked to npc
    bool ramble;        // flag when you activate ramblin mode

    //You may add more flags as needed

} Player;



/////////////////////////
// Get Action
/////////////////////////

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 * Get Actions from User (pushbuttons, and nav_switch)
 * Based on push button and navigation switch inputs, determine which action
 * needs to be performed (may be no action).
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define RAMBLIN_MODE 7

int get_action(GameInputs inputs)
{
    //******************
    // TODO: Implement
    //******************
    
    // 1. Check your action and menu button inputs and return the corresponding action value
    
    // 2. Check for your navigation switch inputs and return the corresponding action value
    
    // If no button is pressed, just return no action value
    if (inputs.ns_down) {
        return GO_DOWN;
    }
    if (inputs.ns_left) {
        return GO_LEFT;
    }
    if (inputs.ns_right) {
        return GO_RIGHT;
    }
    if (inputs.ns_up) {
        return GO_UP;
    }
    if (inputs.b1) {
        return ACTION_BUTTON;
    }
    if (inputs.b2) {
        return RAMBLIN_MODE;
    }

    return NO_ACTION;
}




/////////////////////////
// Helper Functions:
/////////////////////////
// Feel free to define any helper functions here for update game





/////////////////////////
// Update Game
/////////////////////////

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    //Player.talked_to_npc = false;
    //Player.game_solved = false;
    //Player.has_key = false;
    GameInputs inputs;
    
    MapItem* item = NULL;
    

    //******************
    // TODO: Implement
    //******************

    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.

    switch(action)
    {
        case GO_UP:
            //TODO: Implement
            //1. Check the item north of the player
            //2. Make sure to not walk through walls
            //3. If it is not a wall, the walk up by updating player's coordinates

            if (get_north(Player.x, Player.y) -> walkable || Player.ramble) { // able to walk
                Player.y--; 
            }
            return NO_RESULT;
            break;
            
        case GO_LEFT:
            //TODO: Implement

            if (get_west(Player.x, Player.y) -> walkable || Player.ramble) { // able to walk
                Player.x--; 
            }
            return NO_RESULT;
            break;
            
        case GO_DOWN:
            //TODO: Implement

            if (get_south(Player.x, Player.y) -> walkable || Player.ramble) { // able to walk
                Player.y++; 
            }
            return NO_RESULT;
            break;
            
        case GO_RIGHT:
            //TODO: Implement

            if (get_east(Player.x, Player.y) -> walkable || Player.ramble) { // able to walk
                Player.x++; 
            }
            return NO_RESULT;
            break;


        case RAMBLIN_MODE: // ramblin mode case
            if (!Player.ramble) { // if not active, make active
                speech("Ramblin' mode","activated!");
                Player.ramble = true;
            } else { // if active, deactivate
                speech("Ramblin' mode","deactivated!");
                Player.ramble = false;
            }  
            return FULL_DRAW;
            break;


        case ACTION_BUTTON:

            //******************
            // TODO: Implement
            //******************

            // 1. Check if near NPC, 
            //     - if so, mark the player has talked and give instructions on what to do
            //     - if the game is solved (defeated Buzz), give the player the key
            //     - return FULL_DRAW to redraw the scene


            // 2. Check if near a door
            //    - if the player has the key, you win the game
            //    - if not, show speech bubbles that the play needs to get the key 
            //     -return FULL_DRAW to redraw the scene
            


            // 3. Check if on Buzz's cave
            //    - if the player has talked to the npc, then start the speech bubble to fight buzz
            //    - set the players coordinates for the small map
            //    - and set the map to the small map
            //     -return FULL_DRAW to redraw the scene


            // 4. Check if on a stairs
            //    - if so, move the player the correct coordinates
            //    - and set the map back to the main big map
            //     -return FULL_DRAW to redraw the scene


            // 5. Check if at the right spell to end the game
            //    - if so, use speech bubbles to declare that Buzz has been defeated
            //    - and flag that the game is solved
            //     -return FULL_DRAW to redraw the scene


            // Feel free to add more functions as you make the game!
            
            // check adjacent items
            MapItem *items[9];
            items[0] = get_east(Player.x, Player.y); // E
            items[1] = get_west(Player.x, Player.y); // W
            items[2] = get_north(Player.x, Player.y); // N
            items[3] = get_south(Player.x, Player.y); // S
            items[4] = get_east(Player.x, Player.y - 1); // NE
            items[5] = get_west(Player.x, Player.y - 1); // NW
            items[6] = get_east(Player.x, Player.y + 1); // SE
            items[7] = get_west(Player.x, Player.y + 1); // SW
            items[8] = get_here(Player.x, Player.y); // current pos

            for (int i = 0; i < 9; i++) {
                int itemType = items[i] -> type;
                if (itemType == NPC) { // check NPC
                    if (!Player.talked_to_npc) {   
                        speech("If you want to", "escape Buzz,");             
                        speech("you must seek out", "the cave.");
                        speech("One spell will","defeat Buzz."); 
                        speech("He's hydrophobic.","Choose wisely!"); 
                        Player.talked_to_npc = true;
                    } else if (Player.game_solved) {
                        speech("Congratulations!", "Here is your key!");
                        speech("Find the door.", "Free yourself!");
                        Player.has_key = true;
                    } else {
                        speech("Find the cave.", "Buzz awaits!");
                    }
                    return FULL_DRAW;
                }
                
                if (itemType == DOOR) { // check DOOR
                    if (Player.has_key) {
                        speech("You got the key!","Unlocking door...");
                        speech("Congratulations","on your escape!");
                        return GAME_OVER;
                    }
                    speech("You need the key","to pass this door."); // send player to key
                    return FULL_DRAW;
                }

                if (itemType == CAVE) { // check CAVE
                    //pc.printf("its a cave!");
                    if (Player.talked_to_npc) {
                        speech("You found Buzz's","hideout!");
                        speech("Prepare to fight","Buzz.");
                        speech("You must win","to get the key.");
                        speech("Pick the ","correct spell!");
                        Player.x = 1;
                        Player.y = 8;
                        set_active_map(1); // set to smaller map
                    } else {
                        speech("It's a cave!","");
                        speech("Find someone","to talk to...");
                    }
                    return FULL_DRAW;
                }

                if (itemType == STAIRS) { // check stairs
                    //move player coordinates
                    Player.x = 6;
                    Player.y = 21;
                    speech("Make sure to","pick up your key!");
                    set_active_map(0); // main map
                    return FULL_DRAW;
                }

                if (itemType == WATER) { // water, earth, fire spells. choose water to win
                    speech("Water is highly ","effective!");
                    speech("You have ","defeated Buzz!");
                    speech("Get out of here!","");
                    add_slain_buzz(8, 8);
                    Player.game_solved = true;
                    return FULL_DRAW;
                }

                if (itemType == FIRE) { // water, earth, fire spells. choose water to win
                    speech("Buzz destroyed ","your fire spell!");
                    speech("You need to try","again.");
                    set_active_map(0);
                    return FULL_DRAW;
                }

                if (itemType == EARTH) { // water, earth, fire spells. choose water to win
                    speech("Buzz destroyed ","your earth spell!");
                    speech("You need to try","again.");
                    set_active_map(0);
                    return FULL_DRAW;
                }
            }

            break;
    }
    
    return NO_RESULT;
}




/////////////////////////
// Draw Game
/////////////////////////

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
//            if (init && i == 0 && j == 0) // Only draw the player on init
            if ( i == 0 && j == 0) // always draw the player
            {
                draw_player(u, v, Player.has_key);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
                else if (curr_item && curr_item->type == CLEAR)
                {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status();
    draw_lower_status();
}







/////////////////////////
// Map Intialization
/////////////////////////

// Important locations for all maps
int cb_loc[2] = {5,20}; //Location of the center of the cave


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    //Initialize and sets current map to the first map
    Map* map = set_active_map(0);

    /////////////////////////
    //Initial Environmnet
    /////////////////////////

    //Adding random plants
    pc.printf("Adding Plants!\r\n");
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }

    //Adding wall borders 
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    
    //Adding extra chamber borders 
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    add_door(33, 10, HORIZONTAL, 4);

    //Adding extra cave to Buzz's evil lair
    pc.printf("Add cave\r\n");
    add_cave(cb_loc[0],cb_loc[1],1,1,5,5);      //Cave is set as a 4x4 block to be bigger
    add_cave(cb_loc[0]+1,cb_loc[1],2,1,5,5);
    add_cave(cb_loc[0],cb_loc[1]+1,3,1,5,5);
    add_cave(cb_loc[0]+1,cb_loc[1]+1,4,1,5,5);

    pc.printf("Initial environment completed\r\n");

    /////////////////////////////////
    // Characters and Items for the map
    /////////////////////////////////

    // Add NPC
    add_npc(10, 5);  //NPC is initialized to (x,y) = 10, 5. Feel free to move him around
    
    //***********************************
    // TODO: Implement As Needed
    //***********************************

    //Add any extra characters/items here for your project
    //Add custom sprite: basket
    add_basket(8, 8);
    add_basket(20, 40);
    add_basket(42, 11);

    //Prints out map
    print_map();
}







void init_small_map()
{
    //Sets current map to the second map
    set_active_map(1);


    //***********************************
    // TODO: Implement 
    //***********************************

    // 1. Add walls to the smaller map.
    //    Set the dimensions to be 16x16  <-- you may change to your liking, but must be smaller than the main map
    //    Hint: See how walls are initialized in the main map
    //
    // 2. Add your three spells at different locations
    //
    // 3. Add Evil Buzz at the center of the map

    //Adding wall borders 
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());

    //Encase all spells in walls
    add_wall(6, 0, VERTICAL, 6);
    add_wall(0, 6, HORIZONTAL, 6);
    add_basket(6, 6);
    add_wall(10, 0, VERTICAL, 5);
    add_wall(0, 7, VERTICAL, 9);
    add_wall(0, 0, HORIZONTAL, 8);

    //Adding 3 spells (fire, water, earth)
    pc.printf("Adding spells!\r\n");
    add_water(3, 3);
    add_fire(12, 2);
    add_earth(3, 12);

    //Adding evil buzz
    pc.printf("Adding evil Buzz!\r\n");
    add_buzz(8, 8);

    // You may add any extra characters/items here for your project


    // Add stairs back to main (map 0)
    add_stairs(14, 14, 0, cb_loc[0], cb_loc[1]);
    
}


/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    Player.talked_to_npc = false;
    Player.game_solved = false;
    Player.has_key = false;
    Player.ramble = false;
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");


    //uLCD.filled_rectangle(64, 64, 74, 74, RED); //DELETE OR COMMENT THIS LINE  <-- It is a temporary indicator that your LCD is working before you implement your code
    //<------ DELETE THIS LINE

    while (true) { // hold until button pressed
        uLCD.background_color(BLACK);
        //uLCD.cls();
        uLCD.text_char('W', 5, 8, WHITE);
        uLCD.text_char('E', 6, 8, WHITE);
        uLCD.text_char('L', 7, 8, WHITE);
        uLCD.text_char('C', 8, 8, WHITE);
        uLCD.text_char('O', 9, 8, WHITE);
        uLCD.text_char('M', 10, 8, WHITE);
        uLCD.text_char('E', 11, 8, WHITE);
        uLCD.text_char('!', 12, 8, WHITE);
        if (read_inputs().b1) {
            break;
        }
    }
    // Initialize the maps
    maps_init();
    init_main_map();
    init_small_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;
    Player.has_key = false;
    Player.game_solved = false;
    Player.talked_to_npc = false;

    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {

        ////////////////////////////////
        // TODO: Implement 
        ////////////////////////////////

        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actually do the game update:
        // 1. Read inputs  

        GameInputs inputs = read_inputs();

        // 2. Determine action (get_action) 

        int action = get_action(inputs);

        // 3. Update game (update_game)

        int result = update_game(action);  // Set this variable "result" for the resulting state after update game

        // 3b. Check for game over based on update game result
        if (result == GAME_OVER) {
            break;
        }

        // 4. Draw screen to uLCD
        bool full_draw = false;
        if (result == FULL_DRAW) full_draw = true;
        draw_game(full_draw);
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    // DELETE THIS LINE 

    uLCD.background_color(BLACK);
    uLCD.cls();
    uLCD.text_char('G', 5, 7, WHITE);
    uLCD.text_char('A', 6, 7, WHITE);
    uLCD.text_char('M', 7, 7, WHITE);
    uLCD.text_char('E', 8, 7, WHITE);
    uLCD.text_char('O', 10, 7, WHITE);
    uLCD.text_char('V', 11, 7, WHITE);
    uLCD.text_char('E', 12, 7, WHITE);
    uLCD.text_char('R', 13, 7, WHITE);
    uLCD.text_char('Y', 6, 9, WHITE);
    uLCD.text_char('O', 7, 9, WHITE);
    uLCD.text_char('U', 8, 9, WHITE);
    uLCD.text_char('W', 10, 9, WHITE);
    uLCD.text_char('I', 11, 9, WHITE);
    uLCD.text_char('N', 12, 9, WHITE);
    uLCD.text_char('!', 13, 9, WHITE);
}




/////////////////////////////
//Advanced Features
/////////////////////////////

// Plays a wavfile
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", wav);
    return;
}
