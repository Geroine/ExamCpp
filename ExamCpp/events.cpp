//#include "events.h"
//#include <list>
//#include <windows.h>
//
//bool KB_Pressed(int Key)
//{
//	short keyState = GetAsyncKeyState(Key);
//	return ((keyState & 0x8000) > 0);
//}
//
//bool KB_Hit(int Key)
//{
//	static list<int> KBHitBase;
//	if (KB_Pressed(Key))
//	{
//		auto iter = KBHitBase.begin();
//		while (iter != KBHitBase.end())
//		{
//			if (*iter == Key)
//				return false;
//			iter++;
//		}
//		KBHitBase.push_back(Key);
//		return true;
//	}
//	if (KBHitBase.size() && !KB_Pressed(Key))
//	{
//		auto iter = KBHitBase.begin();
//		while (iter != KBHitBase.end())
//		{
//			if (*iter == Key)
//			{
//				KBHitBase.erase(iter);
//				break;
//			}
//			iter++;
//		}
//	}
//
//	return false;
//}