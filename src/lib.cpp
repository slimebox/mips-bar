


template<typename access_type>
access_type read(const u8* buf, b32 be)
{
	access_type v = handle_read<access_type>(buf);

	if(be)
	{
		v = bswap<access_type>(v);
	}

	return v;
}



u64 abs(u64 v)
{
	return s64(v) < 0? -v : v;
}