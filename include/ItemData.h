#pragma once

#include <vector>  // vector
#include <string>

class AlchemyItem;
class TESSoulGem;

namespace RE
{
	class InventoryEntryData;
	class TESForm;
	class TESObjectARMO;
	class TESObjectBOOK;
	class TESObjectMISC;
	class TESObjectREFR;
	class TESObjectWEAP;
}


enum
{
	kDebugType_Name,
	kDebugType_Count,
	kDebugType_Value,
	kDebugType_Weight,
	kDebugType_Type,
	kDebugType_Read,
	kDebugType_Enchanted,
	kDebugType_PickPocketChance,
	kDebugType_ValuePerWeight,
	kDebugType_Priority
};


#define ITEM_DATA_DEBUG_ENABLED	false
#if ITEM_DATA_DEBUG_ENABLED
#pragma message("ItemData debugging is enabled! Don't forget to disable it!")
#endif
#define ITEM_DATA_DEBUG_TYPE	kDebugType_ValuePerWeight


namespace QuickLootRE
{
	class ItemData
	{
	private:
		typedef int(*FnCompare)(const ItemData& a_lhs, const ItemData& a_rhs);


		enum Priority : UInt32
		{
			kPriority_Key,
			kPriority_Gold,
			kPriority_LockPick,
			kPriority_Ammo,
			kPriority_SoulGem,
			kPriority_Potion,
			kPriority_Poison,
			kPriority_EnchantedWeapon,
			kPriority_EnchantedArmor,
			kPriority_Gem,
			kPriority_Amulet,
			kPriority_Ring,
			kPriority_Weapon,
			kPriority_Armor,
			kPriority_Food,
			kPriority_Other = kPriority_Food,
		};


		enum Type : UInt32
		{
			kType_None,
			kType_DefaultWeapon,
			kType_WeaponSword,
			kType_WeaponGreatSword,
			kType_WeaponDaedra,
			kType_WeaponDagger,
			kType_WeaponWarAxe,
			kType_WeaponBattleAxe,
			kType_WeaponMace,
			kType_WeaponHammer,
			kType_WeaponStaff,
			kType_WeaponBow,
			kType_WeaponArrow,
			kType_WeaponPickAxe,
			kType_WeaponWoodAxe,
			kType_WeaponCrossbow,
			kType_WeaponBolt,

			kType_DefaultArmor,

			kType_LightArmorBody,
			kType_LightArmorHead,
			kType_LightArmorHands,
			kType_LightArmorForearms,
			kType_LightArmorFeet,
			kType_LightArmorCalves,
			kType_LightArmorShield,
			kType_LightArmorMask,

			kType_ArmorBody,
			kType_ArmorHead,
			kType_ArmorHands,
			kType_ArmorForearms,
			kType_ArmorFeet,
			kType_ArmorCalves,
			kType_ArmorShield,
			kType_ArmorMask,
			kType_ArmorBracer,
			kType_ArmorDaedra,

			kType_ClothingBody,
			kType_ClothingRobe,
			kType_ClothingHead,
			kType_ClothingPants,
			kType_ClothingHands,
			kType_ClothingForearms,
			kType_ClothingFeet,
			kType_ClothingCalves,
			kType_ClothingShoes,
			kType_ClothingShield,
			kType_ClothingMask,

			kType_ArmorAmulet,
			kType_ArmorRing,
			kType_Circlet,

			kType_DefaultScroll,

			kType_DefaultBook,
			kType_BookRead,
			kType_BookTome,
			kType_TomeRead,
			kType_BookJournal,
			kType_BookNote,
			kType_BookMap,

			kType_DefaultFood,
			kType_FoodWine,
			kType_FoodBeer,

			kType_DefaultIngredient,

			kType_DefaultKey,
			kType_KeyHouse,

			kType_DefaultPotion,
			kType_PotionHealth,
			kType_PotionStam,
			kType_PotionMagic,
			kType_PotionPoison,
			kType_PotionFrost,
			kType_PotionFire,
			kType_PotionShock,

			kType_DefaultMisc,
			kType_MiscArtifact,
			kType_MiscClutter,
			kType_MiscLockPick,
			kType_MiscSoulGem,

			kType_SoulGemEmpty,
			kType_SoulGemPartial,
			kType_SoulGemFull,
			kType_SoulGemGrandEmpty,
			kType_SoulGemGrandPartial,
			kType_SoulGemGrandFull,
			kType_SoulGemAzura,

			kType_MiscGem,
			kType_MiscOre,
			kType_MiscIngot,
			kType_MiscHide,
			kType_MiscStrips,
			kType_MiscLeather,
			kType_MiscWood,
			kType_MiscRemains,
			kType_MiscTrollSkull,
			kType_MiscTorch,
			kType_MiscGoldSack,
			kType_MiscGold,
			kType_MiscDragonClaw
		};

	public:
		explicit ItemData(RE::InventoryEntryData* a_entryData);
		explicit ItemData(RE::InventoryEntryData* a_entryData, SInt32 a_count);
		~ItemData();

		ItemData&						operator= (ItemData a_rhs);
		friend bool						operator==(const ItemData& a_lhs, const ItemData& a_rhs);
		friend bool						operator!=(const ItemData& a_lhs, const ItemData& a_rhs);
		friend bool						operator< (const ItemData& a_lhs, const ItemData& a_rhs);
		friend bool						operator> (const ItemData& a_lhs, const ItemData& a_rhs);
		friend bool						operator<=(const ItemData& a_lhs, const ItemData& a_rhs);
		friend bool						operator>=(const ItemData& a_lhs, const ItemData& a_rhs);
		friend void						swap(ItemData& a_lhs, ItemData& a_rhs);

		RE::InventoryEntryData*			entryData()			const;
		const char*						name()				const;
		SInt32							count()				const;
		SInt32							value()				const;
		float							weight()			const;
		const char*						icon()				const;
		bool							isStolen()			const;
		bool							isRead()			const;
		bool							isEnchanted()		const;
		bool							canPickPocket()		const;
		SInt32							pickPocketChance()	const;
		RE::TESForm*					form()				const;

		void							modCount(SInt32 a_mod);

		static void						setCompareOrder();
		static void						setContainer(RE::TESObjectREFR* a_container);

		void							dbgDumpType(UInt32 a_index);

	private:
		void							constructCommon();

		float							getWeight();
		Type							getType();
		Type							getTypeArmor(RE::TESObjectARMO* a_armor);
		Type							getTypeBook(RE::TESObjectBOOK* a_book);
		Type							getTypeMisc(RE::TESObjectMISC* a_misc);
		Type							getTypeWeapon(RE::TESObjectWEAP* a_weap);
		Type							getTypePotion(AlchemyItem* a_potion);
		Type							getTypeSoulGem(TESSoulGem* a_gem);
		bool							getStolen();
		bool							getRead();
		bool							getEnchanted();
		bool							getCanPickPocket();
		SInt32							getPickPocketChance();
		Priority						getPriority();

		static friend int				compareByName(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByName(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByCount(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByCount(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByValue(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByValue(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByWeight(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByWeight(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByType(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByType(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByRead(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByRead(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByEnchanted(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByEnchanted(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByPickPocketChance(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByPickPocketChance(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByPriority(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByPriority(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				compareByValuePerWeight(const ItemData& a_lhs, const ItemData& a_rhs);
		static friend int				r_compareByValuePerWeight(const ItemData& a_lhs, const ItemData& a_rhs);

		RE::InventoryEntryData*			_entryData;
		const char*						_name;
		SInt32							_count;
		SInt32							_value;
		float							_weight;
		Type							_type;
		bool							_isStolen;
		bool							_isRead;
		bool							_isEnchanted;
		bool							_canPickPocket;
		SInt32							_pickPocketChance;
		Priority						_priority;

		static std::vector<FnCompare>	_compares;
		static RE::TESObjectREFR*		_container;
		static const					std::string NAME;
		static const					std::string COUNT;
		static const					std::string VALUE;
		static const					std::string WEIGHT;
		static const					std::string TYPE;
		static const					std::string READ;
		static const					std::string ENCHANTED;
		static const					std::string PICK_POCKET_CHANCE;
		static const					std::string VALUE_PER_WEIGHT;
		static const					std::string PRIORITY;
		static const char*				_strIcons[];
	};
}
