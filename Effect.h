#pragma once
class Effect
{
private :
	static Effect* __instance;
private :
	bool isHitEffect;
	float HitEffectX, HitEffectY;
	bool isDesEffect;
	float DesEffectX,DesEffectY;
public:
	Effect();
	static Effect* getInstance();
	void setHitEffect(bool eff) {
		isHitEffect = eff;
	}
	void setHitEffectPos(float x, float y) {
		HitEffectX = x;
		HitEffectY = y;
	}
	bool isHitEffectActive() {
		return isHitEffect;
	}
	void getHitEffect(float &x, float &y) {
		x = HitEffectX;
		y = HitEffectY;
	}
	void setDesEffect(bool eff) {
		isDesEffect = eff;
	}
	bool  isDesEffectActive() {
		return isDesEffect;
	}
	void setDesEffect(float x, float y) {
		DesEffectX = x;
		DesEffectY = y;
	}
	void getDesEffect(float &x, float &y) {
		x = DesEffectX;
		y = DesEffectY;
	}
	~Effect();
};

