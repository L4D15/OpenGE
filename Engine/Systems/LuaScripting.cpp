#include "Engine/Systems/LuaScripting.hpp"
#include "Engine/Core/Game.hpp"
#include "Engine/Assets/Asset.hpp"
#include "Engine/Assets/RenderizableAsset.hpp"
#include "Engine/Assets/Sprite.hpp"
#include "Engine/Components/BoxCollider.hpp"
#include "Engine/Components/LuaScript.hpp"
#include "Engine/Components/Physics.hpp"
#include "Engine/Components/SpriteRenderer.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Core/Collisions/Box.hpp"
#include "Engine/Core/Collisions/Circle.hpp"
#include "Engine/Core/Math/Math.hpp"
#include "Engine/Core/Math/Quaternion.hpp"
#include "Engine/Core/Math/Vector2.hpp"
#include "Engine/Core/Math/Vector3.hpp"
#include "Engine/Core/Color.hpp"
#include "Engine/Core/Game.hpp"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Core/Input.hpp"
#include "Engine/Core/ResourceManager.hpp"
#include "Engine/Core/Scene.hpp"
#include "Engine/Core/SceneManager.hpp"
#include "Engine/Core/Settings.hpp"
#include "Engine/Core/Time.hpp"
#include "Engine/Core/Window.hpp"
#include <sstream>
#include <luabind/operator.hpp>

using namespace Systems;

LuaScripting::LuaScripting()
    : Base(anax::ComponentFilter().requires<Components::LuaScript>())
{
    // Initialize Lua
    Game::Log("Initializing Lua...", false);

    luaState = luaL_newstate();

    if (luaState == NULL)
    {
        Game::Log("Failed");
    }
    else
    {
        Game::Log("Ok");
        luaL_openlibs(luaState);
        luabind::open(luaState);
    }
}

LuaScripting::~LuaScripting()
{
    lua_close(luaState);
}

void LuaScripting::RegisterClass(const std::string scriptPath)
{
    int error;

    error = luaL_dofile(luaState, scriptPath.c_str());

    if (error != 0)
    {
        Game::Log("-- [!] Failed to register class in ", false);
        Game::Log(scriptPath);
        Game::Log(lua_tostring(luaState, lua_gettop(luaState)));
        lua_pop(luaState, 1);
    }
}

/**
 * @brief Register the object in Lua so we can add class instances to it.
 * @param object    Object to be registered in Lua.
 */
void LuaScripting::RegisterObject(const anax::Entity &object)
{
    GameObject& gameObject = Game::Find(object);

    std::stringstream ss;

    ss << gameObject.name << " = {}" << std::endl;

    Game::Log("Executing the following Lua code: ");
    Game::Log(ss.str());
    Game::Log("--- END ---");

    int error;

    error = luaL_dostring(luaState, ss.str().c_str());

    if (error != 0)
    {
        Game::Log(lua_tostring(luaState, lua_gettop(luaState)));
        lua_pop(luaState, 1);
    }
}

void LuaScripting::CreateInstance(const std::string className, const anax::Entity &owner)
{
    GameObject& object = Game::Find(owner);

    std::stringstream ss;

    ss << object.name << "['" << className << "'] = " << className << "()" << std::endl;

    std::string luaString = ss.str();

    int error = luaL_dostring(luaState, luaString.c_str());

    if (error != 0)
    {
        Game::Log(lua_tostring(luaState, lua_gettop(luaState)));
        lua_pop(luaState, 1);
    }
}

void LuaScripting::RunFunction(const string function, const string className, const anax::Entity &owner)
{
    GameObject& object = Game::Find(owner);

    // Set gameObject reference to the owner of this script
    SetGlobal<GameObject&>("gameObject", object);

    std::stringstream ss;

    ss << object.name << "['" << className << "']." << function << "()";

    int error = luaL_dostring(luaState, ss.str().c_str());

    if (error != 0)
    {
        Game::Log(lua_tostring(luaState, lua_gettop(luaState)));
        lua_pop(luaState, 1);
    }
}

void LuaScripting::onEntityAdded(anax::Entity& entity)
{
    Components::LuaScript& script = entity.getComponent<Components::LuaScript>();

    RegisterClass(script.GetPath());
    RegisterObject(entity);
    CreateInstance(script.GetClass(), entity);
    RunFunction("Start", entity.getComponent<Components::LuaScript>().GetClass(), entity);
}

void LuaScripting::onEntityRemoved(anax::Entity& entity)
{
    // TODO: Free data from lua. How?!
}

template <class T>
void LuaScripting::SetGlobal(const std::string name, const T& value)
{
    luabind::globals(luaState)[name.c_str()] = value;
}

void LuaScripting::ProcessEntities()
{
    auto entities = getEntities();

    for (auto& entity : entities)
    {
        SetGlobal<GameObject&>("gameObject", Game::Find(entity));
        RunFunction("Update", entity.getComponent<Components::LuaScript>().GetClass(), entity);
    }
}

using namespace Components;

void LuaScripting::CreateEnvironment()
{
    Game::Log("Creating Lua environment...");
    luabind::module(luaState)
    [
        // Vector3
        luabind::class_<Vector3>("Vector3")
            .def(luabind::constructor<>())
            .def(luabind::constructor<float, float, float>())
            .def(luabind::constructor<const Vector3&>())
            .def("DotProduct", &Vector3::DotProduct)
            .def("Length", &Vector3::Length)
            .def("LengthQuadratic", &Vector3::LengthQuadratic)
            .def("Distance", &Vector3::Distance)
            .def("DistanceQuadratic", &Vector3::DistanceQuadratic)
            .def("Normalized", &Vector3::Normalized)
            .def(luabind::self + Vector3())
            .def(luabind::self - Vector3())
            .def(luabind::self * Vector3())
            .def(luabind::self * float()),

        // Quaternion
        luabind::class_<Quaternion>("Quaternion")
            .def(luabind::constructor<>())
            .def(luabind::constructor<float, float, float, float>())
            .def(luabind::constructor<float, Vector3&>())
            .def(luabind::constructor<const Quaternion&>())
            .def("DotProduct", &Quaternion::DotProduct)
            .def("Length", &Quaternion::Length)
            .def("LengtQuadratic", &Quaternion::LengthQuadratic)
            .def("Normalized", &Quaternion::Normalized)
            .def("ToString", &Quaternion::ToString),

        // Game
        luabind::class_<Game>("Game")
            .scope[
                luabind::def("Terminate", &Game::Terminate),
                luabind::def("Log", &Game::Log)
            ],

        // Input
        luabind::class_<Input>("Input")
            .def("MapButton", &Input::MapButton)
            .def("GetButton", &Input::GetButton)
            .def("GetButtonPressTime", &Input::GetButtonPressTime)
            .def("GetButtonReleaseTime", &Input::GetButtonReleaseTime)
            .def("GetButtonHoldTime", &Input::GetButtonHoldTime)
            .def("ToString", &Input::ToString),

        // ResourceManager
        luabind::class_<ResourceManager>("ResourceManager")
            .def("GetPath", &ResourceManager::GetPath)
            .def("GetWorkingPath", &ResourceManager::GetWorkingPath)
            .def("GetSprite", &ResourceManager::GetAsset<Sprite>),

        luabind::class_<Time>("Time")
            .def("GetFPS", &Time::GetFPS)
            .scope[
                luabind::def("GetDeltaTime", &Time::GetDeltaTime),
                luabind::def("GetTime", &Time::GetTime)
            ],

        // Asset
        luabind::class_<Asset>("Asset")
            .def("ToString", &Asset::ToString)
            .def_readonly("name", &Asset::name)
            .def_readonly("filePath", &Asset::filePath),

        // RenderizableAsset
        luabind::class_<RenderizableAsset>("RenderizableAsset")
            .def("Render", &RenderizableAsset::Render),

        // Sprite
        luabind::class_<Sprite>("Sprite")
            .def("ToString", &Sprite::ToString)
            .property("width", &Sprite::GetWidth)
            .property("height", &Sprite::GetHeight),

        // Box
        luabind::class_<Box>("Box")
            .def(luabind::constructor<float, float, float, float>())
            .def("Collides", &Box::Collides)
            .def("ToString", &Box::ToString)
            .def_readwrite("offsetX", &Box::offsetX)
            .def_readwrite("offsetY", &Box::offsetY)
            .def_readwrite("width", &Box::width)
            .def_readwrite("height", &Box::height),

        // Circle
        luabind::class_<Circle>("Circle")
            .def(luabind::constructor<float, float, float>())
            .def("Collides", &Circle::Collides)
            .def_readwrite("radius", &Circle::radius)
            .def_readwrite("offsetX", &Circle::offsetX)
            .def_readwrite("offsetY", &Circle::offsetY),

        // BoxCollider
        luabind::class_<BoxCollider>("BoxCollider")
            .def(luabind::constructor<>())
            .def(luabind::constructor<float, float, float, float>())
            .def_readwrite("box", &BoxCollider::box),

        // LuaScript
        luabind::class_<LuaScript>("LuaScript")
            .def(luabind::constructor<>())
            .def(luabind::constructor<std::string, std::string>())
            .property("className", &LuaScript::GetClass)
            .property("scriptPath", &LuaScript::GetPath),

        // Physics
        luabind::class_<Components::Physics>("Physics")
            .def(luabind::constructor<>())
            .def(luabind::constructor<Vector3&, Vector3&, float, float, float, bool>())
            .def("AddForceVec", (void (Components::Physics::*) (const Vector3&)) &Components::Physics::AddForce)
            .def("AddForce", (void (Components::Physics::*) (const float, const float, const float)) &Components::Physics::AddForce)
            .def("AddTorqueVec", (void (Components::Physics::*) (const Vector3&)) &Components::Physics::AddTorque)
            .def("AddTorque", (void (Components::Physics::*) (const float, const float, const float)) &Components::Physics::AddTorque)
            .def_readwrite("velocity", &Components::Physics::velocity)
            .def_readwrite("aceleration", &Components::Physics::aceleration)
            .def_readwrite("torque", &Components::Physics::torque)
            .def_readwrite("mass", &Components::Physics::mass)
            .def_readwrite("linearDrag", &Components::Physics::linearDrag)
            .def_readwrite("angularDrag", &Components::Physics::angularDrag)
            .def_readwrite("isKinematic", &Components::Physics::isKinematic),

        // SpriteRenderer
        luabind::class_<Components::SpriteRenderer>("SpriteRenderer")
            .def(luabind::constructor<>())
            .def(luabind::constructor<const std::string>())
            .def("Render", &SpriteRenderer::Render)
            .def("Update", &SpriteRenderer::Update)
            .def("ChangeAnimation", &SpriteRenderer::ChangeAnimation),

        // Transform
        luabind::class_<Components::Transform>("Transform")
            .def(luabind::constructor<>())
            .def(luabind::constructor<float, float, float>())
            .def(luabind::constructor<float, float, float, float, float, float>())
            .def(luabind::constructor<float, float, float, float, float, float, float, float, float>())
            .def("ToString", &Transform::ToString)
            .def_readwrite("position", &Transform::position)
            .def_readwrite("rotation", &Transform::rotation)
            .def_readwrite("scale", &Transform::scale),

        // GameObject
        luabind::class_<GameObject>("GameObject")
            .def("AddComponent", (void (GameObject::*) (const std::string)) &GameObject::AddComponent)
            .def("GetTransform", &GameObject::GetComponent<Transform>)
            .def("GetSpriteRenderer", &GameObject::GetComponent<SpriteRenderer>)
            .def("GetPhysics", &GameObject::GetComponent<Components::Physics>)
            .def("GetLuaScript", &GameObject::GetComponent<LuaScript>)
            .def("Activate", &GameObject::Activate)
            .def("Deactivate", &GameObject::Deactivate)
            .property("name", &GameObject::GetName, &GameObject::SetName)
        // ---
    ];

    // Set some Global variables
    SetGlobal<Input&>("input", *Game::input);
    Game::Log("Done");
}
