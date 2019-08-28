struct GameObject;
struct Program;
struct ScriptInstance;

#pragma pack(1)
struct Art {
	long flags;
	char path[16];
	char* names;
	long d18;
	long total;
};

#pragma pack(1)
struct AnimationSet {
	long currentAnim;
	long counter;
	long animCounter;
	long flags;
	struct Animation {
		long number;
		long source;
		long target;
		long data1;
		long elevation;
		long animCode;
		long delay;
		long(__fastcall *callFunc)(DWORD, DWORD);
		long(__fastcall *callFunc3)(DWORD, DWORD);
		long flags;
		long data2;
		long frmPtr;
	} animations[55];
};

static_assert(sizeof(AnimationSet) == 2656, "Incorrect AnimationSet definition.");

// Bounding rectangle, used by tile_refresh_rect and related functions.
#pragma pack(1)
struct BoundRect {
	long x;
	long y;
	long offx;
	long offy;
};

// Game objects (items, critters, etc.), including those stored in inventories.
#pragma pack(1)
struct GameObject {
	long id;
	long tile;
	long x;
	long y;
	long sx;
	long sy;
	long frm;
	long rotation;
	long artFid;
	long flags;
	long elevation;
	long invenSize;
	long invenMax;
	struct InvenItem {
		GameObject *object;
		long count;
	} *invenTable;

	union {
		struct {
			char updatedFlags[4];
			// for weapons - ammo in magazine, for ammo - amount of ammo in last ammo pack
			long charges;
			// current type of ammo loaded in magazine
			long ammoPid;
			char gap_44[32];
		} item;
		struct {
			long reaction;
			// 1 - combat, 2 - enemies out of sight, 4 - running away
			long combatState;
			// aka action points
			long movePoints;
			long damageFlags;
			long damageLastTurn;
			long aiPacket;
			long teamNum;
			long whoHitMe;
			long health;
			long rads;
			long poison;
		} critter;
	};
	DWORD protoId;
	long cid;
	long lightDistance;
	long lightIntensity;
	DWORD outline;
	long scriptId;
	GameObject* owner;
	long scriptIndex;

	inline char Type() {
		return (protoId >> 24);
	}
	inline char TypeFid() {
		return ((artFid >> 24) & 0x0F);
	}
};

// Results of compute_attack_() function.
#pragma pack(1)
struct ComputeAttackResult {
	GameObject* attacker;
	long hitMode;
	GameObject* weapon;
	long field_C;
	long attackerDamage;
	long attackerFlags;
	long numRounds;
	long message;
	GameObject* target;
	long targetTile;
	long bodyPart;
	long targetDamage;
	long targetFlags;
	long knockbackValue;
	GameObject* mainTarget;
	long numExtras;
	GameObject* extraTarget[6];
	long extraBodyPart[6];
	long extraDamage[6];
	long extraFlags[6];
	long extraKnockbackValue[6];
};

// Script instance attached to an object or tile (spatial script).
#pragma pack(1)
struct ScriptInstance {
	long id;
	long next;
	// first 3 bits - elevation, rest - tile number
	long elevationAndTile;
	long spatialRadius;
	long flags;
	long scriptIdx;
	Program *program;
	long selfObjectId;
	long localVarOffset;
	long numLocalVars;
	long returnValue;
	long action;
	long fixedParam;
	GameObject *selfObject;
	GameObject *sourceObject;
	GameObject *targetObject;
	long actionNum;
	long scriptOverrides;
	char gap_48[4];
	long howMuch;
	char gap_50[4];
	long procedureTable[28];
};

// Script run-time data
#pragma pack(1)
struct Program {
	const char* fileName;
	long *codeStackPtr;
	char gap_8[8];
	long *codePtr;
	long field_14;
	char gap_18[4];
	long *dStackPtr;
	long *aStackPtr;
	long *dStackOffs;
	long *aStackOffs;
	char gap_2C[4];
	long *stringRefPtr;
	char gap_34[4];
	long *procTablePtr;
};

#pragma pack(1)
struct ItemButtonItem {
	GameObject* item;
	union {
		long flags;
		struct {
			char cantUse;
			char itsWeapon;
			short unkFlag;
		};
	};
	long primaryAttack;
	long secondaryAttack;
	long mode;
	long fid;
};

// When gained, the perk increases Stat by StatMod, which may be negative. All other perk effects come from being
// specifically checked for by scripts or the engine. If a primary stat requirement is negative, that stat must be
// below the value specified (e.g., -7 indicates a stat must be less than 7). Operator is only non-zero when there
// are two skill requirements. If set to 1, only one of those requirements must be met; if set to 2, both must be met.
#pragma pack(1)
struct PerkInfo {
	const char* name;
	const char* description;
	long image;
	long ranks;
	long levelMin;
	long stat;
	long statMod;
	long skill1;
	long skill1Min;
	long skillOperator;
	long skill2;
	long skill2Min;
	long strengthMin;
	long perceptionMin;
	long enduranceMin;
	long charismaMin;
	long intelligenceMin;
	long agilityMin;
	long luckMin;
};

#pragma pack(1)
struct DbFile {
	long fileType;
	void* handle;
};

#pragma pack(1)
struct ElevatorExit {
	long id;
	long elevation;
	long tile;
};

#pragma pack(1)
struct ElevatorFrms {
	DWORD main;
	DWORD buttons;
};

#pragma pack(1)
struct FrmFile {
	long id;				//0x00
	short fps;				//0x04
	short actionFrame;		//0x06
	short frames;			//0x08
	short xshift[6];		//0x0a
	short yshift[6];		//0x16
	long oriFrameOffset[6];	//0x22
	long frameAreaSize;		//0x3a
	short width;			//0x3e
	short height;			//0x40
	long frameSize;			//0x42
	short xoffset;			//0x46
	short yoffset;			//0x48
	BYTE pixels[80 * 36];	//0x4a
};

//structures for holding frms loaded with fallout2 functions
#pragma pack(1)
typedef class FrmFrameData { // sizeof 12 + 1 byte
public:
	WORD width;
	WORD height;
	DWORD size;   // width * height
	WORD x;
	WORD y;
	BYTE data[1]; // begin frame data
} FrmFrameData;

#pragma pack(2)
typedef class FrmHeaderData { // sizeof 62
public:
	DWORD version;        // version num
	WORD fps;             // frames per sec
	WORD actionFrame;
	WORD numFrames;       // number of frames per direction
	WORD xCentreShift[6]; // shift in the X direction, of frames with orientations [0-5]
	WORD yCentreShift[6]; // shift in the Y direction, of frames with orientations [0-5]
	DWORD oriOffset[6];   // offset of first frame for direction [0-5] from begining of frame area
	DWORD frameAreaSize;  // size of all frames area
} FrmHeaderData;

// structures for loading unlisted frms
#pragma pack(1)
struct UnlistedFrm {
	DWORD version;
	WORD FPS;
	WORD actionFrame;
	WORD numFrames;
	WORD xCentreShift[6];
	WORD yCentreShift[6];
	DWORD oriOffset[6];
	DWORD frameAreaSize;

	struct Frame {
		WORD width;
		WORD height;
		DWORD size;
		WORD x;
		WORD y;
		BYTE *indexBuff;

		Frame() {
			width = 0;
			height = 0;
			size = 0;
			x = 0;
			y = 0;
			indexBuff = nullptr;
		}
		~Frame() {
			if (indexBuff != nullptr)
				delete[] indexBuff;
		}
	} *frames;

	UnlistedFrm() {
		version = 0;
		FPS = 0;
		actionFrame = 0;
		numFrames = 0;
		for (int i = 0; i < 6; i++) {
			xCentreShift[i] = 0;
			yCentreShift[i] = 0;
			oriOffset[i] = 0;
		}
		frameAreaSize = 0;
		frames = nullptr;
	}
	~UnlistedFrm() {
		if (frames != nullptr)
			delete[] frames;
	}
};

#pragma pack(1)
struct MessageNode {
	long number;
	long flags;
	char* audio;
	char* message;

	MessageNode() {
		number = 0;
		flags = 0;
		audio = nullptr;
		message = nullptr;
	}
};

//for holding msg array
#pragma pack(1)
typedef struct MessageList {
	long numMsgs;
	MessageNode *nodes;

	MessageList() {
		nodes = nullptr;
		numMsgs = 0;
	}
} MessageList;

#pragma pack(1)
struct CritInfo {
	union {
		struct {
			// This is divided by 2, so a value of 3 does 1.5x damage, and 8 does 4x damage.
			long damageMult;
			// This is a flag bit field (DAM_*) controlling what effects the critical causes.
			long effectFlags;
			// This makes a check against a (SPECIAL) stat. Values of 2 (endurance), 5 (agility), and 6 (luck) are used, but other stats will probably work as well. A value of -1 indicates that no check is to be made.
			long statCheck;
			// Affects the outcome of the stat check, if one is made. Positive values make it easier to pass the check, and negative ones make it harder.
			long statMod;
			// Another bit field, using the same values as EffectFlags. If the stat check is failed, these are applied in addition to the earlier ones.
			long failureEffect;
			// The message to show when this critical occurs, taken from combat.msg .
			long message;
			// Shown instead of Message if the stat check is failed.
			long failMessage;
		};
		long values[7];
	};
};

#pragma pack(1)
struct SkillInfo
{
	const char* name;
	const char* description;
	long attr;
	long image;
	long base;
	long statMulti;
	long statA;
	long statB;
	long skillPointMulti;
	// Default experience for using the skill: 25 for Lockpick, Steal, Traps, and First Aid, 50 for Doctor, and 100 for Outdoorsman.
	long experience;
	// 1 for Lockpick, Steal, Traps; 0 otherwise
	long f;
};

#pragma pack(1)
struct StatInfo {
	const char* dame;
	const char* description;
	long image;
	long minValue;
	long maxValue;
	long defaultValue;
};

#pragma pack(1)
struct TraitInfo {
	const char* name;
	const char* description;
	long image;
};

//fallout2 path node structure
#pragma pack(1)
struct PathNode {
	char* path;
	void* pDat;
	long isDat;
	PathNode* next;
};

#pragma pack(1)
struct PremadeChar {
	char path[20];
	DWORD fid;
	char unknown[20];
};

// In-memory PROTO structure, not the same as PRO file format.
#pragma pack(1)
struct Proto {
	struct Tile {
		long scriptId;
		Material material;
	};

	struct Item {
		struct Weapon {
			long animationCode;
			long minDamage;
			long maxDamage;
			long damageType;
			long maxRange[2];
			long projectilePid;
			long minStrength;
			long movePointCost[2];
			long critFailTable;
			long perk;
			long burstRounds;
			long caliber;
			long ammoPid;
			long maxAmmo;
			// shot sound ID
			long soundId;
			long gap_68;
		};

		struct Ammo {
			long caliber;
			long packSize;
			long acAdjust;
			long drAdjust;
			long damageMult;
			long damageDiv;
			char gap_3c[48];
		};

		struct Armor {
			long armorClass;
			// for each DamageType
			long damageResistance[7];
			// for each DamageType
			long damageThreshold[7];
			long perk;
			long maleFrameNum;
			long femaleFrameNum;
		};

		struct Container {
			// container size capacity (not weight)
			long maxSize;
			// 1 - has use animation, 0 - no animation
			long openFlags;
		};

		struct Drug {
			long stats[3];
			long immediateEffect[3];
			struct DelayedEffect {
				// delay for the effect
				long duration;
				// effect amount for each stat
				long effect[3];
			} delayed[2];
			long addictionRate;
			long addictionEffect;
			long addictionOnset;
			char gap_68[4];
		};

		struct Misc {
			long powerPid;
			long powerType;
			long maxCharges;
		};

		struct Key {
			long keyCode;
		};

		long flags;
		long flagsExt;
		// 0x0Y00XXXX: Y - script type (0=s_system, 1=s_spatial, 2=s_time, 3=s_item, 4=s_critter); XXXX - number in scripts.lst. -1 means no script.
		long scriptId;
		ItemType type;

		union {
			Weapon weapon;
			Ammo ammo;
			Armor armor;
			Container container;
			Drug drug;
			Misc misc;
			Key key;
		};
		Material material; // should be at 0x6C
		long size;
		long weight;
		long cost;
		long inventoryFid;
		BYTE soundId;
	};

	struct Critter {
		struct Stats {
			long strength;
			long perception;
			long endurance;
			long charisma;
			long intelligence;
			long agility;
			long luck;
			long health;
			// max move points (action points)
			long movePoints;
			long armorClass;
			// not used by engine
			long unarmedDamage;
			long meleeDamage;
			long carryWeight;
			long sequence;
			long healingRate;
			long criticalChance;
			long betterCriticals;
			// for each DamageType
			long damageThreshold[7];
			// for each DamageType
			long damageResistance[7];
			long radiationResistance;
			long poisonResistance;
			long age;
			long gender;
		};

		long flags;
		long flagsExt;
		long scriptId;
		long critterFlags;

		Stats base;
		Stats bonus;

		long skills[SKILL_count];

		long bodyType;
		long experience;
		long killType;
		long damageType;
		long headFid;
		long aiPacket;
		long teamNum;
	};

	struct Scenery {
		struct Door {
			long openFlags;
			long keyCode;
		};
		struct Stairs {
			long elevationAndTile;
			long mapId;
		};
		struct Elevator {
			long id;
			long level;
		};

		long flags;
		long flagsExt;
		long scriptId;
		ScenerySubType type;
		union {
			Door door;
			Stairs stairs;
			Elevator elevator;
		};
		Material material;
		char gap_30[4];
		BYTE soundId;
	};

	struct Wall {
		long flags;
		long flagsExt;
		long scriptId;
		Material material;
	};

	struct Misc {
		long flags;
		long flagsExt;
	};

	long pid;
	long messageNum;
	long fid;
	// range 0-8 in hexes
	long lightDistance;
	// range 0 - 65536
	long lightIntensity;
	union {
		Tile tile;
		Item item;
		Critter critter;
		Scenery scenery;
		Wall wall;
		Misc misc;
	};
};

static_assert(offsetof(Proto, item) + offsetof(Proto::Item, material) == 0x6C, "Incorrect Proto definition.");

#pragma pack(1)
struct ScriptListInfoItem {
	char fileName[16];
	long numLocalVars;
};

//for holding window info
#pragma pack(1)
struct Window {
	long ref;
	long flags;
	RECT wRect;
	long width;
	long height;
	long clearColour;
	long unknown2;
	long unknown3;
	BYTE *surface; // bytes frame data ref to palette
	long buttonListP;
	long unknown5;//buttonptr?
	long unknown6;
	long unknown7;
	long drawFuncP;
};

#pragma pack(1)
struct LSData {
	char signature[24];
	short majorVer;
	short minorVer;
	char charR;
	char playerName[32];
	char comment[30];
	char unused1;
	short realMonth;
	short realDay;
	short realYear;
	short unused2;
	long realTime;
	short gameMonth;
	short gameDay;
	short gameYear;
	short unused3;
	long gameTime;
	short mapElev;
	short mapNumber;
	char mapName[16];
};

#pragma pack(1)
struct AIcap {
	long name;
	long packet_num;
	long max_dist;
	long min_to_hit;
	long min_hp;
	long aggression;
	long hurt_too_much;
	long secondary_freq;
	long called_freq;
	long font;
	long color;
	long outline_color;
	long chance;
	long combat_message_data[24];
	long area_attack_mode;
	long run_away_mode;
	long best_weapon;
	long distance;
	long attack_who;
	long chem_use;
	long chem_primary_desire;
	long chem_primary_desire1;
	long chem_primary_desire2;
	long disposition;
	long body_type;
	long general_type;
};

#pragma pack(1)
struct Queue {
	DWORD time;
	long type;
	GameObject* object;
	long data;
	Queue* next;
};

struct QueueDrug {
	DWORD pid;
	fo::Stat stat0;
	fo::Stat stat1;
	fo::Stat stat2;
	long amount0;
	long amount1;
	long amount2;
};

struct QueueAddict {
	long  init;      // 1 = perk is not active yet
	DWORD drugPid;
	fo::Perk perkId; // effect of addiction
};

#pragma pack(1)
struct DrugInfoList {
	DWORD itemPid;
	long addictGvar;
	long numEffects;
};