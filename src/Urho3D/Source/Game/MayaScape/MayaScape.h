//
// Copyright (c) 2008-2018 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include <MayaScape/ai/evolution_manager.h>
#include "Game.h"
#include "Sample2D.h"
#include "Vehicle.h"
#include "Player.h"


class Player;
class Character2D;
class Sample2D;
class EvolutionManager;

#define MAX_AGENTS 1024 // Set max limit for agents (used for storage)

// Marker Map Tokens
using namespace Urho3D;
Vector3 bkgMarkerToken = Vector3(0.5, 1, 0.5); // Black
Vector3 trackMarkerToken = Vector3(0.500000059604645,1,0.643137276172638); // #494949
Vector3 treeMarkerToken = Vector3(0.5, 1, 0.594117641448975); // #303030
Vector3 waypointToken = Vector3(0.5,1.00000035762787,0.927451014518738); // #dadada

struct ParticlePool {
    bool used; // Is particle emitter used?
    int usedBy; // Node id using particle emitter
    SharedPtr<Node> node; // Scene node
    float lastEmit;
    float currEmit;
    float timeout;
};

/// Urho2D platformer example.
/// This sample demonstrates:
///    - Creating an orthogonal 2D scene from tile map file
///    - Displaying the scene using the Renderer subsystem
///    - Handling keyboard to move a character and zoom 2D camera
///    - Generating physics shapes from the tmx file's objects
///    - Mixing physics and translations to move the character
///    - Using Box2D Contact listeners to handle the gameplay
///    - Displaying debug geometry for physics and tile map
/// Note that this sample uses some functions from Sample2D utility class.
class MayaScape : public Game
{
    URHO3D_OBJECT(MayaScape, Game);

public:
    /// Construct.
    explicit MayaScape(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;
    /// Setup before engine initialization. Modifies the engine parameters.
    void Setup() override;

    void Stop() override;

private:
    /// Construct the scene content.
    void CreateScene();
    void CreatePlayer();
    void SetCameraTarget();

    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the logic post update event.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post render update event.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the end rendering event.
    void HandleSceneRendered(StringHash eventType, VariantMap& eventData);
    void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    /// Handle the contact begin event (Box2D contact listener).
    void HandleCollisionBegin(StringHash eventType, VariantMap& eventData);
    /// Handle the contact end event (Box2D contact listener).
    void HandleCollisionEnd(StringHash eventType, VariantMap& eventData);
    /// Handle reloading the scene.
    void ReloadScene(bool reInit);
    /// Handle 'PLAY' button released event.
    void HandlePlayButton(StringHash eventType, VariantMap& eventData);

    void SetParticleEmitter(int hitId, float contactX, float contactY, int type, float timeStep);
    void HandleUpdateParticlePool(float timeStep);

    // Init Genetic Algorithm sprite generator
    void InitEvolutionSpriteGenerator();

    // Display Genetic Algorithm Evolution Manager statistics
    void ShowEvolutionManagerStats();



        /// The controllable character component.
//    WeakPtr<Character2D> player_;
//    WeakPtr<Character2D> agents_[MAX_AGENTS];

    SharedPtr<Player> player_; // This player
    SharedPtr<Player> agents_[MAX_AGENTS]; // Agents


    WeakPtr<Terrain> terrain_;
    Vector<Vector3> trees_;

    Vector<Vector3> waypoints_;
    unsigned int wpStartIndex_;
    unsigned int wpActiveIndex_;

    Vector<Vector3> focusObjects_;
    unsigned int focusIndex_;

    WeakPtr<TileMap3D> tileMap_;

    /// Flag for drawing debug geometry.
    bool drawDebug_{};
    bool doSpecial_{};
    /// Scaling factor based on tiles' aspect ratio.
    float moveSpeedScale_{};

    /// Sample2D utility object.
    SharedPtr<Sample2D> sample2D_;
    /// Powerbar P1 sprite.
    SharedPtr<Sprite> powerBarP1Sprite_;
    /// Powerbar Bkg P1 sprite.
    SharedPtr<Sprite> powerBarBkgP1Sprite_;

    /// RPM P1 sprite.
    SharedPtr<Sprite> rpmBarP1Sprite_;
    /// RPM Bkg P1 sprite.
    SharedPtr<Sprite> rpmBarBkgP1Sprite_;

    /// Velocity P1 sprite.
    SharedPtr<Sprite> velBarP1Sprite_;
    /// Velocity Bkg P1 sprite.
    SharedPtr<Sprite> velBarBkgP1Sprite_;

    /// Mini-map P1 sprite.
    SharedPtr<Sprite> miniMapP1Sprite_;

    /// Mini-map waypoint sprite.
    SharedPtr<Sprite> miniMapWPSprite_;

    /// Mini-map Bkg sprite.
    SharedPtr<Sprite> miniMapBkgSprite_;
    /// Marker map Bkg sprite.
    SharedPtr<Sprite> markerMapBkgSprite_;

    /// Steering wheel
    SharedPtr<Sprite> steerWheelSprite_;

    /// Particle pool
    ParticlePool particlePool_[20];

    #define NUM_DEBUG_FIELDS 8
    // Debug text
    Text* debugText_[NUM_DEBUG_FIELDS];

    WeakPtr<Node> raceTrack_;
    WeakPtr<CollisionShape> trackColShape_;

    WeakPtr<Text>  textKmH_;

    // smooth step
    Quaternion     vehicleRot_;
    Vector3        targetCameraPos_;
    float          springVelocity_;

    // dbg
    WeakPtr<Text>  textStatus_;
    Timer          fpsTimer_;
    int            framesCount_;

};