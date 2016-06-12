#pragma once
#ifndef __STAGE1_H__
#define __STAGE1_H__

#include "Common\GlobalDefinition.h"
#include "Objects\Enemies\Boss.h"
#include "Stage.h"
#include "Stage2.h"

class Stage1 : public Stage
{
public :
	Stage1();
	~Stage1();
	void Update(std::vector<Enemy*> *enemies);

private:
	Enemy* named1;

	Enemy* named2;

	bool isLargeEnemy1Died;
	bool isLargeEnemy2Died;
};


#endif // ! __STAGE1_H__

