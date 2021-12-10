namespace t6zm
{
	class vec2_t
	{
	public:
		vec2_t() = default;
		vec2_t(float x, float y) :
			x(x), y(y)
		{}

		float x{};
		float y{};
	};

	class vec3_t
	{
	public:
		vec3_t() = default;
		vec3_t(float x, float y, float z) :
			x(x), y(y), z(z)
		{}

		float x{};
		float y{};
		float z{};

		vec3_t operator+(const vec3_t& other)
		{
			vec3_t vec;
			vec.x = this->x + other.x;
			vec.y = this->y + other.y;
			vec.z = this->z + other.z;
			return vec;
		}

		vec3_t& operator+=(const vec3_t& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		vec3_t operator-(const vec3_t& other)
		{
			vec3_t vec;
			vec.x = this->x - other.x;
			vec.y = this->y - other.y;
			vec.z = this->z - other.z;
			return vec;
		}

		vec3_t operator*(const vec3_t& other)
		{
			vec3_t vec;
			vec.x = this->x * other.x;
			vec.y = this->y * other.y;
			vec.z = this->z * other.z;
			return vec;
		}

		vec3_t operator*(const float& other)
		{
			vec3_t vec;
			vec.x = this->x * other;
			vec.y = this->y * other;
			vec.z = this->z * other;
			return vec;
		}
	};
}