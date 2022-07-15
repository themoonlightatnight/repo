#pragma once
#include <string>
namespace Bengine
{
	class StageManager
	{
	public:
		static void setCurrentStageName(const std::string stageName) { m_currentStageName = stageName; }
		static inline const std::string getCurrentStageName() { return m_currentStageName; }
		static void reset() { m_currentStageName.clear(); }
	private:
		static std::string m_currentStageName;
	};
}


