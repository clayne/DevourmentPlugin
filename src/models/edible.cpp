#include "models/edible.hpp"

using namespace std;
using namespace SKSE;
using namespace RE;

namespace Devr {
	/**
	 * Convience function to get the name of a pred`
	 * @return [description]
	 */
	std::string Edible::Name() {
		return actor->GetDisplayFullName();
	}

	/**
	 * Get the scale of the pred this include all effects
	 * such as those made by Giantess Mod or by RaceMenu
	 * or by SetScale
	 * @return [description]
	 */
	float Edible::GetScale() {
		auto refScale = static_cast<float>(actor->refScale) / 100.0F; // This is the scale used by SetScale papyrus

		// This is the model scale which includes aspects like giantess mod and racemenus height
		auto modelScale = 1.0;
		auto model = actor->GetCurrent3D();
		if (model) {
			auto rootNode = model->GetObjectByName("NPC Root [Root]");
			if (rootNode) {
				modelScale = rootNode->world.scale;
			}
		}

		return refScale * modelScale;
	}

	float Edible::GetLength() {
		auto max = actor->GetBoundMax();
		auto min = actor->GetBoundMin();
		auto deltaY = max.y - min.y;

		return deltaY * GetScale();
	}

	bool Edible::IsInFaction(std::string_view tag) {
		auto actor = skyrim_cast<Actor*>(object.get());
		if (actor) {
			return Forms::InFaction(actor, tag);
		} else {
			return false;
		}
	}

	bool Edible::HasKeywordString(std::string_view keyword) {
		return object->HasKeywordString(keyword);
	}

	bool Edible::IsInCombat() {
		auto actor = skyrim_cast<Actor*>(object.get());
		if (actor) {
			return actor->IsInCombat();
		} else {
			return false;
		}
	}

	SEX Edible::GetSex() {
		auto actor = skyrim_cast<Actor*>(object.get());
		if (actor) {
			return actor->GetActorBase()->GetSex();
		} else {
			return SEX::kNone;
		}
	}

	float Edible::GetBaseVolume() {
		auto max = actor->GetBoundMax();
		auto min = actor->GetBoundMin();
		auto deltaX = max.x - min.x;
		auto deltaY = max.y - min.y;
		auto deltaZ = max.z - min.z;

		return deltaX * deltaY * deltaZ;
	}

	float Edible::GetVolume() {
		return GetBaseVolume() + stomach.GetVolume();
	}

	Edible::Edible(TESObjectREFR* inobject) : object(NiPointer<TESObjectREFR>(inobject)) {

	}

}