
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"


namespace frameworks {

enum WindowSize {
  WIDTH  = 1600,
  HEIGHT = 900,
};

// �L�[�{�[�h���͂̈ꗗ
enum KeyBind {
  ESCAPE = GLFW_KEY_ESCAPE,
  ENTER  = GLFW_KEY_ENTER,
  KEY_L  = GLFW_KEY_LEFT,
  KEY_R  = GLFW_KEY_RIGHT,
  KEY_U  = GLFW_KEY_UP,
  KEY_D  = GLFW_KEY_DOWN,
  SPACE  = GLFW_KEY_SPACE,
};

// �d�͂̕���
enum GravityDirection {
  Bottom,
  Right,
  Top,
  Left,
};

// �L�����N�^�[�̌���
enum PlayerDirection {
  Move_L = -1,
  Move_R = 1,
};

// �V�X�e���n
enum System {
  FPS = 60,
};

// ���W�A�T�C�Y�A��]��ԁA��]���x
struct Transform {
  Vec2f pos, scale;
  float rotate, angle;
};

// �摜�A�؂�o���J�n�ʒu�A�؂���T�C�Y�A�F
struct Sprite {
  Texture texture;
  Vec2f start, size;
  Color color;
};

// �A�v���P�[�V�����@�\�̌Ăяo��
AppEnv& Env();

// �����𓾂�
Random& Rand();

}  // end frameworks
