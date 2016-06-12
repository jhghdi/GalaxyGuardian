#pragma once
#ifndef __STAGE2_H__
#define __STAGE2_H__

#include "Common\GlobalDefinition.h"
#include "Objects\Enemies\Boss.h"
#include "Stage.h"
#include "Stage3.h"

class Stage2 : public Stage
{
public:
	Stage2();
	~Stage2();
	void Update(std::vector<Enemy*> *enemies);

private:
	Enemy* named1;

	Enemy* named2;

	bool isLargeEnemy1Died;
	bool isLargeEnemy2Died;
};


#endif // ! __STAGE2_H__

