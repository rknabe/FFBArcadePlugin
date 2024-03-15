/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <string>
#include "CruisinBlast.h"
extern int EnableDamper;
extern int DamperStrength;

void CruisinBlast::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	//float ff = helpers->ReadFloat32(0x7EF524, true);
	float ff1 = helpers->ReadFloat32(0x08babba8, false);
	float ff2 = helpers->ReadFloat32(0x08babbac, false);

	helpers->log("got cruisin value: ");
	std::string ffs1 = std::to_string(ff1);
	helpers->log((char*)ffs1.c_str());
	std::string ffs2 = std::to_string(ff2);
	helpers->log((char*)ffs2.c_str());

	
	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (ff2 > 0)
	{
		double percentForce = ff2 / 1.2;
		double percentLength = 100;
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if (ff2 < 0)
	{
		double percentForce = -ff2 / 1.2;
		double percentLength = 100;
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
}