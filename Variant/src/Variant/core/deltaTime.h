#pragma once

namespace Variant {
	class deltaTime
	{
	private:
		float m_time;
	public:
		deltaTime(float f)
			:m_time(f){}
		float getSeconds() { return m_time; }
		float getMilliSeconds() { return m_time * 1000; }

		operator float() { return m_time; }

	};
}