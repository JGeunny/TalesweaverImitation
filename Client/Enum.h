#pragma once
namespace DIR
{
	enum DIR { UP, DOWN, LEFT, RIGHT };
}

namespace OBJID
{
	enum ID { TILE, CIRCLE, PLAYER, UNIT, WALL, BUILDING, AIRPLANE, ITEM, SKILL, SKILL_CRASH, EFFECT, MENUUI, UI, MYFONT, MOUSE, END };
}

namespace IMGID
{
	enum ID { TITLE, BACKGROUND, END };
}

namespace UNIT_STATEID
{
	enum ID { IDLE, ATTACK, BEATTACKED, FOLLOW, DOSKILL, SLIDING, DEAD, END };
}

namespace OBJ_STATEID
{
	enum ID { DEAD, OVERPOWER, RUN, END };
}

namespace OBJ_TIMEID
{
	enum ID { LIVE, SKILL, RECOVERY, DEAD, RUN, END };
}

namespace SKILL_STATEID
{
	enum ID { BOUNCE, END };
}

