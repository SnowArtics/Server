#pragma once

#include "Allocator.h"

template<typename Type, typename... Args>
Type* xnew(Args&&... args) {
	Type* memory = static_cast<Type*>(xalloc(sizeof(Type)));

	//placement new
	new(memory)Type(forward<Args>(args)...);//할당된 메모리에 있는 객체의 생성자를 호출
	return memory;
}

template<typename Type>
void xdelete(Type* obj) {
	obj->~Type();
	xrelease(obj);
}
