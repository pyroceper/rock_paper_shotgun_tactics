#ifndef SCENE_H
#define SCENE_H

enum SceneType
{
    MENU,
    LVL1
};

class Scene
{
    public:
        virtual void init() = 0;
        virtual void update() = 0;
        virtual ~Scene() = 0;
};

#endif