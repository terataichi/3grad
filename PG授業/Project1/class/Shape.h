#pragma once
#include "../common/Vector2.h"
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <string>

class Shape;
using SharedShape = std::shared_ptr<Shape>;
using ShapeVec = std::vector<SharedShape>;

enum class ShapeType
{
	Square,
	Triangle,
	Circle,
	Carrot,
};

// 図形クラス
class Shape
{
public:
	Shape();
	Shape(Potision2f& pos, Size& size, Vector2f& speed,int& color);
	Shape(Potision2f& pos, float& radius, Vector2f& speed, int& color);
	Shape(Potision2f& pos, Vector2f& speed, int& color);
	Shape(Vector2f& point1, Vector2f& point2, Vector2f& point3, Vector2f& speed, int& color);
	~Shape();

	/// <summary>
	/// Get関数
	/// </summary>
	const bool GetAlive(void)const;
	const Potision2f& GetPotision(void)const;
	const int& GeyMyNamber(void)const;
	const int& GetColor(void)const;
	const Vector2f& GetSpeed(void)const;
	ShapeType GetType(void)const;
	const float GetRadius(void)const;
	const Size GetSize(void)const;
	const std::vector<Vector2f> GetPoint(void)const;
	const std::vector<Potision2f>GetHitPoint(void)const;
	/// <summary>
	/// Set関数
	/// </summary>
	void SetAlive(bool alive);					// false：死亡</param>
	void SetPotision(Potision2f& pos);
	void SetSpeed(Vector2f vec);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="delta">経過時間</param>
	virtual bool Update(const float& delta, const ShapeVec& shapeVec);
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;
	virtual void Draw(float rate) = 0;
	virtual void Draw(Vector2 offset, float rate = 1) {};

	/// <summary>
	/// 当たり判定用
	/// true で当たった
	/// </summary>
	virtual void HitShape(const SharedShape& shape) = 0;
	bool CheckHitSquare(const SharedShape& shape);																			// 四角形同士
	bool CheckHitCircle(const SharedShape& shape);																			// 円同士
	bool CheckHitTriangle(const SharedShape& shape);																		// 三角形同士
	bool CheckHitSquareCircle(const Potision2f& sPos, const Size& sSize, const Potision2f& cPos, const float& cRadius);		// 四角形と円
	bool CheckHitShapeTriangle(const std::vector<Potision2f>& sPoint, const std::vector<Vector2f>& tpoint);					// 四角形or円と三角形
protected:
	Potision2f pos_;
	Size size_;
	Vector2f speed_;
	float radius_;
	int color_;
	ShapeType shapeType_;
	std::vector<Vector2f>point_;
	bool alive_;												// true:生きてる
	int myNamber_;												// 自分の番号保存用
	std::vector<Potision2f> hitPoint_;							// 矩形用
	/// <summary>
	/// 反射ベクトルを求める
	/// </summary>
	/// <param name="N">正規化された法線ベクトル</param>
	virtual Vector2f Reflection(Vector2f N);
	void NewShape();
	/// <summary>
	/// 画面との当たり判定
	/// </summary>
	/// <returns>スピード</returns>
	virtual Vector2f CheckHitWall(const ShapeVec& vec) = 0;
	/// <summary>
	/// ほかの図形との当たり判定(色)
	/// </summary>
	/// <param name="shape"></param>

	std::vector<ShapeType> typeVec_;
private:
	void Init(void);
	static int objectNumber_;
};

