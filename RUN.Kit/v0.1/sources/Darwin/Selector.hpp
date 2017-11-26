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


template <class function> struct Selector;
template <class function, class parameter_list> struct SelectorFunctor;


template <class F, class... P> struct SelectorFunctor<F, Zeta::TypeList<P...> > {
	typedef Selector<F>* This;
	typedef typename Zeta::Type<F>::return_type Returned;

	typedef typename Zeta::Type<typename Zeta::TypeListToFunction<typename Zeta::TypeListPrepend<
		Zeta::TypeList<P...>, id, SEL
	>::type, F>::type>::add_pointer Caller;

	typedef typename Zeta::Type<typename Zeta::TypeListToFunction<typename Zeta::TypeListPrepend<
		Zeta::TypeList<P...>, struct objc_super*, SEL
	>::type, F>::type>::add_pointer SuperCaller;

#	if Z_CPU_ARCHITECTURE == Z_CPU_ARCHITECTURE_AARCH64
		static Z_CONSTANT auto caller	    = objc_msgSend;
		static Z_CONSTANT auto super_caller = objc_msgSendSuper;
#	else
		static Z_CONSTANT auto caller = Zeta::Type<Returned>::is_compound
			? objc_msgSend_stret
			: (Zeta::Type<Returned>::is_real ? objc_msgSend_fpret : objc_msgSend);

		static Z_CONSTANT auto super_caller = Zeta::Type<Returned>::is_compound
			? objc_msgSendSuper_stret
			: objc_msgSendSuper;
#	endif


	template <class R = Returned>
	Z_INLINE_MEMBER typename Zeta::EnableIf<Zeta::Type<R>::is_void, void>::type
	operator ()(id object, typename Zeta::Type<P>::to_forwardable... parameters) const
		{((Caller)objc_msgSend)(object, ((This)this)->selector, parameters...);}


	template <class R = Returned>
	Z_INLINE_MEMBER typename Zeta::EnableIf<!Zeta::Type<R>::is_void, R>::type
	operator ()(id object, typename Zeta::Type<P>::to_forwardable... parameters) const
		{return ((Caller)caller)(object, ((This)this)->selector, parameters...);}


	template <class R = Returned>
	Z_INLINE_MEMBER typename Zeta::EnableIf<Zeta::Type<R>::is_void, void>::type
	super(id object, typename Zeta::Type<P>::to_forwardable... parameters) const
		{
		struct objc_super object_super {object, [[object class] superclass]};
		((SuperCaller)super_caller)(&object_super, ((This)this)->selector, parameters...);
		}


	template <class R = Returned>
	Z_INLINE_MEMBER typename Zeta::EnableIf<!Zeta::Type<R>::is_void, R>::type
	super(id object, typename Zeta::Type<P>::to_forwardable... parameters) const
		{
		struct objc_super object_super {object, [[object class] superclass]};
		return ((SuperCaller)super_caller)(&object_super, ((This)this)->selector, parameters...);
		}


	template <class R = Returned>
	Z_INLINE_MEMBER typename Zeta::EnableIf<Zeta::Type<R>::is_void, void>::type
	super(const struct objc_super &object_super, typename Zeta::Type<P>::to_forwardable... parameters) const
		{((SuperCaller)super_caller)((struct objc_super *)&object_super, ((This)this)->selector, parameters...);}


	template <class R = Returned>
	Z_INLINE_MEMBER typename Zeta::EnableIf<!Zeta::Type<R>::is_void, R>::type
	super(const struct objc_super &object_super, typename Zeta::Type<P>::to_forwardable... parameters) const
		{return ((SuperCaller)super_caller)((struct objc_super *)&object_super, ((This)this)->selector, parameters...);}
};


template <class F> struct Selector : SelectorFunctor<F, typename Zeta::Type<F>::parameters> {
	SEL selector;

	Z_INLINE_MEMBER Selector() {}

	Z_CT_MEMBER(CPP11) Selector(SEL selector) : selector(selector) {}

	Z_CT_MEMBER(CPP11) operator SEL() const {return selector;}
};


#endif // __Selector_HPP__
