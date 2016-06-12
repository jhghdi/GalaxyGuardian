#pragma once
#ifndef __STAGE3_H__
#define __STAGE3_H__

#include "Common\GlobalDefinition.h"
#include "Objects\Enemies\Boss.h"
#include "Stage.h"
#include "Stage4.h"

class Stage3 : public Stage
{
public:
	Stage3();
	~Stage3();
	void Update(std::vector<Enemy*> *enemies);

private:
	Enemy* named1;

	Enemy* named2;

	bool isLargeEnemy1Died;
	bool isLargeEnemy2Died;
};


#endif // ! __STAGE3_H__

