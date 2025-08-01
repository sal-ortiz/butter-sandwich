
#ifndef _SCENE_BASE_HPP

  #define _SCENE_BASE_HPP

  #include <core/list/linked_list.hpp>
  #include <core/map/hash_map.hpp>
  #include <core/renderer.hpp>
  #include <runtime/base.hpp>
  #include <runtime/sprite.hpp>
  #include <runtime/state.hpp>
  #include <runtime/data/position.hpp>
  #include <runtime/data/angle.hpp>
  #include <runtime/data/scale.hpp>
  #include <runtime/data/view.hpp>
  #include <runtime/data/trajectory.hpp>


  class SceneBase: public RuntimeBase {

    private:

      //void*(*evalCallback)(void*);

      const char* action;
      HashMap<Sprite*>* sprites;


    public:

      State* state;

      const char* name;
      const char* type;

      // TODO: hack: find a better way to serve these values.
      uint32_t width;
      uint32_t height;

      bool isActive;
      bool isGarbage;

      SceneBase() {
        //this->evalCallback = NULL;
        this->isActive = true;
        this->isGarbage = false;

        this->sprites = new HashMap<Sprite*>();
        this->state = new State();

        this->state->set("position", new Position());
        this->state->set("angle", new Angle());
        this->state->set("scale", new Scale());
        this->state->set("view", new View());
        this->state->set("color", new Color());
        this->state->set("trajectory", new Trajectory());

        this->state->set("absolute_position", new Position());
      }

      ~SceneBase() {
        LinkedList<Sprite*>* sprites = this->sprites->getValues();

        uint32_t numSprites = sprites->getLength();

        for (uint32_t idx = 0; idx < numSprites; idx++) {
          Sprite* sprite = sprites->get(idx);

          delete sprite;
        }

        delete (Position*)this->state->get("position");
        delete (Angle*)this->state->get("angle");
        delete (Scale*)this->state->get("scale");
        delete (View*)this->state->get("view");
        delete (Color*)this->state->get("color");
        delete (Trajectory*)this->state->get("trajectory");
        delete (Position*)this->state->get("absolute_position");

        delete this->sprites;
        delete this->state;
      }

      void addSprite(const char* actionId, Sprite* sprite) {
        this->sprites->set(actionId, sprite);
      }

      void setAction(const char* curAction) {
        Sprite* curSprite = this->sprites->get(curAction);

        this->action = curAction;

        this->width = curSprite->width;
        this->height = curSprite->height;
      }

      void setName(const char* name) {
        uint32_t nameLen = strlen(name);
        char* newName = new char[nameLen + 1];

        strcpy(newName, name);

        this->name = newName;
      }

      const char* getName() {
        return this->name;
      }

      void setType(const char* type) {
        this->type = type;
      }

      const char* getType() {
        return this->type;
      }

      template <typename ... Args>
      void onCollision(void*(*callback)(Args...)) {
        uint32_t charId = this->getIdentifier();

        char* hookId = new char[Hook::ID_LENGTH];
        Hook::generateIdentifier(hookId, "hook", charId, "onCollision", "action");

        this->on(hookId, callback);
      }

      template <typename ... Args>
      void onEvaluate(void*(*callback)(Args...)) {
        uint32_t charId = this->getIdentifier();

        char* hookId = new char[Hook::ID_LENGTH];
        Hook::generateIdentifier(hookId, "hook", charId, "onEvaluate", "action");

        this->on(hookId, callback);
      }

      void render(Renderer* renderer) {
        const char* actionId = this->action;

        Position* position = (Position*)this->state->get("position");
        Angle* angle = (Angle*)this->state->get("angle");
        Scale* scale = (Scale*)this->state->get("scale");
        View* view = (View*)this->state->get("view");
        Color* color = (Color*)this->state->get("color");

        Sprite* sprite = this->sprites->get(actionId);

        this->width = sprite->width;
        this->height = sprite->height;

        sprite->render(renderer, position, view, angle, scale, color);
      }

      void evaluate(SceneBase* scene) {
        uint32_t charId = this->getIdentifier();

        char* hookId = new char[Hook::ID_LENGTH];
        Hook::generateIdentifier(hookId, "hook", charId, "onEvaluate", "action");

        Hook::executeCallback(hookId, this, scene);

        delete hookId;
      }

  };

#endif
