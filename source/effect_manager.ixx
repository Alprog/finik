export module effect_manager;

import core;
import singleton;
import effect;

export class EffectManager : public Singleton<EffectManager>
{
public:
    std::shared_ptr<Effect> get(std::string key)
    {
        if (Effects.empty())
        {
            init();
        }
        return Effects[key];
    }

    void init();

private:
    HashMap<std::string, std::shared_ptr<Effect>> Effects;
};