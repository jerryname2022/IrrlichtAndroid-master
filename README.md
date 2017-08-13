Urho3D 阅读文档
<p></p>
先在linux下编译出 libUrho3d.a 库。 编译目录在源码新建的 build 目录下
<p></p>  
拷贝(带软链接)
<p></p>
cp -r /home/xiaoming/Downloads/Urho3D-1.6/build/include/ ./include/
<p></p>
阅读cmake编译生成的文件，移到android studio工程下。
<p></p>
例如编译的是 AngelScript 模块，cmake会生成一下目录和文件。
<p></p>
> CMakeFiles
<p></p>
>> ./AngelScript.dir
	 <p></p>
>>> ./source                        该模块编译源文件时生成的中间文件
			 <p></p>
>>> ./ASM.includecache
			 <p></p>
>>> ./build.make                    最主要的编译文件，阅读该文件可详细知道，编译当前模块的编译过程，依赖等信息。
			 <p></p>
>>> ./cmake_clean.cmake
			 <p></p>
>>> ./cmake_clean_target.cmake
			 <p></p>
>>> ./CXX.includecache
			 <p></p>
>>> ./depend.internal
			 <p></p>
>>> ./DependInfo.cmake
>>> ./flags.make                    这是传给编译器的附加 参数 如-fno-strict-aliasing
>>>			 <p></p>
>>> ./link.txt                      包含链接命令的文件
			 <p></p>
>>> ./progress.make
			 <p></p>
>> ./CMakeDirectoryInformation.cmake
	 <p></p>
>> ./progress.marks
	 <p></p>
> cmake_install.cmake
> libAngelScript.a                                         输出的库文件
<p></p>
> Makefile                                                 最后生成的Makefile文件
<p></p>

#include "../../.././include/Urho3D/Core/CoreEvents.h"
#include "../../.././include/Urho3D/Engine/Engine.h"
#include "../../.././include/Urho3D/Graphics/Camera.h"
#include "../../.././include/Urho3D/Graphics/DebugRenderer.h"
#include "../../.././include/Urho3D/Graphics/Graphics.h"
#include "../../.././include/Urho3D/Graphics/Light.h"
#include "../../.././include/Urho3D/Graphics/Material.h"
#include "../../.././include/Urho3D/Graphics/Model.h"
#include "../../.././include/Urho3D/Graphics/Octree.h"
#include "../../.././include/Urho3D/Graphics/Renderer.h"
#include "../../.././include/Urho3D/Graphics/Skybox.h"
#include "../../.././include/Urho3D/Graphics/Zone.h"
#include "../../.././include/Urho3D/Input/Input.h"
#include "../../.././include/Urho3D/IO/File.h"
#include "../../.././include/Urho3D/IO/FileSystem.h"
#include "../../.././include/Urho3D/Physics/CollisionShape.h"
#include "../../.././include/Urho3D/Physics/PhysicsWorld.h"
#include "../../.././include/Urho3D/Physics/RigidBody.h"
#include "../../.././include/Urho3D/Resource/ResourceCache.h"
#include "../../.././include/Urho3D/Scene/Scene.h"
#include "../../.././include/Urho3D/UI/Button.h"
#include "../../.././include/Urho3D/UI/Font.h"
#include "../../.././include/Urho3D/UI/LineEdit.h"
#include "../../.././include/Urho3D/UI/Text.h"
#include "../../.././include/Urho3D/UI/UI.h"
#include "../../.././include/Urho3D/UI/UIEvents.h"


#include "../../.././include/Urho3D/Urho2D/CollisionBox2D.h"
#include "../../.././include/Urho3D/Urho2D/CollisionCircle2D.h"
#include "../../.././include/Urho3D/Urho2D/Drawable2D.h"
#include "../../.././include/Urho3D/Urho2D/PhysicsWorld2D.h"
#include "../../.././include/Urho3D/Urho2D/RigidBody2D.h"
#include "../../.././include/Urho3D/Urho2D/Sprite2D.h"
#include "../../.././include/Urho3D/Urho2D/StaticSprite2D.h"



#include "../../.././include/Urho3D/DebugNew.h"

#include "../Urho3D.h"

#include "../ThirdParty/SDL/SDL_joystick.h"
#include "../ThirdParty/SDL/SDL_gamecontroller.h"
#include "../ThirdParty/SDL/SDL_keycode.h"
#include "../ThirdParty/SDL/SDL_mouse.h"


**********************************************************************************************
build.make文件可以看到具体的编译过程和依赖

demo 03  03_Sprites 的编译过程  见文件 \build\Source\Samples\03_Sprites\CMakeFiles\03_Sprites.dir\build.make
114行
{

cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Samples/03_Sprites && 
arm-linux-androideabi-strip /home/xiaoming/Downloads/Urho3D-1.6/build/libs/armeabi-v7a/lib03_Sprites.so
}

link.txt

arm-linux-androideabi-gcc  -fPIC -fexceptions -frtti -Wno-psabi 
--sysroot=/home/xiaoming/Android/Sdk/ndk-bundle/platforms/android-9/arch-arm 
-funwind-tables -finline-limit=64 -fsigned-char -no-canonical-prefixes 
-march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -fdata-sections -ffunction-sections -Wa,
--noexecstack  -Wno-invalid-offsetof -fvisibility=hidden -fvisibility-inlines-hidden -mthumb -fomit-frame-pointer 
-fno-strict-aliasing -O3 -DNDEBUG  -Wl,--fix-cortex-a8 -Wl,-rpath-link,
/android-9/arch-arm/usr/lib -Wl,--no-undefined -Wl,--gc-sections -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now  
-shared -Wl,-soname,lib03_Sprites.so 
-o ../../../libs/armeabi-v7a/lib03_Sprites.so
 CMakeFiles/03_Sprites.dir/Sprites.cpp.o 
 CMakeFiles/03_Sprites.dir/__/__/__/include/Urho3D/ThirdParty/SDL/android/SDL_android_main.c.o 
 ../../../libs/armeabi-v7a/libUrho3D.a 
 -ldl -llog -landroid -lGLESv1_CM -lGLESv2  
 "/home/xiaoming/Android/Sdk/ndk-bundle/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/libgnustl_static.a" 
 "/home/xiaoming/Android/Sdk/ndk-bundle/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/libsupc++.a" -lm


{
 依赖文件
 
 CMakeFiles/03_Sprites.dir/Sprites.cpp.o 
 CMakeFiles/03_Sprites.dir/__/__/__/include/Urho3D/ThirdParty/SDL/android/SDL_android_main.c.o
 ../../../libs/armeabi-v7a/libUrho3D.a

} 

Sprites.cpp.o    (build.make)
{
cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Samples/03_Sprites &&
arm-linux-androideabi-g++   
$(CXX_DEFINES) $(CXX_FLAGS) 
-o CMakeFiles/03_Sprites.dir/Sprites.cpp.o 
-c /home/xiaoming/Downloads/Urho3D-1.6/Source/Samples/03_Sprites/Sprites.cpp

}
SDL_android_main.c.o 

{
cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Samples/03_Sprites && 
arm-linux-androideabi-gcc  $(C_DEFINES) $(C_FLAGS)
-o CMakeFiles/03_Sprites.dir/__/__/__/include/Urho3D/ThirdParty/SDL/android/SDL_android_main.c.o   
-c /home/xiaoming/Downloads/Urho3D-1.6/build/include/Urho3D/ThirdParty/SDL/android/SDL_android_main.c
}

libUrho3D.a
{
arm-linux-androideabi-gcc-ar cr ../../libs/armeabi-v7a/libUrho3D.a  
CMakeFiles/Urho3D.dir/Urho2D/Drawable2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/ParticleEmitter2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/Urho2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/AnimatedSprite2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/TmxFile2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/ParticleEffect2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/CollisionChain2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/ConstraintRevolute2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/CollisionBox2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/TileMap2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/CollisionEdge2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/StaticSprite2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/ConstraintPrismatic2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/PhysicsWorld2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/ConstraintWheel2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/SpriterInstance2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/ConstraintDistance2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/ConstraintMouse2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/SpriteSheet2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/TileMapDefs2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/CollisionCircle2D.cpp.o 
CMakeFiles/Urho3D.dir/Urho2D/SpriterData2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/ConstraintRope2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/Sprite2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/CollisionPolygon2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/TileMapLayer2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/ConstraintFriction2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/ConstraintPulley2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/Constraint2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/ConstraintWeld2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/RigidBody2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/ConstraintGear2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/AnimationSet2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/ConstraintMotor2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/Renderer2D.cpp.o CMakeFiles/Urho3D.dir/Urho2D/CollisionShape2D.cpp.o CMakeFiles/Urho3D.dir/IO/Compression.cpp.o CMakeFiles/Urho3D.dir/IO/Deserializer.cpp.o CMakeFiles/Urho3D.dir/IO/Log.cpp.o CMakeFiles/Urho3D.dir/IO/MemoryBuffer.cpp.o CMakeFiles/Urho3D.dir/IO/Serializer.cpp.o CMakeFiles/Urho3D.dir/IO/FileWatcher.cpp.o CMakeFiles/Urho3D.dir/IO/VectorBuffer.cpp.o CMakeFiles/Urho3D.dir/IO/PackageFile.cpp.o CMakeFiles/Urho3D.dir/IO/NamedPipe.cpp.o CMakeFiles/Urho3D.dir/IO/File.cpp.o CMakeFiles/Urho3D.dir/IO/FileSystem.cpp.o CMakeFiles/Urho3D.dir/Physics/RigidBody.cpp.o CMakeFiles/Urho3D.dir/Physics/CollisionShape.cpp.o CMakeFiles/Urho3D.dir/Physics/PhysicsWorld.cpp.o CMakeFiles/Urho3D.dir/Physics/Constraint.cpp.o CMakeFiles/Urho3D.dir/Core/Condition.cpp.o CMakeFiles/Urho3D.dir/Core/EventProfiler.cpp.o CMakeFiles/Urho3D.dir/Core/Thread.cpp.o CMakeFiles/Urho3D.dir/Core/Mutex.cpp.o CMakeFiles/Urho3D.dir/Core/Object.cpp.o CMakeFiles/Urho3D.dir/Core/Variant.cpp.o 
CMakeFiles/Urho3D.dir/Core/Context.cpp.o CMakeFiles/Urho3D.dir/Core/Profiler.cpp.o CMakeFiles/Urho3D.dir/Core/WorkQueue.cpp.o CMakeFiles/Urho3D.dir/Core/MiniDump.cpp.o CMakeFiles/Urho3D.dir/Core/Spline.cpp.o CMakeFiles/Urho3D.dir/Core/ProcessUtils.cpp.o CMakeFiles/Urho3D.dir/Core/StringUtils.cpp.o CMakeFiles/Urho3D.dir/Core/Timer.cpp.o CMakeFiles/Urho3D.dir/LibraryInfo.cpp.o CMakeFiles/Urho3D.dir/UI/FontFaceBitmap.cpp.o CMakeFiles/Urho3D.dir/UI/ToolTip.cpp.o CMakeFiles/Urho3D.dir/UI/ScrollBar.cpp.o CMakeFiles/Urho3D.dir/UI/BorderImage.cpp.o CMakeFiles/Urho3D.dir/UI/Menu.cpp.o CMakeFiles/Urho3D.dir/UI/Sprite.cpp.o CMakeFiles/Urho3D.dir/UI/Window.cpp.o CMakeFiles/Urho3D.dir/UI/Text3D.cpp.o CMakeFiles/Urho3D.dir/UI/FontFaceFreeType.cpp.o CMakeFiles/Urho3D.dir/UI/Cursor.cpp.o CMakeFiles/Urho3D.dir/UI/ScrollView.cpp.o CMakeFiles/Urho3D.dir/UI/MessageBox.cpp.o CMakeFiles/Urho3D.dir/UI/DropDownList.cpp.o CMakeFiles/Urho3D.dir/UI/FileSelector.cpp.o CMakeFiles/Urho3D.dir/UI/ListView.cpp.o CMakeFiles/Urho3D.dir/UI/View3D.cpp.o CMakeFiles/Urho3D.dir/UI/UIBatch.cpp.o CMakeFiles/Urho3D.dir/UI/Text.cpp.o CMakeFiles/Urho3D.dir/UI/CheckBox.cpp.o CMakeFiles/Urho3D.dir/UI/UIElement.cpp.o CMakeFiles/Urho3D.dir/UI/Button.cpp.o CMakeFiles/Urho3D.dir/UI/UI.cpp.o CMakeFiles/Urho3D.dir/UI/Slider.cpp.o CMakeFiles/Urho3D.dir/UI/Font.cpp.o CMakeFiles/Urho3D.dir/UI/LineEdit.cpp.o CMakeFiles/Urho3D.dir/UI/FontFace.cpp.o CMakeFiles/Urho3D.dir/Math/Matrix3x4.cpp.o CMakeFiles/Urho3D.dir/Math/Ray.cpp.o CMakeFiles/Urho3D.dir/Math/BoundingBox.cpp.o CMakeFiles/Urho3D.dir/Math/Plane.cpp.o CMakeFiles/Urho3D.dir/Math/Vector4.cpp.o CMakeFiles/Urho3D.dir/Math/MathDefs.cpp.o CMakeFiles/Urho3D.dir/Math/Random.cpp.o CMakeFiles/Urho3D.dir/Math/Frustum.cpp.o CMakeFiles/Urho3D.dir/Math/Rect.cpp.o CMakeFiles/Urho3D.dir/Math/Color.cpp.o CMakeFiles/Urho3D.dir/Math/Matrix3.cpp.o CMakeFiles/Urho3D.dir/Math/Quaternion.cpp.o CMakeFiles/Urho3D.dir/Math/Vector3.cpp.o CMakeFiles/Urho3D.dir/Math/Matrix4.cpp.o CMakeFiles/Urho3D.dir/Math/Sphere.cpp.o CMakeFiles/Urho3D.dir/Math/AreaAllocator.cpp.o CMakeFiles/Urho3D.dir/Math/Vector2.cpp.o CMakeFiles/Urho3D.dir/Math/Matrix2.cpp.o CMakeFiles/Urho3D.dir/Math/Polyhedron.cpp.o CMakeFiles/Urho3D.dir/Math/StringHash.cpp.o CMakeFiles/Urho3D.dir/Input/Input.cpp.o CMakeFiles/Urho3D.dir/Input/Controls.cpp.o CMakeFiles/Urho3D.dir/Resource/JSONFile.cpp.o CMakeFiles/Urho3D.dir/Resource/Image.cpp.o CMakeFiles/Urho3D.dir/Resource/PListFile.cpp.o CMakeFiles/Urho3D.dir/Resource/XMLFile.cpp.o CMakeFiles/Urho3D.dir/Resource/JSONValue.cpp.o CMakeFiles/Urho3D.dir/Resource/ResourceCache.cpp.o CMakeFiles/Urho3D.dir/Resource/Localization.cpp.o CMakeFiles/Urho3D.dir/Resource/Resource.cpp.o CMakeFiles/Urho3D.dir/Resource/BackgroundLoader.cpp.o CMakeFiles/Urho3D.dir/Resource/XMLElement.cpp.o CMakeFiles/Urho3D.dir/Resource/Decompress.cpp.o CMakeFiles/Urho3D.dir/LuaScript/ToluaUtils.cpp.o CMakeFiles/Urho3D.dir/LuaScript/LuaScript.cpp.o CMakeFiles/Urho3D.dir/LuaScript/LuaScriptInstance.cpp.o CMakeFiles/Urho3D.dir/LuaScript/LuaFile.cpp.o CMakeFiles/Urho3D.dir/LuaScript/LuaScriptEventInvoker.cpp.o CMakeFiles/Urho3D.dir/LuaScript/LuaFunction.cpp.o CMakeFiles/Urho3D.dir/Engine/Console.cpp.o CMakeFiles/Urho3D.dir/Engine/Engine.cpp.o CMakeFiles/Urho3D.dir/Engine/Application.cpp.o CMakeFiles/Urho3D.dir/Engine/DebugHud.cpp.o CMakeFiles/Urho3D.dir/AngelScript/GraphicsAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/ScriptFile.cpp.o CMakeFiles/Urho3D.dir/AngelScript/Script.cpp.o CMakeFiles/Urho3D.dir/AngelScript/NavigationAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/DatabaseAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/ScriptAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/NetworkAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/ResourceAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/ScriptAPIDump.cpp.o CMakeFiles/Urho3D.dir/AngelScript/InputAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/AudioAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/MathAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/UIAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/Addons.cpp.o CMakeFiles/Urho3D.dir/AngelScript/Urho2DAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/PhysicsAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/IOAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/CoreAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/SceneAPI.cpp.o CMakeFiles/Urho3D.dir/AngelScript/ScriptInstance.cpp.o CMakeFiles/Urho3D.dir/AngelScript/EngineAPI.cpp.o CMakeFiles/Urho3D.dir/Scene/SplinePath.cpp.o CMakeFiles/Urho3D.dir/Scene/Component.cpp.o CMakeFiles/Urho3D.dir/Scene/SceneResolver.cpp.o CMakeFiles/Urho3D.dir/Scene/ValueAnimation.cpp.o CMakeFiles/Urho3D.dir/Scene/UnknownComponent.cpp.o CMakeFiles/Urho3D.dir/Scene/SmoothedTransform.cpp.o CMakeFiles/Urho3D.dir/Scene/LogicComponent.cpp.o CMakeFiles/Urho3D.dir/Scene/Node.cpp.o CMakeFiles/Urho3D.dir/Scene/Scene.cpp.o CMakeFiles/Urho3D.dir/Scene/ObjectAnimation.cpp.o CMakeFiles/Urho3D.dir/Scene/Serializable.cpp.o CMakeFiles/Urho3D.dir/Scene/ValueAnimationInfo.cpp.o CMakeFiles/Urho3D.dir/Scene/Animatable.cpp.o CMakeFiles/Urho3D.dir/Network/HttpRequest.cpp.o CMakeFiles/Urho3D.dir/Network/NetworkPriority.cpp.o CMakeFiles/Urho3D.dir/Network/Network.cpp.o CMakeFiles/Urho3D.dir/Network/Connection.cpp.o CMakeFiles/Urho3D.dir/Navigation/DynamicNavigationMesh.cpp.o CMakeFiles/Urho3D.dir/Navigation/CrowdManager.cpp.o CMakeFiles/Urho3D.dir/Navigation/Obstacle.cpp.o CMakeFiles/Urho3D.dir/Navigation/CrowdAgent.cpp.o CMakeFiles/Urho3D.dir/Navigation/OffMeshConnection.cpp.o CMakeFiles/Urho3D.dir/Navigation/NavBuildData.cpp.o CMakeFiles/Urho3D.dir/Navigation/Navigable.cpp.o CMakeFiles/Urho3D.dir/Navigation/NavigationMesh.cpp.o CMakeFiles/Urho3D.dir/Navigation/NavArea.cpp.o CMakeFiles/Urho3D.dir/Graphics/Zone.cpp.o CMakeFiles/Urho3D.dir/Graphics/IndexBuffer.cpp.o CMakeFiles/Urho3D.dir/Graphics/RenderSurface.cpp.o CMakeFiles/Urho3D.dir/Graphics/GraphicsDefs.cpp.o CMakeFiles/Urho3D.dir/Graphics/OcclusionBuffer.cpp.o CMakeFiles/Urho3D.dir/Graphics/AnimatedModel.cpp.o CMakeFiles/Urho3D.dir/Graphics/Batch.cpp.o CMakeFiles/Urho3D.dir/Graphics/Texture2DArray.cpp.o CMakeFiles/Urho3D.dir/Graphics/Texture3D.cpp.o CMakeFiles/Urho3D.dir/Graphics/Terrain.cpp.o CMakeFiles/Urho3D.dir/Graphics/ConstantBuffer.cpp.o CMakeFiles/Urho3D.dir/Graphics/TextureCube.cpp.o CMakeFiles/Urho3D.dir/Graphics/BillboardSet.cpp.o CMakeFiles/Urho3D.dir/Graphics/ShaderPrecache.cpp.o CMakeFiles/Urho3D.dir/Graphics/Light.cpp.o CMakeFiles/Urho3D.dir/Graphics/Model.cpp.o CMakeFiles/Urho3D.dir/Graphics/Tangent.cpp.o CMakeFiles/Urho3D.dir/Graphics/Octree.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/RenderPath.cpp.o CMakeFiles/Urho3D.dir/Graphics/TerrainPatch.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/Camera.cpp.o CMakeFiles/Urho3D.dir/Graphics/ParticleEffect.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/Texture2D.cpp.o CMakeFiles/Urho3D.dir/Graphics/Geometry.cpp.o CMakeFiles/Urho3D.dir/Graphics/GPUObject.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/Shader.cpp.o CMakeFiles/Urho3D.dir/Graphics/Skeleton.cpp.o CMakeFiles/Urho3D.dir/Graphics/VertexBuffer.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/RibbonTrail.cpp.o CMakeFiles/Urho3D.dir/Graphics/Texture.cpp.o CMakeFiles/Urho3D.dir/Graphics/View.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/StaticModelGroup.cpp.o CMakeFiles/Urho3D.dir/Graphics/Renderer.cpp.o CMakeFiles/Urho3D.dir/Graphics/OctreeQuery.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/Viewport.cpp.o CMakeFiles/Urho3D.dir/Graphics/AnimationController.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/ShaderVariation.cpp.o CMakeFiles/Urho3D.dir/Graphics/Skybox.cpp.o CMakeFiles/Urho3D.dir/Graphics/DecalSet.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLIndexBuffer.cpp.o CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLGraphicsImpl.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLVertexBuffer.cpp.o CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLTexture2DArray.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLShaderProgram.cpp.o CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLTexture3D.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLShaderVariation.cpp.o CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLTexture.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLConstantBuffer.cpp.o CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLRenderSurface.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLGraphics.cpp.o CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLTextureCube.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/OpenGL/OGLTexture2D.cpp.o CMakeFiles/Urho3D.dir/Graphics/StaticModel.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/ParticleEmitter.cpp.o CMakeFiles/Urho3D.dir/Graphics/Drawable.cpp.o CMakeFiles/Urho3D.dir/Graphics/AnimationState.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/Animation.cpp.o CMakeFiles/Urho3D.dir/Graphics/CustomGeometry.cpp.o CMakeFiles/Urho3D.dir/Graphics/Graphics.cpp.o 
CMakeFiles/Urho3D.dir/Graphics/Material.cpp.o CMakeFiles/Urho3D.dir/Graphics/Technique.cpp.o CMakeFiles/Urho3D.dir/Graphics/DebugRenderer.cpp.o 
CMakeFiles/Urho3D.dir/Container/Str.cpp.o CMakeFiles/Urho3D.dir/Container/HashBase.cpp.o CMakeFiles/Urho3D.dir/Container/Swap.cpp.o 
CMakeFiles/Urho3D.dir/Container/RefCounted.cpp.o CMakeFiles/Urho3D.dir/Container/Allocator.cpp.o CMakeFiles/Urho3D.dir/Container/VectorBase.cpp.o 
CMakeFiles/Urho3D.dir/Audio/SoundStream.cpp.o CMakeFiles/Urho3D.dir/Audio/SoundSource.cpp.o CMakeFiles/Urho3D.dir/Audio/SoundListener.cpp.o 
CMakeFiles/Urho3D.dir/Audio/Sound.cpp.o CMakeFiles/Urho3D.dir/Audio/SoundSource3D.cpp.o CMakeFiles/Urho3D.dir/Audio/BufferedSoundStream.cpp.o 
CMakeFiles/Urho3D.dir/Audio/Audio.cpp.o CMakeFiles/Urho3D.dir/Audio/OggVorbisSoundStream.cpp.o 
CMakeFiles/Urho3D.dir/LuaScript/generated/EngineLuaAPI.cpp.o CMakeFiles/Urho3D.dir/LuaScript/generated/InputLuaAPI.cpp.o 
CMakeFiles/Urho3D.dir/LuaScript/generated/GraphicsLuaAPI.cpp.o CMakeFiles/Urho3D.dir/LuaScript/generated/AudioLuaAPI.cpp.o 
CMakeFiles/Urho3D.dir/LuaScript/generated/UILuaAPI.cpp.o CMakeFiles/Urho3D.dir/LuaScript/generated/PhysicsLuaAPI.cpp.o 
CMakeFiles/Urho3D.dir/LuaScript/generated/NetworkLuaAPI.cpp.o CMakeFiles/Urho3D.dir/LuaScript/generated/CoreLuaAPI.cpp.o 
CMakeFiles/Urho3D.dir/LuaScript/generated/Urho2DLuaAPI.cpp.o CMakeFiles/Urho3D.dir/LuaScript/generated/LuaScriptLuaAPI.cpp.o 
CMakeFiles/Urho3D.dir/LuaScript/generated/IOLuaAPI.cpp.o CMakeFiles/Urho3D.dir/LuaScript/generated/NavigationLuaAPI.cpp.o 
CMakeFiles/Urho3D.dir/LuaScript/generated/ResourceLuaAPI.cpp.o CMakeFiles/Urho3D.dir/LuaScript/generated/SceneLuaAPI.cpp.o 
CMakeFiles/Urho3D.dir/LuaScript/generated/MathLuaAPI.cpp.o
arm-linux-androideabi-ranlib ../../libs/armeabi-v7a/libUrho3D.a



	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	/usr/bin/cmake -E rename /home/xiaoming/Downloads/Urho3D-1.6/build/libs/armeabi-v7a/libUrho3D.a /home/xiaoming/Downloads/Urho3D-1.6/build/libs/armeabi-v7a/libUrho3D.a.engine
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo CREATE /home/xiaoming/Downloads/Urho3D-1.6/build/libs/armeabi-v7a/libUrho3D.a >script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/libs/armeabi-v7a/libUrho3D.a.engine >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/FreeType/libFreeType.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/JO/libJO.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/LZ4/libLZ4.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/PugiXml/libPugiXml.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/SDL/libSDL.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/StanHull/libStanHull.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/AngelScript/libAngelScript.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/Lua/libLua.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/toluapp/src/lib/libtoluapp.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/Civetweb/libCivetweb.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/kNet/libkNet.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/Detour/libDetour.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/DetourCrowd/libDetourCrowd.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/DetourTileCache/libDetourTileCache.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/Recast/libRecast.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/Box2D/libBox2D.a >>script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	echo ADDLIB /home/xiaoming/Downloads/Urho3D-1.6/build/Source/ThirdParty/Bullet/libBullet.a >>script.ar
	
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	/home/xiaoming/Android/Sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-gcc-ar -M <script.ar
	cd /home/xiaoming/Downloads/Urho3D-1.6/build/Source/Urho3D && 
	/usr/bin/cmake -E remove /home/xiaoming/Downloads/Urho3D-1.6/build/libs/armeabi-v7a/libUrho3D.a.engine script.ar
	
	将所有第三方静态库打入 libUrho3D.a 文件中
}

