#include "menu/submenu.h"

class SpawnEntityManagerMenu : public Submenu {
public:
	static SpawnEntityManagerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnEntityManagerMenu() : Submenu() {}
	~SpawnEntityManagerMenu();
};

namespace SpawnEntityManagerMenuVars
{
	struct Vars {

	};

	enum eEntityTypes {
		EntityTypePed = 1,
		EntityTypeVehicle = 2,
		EntityTypeObject = 3,
		EntityTypeMapMod = 4,
	};

	typedef struct {
		bool m_taken;
		int m_type;
		char m_name[75];
		Entity m_handle;
		Vector3 m_origin;
		Hash m_model;
		__int64 m_address;
		bool m_godmode;
		bool m_frozen;
		int m_creation;
		bool m_showcreation;
	} SpawnedEntity;

	extern SpawnedEntity Spawned[500];
	extern int m_selectedEntityToManage;
	extern bool RemoveEntityFromDB(Entity Handle);
}