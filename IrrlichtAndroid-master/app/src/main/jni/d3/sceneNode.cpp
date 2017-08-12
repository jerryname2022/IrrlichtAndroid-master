#include "../include/irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CSampleSceneNode : public ISceneNode {
public:
    aabbox3df Box;
    S3DVertex Viertices[4];
    SMaterial Material;
public:
    CSampleSceneNode(ISceneNode *parent, ISceneManager *smgr, s32 id)
            : ISceneNode(parent,
                         smgr,
                         id) {
        Material.Wireframe = false;
        Material.Lighting = false;
        Viertices[0] = S3DVertex(0, 0, 10, 1, 1, 0, SColor(255, 0, 255, 255), 0, 1);
        Viertices[1] = S3DVertex(10, 0, -10, 1, 0, 0, SColor(255, 255, 0, 255), 1, 1);
        Viertices[2] = S3DVertex(0, 20, 0, 0, 1, 1, SColor(255, 255, 255, 0), 1, 0);
        Viertices[3] = S3DVertex(-10, 0, -10, 0, 0, 1, SColor(255, 0, 255, 0), 0, 0);
        Box.reset(Viertices[0].Pos);
        for (s32 i = 1; i < 4; i++) {
            Box.addInternalPoint(Viertices[i].Pos);
        }
    };

    virtual void OnRegisterSceneNode() override {
        if (IsVisible) {
            SceneManager->registerNodeForRendering(this);
        }
        ISceneNode::OnRegisterSceneNode();
    };

    virtual void render() override {
        u16 indices[] = {0, 2, 3, 2, 1, 3, 1, 0, 3, 2, 0, 1};
        IVideoDriver *driver = SceneManager->getVideoDriver();
        driver->setMaterial(Material);
        driver->setTransform(ETS_WORLD, AbsoluteTransformation);
        driver->drawIndexedTriangleList(&Viertices[0], 4, &indices[0], 4);
    };

    virtual const core::aabbox3d<f32> &getBoundingBox() const override {
        return Box;
    };

    virtual u32 getMaterialCount() {
        return 1;
    };

    virtual SMaterial &getMaterial(u32 i) override {
        return Material;
    };

};

