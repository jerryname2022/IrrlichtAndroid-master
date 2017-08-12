// Copyright (C) 2002-2009 Laurent Mallet & Maxime Biais
// This file is part of the "Irrlicht Android Port".
// For conditions of distribution and use, see copyright notice in irrlicht.h
#include <sys/time.h>
#include <android/log.h>
#include <android-receiver.h>
#include <android-logger.h>
#include "./d3/sceneNode.cpp"
#include <os.h>

using namespace irr;

using namespace os;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


extern IrrlichtDevice *device;
extern IVideoDriver *driver;
extern stringc gSdCardPath;

extern int cameraZ;

ISceneManager *smgr = NULL;
IGUIEnvironment *guienv = NULL;
IVideoDriver *videoDriver = NULL;
IAnimatedMesh *mesh = NULL;
ISceneNode *node = NULL;
IAnimatedMeshSceneNode *nodeSydney = NULL;
ICameraSceneNode *camera = NULL;
IGUIStaticText *diagnostics = NULL;
SAppContext context;
AndroidEventReceiver *receiver;
bool useHightLevelShaders = false;

class MyShaderCallBack : public video::IShaderConstantSetCallBack {
public:
    virtual void OnSetConstants(video::IMaterialRendererServices *services, s32 userData) {
        video::IVideoDriver *dv = services->getVideoDriver();
        core::matrix4 invWorld = dv->getTransform(video::ETS_WORLD);
        invWorld.makeInverse();
        if (useHightLevelShaders) {
            services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);
        } else {
            services->setVertexShaderConstant(invWorld.pointer(), 0, 4);
        }

        core::matrix4 worldViewProj;
        worldViewProj = dv->getTransform(ETS_PROJECTION);
        worldViewProj *= dv->getTransform(video::ETS_VIEW);
        worldViewProj *= dv->getTransform(ETS_WORLD);

        if (useHightLevelShaders) {
            services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);
        } else {
            services->setVertexShaderConstant(worldViewProj.pointer(), 4, 4);
        }

        core::vector3df pos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
        if (useHightLevelShaders) {
            services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32 *>(&pos), 3);
        } else {
            services->setVertexShaderConstant(reinterpret_cast<f32 *>(&pos), 8, 1);
        }
        video::SColorf col(0.0f, 1.0f, 1.0f, 1.0f);
        if (useHightLevelShaders) {
            services->setVertexShaderConstant("mLightColor", reinterpret_cast<f32 *>(&col), 4);
        } else {
            services->setVertexShaderConstant(reinterpret_cast<f32 *>(&col), 9, 1);
        }

        core::matrix4 world = dv->getTransform(ETS_WORLD);
        world = world.getTransposed();
        if (useHightLevelShaders) {
            services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);
        } else {
            services->setVertexShaderConstant(world.pointer(), 10, 4);
        }

    }
};

static long _getTime(void) {
    struct timeval now;

    gettimeofday(&now, NULL);
    return (long) (now.tv_sec * 1000 + now.tv_usec / 1000);
}


void initQuake() {
    //appInit();

    smgr = device->getSceneManager();

    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "getSceneManager r=%d", smgr);

    guienv = device->getGUIEnvironment();

    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "getGUIEnvironment r=%d", guienv);

    stringc quakeMapFilename = "/Irrlicht/map-20kdm2.pk3";
    device->getFileSystem()->addZipFileArchive((gSdCardPath + quakeMapFilename).c_str());

    mesh = smgr->getMesh("20kdm2.bsp");

    if (mesh) {
        __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "mesh available");
        node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
    } else {
        __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "mesh not available");
    }

    if (node) {
        __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "node available");
        node->setPosition(core::vector3df(-1300, -144, -1249));
    } else {
        __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "node not available");
    }

    camera = smgr->addCameraSceneNodeFPS();

    stringc logoFilename = "/Irrlicht/irrlichtlogoalpha2.tga";
    guienv->addImage(driver->getTexture((gSdCardPath + logoFilename).c_str()),
                     core::position2d<s32>(10, 40));
    diagnostics = guienv->addStaticText(L"Ceci est un text",
                                        core::rect<s32>(10, 100, 10 + 400, 100 + 20));
    diagnostics->setOverrideColor(video::SColor(255, 255, 255, 0));

    guienv->addButton(rect<s32>(10, 10, 110, 10 + 32), 0, GUI_ID_QUIT_BUTTON,
                      L"Quit", L"Exits Program");


    context.device = device;
    context.counter = 0;
    context.listbox = 0;

    // Then create the event receiver, giving it that context structure.
    receiver = new AndroidEventReceiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(receiver);

}

void initSydney() {
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();


    stringc sydneyFilename = "/Irrlicht/sydney.md2";
    mesh = smgr->getMesh((gSdCardPath + sydneyFilename).c_str());
    if (!mesh) {
        device->drop();
        __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "cannot getMesh");
        return;
    }
    nodeSydney = smgr->addAnimatedMeshSceneNode(mesh);
    if (nodeSydney) {
        nodeSydney->setMaterialFlag(EMF_LIGHTING, false);
        //--// no animation
        //--nodeSydney->setMD2Animation(scene::EMAT_STAND);
        // with animation
        nodeSydney->setMD2Animation(scene::EMAT_RUN);
        stringc sydneyTextureFilename = "/Irrlicht/sydney.bmp";
        nodeSydney->setMaterialTexture(0, driver->getTexture(
                (gSdCardPath + sydneyTextureFilename).c_str()));
        __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "add texture");

        /*CSampleSceneNode *myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);
        myNode->drop();

        scene::ISceneNodeAnimator *anim = smgr->createRotationAnimator(
                core::vector3df(0.8f, 0, 0.8f));
        if (anim != 0) {
            myNode->addAnimator(anim);
            anim->drop();
        }
         */
    }

    smgr->addCameraSceneNode(0, vector3df(0, 10, cameraZ), vector3df(0, 5, 0));

    // Then create the event receiver, giving it that context structure.
    receiver = new AndroidEventReceiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(receiver);
}


void initIrr() {

    Printer::Logger = new CAndroidLogger();

    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    stringc _3dsFilename = "/Irrlicht/room.3ds";
    mesh = smgr->getMesh((gSdCardPath + _3dsFilename).c_str());
    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "mesh: %d", mesh);

    smgr->getMeshManipulator()->makePlanarTextureMapping(mesh->getMesh(0), 0.004f);

    node = smgr->addAnimatedMeshSceneNode(mesh);
    stringc _3dsTextureFilename = "/Irrlicht/wall.jpg";
    node->setMaterialTexture(0, driver->getTexture((gSdCardPath + _3dsTextureFilename).c_str()));
    node->getMaterial(0).SpecularColor.set(0, 0, 0, 0);

    mesh = smgr->addHillPlaneMesh("myHill",
                                  core::dimension2d<f32>(20, 20),
                                  core::dimension2d<u32>(40, 40), 0, 0,
                                  core::dimension2d<f32>(0, 0),
                                  core::dimension2d<f32>(10, 10));

    node = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0), 3.0f, 300.0f, 30.0f);
    node->setPosition(core::vector3df(0, 7, 0));

    stringc stonesFilename = "/Irrlicht/stones.jpg";
    node->setMaterialTexture(0, driver->getTexture((gSdCardPath + stonesFilename).c_str()));
    stringc waterFilename = "/Irrlicht/water.jpg";
    node->setMaterialTexture(1, driver->getTexture((gSdCardPath + waterFilename).c_str()));

    node->setMaterialType(video::EMT_REFLECTION_2_LAYER);

    // create light

    node = smgr->addLightSceneNode(0, core::vector3df(0, 0, 0),
                                   video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
    scene::ISceneNodeAnimator *anim = 0;
    anim = smgr->createFlyCircleAnimator(core::vector3df(0, 150, 0), 250.0f);
    node->addAnimator(anim);
    anim->drop();


    camera = smgr->addCameraSceneNodeFPS();
    camera->setPosition(core::vector3df(-50, 50, -150));

}

static int counter = 0;
bool isFrontEnd = false;
bool isBlackEnd = false;

/* Call to render the next GL frame */
void nativeDrawIterationSydney() {

    device->run();
    if (counter == 0) {
        initSydney();
    }

    // SColor is the background color
    driver->beginScene(true, true, SColor(255, 120, 102, 136));
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();

    counter++;

    int fps = driver->getFPS();
    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "fps=%d cameraZ=%d", fps, cameraZ);

}

gui::IGUIFont *font;
gui::IGUIFont *font2;
core::rect<s32> imp1(349, 15, 385, 78);
core::rect<s32> imp2(387, 15, 423, 78);
video::ITexture *images;

void init07() {
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    images = driver->getTexture((gSdCardPath + "/Irrlicht/faerie2.bmp").c_str());
    driver->makeColorKeyTexture(images, core::position2d<s32>(0, 0));

    font = device->getGUIEnvironment()->getBuiltInFont();
    font2 =
            device->getGUIEnvironment()->getFont(
                    (gSdCardPath + "/Irrlicht/fonthaettenschweiler.bmp").c_str());
    //driver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
    //driver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;

}

/* Call to render the next GL frame */
void demo07() {

    device->run();

    if (!device->isWindowActive())return;
    if (counter == 0) {
        init07();
    }
    counter++;

    u32 time = device->getTimer()->getTime();
    driver->beginScene(true, true, video::SColor(255, 120, 102, 136));

    driver->draw2DImage(images, core::position2d<s32>(50, 50),
                        core::rect<s32>(0, 0, 342, 224), 0,
                        video::SColor(255, 255, 255, 255), true);

    // draw flying imp
    driver->draw2DImage(images, core::position2d<s32>(164, 125),
                        (time / 500 % 2) ? imp1 : imp2, 0,
                        video::SColor(255, 255, 255, 255), true);

    // draw second flying imp with colorcylce
    driver->draw2DImage(images, core::position2d<s32>(270, 105),
                        (time / 500 % 2) ? imp1 : imp2, 0,
                        video::SColor(255, (time) % 255, 255, 255), true);

    /*
    Drawing text is really simple. The code should be self
    explanatory.
    */

    // draw some text
    if (font)
        font->draw(L"This demo shows that Irrlicht is also capable of drawing 2D graphics.",
                   core::rect<s32>(130, 10, 300, 50),
                   video::SColor(255, 255, 255, 255));

    // draw some other text
    if (font2)
        font2->draw(L"Also mixing with 3d graphics is possible.",
                    core::rect<s32>(130, 20, 300, 60),
                    video::SColor(255, time % 255, time % 255, 255));

    /*
    Next, we draw the Irrlicht Engine logo (without
    using a color or an alpha channel). Since we slightly scale
    the image we use the prepared filter mode.
    */
    driver->enableMaterial2D();
    driver->draw2DImage(images, core::rect<s32>(10, 10, 108, 48),
                        core::rect<s32>(354, 87, 442, 118));
    driver->enableMaterial2D(false);

    /*
    Finally draw a half-transparent rect under the mouse cursor.
    */
    core::position2d<s32> m = device->getCursorControl()->getPosition();
    driver->draw2DRectangle(video::SColor(100, 255, 255, 255),
                            core::rect<s32>(m.X - 20, m.Y - 20, m.X + 20, m.Y + 20));
    driver->endScene();


    int fps = driver->getFPS();
    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "fps=%d cameraZ=%d", fps, cameraZ);

}


void init08() {
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    videoDriver = device->getVideoDriver();

    IAnimatedMesh *mesh = smgr->getMesh((gSdCardPath + "/Irrlicht/room.3ds").c_str());
    smgr->getMeshManipulator()->makePlanarTextureMapping(mesh->getMesh(0), 0.004f);
    ISceneNode *node = 0;
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node->setMaterialTexture(0, driver->getTexture((gSdCardPath + "/Irrlicht/wall.jpg").c_str()));
    node->getMaterial(0).SpecularColor.set(0, 0, 0, 0);

    mesh = smgr->addHillPlaneMesh("myHill",
                                  dimension2d<f32>(20, 20),
                                  dimension2d<u32>(40, 40), 0, 0,
                                  dimension2d<f32>(0, 0),
                                  dimension2d<f32>(10, 10));
    node = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0), 3.0f, 300.0f, 30.0f);
    node->setPosition(vector3df(0, 7, 0));
    node->setMaterialTexture(0, driver->getTexture((gSdCardPath + "/Irrlicht/stones.jpg").c_str()));
    node->setMaterialTexture(1, driver->getTexture((gSdCardPath + "/Irrlicht/water.jpg").c_str()));
    node->setMaterialType(EMT_REFLECTION_2_LAYER);

    node = smgr->addLightSceneNode(0, vector3df(0, 0, 0), SColorf(1.0f, 0.6f, 0.7f), 600.0f);
    ISceneNodeAnimator *anim = 0;
    anim = smgr->createFlyCircleAnimator(vector3df(0, 150, 0), 250.0f);
    node->addAnimator(anim);
    anim->drop();

    node = smgr->addBillboardSceneNode(node, dimension2d<f32>(50, 50));
    node->setMaterialFlag(EMF_LIGHTING, false);
    node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
    node->setMaterialTexture(0, driver->getTexture(
            (gSdCardPath + "/Irrlicht/particlewhite.bmp").c_str()));

    IParticleSystemSceneNode *ps = 0;
    ps = smgr->addParticleSystemSceneNode(false);
    ps->setPosition(vector3df(-70, 60, 40));
    ps->setScale(vector3df(2, 2, 2));
    ps->setParticleSize(dimension2d<f32>(20.0f, 20.0f));
    IParticleEmitter *em = ps->createBoxEmitter(
            aabbox3d<f32>(-7, 0, -7, 7, 1, 7),
            vector3df(0.0f, 0.06f, 0.0f),
            80, 100,
            SColor(0, 255, 255, 255), SColor(0, 255, 255, 255),
            800, 2000);
    ps->setEmitter(em);
    em->drop();
    IParticleAffector *paf = ps->createFadeOutParticleAffector();
    ps->addAffector(paf);
    paf->drop();
    ps->setMaterialFlag(EMF_LIGHTING, false);
    ps->setMaterialTexture(0, driver->getTexture((gSdCardPath + "/Irrlicht/fire.bmp").c_str()));
    ps->setMaterialType(EMT_TRANSPARENT_VERTEX_ALPHA);

    mesh = smgr->getMesh((gSdCardPath + "/Irrlicht/dwarf.x").c_str());
    IAnimatedMeshSceneNode *anode = 0;
    anode = smgr->addAnimatedMeshSceneNode(mesh);
    anode->setPosition(vector3df(-50, 20, -60));
    anode->setAnimationSpeed(15);
    anode->addShadowVolumeSceneNode();
    smgr->setShadowColor(SColor(150, 0, 0, 0));
    anode->setScale(vector3df(2, 2, 2));
    anode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

    ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS();
    camera->setPosition(vector3df(-50, 50, -150));
    device->getCursorControl()->setVisible(false);
}

/* 做一些特效 */
void demo08() {

    device->run();

    if (!device->isWindowActive())return;
    if (counter == 0) {
        init08();
    }
    counter++;

    driver->beginScene(true, true, 0);
    smgr->drawAll();
    driver->endScene();


    int fps = driver->getFPS();
    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "fps=%d cameraZ=%d", fps, cameraZ);

}


void init10() {
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    videoDriver = device->getVideoDriver();
    //(gSdCardPath + "/Irrlicht/room.3ds").c_str()
    c8 *vsFileName = 0;
    c8 *psFileName = 0;

    if (useHightLevelShaders) {
        vsFileName = (c8 *) (gSdCardPath + "/Irrlicht/opengl.frag").c_str();
        psFileName = (c8 *) (gSdCardPath + "/Irrlicht/opengl.vert").c_str();
    } else {
        vsFileName = (c8 *) (gSdCardPath + "/Irrlicht/opengl.psh").c_str();
        psFileName = (c8 *) (gSdCardPath + "/Irrlicht/opengl.vsh").c_str();
    }

    if (!driver->queryFeature(EVDF_PIXEL_SHADER_1_1) &&
        !driver->queryFeature(EVDF_ARB_FRAGMENT_PROGRAM_1)) {
        __android_log_print(ANDROID_LOG_INFO, "Irrlicht",
                            "WARNIG:Pixel shaders disabled bacause of missing driver/hardware support.");
        psFileName = 0;
    }

    if (!driver->queryFeature(EVDF_VERTEX_SHADER_1_1) &&
        !driver->queryFeature(EVDF_ARB_VERTEX_PROGRAM_1)) {
        __android_log_print(ANDROID_LOG_INFO, "Irrlicht",
                            "WARNIG:Vertex shaders disabled bacause of missing driver/hardware support.");
        vsFileName = 0;
    }

    IGPUProgrammingServices *gpu = driver->getGPUProgrammingServices();
    s32 newMaterialType1 = 0;
    s32 newMaterialType2 = 0;
    if (gpu) {
        MyShaderCallBack *mc = new MyShaderCallBack();
        if (useHightLevelShaders) {
            newMaterialType1 = gpu->addHighLevelShaderMaterialFromFiles(vsFileName, "vertexMain",
                                                                        EVST_VS_1_1,
                                                                        psFileName, "pixelMain",
                                                                        EPST_PS_1_1,
                                                                        mc, EMT_SOLID);

            newMaterialType2 = gpu->addHighLevelShaderMaterialFromFiles(vsFileName, "vertexMain",
                                                                        EVST_VS_1_1,
                                                                        psFileName, "pixelMain",
                                                                        EPST_PS_1_1,
                                                                        mc,
                                                                        EMT_TRANSPARENT_ADD_COLOR);
        } else {
            newMaterialType1 = gpu->addShaderMaterialFromFiles(vsFileName,
                                                               psFileName,
                                                               mc, EMT_SOLID);

            newMaterialType2 = gpu->addShaderMaterialFromFiles(vsFileName,
                                                               psFileName,
                                                               mc, EMT_TRANSPARENT_ADD_COLOR);
        }
        mc->drop();
    }

    ISceneNode *node = smgr->addCubeSceneNode(50);
    node->setPosition(vector3df(0, 0, 0));
    node->setMaterialTexture(0, driver->getTexture((gSdCardPath + "/Irrlicht/wall.bmp").c_str()));
    node->setMaterialFlag(EMF_LIGHTING, false);
    node->setMaterialType(E_MATERIAL_TYPE(newMaterialType1));
    smgr->addTextSceneNode(guienv->getBuiltInFont(), L"PS & VS & EMT_SOLID",
                           SColor(255, 255, 255, 255), node);
    ISceneNodeAnimator *anim = smgr->createRotationAnimator(vector3df(0, 0.3f, 0));
    node->addAnimator(anim);
    anim->drop();

    node = smgr->addCubeSceneNode(50);
    node->setPosition(vector3df(0, -10, 50));
    node->setMaterialTexture(0, driver->getTexture((gSdCardPath + "/Irrlicht/wall.bmp").c_str()));
    node->setMaterialFlag(EMF_LIGHTING, false);
    node->setMaterialType(E_MATERIAL_TYPE(newMaterialType2));
    smgr->addTextSceneNode(guienv->getBuiltInFont(), L"PS & VS &EMT_TRANSPARENT",
                           SColor(255, 255, 255, 255), node);
    anim = smgr->createRotationAnimator(vector3df(0, 0.3f, 0));
    node->addAnimator(anim);
    anim->drop();

    node = smgr->addCubeSceneNode(50);
    node->setPosition(vector3df(0, 50, 25));
    node->setMaterialTexture(0, driver->getTexture((gSdCardPath + "/Irrlicht/wall.bmp").c_str()));
    node->setMaterialFlag(EMF_LIGHTING, false);
    smgr->addTextSceneNode(guienv->getBuiltInFont(), L"NO SHADER", SColor(255, 255, 255, 255),
                           node);

    driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, false);
    smgr->addSkyBoxSceneNode(
            driver->getTexture((gSdCardPath + "/Irrlicht/irrlicht2_up.jpg").c_str()),
            driver->getTexture((gSdCardPath + "/Irrlicht/irrlicht2_dn.jpg").c_str()),
            driver->getTexture((gSdCardPath + "/Irrlicht/irrlicht2_lf.jpg").c_str()),
            driver->getTexture((gSdCardPath + "/Irrlicht/irrlicht2_rt.jpg").c_str()),
            driver->getTexture((gSdCardPath + "/Irrlicht/irrlicht2_ft.jpg").c_str()),
            driver->getTexture((gSdCardPath + "/Irrlicht/irrlicht2_bk.jpg").c_str()));
    driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, true);
    ICameraSceneNode *cam = smgr->addCameraSceneNodeFPS(0, 100.0f, 100.0f);
    cam->setPosition(vector3df(-100, 50, 100));
    cam->setTarget(vector3df(0, 0, 0));
    device->getCursorControl()->setVisible(false);
}


void demo10() {

    device->run();

    if (!device->isWindowActive())return;
    if (counter == 0) {
        init10();
    }
    counter++;

    driver->beginScene(true, true, 0);
    smgr->drawAll();
    driver->endScene();


    int fps = driver->getFPS();
    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "fps=%d cameraZ=%d", fps, cameraZ);

}

/* Call to render the next GL frame */
void nativeDrawIterationQuake() {
    device->run();
    if (counter == 0) {
        initQuake();
    }

    if (node) {
        node->setPosition(core::vector3df(-1300, -144, -1249));
        camera->setRotation(core::vector3df(0, counter, 0));
    }

    driver->beginScene(true, true, SColor(255, 0, 0, 0));

    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();

    counter++;


    int fps = driver->getFPS();
    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "fps=%d", fps);

}

void nativeDrawIterationIrr() {
    device->run();
    if (counter == 0) {
        initIrr();
    }

    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "Load irr scene");

    driver->beginScene(true, true, SColor(255, 0, 0, 0));

    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();

    counter++;


    int fps = driver->getFPS();
    __android_log_print(ANDROID_LOG_INFO, "Irrlicht", "fps=%d", fps);

}

void nativeDrawIteration() {
    // nativeDrawIterationSydney();
    // nativeDrawIterationQuake();
    // nativeDrawIterationIrr();
    // demo08();
    demo10();
}

