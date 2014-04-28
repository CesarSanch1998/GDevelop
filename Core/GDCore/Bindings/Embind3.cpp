/** \file
 *  Game Develop
 *  2008-2014 Florian Rival (Florian.Rival@gmail.com)
 */

/*
 * When cross-compiling using emscripten, this file exposes the GDCore API
 * to javascript.
 *
 * The javascript API of GDCore is the same as the C++ one except that:
 *  - functions begins lowercase ("getLayout"),
 *  - not all methods or classes are available.
 */
#if defined(EMSCRIPTEN)
#include "Embind.h"
#include <emscripten/bind.h>
#include "GDCore/IDE/Dialogs/PropertyDescriptor.h"
#include "GDCore/PlatformDefinition/Layout.h"
#include "GDCore/PlatformDefinition/Project.h"
#include "GDCore/PlatformDefinition/Platform.h"
#include "GDCore/PlatformDefinition/VariablesContainer.h"
#include "GDCore/PlatformDefinition/Object.h"
#include "GDCore/PlatformDefinition/Automatism.h"
#include "GDCore/BuiltinExtensions/SpriteExtension/SpriteObject.h"
#include <set>

using namespace emscripten;
using namespace gd;

namespace gd {
SpriteObject * AsSpriteObject(gd::Object * object) { return static_cast<SpriteObject *>(object); }
gd::Animation * SpriteObject_GetAnimation(gd::SpriteObject & o, unsigned int i) { return &o.GetAnimation(i); }
gd::Direction * Animation_GetDirection(gd::Animation & a, unsigned int i) { return &a.GetDirection(i); }
gd::Sprite * Direction_GetSprite(gd::Direction & d, unsigned int i) { return &d.GetSprite(i); }
}

EMSCRIPTEN_BINDINGS(gd_SpriteObject) {
    class_<Sprite>("Sprite")
        .constructor<>()
        //TODO
        ;

    class_<Direction>("Direction")
        .constructor<>()
        .function("getSprite", &Direction_GetSprite, allow_raw_pointers())
        .function("getSpritesCount", &Direction::GetSpritesCount)
        .function("hasNoSprites", &Direction::HasNoSprites)
        .function("removeAllSprites", &Direction::RemoveAllSprites)
        //TODO
        ;

    class_<Animation>("Animation")
        .constructor<>()
        .function("setDirectionsCount", &Animation::SetDirectionsCount)
        .function("getDirectionsCount", &Animation::GetDirectionsCount)
        .function("getDirection", &Animation_GetDirection, allow_raw_pointers())
        .function("setDirection", &Animation::SetDirection)
        .function("hasNoDirections", &Animation::HasNoDirections)
        ;

    class_<SpriteObject, base<gd::Object> >("SpriteObject")
        .constructor<const std::string &>()
        .function("addAnimation", &SpriteObject::AddAnimation)
        .function("getAnimation", &SpriteObject_GetAnimation, allow_raw_pointers())
        .function("getAnimationsCount", &SpriteObject::GetAnimationsCount)
        .function("removeAnimation", &SpriteObject::RemoveAnimation)
        .function("removeAllAnimations", &SpriteObject::RemoveAllAnimations)
        .function("hasNoAnimations", &SpriteObject::HasNoAnimations)
        ;

    function("asSpriteObject", &AsSpriteObject, allow_raw_pointers());
}

#endif