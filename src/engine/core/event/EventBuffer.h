#ifndef _MICRON_ENGINE_CORE_EVENT_EVENT_BUFFER_H
#define _MICRON_ENGINE_CORE_EVENT_EVENT_BUFFER_H

#include "../types/BasicTypes.h"
#include "../types/ContainerTypes.h"
#include "Event.h"

namespace Micron
{
	using EventRc = Rc<Event>;

	class EventBuffer
	{
	public:
		inline EventBuffer() noexcept :
			size{ 16 }, internalBuffer{ }
		{}

		inline EventBuffer(USize size) noexcept :
			size{ size }, internalBuffer{ }
		{}

		inline ~EventBuffer() noexcept = default;
		inline EventBuffer(EventBuffer const& other) noexcept = default;
		inline EventBuffer(EventBuffer&& other) noexcept = default;
		inline EventBuffer& operator=(EventBuffer const& other) = default;
		inline EventBuffer& operator=(EventBuffer&& other) = default;

		inline EventRc Front() noexcept { return internalBuffer.front(); }
		inline EventRc Back() noexcept { return internalBuffer.back(); }

		inline Bool IsEmpty() const noexcept { return internalBuffer.empty(); }
		inline USize Size() const noexcept { return internalBuffer.size(); }
		inline Void Resize(USize newSize) noexcept { size = newSize; this->TrimInternalBuffer(); }
		inline Void Flush() noexcept { internalBuffer = Deque<EventRc>(); }

		inline Void Push(EventRc const& value) noexcept { internalBuffer.push_front(value); this->TrimInternalBuffer(); }
		inline Void Push(EventRc &&value) noexcept { internalBuffer.push_front(std::forward<EventRc>(value)); this->TrimInternalBuffer(); }
		inline Void Pop() noexcept { internalBuffer.pop_back(); }
		template<typename ...Args> inline decltype(auto) Emplace(Args &&...args) noexcept { return internalBuffer.emplace_front(std::forward<Args>(args)...); this->TrimInternalBuffer(); }
	private:
		Void TrimInternalBuffer() noexcept { while (internalBuffer.size() > size) { internalBuffer.pop_back(); } }
	private:
		USize size;
		Deque<EventRc> internalBuffer;
	};
}

#endif