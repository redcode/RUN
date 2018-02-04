// Selector v1.0
// Copyright (C) 2017 Manuel Sainz de Baranda y Goñi.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// UNALTERED in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE. */

#ifndef __Selector_HPP__
#define __Selector_HPP__

#include <Z/traits/Type.hpp>
#include <Z/traits/filtering.hpp>
#include <objc/message.h>


template <class F> struct Selector;

template <class R, class... P> struct Selector<R(P...)> {
	SEL selector;

	typedef R (* Caller	)(id,		      SEL, P...);
	typedef R (* SuperCaller)(struct objc_super*, SEL, P...);


#	if Z_CPU_ARCHITECTURE == Z_CPU_ARCHITECTURE_AARCH64
		static Z_CONSTANT auto caller	    = objc_msgSend;
		static Z_CONSTANT auto super_caller = objc_msgSendSuper;
#	else
		static Z_CONSTANT auto caller = Zeta::Type<R>::is_compound
			? objc_msgSend_stret
			: (Zeta::Type<R>::is_real ? objc_msgSend_fpret : objc_msgSend);

		static Z_CONSTANT auto super_caller = Zeta::Type<R>::is_compound
			? objc_msgSendSuper_stret
			: objc_msgSendSuper;
#	endif


	template <bool returns_void = Zeta::Type<R>::is_void>
	Z_INLINE_MEMBER typename Zeta::EnableIf<returns_void, void>::type
	operator ()(id object, typename Zeta::Type<P>::to_forwardable... parameters) const
		{((Caller)objc_msgSend)(object, selector, parameters...);}


	template <bool returns_void = Zeta::Type<R>::is_void>
	Z_INLINE_MEMBER typename Zeta::EnableIf<!returns_void, R>::type
	operator ()(id object, typename Zeta::Type<P>::to_forwardable... parameters) const
		{return ((Caller)caller)(object, selector, parameters...);}


	template <bool returns_void = Zeta::Type<R>::is_void>
	Z_INLINE_MEMBER typename Zeta::EnableIf<returns_void, void>::type
	super(id object, typename Zeta::Type<P>::to_forwardable... parameters) const
		{
		struct objc_super object_super {object, [[object class] superclass]};
		((SuperCaller)super_caller)(&object_super, selector, parameters...);
		}


	template <bool returns_void = Zeta::Type<R>::is_void>
	Z_INLINE_MEMBER typename Zeta::EnableIf<!returns_void, R>::type
	super(id object, typename Zeta::Type<P>::to_forwardable... parameters) const
		{
		struct objc_super object_super {object, [[object class] superclass]};
		return ((SuperCaller)super_caller)(&object_super, selector, parameters...);
		}


	template <bool returns_void = Zeta::Type<R>::is_void>
	Z_INLINE_MEMBER typename Zeta::EnableIf<returns_void, void>::type
	super(const struct objc_super &object_super, typename Zeta::Type<P>::to_forwardable... parameters) const
		{((SuperCaller)super_caller)((struct objc_super *)&object_super, selector, parameters...);}


	template <bool returns_void = Zeta::Type<R>::is_void>
	Z_INLINE_MEMBER typename Zeta::EnableIf<!returns_void, R>::type
	super(const struct objc_super &object_super, typename Zeta::Type<P>::to_forwardable... parameters) const
		{return ((SuperCaller)super_caller)((struct objc_super *)&object_super, selector, parameters...);}


	Z_INLINE_MEMBER Selector() {}

	Z_CT_MEMBER(CPP11) Selector(SEL selector) : selector(selector) {}

	Z_CT_MEMBER(CPP11) operator SEL() const {return selector;}
};


#endif // __Selector_HPP__
