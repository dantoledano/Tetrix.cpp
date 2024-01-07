// Tetromino.h
#pragma once

class Tetromino
{
public:

private:

};

class Straight : public Tetromino
{
private:
	static constexpr bool shape[] = { 0,0,0,0,
									  1,1,1,1,
									  0,0,0,0,
									  0,0,0,0 };
	static constexpr int dimension = 4;
};

class Square : public Tetromino
{
private:
	static constexpr bool shape[] = { 1,1,
									  1,1 };
	static constexpr int dimension = 2;
};

class Tee : public Tetromino
{
private:
	static constexpr bool shape[] = { 0,1,0,
									  1,1,1,
									  0,0,0 };
	static constexpr int dimension = 3;
};

class Jay : public Tetromino
{
private:
	static constexpr bool shape[] = { 1,0,0,
									  1,1,1,
									  0,0,0 };
	static constexpr int dimension = 3;
};

class El : public Tetromino
{
private:
	static constexpr bool shape[] = { 0,0,1,
									  1,1,1,
									  0,0,0 };
	static constexpr int dimension = 3;
};

class Es : public Tetromino
{
private:
	static constexpr bool shape[] = { 0,1,1,
									  1,1,0,
									  0,0,0 };
	static constexpr int dimension = 3;
};

class Zed : public Tetromino
{
private:
	static constexpr bool shape[] = { 1,1,0,
									  0,1,1,
									  0,0,0 };
	static constexpr int dimension = 3;
};
