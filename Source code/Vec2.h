#pragma once

template <typename T>
class Vec2 {
public:
	Vec2() {  };
	constexpr Vec2(T x, T y) : x(x), y(y) {
	}
	constexpr T getX() const { return x; }
	constexpr T getY() const { return y; }
	constexpr void setX(T x) { this->x = x; }
	constexpr void setY(T y) { this->y = y; }
	constexpr Vec2 operator+(const Vec2& rhs) const {
		return Vec2{ x + rhs.x,y + rhs.y };
	}
	constexpr Vec2 operator-(const Vec2& rhs) const {
		return Vec2{ x - rhs.x,y - rhs.y };
	}
	constexpr Vec2 operator*(const Vec2& rhs) const {
		return Vec2{ x * rhs.x,y * rhs.y };
	}
	constexpr Vec2& operator+=(const Vec2& rhs) {
		*this = *this + rhs;
		return *this;
	}
	constexpr Vec2& operator-=(const Vec2& rhs) {
		*this = *this - rhs;
		return *this;
	}
	constexpr Vec2& operator*=(const Vec2& rhs) {
		*this = *this * rhs;
		return *this;
	}
	constexpr bool operator==(const Vec2& rhs) const {
		return (x == rhs.x && y == rhs.y);
	}
	constexpr bool operator!=(const Vec2& rhs) const {
		return !(x == rhs.x && y == rhs.y);
	}
	constexpr Vec2 operator+(const T& rhs) const {
		return Vec2{ x + rhs,y + rhs };
	}
	constexpr Vec2 operator-(const T& rhs) const {
		return Vec2{ x - rhs,y - rhs };
	}
	constexpr Vec2 operator*(const T& rhs) const {
		return Vec2{ x * rhs,y * rhs };
	}

private:
	T x;
	T y;
};
