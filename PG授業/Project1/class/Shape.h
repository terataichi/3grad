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

// �}�`�N���X
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
	/// Get�֐�
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
	/// Set�֐�
	/// </summary>
	void SetAlive(bool alive);					// false�F���S</param>
	void SetPotision(Potision2f& pos);
	void SetSpeed(Vector2f vec);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="delta">�o�ߎ���</param>
	virtual bool Update(const float& delta, const ShapeVec& shapeVec);
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
	virtual void Draw(float rate) = 0;
	virtual void Draw(Vector2 offset, float rate = 1) {};

	/// <summary>
	/// �����蔻��p
	/// true �œ�������
	/// </summary>
	virtual void HitShape(const SharedShape& shape) = 0;
	bool CheckHitSquare(const SharedShape& shape);																			// �l�p�`���m
	bool CheckHitCircle(const SharedShape& shape);																			// �~���m
	bool CheckHitTriangle(const SharedShape& shape);																		// �O�p�`���m
	bool CheckHitSquareCircle(const Potision2f& sPos, const Size& sSize, const Potision2f& cPos, const float& cRadius);		// �l�p�`�Ɖ~
	bool CheckHitShapeTriangle(const std::vector<Potision2f>& sPoint, const std::vector<Vector2f>& tpoint);					// �l�p�`or�~�ƎO�p�`
protected:
	Potision2f pos_;
	Size size_;
	Vector2f speed_;
	float radius_;
	int color_;
	ShapeType shapeType_;
	std::vector<Vector2f>point_;
	bool alive_;												// true:�����Ă�
	int myNamber_;												// �����̔ԍ��ۑ��p
	std::vector<Potision2f> hitPoint_;							// ��`�p
	/// <summary>
	/// ���˃x�N�g�������߂�
	/// </summary>
	/// <param name="N">���K�����ꂽ�@���x�N�g��</param>
	virtual Vector2f Reflection(Vector2f N);
	void NewShape();
	/// <summary>
	/// ��ʂƂ̓����蔻��
	/// </summary>
	/// <returns>�X�s�[�h</returns>
	virtual Vector2f CheckHitWall(const ShapeVec& vec) = 0;
	/// <summary>
	/// �ق��̐}�`�Ƃ̓����蔻��(�F)
	/// </summary>
	/// <param name="shape"></param>

	std::vector<ShapeType> typeVec_;
private:
	void Init(void);
	static int objectNumber_;
};

