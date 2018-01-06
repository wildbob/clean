#pragma once
namespace sdk
{
	class c_basehandle;

	class IHandleEntity
	{
	public:
		virtual ~IHandleEntity() {}
		virtual void SetRefEHandle(const c_basehandle &handle) = 0;
		virtual const c_basehandle& GetRefEHandle() const = 0;
	};
}