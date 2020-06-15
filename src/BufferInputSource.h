#pragma once

#include "ffmpegcpp.h"
#include <memory>

namespace ffmpegcpp {

template<typename T, typename U> 
class BufferInputSource : public InputSource
{
public:
	static std::shared_ptr<BufferInputSource<T, U>>	create( FrameSink* frameSink );
	~BufferInputSource<T, U>();

	virtual void PreparePipeline();
	virtual bool IsDone();
	virtual void Step();

	U*			getBuffer() const { return mBuffer };
	int32_t		getFrameNumber() const { return mFrameNumber };
	T*			getOutput() const { return mOutput }
private:
	BufferInputSource<T, U>( FrameSink* frameSink );

	U*			mBuffer			{ nullptr };
	int32_t		mFrameNumber	{ 0 };
	T*			mOutput			{ nullptr };
};

using AudioBufferInputSourceRef = std::shared_ptr<BufferInputSource<RawAudioDataSource, uint16_t>>;
using VideoBufferInputSourceRef = std::shared_ptr<BufferInputSource<RawVideoDataSource, uint8_t>>;

}

 