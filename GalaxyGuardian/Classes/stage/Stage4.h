#pragma once
#ifndef __STAGE4_H__
#define __STAGE4_H__

#include "Common\GlobalDefinition.h"
#include "Objects\Enemies\Boss.h"
#include "Stage.h"

class Stage4 : public Stage
{
public:
	Stage4();
	~Stage4();
	void Update(std::vector<Enemy*> *enemies);

private:
	Enemy* named1;

	Enemy* named2;

	bool isLargeEnemy1Died;
	bool isLargeEnemy2Died;
};


#endif // ! __STAGE4_H__

