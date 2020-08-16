#include "mod.h"

#include "../texture_manager/mod.h"

const char *ROBOT_SPRITE = "src/robot/assets/Robot.png";

void Robot_Draw(Robot robot) {
  TM_Draw(TM_LoadTexture(ROBOT_SPRITE), robot.src, robot.dst);
}
