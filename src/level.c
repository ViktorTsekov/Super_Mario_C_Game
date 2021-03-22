#include "common.h"

void loadNextLevel(void) {
  level.currentLevel++;
  stage.pizzaTotal = 0;
  stage.pizzaFound = 0;
  initStage();
}
