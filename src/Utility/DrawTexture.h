
#pragma once
#include "../Common.hpp"


namespace frameworks {
namespace utility {

// ���_�̈ꗗ
enum class Origin {
  LeftTop,
  Left,
  LeftBottom,
  CenterTop,
  Center,
  CenterBottom,
  RightTop,
  Right,
  RightBottom,

  All_Info,
};

// �摜�̌��_���w��A�ړ��ʂ�Ԃ�
const Vec2f& OffsetTextureOrigin(const Origin info);

// �摜�̕`��F�@�\�ǉ���
void DrawTexture(const Transform& transform,
                 const Sprite& sprite,
                 const Vec2f& offset = Vec2f::Zero());

}  // end utility
}  // end frameworks
