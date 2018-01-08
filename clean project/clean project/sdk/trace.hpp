#pragma once
#include <windows.h>
#include "angles.hpp"
#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

#define   CONTENTS_EMPTY                0

#define   CONTENTS_SOLID                0x1       
#define   CONTENTS_WINDOW               0x2
#define   CONTENTS_AUX                  0x4
#define   CONTENTS_GRATE                0x8
#define   CONTENTS_SLIME                0x10
#define   CONTENTS_WATER                0x20
#define   CONTENTS_BLOCKLOS             0x40 
#define   CONTENTS_OPAQUE               0x80 
#define   LAST_VISIBLE_CONTENTS         CONTENTS_OPAQUE

#define   ALL_VISIBLE_CONTENTS            (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define   CONTENTS_TESTFOGVOLUME        0x100
#define   CONTENTS_UNUSED               0x200     
#define   CONTENTS_BLOCKLIGHT           0x400
#define   CONTENTS_TEAM1                0x800 
#define   CONTENTS_TEAM2                0x1000 
#define   CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define   CONTENTS_MOVEABLE             0x4000
#define   CONTENTS_AREAPORTAL           0x8000
#define   CONTENTS_PLAYERCLIP           0x10000
#define   CONTENTS_MONSTERCLIP          0x20000
#define   CONTENTS_CURRENT_0            0x40000
#define   CONTENTS_CURRENT_90           0x80000
#define   CONTENTS_CURRENT_180          0x100000
#define   CONTENTS_CURRENT_270          0x200000
#define   CONTENTS_CURRENT_UP           0x400000
#define   CONTENTS_CURRENT_DOWN         0x800000

#define   CONTENTS_ORIGIN               0x1000000 

#define   CONTENTS_MONSTER              0x2000000 
#define   CONTENTS_DEBRIS               0x4000000
#define   CONTENTS_DETAIL               0x8000000 
#define   CONTENTS_TRANSLUCENT          0x10000000
#define   CONTENTS_LADDER               0x20000000
#define   CONTENTS_HITBOX               0x40000000

#define   SURF_LIGHT                    0x0001 
#define   SURF_SKY2D                    0x0002 
#define   SURF_SKY                      0x0004 
#define   SURF_WARP                     0x0008 
#define   SURF_TRANS                    0x0010
#define   SURF_NOPORTAL                 0x0020 
#define   SURF_TRIGGER                  0x0040 
#define   SURF_NODRAW                   0x0080 

#define   SURF_HINT                     0x0100 

#define   SURF_SKIP                     0x0200   
#define   SURF_NOLIGHT                  0x0400   
#define   SURF_BUMPLIGHT                0x0800   
#define   SURF_NOSHADOWS                0x1000   
#define   SURF_NODECALS                 0x2000   
#define   SURF_NOPAINT                  SURF_NODECALS
#define   SURF_NOCHOP                   0x4000   
#define   SURF_HITBOX                   0x8000   

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define   MASK_ALL                      (0xFFFFFFFF)
#define   MASK_SOLID                    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCSOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCFLUID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_WATER                    (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define   MASK_OPAQUE                   (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define   MASK_OPAQUE_AND_NPCS          (MASK_OPAQUE|CONTENTS_MONSTER)
#define   MASK_BLOCKLOS                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define   MASK_BLOCKLOS_AND_NPCS        (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define   MASK_VISIBLE                  (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_VISIBLE_AND_NPCS         (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define   MASK_SHOT_BRUSHONLY           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define   MASK_SHOT_HULL                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define   MASK_SHOT_PORTAL              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_SOLID_BRUSHONLY          (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define   MASK_NPCSOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC           (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC_FLUID     (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define   MASK_SPLITAREAPORTAL          (CONTENTS_WATER|CONTENTS_SLIME)
#define   MASK_CURRENT                  (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define   MASK_DEADSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

namespace sdk
{
	class IHandleEntity;
	struct ray_t;
	class c_gametrace;
	typedef c_gametrace trace_t;
	class i_collideable;
	class i_tracelistdata;
	class c_physcollide;
	struct cplane_t;
	struct virtualmeshlist_t;
	class entity_t;

	enum class TraceType {
		TRACE_EVERYTHING = 0,
		TRACE_WORLD_ONLY,
		TRACE_ENTITIES_ONLY,
		TRACE_EVERYTHING_FILTER_PROPS,
	};

	class i_tracefilter
	{
	public:
		virtual bool ShouldHitEntity(IHandleEntity *pEntity, int contentsMask) = 0;
		virtual TraceType GetTraceType() const = 0;
	};


	//-----------------------------------------------------------------------------
	// Classes are expected to inherit these + implement the ShouldHitEntity method
	//-----------------------------------------------------------------------------

	// This is the one most normal traces will inherit from
	class c_tracefilter : public i_tracefilter {
	public:
		bool should_hit_entity(IHandleEntity* pEntityHandle, int /*contentsMask*/) {
			return !(pEntityHandle == p_skip);
		}
		virtual TraceType get_trace_type() const {
			return TraceType::TRACE_EVERYTHING;
		}
		void* p_skip;
	};

	class c_tracefilterentitites_only : public i_tracefilter {
	public:
		bool should_hit_entity(IHandleEntity* pEntityHandle, int /*contentsMask*/) {
			return !(pEntityHandle == p_skip);
		}
		virtual TraceType get_trace_type() const {
			return TraceType::TRACE_ENTITIES_ONLY;
		}
		void* p_skip;
	};
	//-----------------------------------------------------------------------------
	// Classes need not inherit from these
	//-----------------------------------------------------------------------------
	class c_traceworldonly : public i_tracefilter {
	public:
		bool should_hit_entity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/) {
			return false;
		}
		virtual TraceType get_trace_type() const {
			return TraceType::TRACE_WORLD_ONLY;
		}
	};

	class c_tracefilterworldandpropsonly : public i_tracefilter {
	public:
		bool should_hit_entity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/) {
			return false;
		}
		virtual TraceType get_trace_type() const {
			return TraceType::TRACE_EVERYTHING;
		}
	};

	class c_simpletracefilter : public i_tracefilter
	{
	public:
		c_simpletracefilter(PVOID pEnt)
		{
			m_pPassEnt = pEnt;
		}

		virtual bool should_hit_entity(IHandleEntity *pHandleEntity, int contentsMask)
		{
			return pHandleEntity != m_pPassEnt;
		}

		virtual TraceType	get_trace_type() const
		{
			return TraceType::TRACE_EVERYTHING;
		}

		PVOID m_pPassEnt;
	};

	class c_tracefilterhitall : public c_tracefilter {
	public:
		virtual bool should_hit_entity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/) {
			return true;
		}
	};

	enum class DebugTraceCounterBehavior_t {
		kTRACE_COUNTER_SET = 0,
		kTRACE_COUNTER_INC,
	};

	//-----------------------------------------------------------------------------
	// Enumeration interface for EnumerateLinkEntities
	//-----------------------------------------------------------------------------
	class i_entityenumerator
	{
	public:
		// This gets called with each handle
		virtual bool enum_entity(IHandleEntity *pHandleEntity) = 0;
	};


	struct BrushSideInfo_t {
		vec3_t plane;               // The plane of the brush side
		unsigned short bevel;    // Bevel plane?
		unsigned short thin;     // Thin?
	};

	class c_physcollide;

	struct vcollide_t {
		unsigned short solidCount : 15;
		unsigned short isPacked : 1;
		unsigned short descSize;
		// VPhysicsSolids
		c_physcollide   **solids;
		char           *pKeyValues;
		void           *pUserData;
	};

	struct cmodel_t {
		vec3_t         mins, maxs;
		vec3_t         origin;        // for sounds or lights
		int            headnode;
		vcollide_t     vcollisionData;
	};

	struct csurface_t {
		const char     *name;
		short          surfaceProps;
		unsigned short flags;         // BUGBUG: These are declared per surface, not per material, but this database is per-material now
	};

	//-----------------------------------------------------------------------------
	// A ray...
	//-----------------------------------------------------------------------------
	struct ray_t {
		vec3_tAligned  m_Start;  // starting point, centered within the extents
		vec3_tAligned  m_Delta;  // direction + length of the ray
		vec3_tAligned  m_StartOffset; // Add this to m_Start to get the actual ray start
		vec3_tAligned  m_Extents;     // Describes an axis aligned box extruded along a ray
		const matrix3x4_t *m_pWorldAxisTransform;
		bool m_IsRay;  // are the extents zero?
		bool m_IsSwept;     // is delta != 0?

		ray_t() : m_pWorldAxisTransform(NULL) {}

		void init(vec3_t const& start, vec3_t const& end) {
			m_Delta = end - start;

			m_IsSwept = (m_Delta.LengthSqr() != 0);

			m_Extents.Init();

			m_pWorldAxisTransform = NULL;
			m_IsRay = true;

			// Offset m_Start to be in the center of the box...
			m_StartOffset.Init();
			vec3_tCopy(start, m_Start);
		}

		void init(vec3_t const& start, vec3_t const& end, vec3_t const& mins, vec3_t const& maxs) {
			m_Delta = end - start;

			m_pWorldAxisTransform = NULL;
			m_IsSwept = (m_Delta.LengthSqr() != 0);

			m_Extents = maxs - mins;
			m_Extents *= 0.5f;
			m_IsRay = (m_Extents.LengthSqr() < 1e-6);

			// Offset m_Start to be in the center of the box...
			m_StartOffset = maxs + mins;
			m_StartOffset *= 0.5f;
			m_Start = start + m_StartOffset;
			m_StartOffset *= -1.0f;
		}
		vec3_t inv_delta() const {
			vec3_t vecInvDelta;
			for (int iAxis = 0; iAxis < 3; ++iAxis) {
				if (m_Delta[iAxis] != 0.0f) {
					vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];
				}
				else {
					vecInvDelta[iAxis] = FLT_MAX;
				}
			}
			return vecInvDelta;
		}

	private:
	};

	class c_basetrace {
	public:
		bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
		bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
		bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
		bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
		bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

	public:

		// these members are aligned!!
		vec3_t         startpos;                // start position
		vec3_t         endpos;                       // final position
		cplane_t       plane;                        // surface normal at impact

		float          fraction;                // time completed, 1.0 = didn't hit anything

		int            contents;                // contents on other side of surface hit
		unsigned short dispFlags;                    // displacement flags for marking surfaces with data

		bool           allsolid;                // if true, plane is not valid
		bool           startsolid;                   // if true, the initial point was in a solid area

		c_basetrace() {}

	};

	class c_gametrace : public c_basetrace
	{
	public:
		bool                    did_hit_world() const;
		bool                    did_hit_non_world_entity() const;
		int                     get_entity_index() const;
		bool                    did_hit() const;
		bool					is_visible() const;

	public:

		float                   fractionleftsolid;
		csurface_t              surface;
		int                     hitgroup;
		short                   physicsbone;
		unsigned short          worldSurfaceIndex;
		entity_t*        m_pEnt;
		int                     hitbox;

		c_gametrace() { }

	private:
		c_gametrace(const c_gametrace& vOther);
	};
}