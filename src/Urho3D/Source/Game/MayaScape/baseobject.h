/*
*/
/** \file
 *  Functions for the base object type.
 */

#pragma once

#include "types.h"

struct BASE_OBJECT;
struct BASE_STATS;
struct SIMPLE_OBJECT;
struct Spacetime;

struct StructureBounds
{
	StructureBounds()
		: map(0,0)
		, size(0,0)
	{}
	StructureBounds(Vector2i const &map, Vector2i const &size) : map(map), size(size) {}
	bool valid()
	{
		return size.x >= 0;
	}

	Vector2i map;           ///< Map coordinates of upper left corner of structure.
	Vector2i size;          ///< Size (in map coordinates) of the structure.
};


static const unsigned int max_check_object_recursion = 4;

/// Get interpolated direction at time t.
Rotation interpolateRot(Rotation v1, Rotation v2, uint32_t t1, uint32_t t2, uint32_t t);
/// Get interpolated object spacetime at time t.
Spacetime interpolateObjectSpacetime(const SIMPLE_OBJECT *obj, uint32_t t);

void checkObject(const SIMPLE_OBJECT *psObject, const char *const location_description, const char *function, const int recurse);

/* assert if object is bad */
#define CHECK_OBJECT(object) checkObject((object), AT_MACRO, __FUNCTION__, max_check_object_recursion)

#define syncDebugObject(psObject, ch) _syncDebugObject(__FUNCTION__, psObject, ch)
void _syncDebugObject(const char *function, SIMPLE_OBJECT const *psObject, char ch);

Vector2i getStatsSize(BASE_STATS const *pType, uint16_t direction);
StructureBounds getStructureBounds(BASE_OBJECT const *object);
StructureBounds getStructureBounds(BASE_STATS const *stats, Vector2i pos, uint16_t direction);
