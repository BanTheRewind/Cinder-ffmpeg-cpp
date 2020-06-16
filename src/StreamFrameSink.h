#pragma once

#include "ffmpegcpp.h"
#include <atomic>
#include <memory>

namespace ffmpegcpp {

class Decoder;
using StreamFrameSinkRef = std::shared_ptr<class StreamFrameSink>;

class StreamFrameSink : public FrameSink, public FrameWriter
{
public:
	static StreamFrameSinkRef	create( AVMediaType mediaType );
	~StreamFrameSink();

	bool				checkNewFrame();

	void				Close( int32_t streamIndex );
	FrameSinkStream*	CreateStream();
	AVMediaType			GetMediaType() { return mMediaType; }
	bool				IsPrimed() { return true; }
	void				WriteFrame( int32_t streamIndex, AVFrame* frame, StreamData* streamData );
private:
	StreamFrameSink( AVMediaType mediaType );

	std::atomic_bool	mNewFrame	{ false };
	FrameSinkStream*	mStream		{ nullptr };
	AVMediaType			mMediaType;
protected:
	struct Frame
	{
	protected:
		AVFrame*		frame		{ nullptr };
		StreamData*		streamData	{ nullptr };
		int32_t			streamIndex	{ 0 };

		friend class	Decoder;
		friend class	StreamFrameSink;
	};

	Frame				getFrame() const { return mFrame; }
 	Frame				mFrame;

	friend class		Decoder;
};

} 