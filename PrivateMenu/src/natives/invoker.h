#pragma once

typedef int(*pGetStatInt)(Hash statHash, int* outValue, int p2);
extern pGetStatInt OriginalGetStatInt;

#pragma warning(disable : 4244)

class nativeCallContext
{
protected:
	void* m_return;
	uint32_t m_arg_count;
	void* m_args;
	uint32_t m_dataCount;
	Vector3* m_script_vectors[4];
	Vector4 m_vector_results[4];

public:

	void reset() {
		m_arg_count = 0;
		m_dataCount = 0;
	}

	template<typename type>
	inline type getArgument(int index)
	{
		intptr_t* args = (intptr_t*)m_args;
		return *(type*)&args[index];
	}

	template<typename type>
	inline void setArgument(int index, type value)
	{
		intptr_t* values = (intptr_t*)m_args;
		*(type*)&values[index] = value;
	}

	template<typename type>
	inline void setResult(int index, type value)
	{
		intptr_t* return_values = (intptr_t*)m_return;
		*(type*)&return_values[index] = value;
	}

	inline int getArgumentCount()
	{
		return m_arg_count;
	}

	template<typename return_t>
	inline return_t getResult(int index)
	{
		intptr_t* return_values = (intptr_t*)m_return;
		return *(return_t*)&return_values[index];
	}

	inline void* getResultPtr() {
		return m_return;
	}

	void setVectorResults();
};

class NativeContext : public nativeCallContext
{
private:
	enum
	{
		max_native_params = 32,
		arg_size = sizeof(void*),
	};

	uint8_t m_temp_stack[max_native_params * arg_size];

public:
	inline NativeContext()
	{
		m_args = &m_temp_stack;
		m_return = &m_temp_stack;

		m_arg_count = 0;
		m_dataCount = 0;

		memset(m_temp_stack, 0, sizeof(m_temp_stack));
	}

	template <typename type>
	inline void push(type value)
	{
		if (sizeof(type) > arg_size)
			throw "Argument has an invalid size";

		else if (sizeof(type) < arg_size)
			*reinterpret_cast<uintptr_t*>(m_temp_stack + arg_size * m_arg_count) = 0;

		*reinterpret_cast<type*>(m_temp_stack + arg_size * m_arg_count) = value;
		m_arg_count++;
	}

	inline void reverse()
	{
		uintptr_t temp_values[max_native_params];
		uintptr_t* args = (uintptr_t*)m_args;

		for (uint32_t i = 0; i < m_arg_count; i++)
		{
			int target = m_arg_count - i - 1;
			temp_values[target] = args[i];
		}

		memcpy(m_temp_stack, temp_values, sizeof(m_temp_stack));
	}

	template <typename type>
	inline type getResult()
	{
		return *reinterpret_cast<type*>(m_temp_stack);
	}
};

struct pass
{
	template<typename ...type> pass(type...) {}
};

class Invoker
{
public:
	template<typename return_t, typename... args_t>
	static inline return_t invoke(uint64_t hash, args_t... args)
	{
		NativeContext cxt;

		pass{ ([&]()
		{
			cxt.push(args);
		}(), 1)... };

		call(hash, &cxt);

		cxt.setVectorResults();

		return cxt.getResult<return_t>();
	}

	static void call(uint64_t hash, NativeContext* cxt);
	static vector<uint64_t> m_failedInvokes;
};

typedef void(*NativeHandler)(nativeCallContext* context);

// fuck this monstrosity
struct NativeRegistration
{
	uint64_t nextRegistration1;
	uint64_t nextRegistration2;
	NativeHandler handlers[7];
	uint32_t numEntries1;
	uint32_t numEntries2;
	uint64_t hashes;

	inline NativeRegistration* getNextRegistration()
	{
		uintptr_t result;
		auto v5 = reinterpret_cast<uintptr_t>(&nextRegistration1);
		auto v12 = 2i64;
		auto v13 = v5 ^ nextRegistration2;
		auto v14 = (char *)&result - v5;
		do
		{
			*(DWORD*)&v14[v5] = v13 ^ *(DWORD*)v5;
			v5 += 4i64;
			--v12;
		} while (v12);

		return reinterpret_cast<NativeRegistration*>(result);
	}

	inline uint32_t getNumEntries()
	{
		return ((uintptr_t)&numEntries1) ^ numEntries1 ^ numEntries2;
	}

	inline uint64_t getHash(uint32_t index)
	{

		auto naddr = 16 * index + reinterpret_cast<uintptr_t>(&nextRegistration1) + 0x54;
		auto v8 = 2i64;
		uint64_t result;
		auto v11 = (char *)&result - naddr;
		auto v10 = naddr ^ *(DWORD*)(naddr + 8);
		do
		{
			*(DWORD *)&v11[naddr] = v10 ^ *(DWORD*)(naddr);
			naddr += 4i64;
			--v8;
		} while (v8);

		return result;
	}
};