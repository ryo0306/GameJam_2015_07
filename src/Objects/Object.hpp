
#pragma once
#include "../Common.hpp"
#include "../Resources/Resource.h"
#include "../Utility/Collision.h"
#include "../Utility/GameData.h"
#include <memory>


namespace frameworks {
namespace object {

struct Block {
  Vec2f pos, size;
  u_int id;
};
typedef std::vector<Block>  Blocks;

enum ObjectState {
  ALIVE = -1,
  DEAD = 0,

  All_State,
};

class Object {
public:
  Object() : deadTime(ALIVE) {}
  virtual ~Object() = default;

  virtual void Update() {}
  virtual void Draw() = 0;

  // �I�u�W�F�N�g�̍폜�J�E���^�����炷
  void DeadTimeUpdate() { if (deadTime > DEAD) --deadTime; }

  // �I�u�W�F�N�g�̍폜�t���O��Ԃ�
  const bool IsDead() const { return deadTime == DEAD; }

  // ���W�Ȃǂ�Ԃ�
  const Transform& GetTransform() const { return transform; }

protected:
  int deadTime;          // �폜�J�E���^�F0 �̂Ƃ��A�폜�����
  Transform transform;   // ���W�A�T�C�Y�A��]��ԁA��]���x
};

}  // end object
}  // end frameworks

typedef std::shared_ptr<frameworks::object::Object>  ObjectRef;
