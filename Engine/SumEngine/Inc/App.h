#pragma once

namespace SumEngine
{
	class App final
	{
	public:
		void Run();
		void Quit();

	private:
		bool mRunning = false;
	};
}