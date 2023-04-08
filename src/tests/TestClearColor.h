#ifndef __TEST_CLEARCOLOR_H
#define __TEST_CLEARCOLOR_H

#include "test.h"

namespace test {
	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();
		
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}

#endif