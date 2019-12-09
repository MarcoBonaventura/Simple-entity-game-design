/* Standard old school Entity class in C++ for game design programming */

#ifndef _ENTITY_H_
    #define _ENTITY_H_

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <string>
#include <exception>
#include <map>


// code missing here...



// type of entity
enum eType
{
    ENTITY_TYPE_GENERIC     = 0,
    ENTITY_TYPE_PLAYER      = 1,
    ENTITY_TYPE_BOSS        = 2,
    ENTITY_TYPE_MyBULLET    = 3,
    ENTITY_TYPE_BULLET_E    = 4,
    ENTITY_TYPE_PARTICLE    = 5,
    ENTITY_TYPE_MyBOMB      = 6,
    ENTITY_TYPE_MEDAL       = 7,
	ENTITY_TYPE_GAMMARAY	= 8,
    ENTITY_TYPE_LASER       = 9,
    ENTITY_TYPE_ENEMY		= 10
};

// size of entity (for collision detection)
enum eSize
{
    ENTITY_SIZE_PP          = 0,
    ENTITY_SIZE_SX          = 1,
    ENTITY_SIZE_SSX         = 2,
    ENTITY_SIZE_MM          = 3,
    ENTITY_SIZE_BB          = 4,
    ENTITY_SIZE_BOSS        = 5,
    ENTITY_SIZE_BOMB        = 6,
    ENTITY_SIZE_ROCKET      = 7,
    ENTITY_SIZE_MEDAL       = 8,
    ENTITY_SIZE_PB          = 9,
    ENTITY_SIZE_AST         = 10,
    ENTITY_SIZE_JOLLY       = 11,
    ENTITY_SIZE_NONE		= 12
};

// this flag is for physics interaction
enum eFlag
{
    ENTITY_FLAG_NONE        = 0,
    ENTITY_FLAG_GRAVITY     = 1,
    ENTITY_FLAG_GHOST       = 2,
    ENTITY_FLAG_MAPONLY     = 3,
    ENTITY_FLAG_ENEMY_S     = 4,
    ENTITY_FLAG_ENEMY_M     = 5,
	ENTITY_FLAG_ENEMY_M1	= 6,
	ENTITY_FLAG_ENEMY_M2	= 7,
    ENTITY_FLAG_ENEMY_F     = 8,
    ENTITY_FLAG_PLAYER      = 9,
    ENTITY_FLAG_BOSS        = 10,
    ENTITY_FLAG_GAMMARAY    = 11,
    ENTITY_FLAG_MyBULLET	= 12
};

// how to move the entity
enum eMove
{
	BEZIER 		= 0,
	LOGARITMIC 	= 1,
	BEZIER_BOSS = 2,
	MOVE_DX 	= 3,
	MOVE_SX 	= 4,
	MOVE_DOWN 	= 5,
	ESCAPE_DX 	= 6,
	ESCAPE_SX 	= 7,
	ROTATE 		= 8,
	FALLING 	= 9,
	SNAKE 		= 10,
	PYRAMID     = 11,
	DIAMOND     = 12,
	GRID        = 13,
    ASTEROID    = 14,
    NONE        = 15
};

// entity enemy fire mode
enum EnemyFireMode
{
    NORMAL          = 0,
    SNIPER          = 1,
    ROCKET          = 2,
    SMART           = 3
};

// in-game bonus
enum MedalFire
{
    MEDAL_NONE      = 0,
    MEDAL_TRIPLE 	= 1,
    MEDAL_PENTA		= 2,
    MEDAL_ROCKET	= 3,
    MEDAL_GAMMARAY  = 4,
    MEDAL_COMBOTOT  = 5

};

// Boss final-level scheme
enum BossPath
{
    BOSS_LF_RX  = 0,
    BOSS_ABC    = 1,
    BOSS_RANDOM = 2,
    BOSS_SEEK   = 3
};



struct Vector {

    float X;
    float Y;

    Vector()
    {
        X = 0.0f;
        Y = 0.0f;
    }


};


class Entity {

    
    protected:

        CAnimation      Anim_Control;

		// SDL Renderer, Window and Surface
        SDL_Renderer*   entityRenderer;
        SDL_Window*     Window;		
        SDL_Surface*    PrimarySurface;
		
		float       SpeedX;
        float       SpeedY;
		
		float       AccelX;
        float       AccelY;
		float		kAcc;



    public:
	
		static std::vector<CEntity*>EntityList;			// the main container of every entity
		static std::map<int, CEntity*> EntityMap;		// 
		static std::map<int, CEntity*> TargetEnemyMap;

        //static const int DOT_VEL = 1;

        std::string     entityTexture;

        bool collision;

		// the unique ID for every entity
		int ID, BRO;
		static int current_ID;
		static int counter_BRO;

        int             X, X1, X2;
        int             Y, Y1, Y2;

        int             mx, my;

        int             ib, kb;

        int             *XXP = &X;
        int             *YYP = &Y;
        int             *pX2 = &X2;
        int             *pY2 = &Y2;

        static int      Xp, Yp;

        int             Width, W2;		// for SDL2 rendering: Width for destination SDL_Rect, W2 for source SDL_Rect
        int             Height, H2;		// as like as Width/W2 properties

        int 			selected;

        int             counter;
		int 			Laser_time;
		int				targetID;

        int             PlayerScore;
        int             playerHonor;
        int             medalHonor;
        int             medalReward;
		int 			stamina;

        //-------------------------
        //SDL2 collision properties
        int mPosX, mPosY;
        //The velocity of the dot
		int mVelX, mVelY;
        
		// a container for every entity pixel to detect a collision 
		std::vector<SDL_Rect> mColliders;
	    int r;
        
		
        int         AnimState;

        int         Sound_explSX, Sound_PlayerFire, Sound_PlayerXPL;

        bool        MoveLeft, MoveRight, MoveUp, MoveDown;
        bool        boom;

        char        *anim_filename;		// sprite made-up by 14 frames 

        int         Type, Size, Flags, Move;
        eMove       motion;
		
		int 		Pattern;
        int         EnemyFireMode;

        bool        Dead = false;
        
        int         shot, fire, hit;
        int         TimeStart;
        int         triggerFIRE;
        SDL_Point   EnemyLimit;

        Vector      position;
        Vector      origin;

   
        float       MaxSpeedX,MaxSpeedY, MinSpeedX, MinSpeedY;
        
    

		Entity();
		
		virtual ~CEntity();

	
        virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        virtual bool OnLoad(char* File, int Width, int Height);

        virtual bool OnLoad(char* File, int RGBalpha);

        virtual bool OnLoad(char* File);

        virtual void OnLoop();		

        virtual void OnRender();

        void OnCleanup();	

        virtual void EntityDEL();

        virtual void OnAnimate();

		virtual bool OnCollision(CEntity* Entity);		// collision detected, here we select what to do

		virtual void CollisionLoop();		// check entity collision

		std::vector<SDL_Rect>& getColliders();
        virtual void shiftColliders();

        virtual void OnFire();

        bool canFIRE();
        bool booleanFIRE();

        virtual void IA();		// enetity enemie's "mind"

		static int GetX();
		static int GetY();

		static CEntity* GetEntity(int temp_ID);

		int GetEntityMoving();

		virtual int		EnemyGetX();
		virtual int		EnemyGetY();

		virtual float	PlayerGetX();
		virtual float 	PlayerGetY();

		bool    Jump();

		bool    Crash();

		void    ScoreInc();

    public:

        void    OnMove(float MoveX, float MoveY);

        void    StopMove();
		void    StopMoveX();
		void    StopMoveY();


		/* old func for pixel collision detection (not used anymore) 
        SDL_Rect GetBounds();

        SDL_Rect NormalizeBounds(const SDL_Rect& rect);

        bool CollisionEntity(CEntity *Entity, int NewX, int NewY);

        static SDL_Rect Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB);

        bool CheckCollision(CEntity *Entity);

        //SDL2 Collision Engine
        bool CheckCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);
        void CheckCollision(CEntity* Entity);
        bool GetAlphaXY(CEntity* Entity, int x, int y);
		*/

};


class CEntityCol {

    public:
        static std::vector<CEntityCol>  EntityColList;

    public:
        CEntity *EntityA;
        CEntity *EntityB;


    public:
        CEntityCol();
};



#endif
