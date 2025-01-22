#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);
	~Vector2();

	float x, y;

	Vector2 operator *(Vector2 a);
	Vector2 operator /(Vector2 a);
	Vector2 operator +(Vector2 a);
	Vector2 operator -(Vector2 a);
	Vector2 operator*(float f) const;
	friend Vector2 operator*(float f, const Vector2& v);
	bool operator ==(Vector2 a);
	bool operator !=(Vector2 a);

	bool IsZero() const;

	static Vector2 Zero();

	static float Distance(Vector2 a, Vector2 b);
};

class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();

	float x, y, z;

	Vector3 operator *(Vector3 a);
	Vector3 operator *(float f);
	Vector3 operator /(Vector3 a);
	Vector3 operator /(float f);
	Vector3 operator +(Vector3 a);
	Vector3 operator -(Vector3 a);
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator*(float f) const;
	friend Vector3 operator*(float f, const Vector3& v);
	bool operator ==(Vector3 a);
	bool operator !=(Vector3 a);

	bool IsZero() const;
	Vector3 Normalize() const;
	float& operator[](int index);
	const float& operator[](int index) const;
	static float Dot(Vector3 left, Vector3 right);
	float Dot(const Vector3& v) const;
	static float Distance(Vector3 a, Vector3 b);
	Vector3 Cross(const Vector3& other) const;
	static int FormattedDistance(Vector3 a, Vector3 b);
	static Vector3 Zero();
	static Vector3 Lerp(Vector3 a, Vector3 b, float t);

	float Length() const;
	float LengthSqr() const;

	Vector3 Clamp() const;
};

struct ViewMatrix
{
public:
	float matrix[4][4];

	void DecomposeBasis(Vector3& forward, Vector3& right, Vector3& up) const {
		right = { matrix[0][0], matrix[1][0], matrix[2][0] };

		up = { matrix[0][1], matrix[1][1], matrix[2][1] };

		forward = { matrix[0][2], matrix[1][2], matrix[2][2] };
	}

	Vector3 Transform(const Vector3 vector) const;
};
