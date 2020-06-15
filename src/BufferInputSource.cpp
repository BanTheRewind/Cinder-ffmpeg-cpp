#include "BufferInputSource.h"

namespace ffmpegcpp {

using namespace std;

template<typename T, typename U> 
static shared_ptr<BufferInputSource<T, U>> BufferInputSource<T, U>::create( FrameSink* frameSink )
{
	return shared_ptr{ new BufferInputSource<T, U>{ frameSink } };
}

template<typename T, typename U> 
BufferInputSource<T, U>::BufferInputSource<T, U>( FrameSink* frameSink )
{
}

template<typename T, typename U> 
BufferInputSource<T, U>::~BufferInputSource<T, U>()
{
}

template<typename T, typename U> 
void BufferInputSource<T, U>::PreparePipeline()
{
}

template<typename T, typename U> 
bool BufferInputSource<T, U>::IsDone()
{
}

template<typename T, typename U> 
void BufferInputSource<T, U>::Step()
{
}

}