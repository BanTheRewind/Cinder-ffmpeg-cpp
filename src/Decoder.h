#pragma once

#include "ffmpegcpp.h"
#include <filesystem>
#include <memory>

namespace ffmpegcpp {
	using DecoderRef = std::shared_ptr<class Decoder>;

	class Decoder
	{
	public:
		static DecoderRef create();
		~Decoder();
	private:
		Decoder();

		InputSource*	mInputSourceAudio { nullptr };
		InputSource*	mInputSourceVideo { nullptr };
	};
}
