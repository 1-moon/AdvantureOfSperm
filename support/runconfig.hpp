#ifndef RUNCONFIG_HPP_86D42BBB-4F53-4ED2-8986-14FA2CABDD02
#define RUNCONFIG_HPP_86D42BBB-4F53-4ED2-8986-14FA2CABDD02

namespace config {
	constexpr unsigned kInitWindowWidth = 1280;
	constexpr unsigned kInitWindowHeight = 720;
}

struct RuntimeConfig {
	unsigned initWindowWidth = config::kInitWindowWidth;
	unsigned initWindowHeight = config::kInitWindowHeight;
};



#endif // RUNCONFIG_HPP_86D42BBB-4F53-4ED2-8986-14FA2CABDD02
