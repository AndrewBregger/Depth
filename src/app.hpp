#ifndef APP_HPP_
#define APP_HPP_

namespace app {
	class App {
		public:

			App();

			void event_loop();

		private:
			bool running;
	};
}

#endif
