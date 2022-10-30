#pragma once
#include "CommonHeaders.h"

namespace sn::id {
	//ID TYPE - BIGGEST BEING u64
	using id_type = u32;
	// BEGINNING OF INDEX - BIGGEST BEING 31?
	constexpr u32 generation_bits{ 8 };
	//REMAINDER OF 32 BITS
	constexpr u32 index_bits{ sizeof(id_type) * 8 - generation_bits };
	// SHIFT BIT TO THE RIGHT ISOLATING THE INDEX FROM GENERATION BIT
	constexpr id_type index_mask{ (id_type{1} << index_bits) - 1 };
	// SAME AS ABOVE BUT ISOLATING GENERATION BITS
	constexpr id_type generation_mask{ (id_type{1} << generation_bits) - 1 };
	// SIZE OF ID_TYPE
	constexpr id_type id_mask{ id_type{-1} };

	// GENERATION TYPE
	// CHECK WHICH SIZE OF GENERATION BITS TO USE
	using generation_type = std::conditional_t<generation_bits <= 16, std::conditional_t<generation_bits <= 8, u8, u16>, u32>;
	// MAKE SURE GENERATION TYPE REQUIRES MORE BITS THAN GENERATION BITS
	static_assert(sizeof(generation_type) * 8 >= generation_bits);
	// GENERATION TYPE != SAME SIZE AS INDEX TYPE
	static_assert((sizeof(id_type) - sizeof(generation_type)) > 0);
	// CHECK IF ID IS VALID
	inline bool
		is_valid(id_type id)
	{
		return id != id_mask;
	}
	inline id_type
		index(id_type id)
	{
		return id & index_mask;
	}
	inline id_type
		generation(id_type id)
	{
		return (id >> index_bits) & generation_mask;
	}
	// VERIFY GENERATION IS LESS THAN 255 BITS / SHIFT BITS
	inline id_type
		new_generation(id_type id)
	{
		const id_type generation{ id::generation(id) + 1 };
		assert(generation < 255);
		return index(id) | (generation << index_bits);
	}
	// DIFFERENTIATE BETWEEN IDS RELEASE VS DEBUG
#if _DEBUG
	namespace internal {
		struct id_base
		{
			constexpr explicit id_base(id_type id) : _id{ id } {}
			constexpr operator id_type() const { return _id; }
		private :
			id_type _id;
		};
	}
#define DEFINE_TYPED_ID(name)									\
	struct name final : id::internal::id_base {					\
		constexpr explicit name(id::id_type id)					\
			: id_base{ id } {}									\
		constexpr name() : id_base{ id::id_mask } {}			\
	};
#else
#define DEFINE_TYPED_ID(name) using name = id::id_type;
#endif
}