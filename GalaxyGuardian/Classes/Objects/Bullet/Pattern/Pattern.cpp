#include "Pattern.h"


std::vector<Bullet*> Pattern::Create(const int & patternIndex )
{
	std::vector<Bullet*> bullets;
	Bullet* bullet;
	float angle = 10.0f;
	int rand, bulletSpeed;
	switch (patternIndex)
	{

	#pragma region player bullet pattern
	case  PLAYER_WEAPON::DEFAULT:
		bullet = Bullet::create(PLAYER_DEFAULT_IMG, PLAYER_WEAPON_DMG::DEFAULT_DMG, BULLET_PATTERN::STRAIGHT, DEFAULT_SPEED_PLAYER);
		bullets.push_back(bullet);
		break;
	case PLAYER_WEAPON::WIDE: 
		bullets.push_back(Bullet::create(PLAYER_WIDE_LEFT_IMG, PLAYER_WEAPON_DMG::WIDE_DMG, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_PLAYER,  120.0f));
		bullet = Bullet::create(PLAYER_WIDE_CENTER_IMG, PLAYER_WEAPON_DMG::WIDE_DMG, BULLET_PATTERN::STRAIGHT, DEFAULT_SPEED_PLAYER);
		bullets.push_back(bullet);
		bullets.push_back(Bullet::create(PLAYER_WIDE_RIGHT_IMG, PLAYER_WEAPON_DMG::WIDE_DMG, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_PLAYER, 60.0f));
		break;
	case PLAYER_WEAPON::AUTO:
		bullet = Bullet::create(PLAYER_AUTO_IMG, PLAYER_WEAPON_DMG::AUTO_DMG, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_PLAYER, angleBetweenPlayerAndEnemy);
		bullets.push_back(bullet);
		break;
	#pragma endregion

	#pragma region enemy bullet pattern
	case  ENEMY_WEAPON::BASIC:
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::STRAIGHT, DEFAULT_SPEED_ENEMY, angleBetweenPlayerAndEnemy);
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::THREE_WAYS:
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 120.0f));
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::STRAIGHT, DEFAULT_SPEED_ENEMY);
		bullets.push_back(bullet);
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 60.0f));
		break;

	case ENEMY_WEAPON::TO_PLAYER:
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, angleBetweenPlayerAndEnemy);
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::SIN:
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::CURVE_SIN, DEFAULT_SPEED_ENEMY);
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::FOUR_WAYS:
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 140.0f));
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 105.0f);
		bullets.push_back(bullet);
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 75.0f));
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 30.0f));
		break;

	case ENEMY_WEAPON::SIN_COS:
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::CURVE_COS, BulletSpeed(10, -5), 90.0f);
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::CURVE_SIN, BulletSpeed(10, -5), 0.0f);
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::SPREAD_ON_POINT:
		for (int i = 0; i < 18; ++i)
		{ 
			bullet = Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::SPREAD, DEFAULT_SPEED_ENEMY, 20.0f *(1+i) );
			bullets.push_back(bullet);
		}
		break;

	case ENEMY_WEAPON::HOLE:
		rand = random(1, 9);
		for (int i = 0; i < 36; ++i)
		{
			if(i *5 != rand * 10 )

			bullet = Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(-3, -3), i * 5 );
			bullets.push_back(bullet);
		}
		break;

	case ENEMY_WEAPON::ARCS:
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::ARC, BulletSpeed(10, 30));
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::ARC, BulletSpeed(-10, 30));
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::ARC_REVERSE, BulletSpeed(10, -30));
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::ARC_REVERSE, BulletSpeed(-10, -30));
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::TWO_ARC:
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::ARC, BulletSpeed(7, 25));
		bullet->image->setPosition(Vec2(0, 10));
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::ARC, BulletSpeed(-7, 25));
		bullet->image->setPosition(Vec2(WIN_WIDTH, 10));
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::VOLTEX_4WAYS:
		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::VOLTEX, DEFAULT_SPEED_ENEMY, 30.0f);
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VOLTEX, DEFAULT_SPEED_ENEMY, 40.0f);
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::VOLTEX, DEFAULT_SPEED_ENEMY, 50.0f);
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VOLTEX, DEFAULT_SPEED_ENEMY, 60.0f);
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::VOLTEX_AROUND_1:
		for (int i = 0; i < 22; ++i)
		{
			auto image = i % 2 == 0 ? ENEMY_BULLET_IMG1 : ENEMY_BULLET_IMG2;
			bullet = Bullet::create(image, DAMAGE_TO_PLAYER, BULLET_PATTERN::VOLTEX, DEFAULT_SPEED_ENEMY,  i * 10);
			bullets.push_back(bullet);
		}
		break;

	case ENEMY_WEAPON::VOLTEX_AROUND_2:
		for (int i = 0; i < 22; ++i)
		{
			auto image = i % 2 == 0 ? ENEMY_BULLET_IMG1 : ENEMY_BULLET_IMG2;
			bullet = Bullet::create(image, DAMAGE_TO_PLAYER, BULLET_PATTERN::VOLTEX_REVERSE, DEFAULT_SPEED_ENEMY, i * 10);
			bullets.push_back(bullet);
		}
		break;

	case ENEMY_WEAPON::TWO_CIRCIES:
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::CIRCLE, DEFAULT_SPEED_ENEMY, 0.0f);
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::CIRCLE, DEFAULT_SPEED_ENEMY, 0.0f);
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::TO_PLAYER_RAND:
		bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(-8, -8), angleBetweenPlayerAndEnemy +random(-10,10));
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::TO_BIGGER:
		bullet = Bullet::create(ENEMY_BULLET_IMG4, DAMAGE_TO_PLAYER, BULLET_PATTERN::BIGGER, BulletSpeed(1, 1));
		bullet->image->setPosition(Vec2(random(1, 10) * (WIN_WIDTH / 11), WIN_HEIGHT * 0.9));
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::THREE_WAYS_BIG:
		bullet = Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(10, -7), 60.0f);
		bullets.push_back(bullet);
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(10, -7)));
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(10, -7), 120.0f));
		break;

	case ENEMY_WEAPON::FOUR_WAYS_BIG:
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(10, -7), 140.0f));
		bullet = Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(10, -7), 105.0f);
		bullets.push_back(bullet);
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(10, -7), 75.0f));
		bullets.push_back(Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(10, -7), 30.0f));
		break;

	case ENEMY_WEAPON::WIDE_RAND_EXCEPT:
		rand = random(3, 5);
		for (int i = 0; i < 17; ++i)
		{
			angleBetweenPlayerAndEnemy = (i + 1) * 10;
			if (rand * 20 < angleBetweenPlayerAndEnemy && (rand+1) * 20 > angleBetweenPlayerAndEnemy)
				continue;

			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(5,-5), angleBetweenPlayerAndEnemy);
			bullets.push_back(bullet);
		}
		break;

	case ENEMY_WEAPON::VECTOR_RIGHT_ANGLES:
		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, DEFAULT_SPEED_ENEMY, 60.0f);
		bullet->image->setPosition(Vec2(0, WIN_HEIGHT * 0.9));
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, DEFAULT_SPEED_ENEMY, 60.0f);
		bullet->image->setPosition(Vec2(0, WIN_HEIGHT * 0.7 +random(0,10) ));
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, DEFAULT_SPEED_ENEMY, 60.0f);
		bullet->image->setPosition(Vec2(0, WIN_HEIGHT * 0.5 + random(0, 10) ));
		bullets.push_back(bullet);

		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, DEFAULT_SPEED_ENEMY, 60.0f);
		bullet->image->setPosition(Vec2(WIN_WIDTH, WIN_HEIGHT * 0.9));
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, DEFAULT_SPEED_ENEMY, 60.0f);
		bullet->image->setPosition(Vec2(WIN_WIDTH, WIN_HEIGHT * 0.7 - random(0, 10) ));
		bullets.push_back(bullet);
		bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, DEFAULT_SPEED_ENEMY, 60.0f);
		bullet->image->setPosition(Vec2(0, WIN_HEIGHT * 0.5 - random(0, 10) ));
		bullets.push_back(bullet);
		break;

	case ENEMY_WEAPON::STAR_1:
		for (int i = 0; i < 5; ++i)
			for (int cnt = 0; cnt < 5; ++cnt)
			{
				rand = 8 - abs(4 - (2*cnt));
				angle = (14.4*(cnt + 1)) + (i * 72);
				bullet = Bullet::create(ENEMY_BULLET_IMG1,DAMAGE_TO_PLAYER,BULLET_PATTERN::VECTOR,BulletSpeed(-rand, -rand),angle);
				bullets.push_back(bullet);
			}
		break;

	case ENEMY_WEAPON::STAR_2:
		for (int i = 0; i < 5; ++i)
			for (int cnt = 0; cnt < 5; ++cnt)
			{
				rand = 8 - abs(4 - (2 * cnt));
				angle = (43.2 + (14.4*cnt)) + (i * 72);
				bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(-rand, -rand), angle);
				bullets.push_back(bullet);
			}
		break;

	case ENEMY_WEAPON::VECTOR_WIDE_1:
			for (int cnt = 0; cnt < 36; ++cnt)
			{
				bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(-8, -8), 10 * cnt);
				bullets.push_back(bullet);
			}
		break;

	case ENEMY_WEAPON::VECTOR_WIDE_2:
		for (int cnt = 0; cnt < 36; ++cnt)
		{
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(-8, -8), 5 + (10* cnt));
			bullets.push_back(bullet);
		}
		break;


	case ENEMY_WEAPON::RANDOM:
			bullet = Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 50.0f);
			bullets.push_back(bullet);
			rand = RANDOM_BULLET_SPEED;
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(rand, rand), random(60, 80));
			bullets.push_back(bullet);
			rand = RANDOM_BULLET_SPEED;
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(rand, rand), random(80, 100));
			bullets.push_back(bullet);
			rand = RANDOM_BULLET_SPEED;
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(rand, rand), random(100, 120));
			bullets.push_back(bullet);
			bullet = Bullet::create(ENEMY_BULLET_IMG5, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 130.0f);
			bullets.push_back(bullet);
		break;


	case ENEMY_WEAPON::FINAL_PATTERN:
		#pragma region final boss pattern
				switch (random(1,4))
				{
				case 1:
					for (int cnt = 0; cnt < 18; ++cnt)
					{
						bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(-4, -4), 20 * cnt);
						bullets.push_back(bullet);
					}
					break;

				case 2:
					for (int i = 0; i < 5; ++i)
						for (int cnt = 0; cnt < 5; ++cnt)
						{
							rand = 6 - abs(2 -  cnt);
							angle = (43.2 + (14.4*cnt)) + (i * 72);
							bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, BulletSpeed(-rand, -rand), angle);
							bullets.push_back(bullet);
						}
					break;

				case 3:
					for (int i = 0; i < 11; ++i)
					{
						auto image = i % 2 == 0 ? ENEMY_BULLET_IMG1 : ENEMY_BULLET_IMG2;
						bullet = Bullet::create(image, DAMAGE_TO_PLAYER, BULLET_PATTERN::VOLTEX_REVERSE, BulletSpeed(-5, -5), i* 20);
						bullets.push_back(bullet);
					}

				case 4:
					bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, BulletSpeed(-3, -3), 30.0f);
					bullet->image->setPosition(Vec2(0, WIN_HEIGHT * 0.9));
					bullets.push_back(bullet);
					bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, BulletSpeed(-3, -3), 60.0f);
					bullet->image->setPosition(Vec2(0, WIN_HEIGHT * 0.7 + random(0, 10)));
					bullets.push_back(bullet);
					bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, BulletSpeed(3, 3), 60.0f);
					bullet->image->setPosition(Vec2(0, WIN_HEIGHT * 0.3 + random(0, 10)));
					bullets.push_back(bullet);
					bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, BulletSpeed(-3, -3), 25.0f);
					bullet->image->setPosition(Vec2(WIN_WIDTH, WIN_HEIGHT * 0.9));
					bullets.push_back(bullet);
					bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, BulletSpeed(-3, -3), 50.0f);
					bullet->image->setPosition(Vec2(WIN_WIDTH, WIN_HEIGHT * 0.7 + random(0, 10)));
					bullets.push_back(bullet);
					bullet = Bullet::create(ENEMY_BULLET_IMG2, DAMAGE_TO_PLAYER, BULLET_PATTERN::RIGHT_ANGLE, BulletSpeed(3, 3), 30.0f);
					bullet->image->setPosition(Vec2(WIN_WIDTH, WIN_HEIGHT * 0.3 + random(0, 10)));
					bullets.push_back(bullet);

				default:
					break;
				}
		#pragma endregion
		break;
	#pragma region fixed Vector
		case ENEMY_WEAPON::VECTOR_5:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 5.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_10:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 10.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_15:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY,15.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_20:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 20.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_25:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 25.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_30:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 30.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_35:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 35.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_40:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 40.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_45:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 45.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_50:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 50.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_55:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 55.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_60:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 60.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_65:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 65.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_70:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 70.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_75:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 75.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_80:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 80.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_85:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 85.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_90:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_95:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 95.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_100:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 100.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_105:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 105.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_110:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 110.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_115:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 115.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_120:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 120.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_125:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 125.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_130:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 130.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_135:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 135.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_140:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 140.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_145:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 145.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_150:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 150.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_155:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 155.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_160:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 160.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_165:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 165.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_170:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 170.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_175:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 175.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_180:
			bullet = Bullet::create(ENEMY_BULLET_IMG1, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 180.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_185:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 185.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_195:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 195.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_205:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 205.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_215:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 215.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_225:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 225.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_235:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 235.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_245:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 245.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_255:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 255.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_265:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 265.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_275:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 275.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_285:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 285.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_295:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 295.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_305:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 305.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_315:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 315.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_325:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 325.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_335:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 335.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_345:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 345.0f);
			bullets.push_back(bullet);
			break;
		case ENEMY_WEAPON::VECTOR_355:
			bullet = Bullet::create(ENEMY_BULLET_IMG3, DAMAGE_TO_PLAYER, BULLET_PATTERN::VECTOR, DEFAULT_SPEED_ENEMY, 355.0f);
			bullets.push_back(bullet);
			break;

	#pragma endregion

	#pragma endregion
	}

	return bullets;
}

void Pattern::Move(Bullet *bullet)
{
	float angle = bullet->GetAngle();
	double x;
	double y;
	int pattern = bullet->GetPattern();

#pragma region bullet pattern
	switch (pattern)
	{
	case  BULLET_PATTERN::STRAIGHT:
		bullet->image->setPositionY(bullet->image->getPositionY() + bullet->speed.x);
		break;

	case BULLET_PATTERN::VECTOR:
		x = COS(angle, bullet->speed.x);
		y = SIN(angle, bullet->speed.y);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + x, bullet->image->getPositionY() + y));
		break;

	case BULLET_PATTERN::CURVE_SIN:
		y = bullet->speed.y;
		x = SIN(angle, bullet->speed.x);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + x, bullet->image->getPositionY() + y));
		bullet->angle += 4;
		break;

	case BULLET_PATTERN::CURVE_COS:
		y = bullet->speed.y;
		x = COS(angle, bullet->speed.x);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + x, bullet->image->getPositionY() + y));
		bullet->angle += 4;
		break;

	case BULLET_PATTERN::ARC:
		y = --(bullet->speed.y);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + bullet->speed.x, bullet->image->getPositionY() + y));
		break;

	case BULLET_PATTERN::ARC_REVERSE:
		y = ++(bullet->speed.y);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + bullet->speed.x, bullet->image->getPositionY() + y));
		break;

	case BULLET_PATTERN::CIRCLE:
		x = 5 * cos(angle);
		y = 5 * sin(angle);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + x , bullet->image->getPositionY() + y));
		bullet->angle += 0.1f;
		bullet->image->setPositionY(bullet->image->getPositionY() - 7);
		break;

	case BULLET_PATTERN::VOLTEX:
		x = bullet->speed.x * cos(angle);
		y = bullet->speed.y * sin(angle);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + x, bullet->image->getPositionY() - y));	
		bullet->speed.x += 0.5f;
		bullet->speed.y += 0.5f;
		bullet->angle += 0.05f;
		break;

	case BULLET_PATTERN::VOLTEX_REVERSE:
		x = bullet->speed.x * sin(angle);
		y = bullet->speed.y * cos(angle);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + x, bullet->image->getPositionY() - y));
		bullet->speed.x += 0.5f;
		bullet->speed.y += 0.5f;
		bullet->angle += 0.05f;
		break;

	case BULLET_PATTERN::BIGGER:
		bullet->image->setPosition(Vec2(bullet->image->getPositionX(), bullet->image->getPositionY() - bullet->speed.y));
		bullet->speed.y += 0.5f;
		if(bullet->speed.y < 5.0f*SCALE_FACTOR )
			bullet->image->setScale(bullet->speed.y);
		break;

	case BULLET_PATTERN::RIGHT_ANGLE:
		if (bullet->image->getPositionX() < 0 || bullet->image->getPositionX() > WIN_WIDTH)
			bullet->speed.x = -(bullet->speed.x);

		x = COS(angle, bullet->speed.x);
		y = SIN( abs(angle - 90), bullet->speed.y);
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + x, bullet->image->getPositionY() + y));
		break;

	case BULLET_PATTERN::SPREAD:
		
		if (bullet->time > 60)
		{
			x = COS(angle, bullet->speed.x);
			y = SIN(angle, bullet->speed.y);
		}
		else if (bullet->time < SPREAD_TIME)
		{
			x = 0;
			y = bullet->speed.y;
			++(bullet->time);
		}
		else if (bullet->time == SPREAD_TIME)
		{
			bullet->image->setSpriteFrame(ENEMY_BULLET_IMG1);
			x = COS(angle, bullet->speed.x);
			y = SIN(angle, bullet->speed.y);
		}
		bullet->image->setPosition(Vec2(bullet->image->getPositionX() + x, bullet->image->getPositionY() + y));
		break;
	}
#pragma endregion

}
