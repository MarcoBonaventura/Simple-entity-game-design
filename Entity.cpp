#define _CRT_SECURE_NO_DEPRECATE

#include "Entity.h"
#include "Define.h"

// code missing here...

#include <iostream>
#include <algorithm>
#include <functional>

#define Maximum(a, b) ((a > b) ? a : b)
#define Minimum(a, b) ((a < b) ? a : b)

// in addition to android/log.h we use SDL_Log() logger too
#include <android/log.h>		// for logcat
#define  LOG_TAG "SDL/APP"  	// the key to filter


int WWIDTH;		// global extern var in define.h
int WHEIGHT;	// global extern var in define.h

std::vector<CEntity*> CEntity::EntityList;
std::map<int, CEntity*> CEntity::EntityMap;
std::map<int, CEntity*> CEntity::TargetEnemyMap;

int CEntity::current_ID = 0;
int CEntity::counter_BRO = 0;


int CEntity::Xp = 0;
int CEntity::Yp = 0;

Entity::Entity() {

    ID = current_ID++;		// the identifier of each entity

    if(this->Type == ENTITY_SIZE_SSX) BRO = counter_BRO++;

    X  = Y  =   0;
    X1 = Y1 =   0;
    X2 = Y2 =   0;
    Xe = Ye =   0;
    Xb = Yb =   0;


    ib = 0;
    kb = 0;

    counter     = 0;

    MoveLeft  = false;
    MoveRight = false;
    MoveUp    = false;
    MoveDown  = false;

    boom      = false;
    Dead      = false;

    SpeedX = 0;
    SpeedY = 0;

    AccelX = 0;
    AccelY = 0;

    Col_X = 0;
    Col_Y = 0;

    // gets Window from another class (not included here)
    Window = AppStateGame::GetInstance()->GetWindow();

    // gets Renderer from another class (not included here)
    entityRenderer = AppStateGame::GetInstance()->GetRenderer();

}

Entity::~Entity() {
    
}


bool Entity::OnLoad(char *File, int Width, int Height, int MaxFrames) {

	this->Width = Width;
	this->Height = Height;

	return true;

}

bool Entity::OnLoad(char *File, int Width, int Height) {

	this->Width = Width;
	this->Height = Height;

	return true;

}

bool Entity::OnLoad(char *File, int RGBalpha) {

    return true;

}

bool Entity::OnLoad(char *File) {

    return true;

}


void Entity::OnLoop() {

    SDL_Log("Entity loop");

}


//==============================================================================
void Entity::OnMove(float MoveX, float MoveY) {

    
}

void Entity::StopMove() {

	
}

void Entity::StopMoveX() {

	
}

void Entity::StopMoveY() {


}

void Entity::OnRender() {


}

void Entity::OnCleanup() {


}

void Entity::OnAnimate() {

    
}

bool Entity::OnCollision(CEntity *Entity) {

    return true;

}

SDL_Rect Entity::GetBounds() {

    SDL_Rect bounds;
    bounds.x = (Sint16)(X);
    bounds.y = (Sint16)(Y);
    bounds.w = (Sint16)(Width);
    bounds.h = (Sint16)(Height);

    return bounds;

}


SDL_Rect Entity::NormalizeBounds(const SDL_Rect& rect) {

    SDL_Rect normalized;

    normalized.x = rect.x - (Sint16)X + Width;
    normalized.y = rect.y - (Sint16)Y;
    normalized.w = rect.w;
    normalized.h = rect.h;

    return normalized;

}

SDL_Rect Entity::Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB) {

    int x1 = Maximum(boundsA.x, boundsB.x);
    int y1 = Maximum(boundsA.y, boundsB.y);

    int x2 = Minimum(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
    int y2 = Minimum(boundsA.y + boundsA.h, boundsB.y + boundsB.h);

    int width   = x2 - x1;
    int height  = y2 - y1;

    if (width > 0 && height > 0)
    {
        SDL_Rect intersect = {x1, y1, width, height};
        return intersect;
    }
    else
    {
        SDL_Rect intersect = {0, 0, 0, 0};
        return intersect;
    }



}


/* Old collision funcs, just for info...
bool Entity::CheckCollision(CEntity *Entity) {


    if ( this->Type != Entity->Type &&
         this != NULL   &&
         this != false  &&
         Entity != NULL &&
         Entity->Dead == false &&
         Entity->Flags ^ ENTITY_FLAG_MAPONLY )
    {

        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_BOSS)	  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_BOSS)	  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;

        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MyBOMB)    goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_PLAYER)    goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;

        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_PLAYER)	  goto jump;
        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;

        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_MyBOMB)    goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;

        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        SDL_Rect collisionRect = Intersection(this->GetBounds(), Entity->GetBounds());

        SDL_Rect normalA = this->NormalizeBounds(collisionRect);
        SDL_Rect normalB = Entity->NormalizeBounds(collisionRect);

        for(int y=0; y<collisionRect.h; y++)
        {
            for(int x=0; x<collisionRect.w; x++)
            {
                if(GetAlphaXY(this, normalA.x + x, normalA.y + y) && GetAlphaXY(Entity, normalB.x + x, normalB.y + y))
                {
                    CEntityCol EntityCol;

                    EntityCol.EntityA = this;
                    EntityCol.EntityB = Entity;

                    CEntityCol::EntityColList.push_back(EntityCol);

                    return true;

                }

            }

        }





    }

    jump:

    return false;

}



bool Entity::GetAlphaXY(CEntity *Entity, int x, int y) {

    int bpp = TextureBank::Get(entityTexture)->bpp;

    Uint8 *p = (Uint8*)TextureBank::Get(entityTexture)->pxl + y * TextureBank::Get(entityTexture)->ptc + x * bpp;

    Uint32 pixelColor;

    switch(bpp)
    {
        case(1):
            pixelColor = *p;
            break;

        case(2):
            pixelColor = *(Uint16*)p;
            break;

        case(3):
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                pixelColor = p[0] << 16 | p[1] << 8 | p[2];
            else
                pixelColor = p[0] | p[1] << 8 | p[2] << 16;
            break;

        case(4):
            pixelColor = *(Uint32*)p;
            break;
    }

    Uint8 red, green, blue, alpha;

    SDL_PixelFormat* format = TextureBank::Get(entityTexture)->fmt;

    SDL_GetRGBA(pixelColor, format, &red, &green, &blue, &alpha);

    return alpha > 128;




}
*/


// new collision detection funcs
void Entity::CheckCollision(CEntity *Entity) {

    if ( this != Entity && this->Dead == false && Entity->Dead == false && Entity->Flags ^ ENTITY_FLAG_MAPONLY )
    {
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
		if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_BOSS)	  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_GENERIC   && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_BOSS)	  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_ENEMY     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;

        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
		if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_BULLET_E  && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_MyBOMB)    goto jump;
		if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_MEDAL     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_PLAYER)    goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_MyBULLET  && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;

		if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
		if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
		if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_PLAYER)	  goto jump;
        if (this->Type == ENTITY_TYPE_GAMMARAY  && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
		
		if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_MyBOMB)    goto jump;
        if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_PARTICLE)  goto jump;
		if (this->Type == ENTITY_TYPE_PLAYER    && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;

        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
		if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_BOSS      && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;

        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_LASER)     goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_GENERIC)   goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_BULLET_E)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_MEDAL)     goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_MyBULLET)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_GAMMARAY)  goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_BOSS)      goto jump;
        if (this->Type == ENTITY_TYPE_LASER     && Entity->Type == ENTITY_TYPE_ENEMY)     goto jump;
		
        SDL_Rect collisionRect = Intersection(this->GetBounds(), Entity->GetBounds());

        if(collisionRect.w > 0 && collisionRect.h > 0)
        {
            // The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;

            // SDL_Rect RectA = mColliders;
            std::vector<SDL_Rect> RectA = this->getColliders();

            // SDL_Rect RectB = EntityRect;
            std::vector<SDL_Rect> RectB = Entity->getColliders();

            // Go through the A boxes
			for (Uint32 Abox = 0; Abox < RectA.size(); Abox++)
            {

                //Calculate the sides of rect A
                leftA   = RectA[Abox].x;
                rightA  = RectA[Abox].x + RectA[Abox].w;
                topA    = RectA[Abox].y;
                bottomA = RectA[Abox].y + RectA[Abox].h;

                // Go through the B boxes
				for (Uint32 Bbox = 0; Bbox < RectB.size(); Bbox++)
                {
                    // Calculate the sides of rect B
                    leftB = RectB[Bbox].x;
                    rightB = RectB[Bbox].x + RectB[Bbox].w;
                    topB = RectB[Bbox].y;
                    bottomB = RectB[Bbox].y + RectB[Bbox].h;

                    // If no sides from A are outside of B
                    if(!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
                    {
						// collision is detected
                        CEntityCol EntityCol;

                        EntityCol.EntityA = this;
                        EntityCol.EntityB = Entity;

                        /** just for debug
                        char TempA[255];
                        int Temp1 = EntityCol.EntityA->Type;
                        int n1 = sprintf(TempA, "%d", Temp1);
                        SDL_Log("EntityA.x: %d",EntityCol.EntityA->X);
                        SDL_Log("EntityA.y: %d",EntityCol.EntityA->Y);

                        char TempB[255];
                        int Temp2 = EntityCol.EntityB->Type;
                        int n2 = sprintf(TempB, "%d", Temp2);
                        SDL_Log("EntityB.x: %d",EntityCol.EntityB->X);
                        SDL_Log("EntityB.y: %d",EntityCol.EntityB->Y);

                        SDL_Log("EntityColEnd");

                        TempA[255];
                        Temp1 = EntityCol.EntityA->Size;
                        n1 = sprintf(TempA, "%d", Temp1);

                        TempB[255];
                        Temp2 = EntityCol.EntityB->Size;
                        n2 = sprintf(TempB, "%d", Temp2);
                        */

                        CEntityCol::EntityColList.push_back(EntityCol);

                        break;
                    }
                }
            }
        }
    }

    jump:

    return;


}

void Entity::CollisionLoop() {

    //LEAVE BLANK!!!!

}

void Entity::shiftColliders() {

	//LEAVE BLANK!!!!

}


std::vector<SDL_Rect>& CEntity::getColliders() {

    return mColliders;

}

bool Entity::Jump() {

    return true;

}


void Entity::ScoreInc() {

}


void Entity::OnFire() {

}

bool Entity::canFIRE() {}

bool Entity::booleanFIRE() {}

void Entity::IA() {

}


int Entity::GetX() {

    return Xp;

}

int Entity::GetY() {

    return Yp;

}

int Entity::EnemyGetX() {}
int Entity::EnemyGetY() {}

float Entity::PlayerGetX() {}
float Entity::PlayerGetY() {}

int Entity::GetEntityMoving() {}


Entity* Entity::GetEntity(int temp_ID) {

    if (EntityMap.find(temp_ID) == EntityMap.end())
    {
        SDL_Log("Map not found");
        return 0;
    }

    return EntityMap[temp_ID];


}


//-----------------------------------------------------------------------------
void Entity::EntityDEL() {

    int temp_ID;

    for(std::vector<CEntity*>::iterator it = CEntity::EntityList.begin(); it != CEntity::EntityList.end();)
    {
        if(!(*it)) continue;
        if((*it)->Dead)
        {
            temp_ID = (*it)->ID;
            if (!CEntity::TargetEnemyMap.empty())
            {
                std::map<int, CEntity*>::iterator iter;
                if(CEntity::TargetEnemyMap.find(this->ID) != CEntity::TargetEnemyMap.end())
                {
                    iter = CEntity::TargetEnemyMap.find(this->ID);
                    CEntity::TargetEnemyMap.erase(iter);
                }
            }


            (*it)->OnCleanup();
            delete *it;
            (it) = CEntity::EntityList.erase(it);
        }
        else
        {
            it++;
        }
    }


	

}

